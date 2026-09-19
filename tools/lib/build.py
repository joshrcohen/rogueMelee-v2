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


def build(cfg, profile='debug', target='all'):
    from .integration import prepare
    from generate_data import generate
    generate()
    image = cfg['paths'].get('melee_iso')
    if not image:
        raise ValueError('Set MELEE_ISO_PATH')
    source = verify(image, ROOT)
    clean = ensure('melee')
    work = prepare(profile)
    run([sys.executable, 'configure.py', '--non-matching', '--map',
         '--compilers', clean / 'build/compilers',
         '--binutils', clean / 'build/binutils',
         '--dtk', clean / 'build/tools/dtk.exe',
         '--objdiff', clean / 'build/tools/objdiff-cli.exe',
         '--sjiswrap', clean / 'build/tools/sjiswrap.exe',
         '--ninja', ninja()], work)
    run([ninja(), '-j', cfg['build']['jobs']], work)
    output = ROOT / 'build/output/rogueMelee.iso'
    if Path(image).resolve() == output.resolve():
        raise ValueError('Input and output images must differ')
    shutil.copyfile(image, output)
    fst = ROOT / '.cache/deps/gc_fst/target/release/gc_fst.exe'
    run([fst, 'fs', output, 'insert', 'Start.dol', work / 'build/GALE01/main.dol'])
    shutil.copyfile(work / 'build/GALE01/main.elf.MAP', output.parent / 'GALE01.map')
    if file_hash(Path(image), 'md5') != source['md5']:
        raise ValueError('Source image changed')
    result = dict(profile=profile, target=target, source=source, work=str(work),
                  dependency_lock_sha256=file_hash(ROOT / 'deps/lock.json'),
                  hook_manifest_sha256=file_hash(ROOT / 'integration/hook_manifest.toml'),
                  dol_sha1=file_hash(work / 'build/GALE01/main.dol','sha1'),
                  output_sha256=file_hash(output), output=str(output))
    (ROOT / 'build/build-manifest.json').write_text(json.dumps(result,indent=2)+'\n')
    print(f'Built {profile}: {output}')
    return result
