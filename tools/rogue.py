"""Single command entry point for rogueMelee development."""
import argparse
import json
import shutil
import subprocess
import sys
from pathlib import Path
from lib.config import ROOT, load
from lib.iso import verify


def doctor(cfg):
    print(f"Python: {sys.version.split()[0]} ({sys.executable})")
    for name in ("git", "ninja", "powerpc-eabi-gcc", "gc_fst", "hgecko", "cdat"):
        print(f"{name}: {shutil.which(name) or 'not on PATH'}")
    print(f"ISO: {cfg['paths'].get('melee_iso', 'set MELEE_ISO_PATH')}")
    dolphin = cfg['paths'].get('dolphin')
    print(f"Dolphin: {dolphin if dolphin and Path(dolphin).is_file() else 'not configured'}")
    probe = ROOT / 'build/.write-probe'
    probe.parent.mkdir(exist_ok=True)
    probe.write_text('writable', encoding='utf-8')
    probe.unlink()
    if not shutil.which('git'):
        raise ValueError('Install Git and add it to PATH')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    sub.add_parser("doctor", help="Inspect local build environment")
    p = sub.add_parser("bootstrap", help="Build exact pinned retail baseline and separate ISO")
    p.add_argument("--image", type=Path)
    p = sub.add_parser("build", help="Compile the source overlay and assemble a separate ISO")
    p.add_argument("--profile", choices=['debug','release'], default='debug')
    p.add_argument("--target", choices=['all','dol','hooks','progression','specials','assets'], default='all')
    p = sub.add_parser("verify-image", help="Verify immutable NTSC-U 1.02 input")
    p.add_argument("--image", type=Path)
    p = sub.add_parser("test", help="Execute automated tests")
    p.add_argument("--suite", choices=['all','tooling','core','specials','integration','golden'], default='all')
    sub.add_parser("status", help="Show implementation evidence")
    args = parser.parse_args()
    try:
        cfg = load()
        if args.command == 'doctor':
            doctor(cfg)
        elif args.command == 'bootstrap':
            from lib.build import bootstrap
            bootstrap(cfg, args.image)
        elif args.command == 'build':
            from lib.build import build
            build(cfg, args.profile, args.target)
        elif args.command == 'verify-image':
            image = args.image or cfg['paths'].get('melee_iso')
            if not image:
                raise ValueError('Set MELEE_ISO_PATH or pass --image PATH')
            print(json.dumps(verify(image, ROOT), indent=2))
        elif args.command == 'test':
            folder = ROOT / 'tests' / (args.suite if args.suite != 'all' else '')
            return subprocess.call([sys.executable, '-m', 'unittest', 'discover', '-s', str(folder), '-v'], cwd=ROOT)
        else:
            print((ROOT / 'IMPLEMENTATION_STATUS.md').read_text(encoding='utf-8'))
        return 0
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        print(f'ERROR: {error}', file=sys.stderr)
        return 2


if __name__ == '__main__':
    raise SystemExit(main())
