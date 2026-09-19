"""Pinned xdelta build and verified, retail-image-free release packaging."""
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path
from .config import ROOT
from .deps import ensure
from .hash import file_hash
from .process import run


def xdelta():
    source = ensure('xdelta') / 'xdelta3'
    output = ROOT / 'build/tools/xdelta3.exe'
    if output.exists():
        return output
    output.parent.mkdir(parents=True, exist_ok=True)
    vswhere = Path(os.environ.get('ProgramFiles(x86)', '')) / 'Microsoft Visual Studio/Installer/vswhere.exe'
    install = subprocess.check_output([str(vswhere), '-latest', '-products', '*', '-requires', 'Microsoft.VisualStudio.Component.VC.Tools.x86.x64', '-property', 'installationPath'], text=True).strip()
    if not install:
        raise ValueError('Install MSVC Build Tools to build the pinned xdelta3 release tool')
    defines = ['XD3_MAIN=1', 'XD3_DEBUG=0', 'XD3_USE_LARGEFILE64=1', 'REGRESSION_TEST=0', 'SECONDARY_DJW=1', 'SECONDARY_FGK=1', 'SECONDARY_LZMA=0', 'XD3_WIN32=1', 'EXTERNAL_COMPRESSION=0', 'SHELL_TESTS=0', 'XD3_STDIO=0', 'XD3_POSIX=0']
    defines += ['SIZEOF_SIZE_T=8', 'SIZEOF_UNSIGNED_INT=4', 'SIZEOF_UNSIGNED_LONG=4', 'SIZEOF_UNSIGNED_LONG_LONG=8']
    config = output.with_suffix('.h')
    config.write_text('#define PRINTF_ATTRIBUTE(x,y)\n#define _CRT_SECURE_NO_WARNINGS\n')
    args = ['cl', '/nologo', '/O2', '/W3', '/FI'+str(config), *('/D'+value for value in defines), str(source/'xdelta3.c'), '/Fe:'+str(output)]
    script = output.with_suffix('.cmd')
    script.write_text('@echo off\ncall "'+install+'/VC/Auxiliary/Build/vcvars64.bat" >nul\n'+subprocess.list2cmdline(args)+'\n')
    run(['cmd', '/c', script], output.parent)
    run([output, '-V'])
    return output


def package(cfg):
    if subprocess.check_output(['git', 'status', '--porcelain'], cwd=ROOT, text=True).strip():
        raise ValueError('Commit or resolve worktree changes before release validation')
    from .build import build
    from .deps import manifest as dependencies
    from .iso import verify
    for dependency in dependencies():
        ensure(dependency['name'])
    gates = {}
    for name in ['100-matches-stage-clear', 'specials-full-matrix', 'extended-ledge-grab', 'normal-controller-flow', 'passive-behavior', 'borrowed-transform', 'stock-classic', 'stock-vs']:
        path = ROOT/'docs/qa'/f'{name}.json'
        if not path.is_file() or json.loads(path.read_text()).get('status') != 'pass':
            raise ValueError('Required native release gate is missing or failed: '+name)
        gates[name] = file_hash(path)
    run([sys.executable, ROOT/'tools/rogue.py', 'test', '--suite', 'all'], ROOT)
    manifest = build(cfg, 'release')
    if subprocess.check_output(['git','status','--porcelain'],cwd=ROOT,text=True).strip():
        raise ValueError('Build changed tracked source or generated registries; review and commit before packaging')
    tool = xdelta()
    output = Path(manifest['output'])
    original = Path(cfg['paths']['melee_iso'])
    stage = ROOT/'build/release-staging'
    stage.mkdir(parents=True, exist_ok=True)
    patch = stage/'rogueMelee-v0.1.0.xdelta'
    run([tool, '-f', '-e', '-9', '-s', original, output, patch])
    reconstructed = stage/'reconstructed.iso'
    run([tool, '-f', '-d', '-s', original, patch, reconstructed])
    if file_hash(reconstructed) != manifest['output_sha256']:
        raise ValueError('Release reconstruction hash does not match the built image')
    verify(original, ROOT)  # Revalidate the immutable source after encoding/decoding.
    manifest.update(native_gate_sha256=gates, git_commit=subprocess.check_output(['git','rev-parse','HEAD'],cwd=ROOT,text=True).strip(), patch_sha256=file_hash(patch), reconstructed_sha256=file_hash(reconstructed), xdelta_sha256=file_hash(tool))
    # Explicit allowlist: never copy the staging tree or any retail data into dist.
    dist = ROOT/'dist'
    dist.mkdir(exist_ok=True)
    allowed = {patch.name,'build-manifest.json','THIRD_PARTY_NOTICES.md','README.txt'}
    unexpected = [p.name for p in dist.iterdir() if p.name not in allowed or not p.is_file()]
    if unexpected:
        raise ValueError('Unexpected release-directory contents; move them aside: '+', '.join(unexpected))
    shutil.copyfile(patch, dist/patch.name)
    (dist/'build-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    shutil.copyfile(ROOT/'THIRD_PARTY_NOTICES.md', dist/'THIRD_PARTY_NOTICES.md')
    (dist/'README.txt').write_text('rogueMelee v0.1.0\nRequires a clean NTSC-U Melee v1.02 image.\nInput MD5: 0e63d4223b01d9aba596259dc155a174\nApply with xdelta3 v3.1.0 or a compatible VCDIFF patcher:\nxdelta3 -d -s "clean.iso" "rogueMelee-v0.1.0.xdelta" "rogueMelee.iso"\nOutput SHA256: '+manifest['output_sha256']+'\nThis package contains no full game image. Aerial swapping is disabled.\n')
    print('Verified release patch: '+str(dist/patch.name))
    return manifest
