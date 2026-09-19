"""Isolated Dolphin launch and log-based integration evidence."""
import configparser
import json
import re
import subprocess
import time
from pathlib import Path
from .config import ROOT
from .hash import file_hash


def launch(cfg):
    executable = Path(cfg['paths'].get('dolphin', ''))
    if not executable.is_file():
        raise ValueError('Set DOLPHIN_PATH to Dolphin.exe')
    manifest = json.loads((ROOT/'build/build-manifest.json').read_text())
    image = Path(manifest['output'])
    if file_hash(image) != manifest['output_sha256']:
        raise ValueError('Image differs from build manifest; rebuild before running')
    user = ROOT/'build/dolphin-user'
    config = user/'Config'
    config.mkdir(parents=True, exist_ok=True)
    # This profile is owned by this workspace; global emulator settings are untouched.
    ini = configparser.ConfigParser()
    ini.optionxform = str
    path = config/'Dolphin.ini'
    ini.read(path)
    for section, values in {'Interface': {'ConfirmStop': 'False'},
                            'Display': {'RenderToMain': 'True'},
                            'Core': {'EnableCheats': 'False'}}.items():
        if section not in ini: ini[section] = {}
        ini[section].update(values)
    with path.open('w') as stream: ini.write(stream)
    (config/'Logger.ini').write_text('[Options]\nWriteToFile = True\nVerbosity = 3\n[Logs]\nOSREPORT = True\n')
    process = subprocess.Popen([str(executable), '-b', '-e', str(image), '-u', str(user)])
    print(f'Dolphin PID {process.pid}; log {user / "Logs/dolphin.log"}', flush=True)
    return process, manifest


def verify_scene_log(log, expected):
    if re.search(r'assertion|OSPanic|ERROR scene|Invalid (read|write)', log, re.I):
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
    if re.search(r'assertion|OSPanic|ERROR scene|Invalid (read|write)', log, re.I):
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


def scene_soak(cfg, iterations=100, timeout=180):
    from .build import build
    manifest = build(cfg, 'debug', 'all', iterations)
    log_path = ROOT/'build/dolphin-user/Logs/dolphin.log'
    if log_path.exists(): log_path.write_text('')
    process, manifest = launch(cfg)
    started = time.monotonic()
    try:
        while time.monotonic() - started < timeout:
            log = log_path.read_text(errors='replace') if log_path.exists() else ''
            if verify_scene_log(log, iterations):
                folder = ROOT/'build/qa'
                folder.mkdir(exist_ok=True)
                (folder/'scene-lifetimes.log').write_text(log)
                result = {'scenario': 'native-scene-lifetimes', 'status': 'pass',
                          'cycles': iterations, 'seconds': time.monotonic() - started,
                          'build': manifest, 'log_sha256': file_hash(folder/'scene-lifetimes.log')}
                (folder/'scene-lifetimes.json').write_text(json.dumps(result, indent=2)+'\n')
                print(f'PASS: {iterations} native scene lifetimes and return to stock menu', flush=True)
                return result
            if process.poll() is not None:
                raise ValueError('Emulator exited before completing scene QA')
            time.sleep(0.25)
        raise ValueError('Scene QA timed out; no pass recorded')
    finally:
        if process.poll() is None:
            process.terminate()
            process.wait(timeout=10)
