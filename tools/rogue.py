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
    p.add_argument('--qa-scene-cycles', type=int, default=0, help='Debug-only real scene lifecycle test')
    p.add_argument('--qa-match', action='store_true', help='Debug-only controlled native match lifecycle fixture')
    p.add_argument("--qa-matches", type=int, default=20)
    p.add_argument("--qa-specials", action="store_true", help="Debug-only 104-special native lifecycle fixture")
    p.add_argument("--qa-special-start", type=int, default=0)
    p.add_argument("--qa-special-count", type=int, default=104)
    p.add_argument("--qa-lifecycle", action="store_true", help="Extend special QA through damage interruption and real death/respawn")
    p.add_argument("--qa-ui", action="store_true", help="Debug-only fixed-seed interactive progression preview")
    p.add_argument("--target", choices=['all','dol','hooks','progression','specials','assets'], default='all')
    p = sub.add_parser("verify-image", help="Verify immutable NTSC-U 1.02 input")
    p.add_argument("--image", type=Path)
    p = sub.add_parser("test", help="Execute automated tests")
    p.add_argument("--suite", choices=['all','tooling','core','specials','integration','golden'], default='all')
    sub.add_parser("status", help="Show implementation evidence")
    p = sub.add_parser('package', help='Validate a clean release and verify xdelta reconstruction')
    p.add_argument('--profile', choices=['release'], default='release')
    p = sub.add_parser('run', help='Launch the verified image or build a reproducible debug fixture')
    p.add_argument('--seed', type=int)
    p.add_argument('--scene', choices=['progression','encounter','shop','rest'])
    p.add_argument('--encounter')
    p.add_argument('--special')
    p.add_argument('--recipient')
    p.add_argument('--check-passives', action='store_true', help='Native controlled passive-behavior assertions')
    p = sub.add_parser('soak', help='Run native lifecycle fixtures and save pass/failure evidence')
    p.add_argument('--scenario', choices=['scenes','matches','specials'], default='scenes')
    p.add_argument('--iterations', '--transitions', type=int)
    p.add_argument('--matches', type=int, help='Shorthand for --scenario matches --iterations N')
    p.add_argument('--seed', type=int)
    p.add_argument('--start', type=int, default=0, help='First recipient x special matrix index')
    p.add_argument('--lifecycle', action='store_true', help='Include native damage interruption and death/respawn special cases')
    p.add_argument('--timeout', type=int, default=600)
    sub.add_parser("migrate-specials", help="Inventory the prepared pinned special migration oracle")
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
            build(cfg, args.profile, args.target, args.qa_scene_cycles, args.qa_match, args.qa_ui, args.qa_matches, args.qa_specials, args.qa_special_start, args.qa_special_count, args.qa_lifecycle)
        elif args.command == 'verify-image':
            image = args.image or cfg['paths'].get('melee_iso')
            if not image:
                raise ValueError('Set MELEE_ISO_PATH or pass --image PATH')
            print(json.dumps(verify(image, ROOT), indent=2))
        elif args.command == 'test':
            folder = ROOT / 'tests' / ('core' if args.suite == 'golden' else args.suite if args.suite != 'all' else '')
            return subprocess.call([sys.executable, '-m', 'unittest', 'discover', '-s', str(folder), '-v'], cwd=ROOT)
        elif args.command == 'migrate-specials':
            from lib.migration import inventory
            inventory()
        elif args.command == 'run':
            from lib.emulator import launch
            if args.check_passives or any(getattr(args,key) is not None for key in ('seed','scene','encounter','special','recipient')):
                from lib.debug_launch import options
                from lib.build import build
                if args.check_passives:
                    if args.special or args.encounter or args.recipient not in (None,'fox') or args.scene not in (None,'encounter'):
                        raise ValueError('--check-passives requires the controlled Fox/duel fixture; only --seed may be customized')
                    fixture = options(args.seed,'encounter',recipient='fox')
                    fixture['passives'] = 1
                else:
                    fixture = options(args.seed,args.scene,args.encounter,args.special,args.recipient)
                build(cfg,'debug',qa_ui=True,debug_launch=fixture)
            launch(cfg)
        elif args.command == 'package':
            from lib.packaging import package
            package(cfg)
        elif args.command == 'soak':
            from lib.emulator import soak
            scenario = 'matches' if args.matches is not None else args.scenario
            iterations = args.matches if args.matches is not None else args.iterations
            if iterations is None: iterations = 104 if scenario == 'specials' else 100
            soak(cfg, scenario, iterations, args.timeout, args.start, args.lifecycle, args.seed)
        else:
            print((ROOT / 'IMPLEMENTATION_STATUS.md').read_text(encoding='utf-8'))
        return 0
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        print(f'ERROR: {error}', file=sys.stderr)
        return 2


if __name__ == '__main__':
    raise SystemExit(main())
