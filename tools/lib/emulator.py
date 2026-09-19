"""Isolated Dolphin launch and log-based integration evidence."""
import configparser
import json
import re
import subprocess
import time
from pathlib import Path
from .config import ROOT
from .hash import file_hash


def launch(cfg, fast=False, movie=None, manifest=None, user=None):
    executable = Path(cfg['paths'].get('dolphin', ''))
    if not executable.is_file():
        raise ValueError('Set DOLPHIN_PATH to Dolphin.exe')
    if manifest is None:
        manifest = json.loads((ROOT/'build/build-manifest.json').read_text())
    image = Path(manifest['output'])
    if file_hash(image) != manifest['output_sha256']:
        raise ValueError('Image differs from build manifest; rebuild before running')
    user = Path(user) if user is not None else ROOT/'build/dolphin-user'
    config = user/'Config'
    config.mkdir(parents=True, exist_ok=True)
    # This profile is owned by this workspace; global emulator settings are untouched.
    ini = configparser.ConfigParser()
    ini.optionxform = str
    path = config/'Dolphin.ini'
    ini.read(path)
    for section, values in {'Interface': {'ConfirmStop': 'False'},
                            'Display': {'RenderToMain': 'True'},
                            'Core': {'EnableCheats': 'False', 'EmulationSpeed': '0' if fast else '1'}}.items():
        if section not in ini: ini[section] = {}
        ini[section].update(values)
    with path.open('w') as stream: ini.write(stream)
    (config/'Logger.ini').write_text('[Options]\nWriteToFile = True\nVerbosity = 3\n[Logs]\nOSREPORT = True\n')
    command = [str(executable), '-b', '-e', str(image), '-u', str(user)]
    if movie is not None:
        if not Path(movie).is_file(): raise ValueError('Controller movie does not exist')
        command += ['-m', str(Path(movie).resolve())]
    process = subprocess.Popen(command)
    print(f'Dolphin PID {process.pid}; log {user / "Logs/dolphin.log"}', flush=True)
    return process, manifest


def verify_scene_log(log, expected):
    if re.search(r'assertion|OSPanic|UNHANDLED EXCEPTION|ERROR scene|Invalid (read|write)|Memory Empty|on line [0-9]+\.', log, re.I):
        raise ValueError('Emulator assertion or resource failure; inspect saved log')
    generations = [int(x) for x in re.findall(r'\[rogue\] scene_enter=45 generation=(\d+)', log)]
    result = re.search(r'\[rogue\] scene_qa cycles=(\d+) resources=(\d+) active=(\d+)', log)
    if not result: return False
    if tuple(map(int, result.groups())) != (expected, 0, 1):
        raise ValueError('Scene lifecycle result did not satisfy resource contract')
    if generations != list(range(1, expected + 1)):
        raise ValueError('Scene generation history incomplete or repeated')
    return '[rogue] native_scene=1 active=0' in log


def verify_match_log(log, expected=20):
    """Require actual ordered native results, entity counts and successful entries."""
    if re.search(r'assertion|OSPanic|UNHANDLED EXCEPTION|ERROR scene|Invalid (read|write)|Memory Empty|on line [0-9]+\.', log, re.I):
        raise ValueError('Emulator assertion or resource failure; inspect saved log')
    result = re.search(r'\[rogue\] match_qa_complete transitions=(\d+) failures=(\d+) phase=(\d+)', log)
    if not result: return False
    if tuple(map(int, result.groups())) != (expected, 0, 6):
        raise ValueError('Native match fixture failed or did not finish with a loss')
    transitions = [tuple(map(int, row)) for row in re.findall(
        r'\[rogue\] transition_qa index=(\d+) won=(\d+) failures=(\d+)', log)]
    if transitions != [(i, int(i < expected), 0) for i in range(1, expected + 1)]:
        raise ValueError('Missing, repeated or incorrect native match result')
    counts = re.findall(r'\[rogue\] match_qa frames=450 fighters=(\d+) expected=(\d+)', log)
    if len(counts) != expected or any(a != b for a, b in counts):
        raise ValueError('Native fighter count did not match encounter composition')
    entries = [tuple(map(int, row)) for row in re.findall(
        r'\[rogue\] special_qa id=(\d+) air=(\d+) entered=(\d+)', log)]
    if entries != [(89, air, 1) for _ in range(expected) for air in (0, 1)]:
        raise ValueError('Borrowed special ground/air entry missing or failed')
    return '[rogue] native_scene=1 active=0' in log


def verify_special_log(log, start, count):
    if re.search(r'assertion|OSPanic|UNHANDLED EXCEPTION|ERROR scene|Invalid (read|write)|Memory Empty|on line [0-9]+\.', log, re.I):
        raise ValueError('Emulator assertion or resource failure; inspect saved log')
    results = [tuple(map(int, row)) for row in re.findall(
        r'\[rogue\] special_result index=(\d+) won=(\d+) entries=(\d+) cleanups=(\d+) failures=(\d+)', log)]
    if any(row[1:] != (1,2,2,0) for row in results):
        raise ValueError('Special lifecycle result failed; inspect saved case index')
    result = re.search(r'\[rogue\] special_matrix_complete start=(\d+) count=(\d+) failures=(\d+)', log)
    if not result: return False
    if tuple(map(int, result.groups())) != (start,count,0):
        raise ValueError('Special matrix stopped before requested range completed')
    if [row[0] for row in results] != list(range(start,start+count)):
        raise ValueError('Special matrix has missing or repeated cases')
    for label, field in [('entry','entered'), ('cleanup','restored')]:
        actual = [tuple(map(int, row)) for row in re.findall(
            r'\[rogue\] special_' + label + r' index=(\d+) air=(\d+) ' + field + r'=(\d+)', log)]
        if actual != [(i, air, 1) for i in range(start,start+count) for air in (0,1)]:
            raise ValueError('Special matrix lacks successful ground/air ' + label)
    return '[rogue] native_scene=1 active=0' in log


def verify_extended_log(log, start, count):
    complete = verify_special_log(log, start, count)
    if not complete:
        return False
    interrupted = [tuple(map(int, row)) for row in re.findall(
        r'\[rogue\] special_interrupt index=(\d+) restored=(\d+)', log)]
    respawned = [tuple(map(int, row)) for row in re.findall(
        r'\[rogue\] special_respawn index=(\d+) stocks=(\d+) restored=(\d+) motion=(\d+)', log)]
    if interrupted != [(i,1) for i in range(start,start+count)]:
        raise ValueError('Missing successful native damage interruption evidence')
    if [(i,stocks,restored) for i,stocks,restored,motion in respawned] != [(i,98,1) for i in range(start,start+count)]:
        raise ValueError('Missing successful blast-zone death and respawn evidence')
    return True


def soak(cfg, scenario='scenes', iterations=100, timeout=600, start=0, lifecycle=False, seed=None):
    from .build import build
    if iterations < 1 or timeout < 1:
        raise ValueError('Iterations and timeout must be positive')
    if lifecycle and scenario != 'specials':
        raise ValueError('--lifecycle requires --scenario specials')
    if scenario == 'scenes':
        options = dict(qa_cycles=iterations)
        verify = lambda log: verify_scene_log(log, iterations)
    elif scenario == 'matches':
        options = dict(qa_match=True, qa_matches=iterations)
        verify = lambda log: verify_match_log(log, iterations)
    elif scenario == 'specials':
        options = dict(qa_specials=True, qa_special_start=start, qa_special_count=iterations, qa_lifecycle=lifecycle)
        verify = lambda log: (verify_extended_log if lifecycle else verify_special_log)(log, start, iterations)
    else:
        raise ValueError('Unknown soak scenario: ' + scenario)
    if seed is not None:
        from .debug_launch import options as launch_options
        options['debug_launch'] = launch_options(seed=seed)
    manifest = build(cfg, 'debug', 'all', **options)
    return run_soak(cfg, manifest, 'extended' if lifecycle else scenario, iterations, timeout, start, verify)


def run_soak(cfg, manifest, scenario, iterations, timeout, start=0, verifier=None, user=None):
    """Also usable to execute an already-built fixture without recompiling."""
    if verifier is None:
        verifier = (lambda log: verify_scene_log(log, iterations)) if scenario == 'scenes' else (lambda log: verify_match_log(log, iterations)) if scenario == 'matches' else (lambda log: verify_special_log(log, start, iterations))
    user = Path(user) if user is not None else ROOT/'build/dolphin-user'
    log_path = user/'Logs/dolphin.log'
    if log_path.exists(): log_path.write_text('')
    process, launched = launch(cfg, fast=True, manifest=manifest, user=user)
    if launched != manifest:
        process.terminate()
        raise ValueError('Build manifest changed before soak launch')
    started = time.monotonic()
    folder = ROOT/'build/qa'
    folder.mkdir(exist_ok=True)
    stem = f'{scenario}-{start}-{iterations}'
    result = {'scenario': scenario, 'status': 'failed', 'start': start,
              'iterations': iterations, 'build': manifest}
    log = ''
    last_progress, last_size = started, 0
    try:
        while time.monotonic() - started < timeout:
            log = log_path.read_text(errors='replace') if log_path.exists() else ''
            if len(log) != last_size:
                last_progress, last_size = time.monotonic(), len(log)
            elif time.monotonic() - last_progress > 60:
                raise ValueError('No native QA progress for 60 seconds; inspect Dolphin failure dialog and saved case index')
            if verifier(log):
                result['status'] = 'pass'
                print(f'PASS: {scenario}, {iterations} iterations and return to stock menu', flush=True)
                return result
            if process.poll() is not None:
                raise ValueError('Emulator exited before completing ' + scenario + ' QA')
            time.sleep(0.25)
        raise ValueError(scenario + ' QA timed out; no pass recorded')
    except (ValueError, OSError) as error:
        result['error'] = str(error)
        raise
    finally:
        result['seconds'] = time.monotonic() - started
        (folder/(stem+'.log')).write_text(log)
        result['log_sha256'] = file_hash(folder/(stem+'.log'))
        (folder/(stem+'.json')).write_text(json.dumps(result,indent=2)+'\n')
        if process.poll() is None:
            process.terminate()
            process.wait(timeout=10)


def scene_soak(cfg, iterations=100, timeout=180):
    return soak(cfg, 'scenes', iterations, timeout)
