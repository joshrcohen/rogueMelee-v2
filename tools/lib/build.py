import json
import shutil
import subprocess
import sys
from pathlib import Path
from .config import ROOT
from .deps import ensure, ninja, rust_tool
from .hash import file_hash
from .iso import DOL_SHA1, verify
from .process import run


def bootstrap(cfg, image=None):
    image = image or cfg['paths'].get('melee_iso')
    if not image:
        raise ValueError('Set MELEE_ISO_PATH or pass --image')
    source = verify(image, ROOT)
    fst = rust_tool('gc_fst')
    upstream = ensure('melee')
    original = ROOT / 'build/original'
    original.mkdir(parents=True, exist_ok=True)
    sentinel = original / 'extraction.json'
    if not sentinel.exists():
        if (original / 'root').exists():
            raise ValueError('Incomplete build/original/root extraction; move it aside and retry')
        run([fst, 'extract', Path(image).resolve()], original)
        entries = {str(p.relative_to(original)):file_hash(p) for p in sorted((original / 'root').rglob('*')) if p.is_file()}
        sentinel.write_text(json.dumps(entries, indent=2) + '\n')
    dol = original / 'root/&&systemdata/Start.dol'
    if file_hash(dol, 'sha1') != DOL_SHA1:
        raise ValueError('Extracted original DOL changed')
    target = upstream / 'orig/GALE01/sys/main.dol'
    target.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(dol, target)
    run([sys.executable, 'configure.py', '--map', '--ninja', ninja()], upstream)
    run([ninja(), '-j', cfg['build']['jobs']], upstream)
    built = upstream / 'build/GALE01/main.dol'
    if file_hash(built, 'sha1') != DOL_SHA1:
        raise ValueError('Upstream baseline does not match retail DOL')
    output = ROOT / 'build/output/rogueMelee.iso'
    output.parent.mkdir(parents=True, exist_ok=True)
    if Path(image).resolve() == output.resolve():
        raise ValueError('Input and output images must differ')
    shutil.copyfile(image, output)
    run([fst, 'fs', output, 'insert', 'Start.dol', built])
    shutil.copyfile(upstream / 'build/GALE01/main.elf.MAP', output.parent / 'GALE01.map')
    if file_hash(Path(image), 'md5') != source['md5']:
        raise ValueError('Source image changed during build')
    result = dict(profile='baseline', source=source,
                  git_commit=subprocess.check_output(['git','rev-parse','HEAD'],cwd=ROOT,text=True).strip(),
                  dependency_lock_sha256=file_hash(ROOT / 'deps/lock.json'),
                  dol_sha1=file_hash(built,'sha1'), output_sha256=file_hash(output),
                  output=str(output), map_sha256=file_hash(output.parent / 'GALE01.map'))
    (ROOT / 'build/build-manifest.json').write_text(json.dumps(result,indent=2)+'\n')
    print(f'Baseline image: {output}')
    return result


def build(cfg, profile='debug', target='all', qa_cycles=0, qa_match=False, qa_ui=False, qa_matches=20, qa_specials=False, qa_special_start=0, qa_special_count=104, qa_lifecycle=False, debug_launch=None, aerials=True, qa_aerials=False, qa_aerial_stress=False):
    from .integration import prepare, hooks, validate
    if target not in ('all', 'dol', 'hooks', 'progression', 'specials', 'assets'):
        raise ValueError('Unknown build target: ' + target)
    if target == 'hooks':
        validate(hooks(), ensure('melee'))
        print('PASS: hook ownership, unique sites and pinned source anchors')
        return dict(profile=profile, target=target, status='pass')
    from generate_data import generate
    generate()
    from generate_ui import generate as generate_ui
    generate_ui()
    if target == 'assets':
        result = dict(profile=profile, target=target, asset=str(ROOT/'build/assets/RogueUi.dat'), asset_sha256=file_hash(ROOT/'build/assets/RogueUi.dat'))
        (ROOT/'build/assets/build-manifest.json').write_text(json.dumps(result,indent=2)+'\n')
        return result
    image = cfg['paths'].get('melee_iso')
    if not image:
        raise ValueError('Set MELEE_ISO_PATH')
    source = verify(image, ROOT)
    clean = ensure('melee')
    if qa_cycles and (profile != 'debug' or not 1 <= qa_cycles <= 10000):
        raise ValueError('Scene QA requires debug profile and 1..10000 cycles')
    if qa_match and (profile != 'debug' or qa_cycles):
        raise ValueError('Match QA requires debug profile and cannot combine with scene QA')
    if qa_ui and (profile != 'debug' or qa_match or qa_cycles):
        raise ValueError('UI QA requires an exclusive debug build')
    if qa_specials and (profile != 'debug' or qa_match or qa_cycles or qa_ui):
        raise ValueError('Special QA requires an exclusive debug build')
    if not 1 <= qa_matches <= 10000:
        raise ValueError('Match QA count must be 1..10000')
    if qa_special_start < 0 or qa_special_count < 1 or qa_special_start + qa_special_count > (3380 if qa_aerials else 2704):
        raise ValueError('Special matrix range must fit 26 recipients x 104 specials')
    if debug_launch is not None and profile != 'debug':
        raise ValueError('Developer launch overrides require a debug build')
    if qa_lifecycle and not (qa_specials or qa_aerials):
        raise ValueError('Extended lifecycle QA requires --qa-specials')
    if qa_aerials and (not aerials or qa_specials or qa_match or qa_cycles or qa_ui):
        raise ValueError('Aerial QA requires an exclusive build with aerials enabled')
    if qa_aerial_stress and (not qa_aerials or not qa_lifecycle or qa_special_start+qa_special_count>130):
        raise ValueError('Aerial stress requires extended aerial QA and a range within 130 spread cases')
    work = prepare(profile, qa_cycles, qa_match, qa_ui, qa_matches, qa_specials, qa_special_start, qa_special_count, qa_lifecycle, debug_launch, aerials, qa_aerials, qa_aerial_stress)
    run([sys.executable, 'configure.py', '--non-matching', '--map',
         '--compilers', clean / 'build/compilers',
         '--binutils', clean / 'build/binutils',
         '--dtk', clean / 'build/tools/dtk.exe',
         '--objdiff', clean / 'build/tools/objdiff-cli.exe',
         '--sjiswrap', clean / 'build/tools/sjiswrap.exe',
         '--ninja', ninja()], work)
    run([ninja(), '-j', cfg['build']['jobs']], work)
    if target == 'dol':
        result = dict(profile=profile, target=target, work=str(work),
                      dol=str(work/'build/GALE01/main.dol'),
                      dol_sha1=file_hash(work/'build/GALE01/main.dol','sha1'),
                      map=str(work/'build/GALE01/main.elf.MAP'))
        (ROOT/'build/dol-manifest.json').write_text(json.dumps(result,indent=2)+'\n')
        print('Built DOL: '+result['dol'])
        return result
    # Progression and specials are linked scene/subsystem targets. Each produces
    # a complete playable image because the native executable shares its ABI.
    output = ROOT / 'build/output/rogueMelee.iso'
    if Path(image).resolve() == output.resolve():
        raise ValueError('Input and output images must differ')
    from .image_build import assemble
    assemble(image, work / 'build/GALE01/main.dol', output)
    shutil.copyfile(work / 'build/GALE01/main.elf.MAP', output.parent / 'GALE01.map')
    if file_hash(Path(image), 'md5') != source['md5']:
        raise ValueError('Source image changed')
    result = dict(profile=profile, target=target, aerials=bool(aerials), qa_aerials=qa_aerials, qa_aerial_stress=qa_aerial_stress, qa_scene_cycles=qa_cycles, qa_match=qa_match, qa_ui=qa_ui, qa_matches=qa_matches, qa_specials=qa_specials, qa_special_start=qa_special_start, qa_special_count=qa_special_count, qa_lifecycle=qa_lifecycle, debug_launch=debug_launch, source=source, work=str(work),
                  dependency_lock_sha256=file_hash(ROOT / 'deps/lock.json'),
                  hook_manifest_sha256=file_hash(ROOT / 'integration/hook_manifest.toml'),
                  dol_sha1=file_hash(work / 'build/GALE01/main.dol','sha1'),
                  output_sha256=file_hash(output), output=str(output))
    (ROOT / 'build/build-manifest.json').write_text(json.dumps(result,indent=2)+'\n')
    print(f'Built {profile}: {output}')
    return result
