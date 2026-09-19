import hashlib
import json
import re
import shutil
import subprocess
import tomllib
from .config import ROOT
from .deps import ensure
from .process import run


def hooks():
    return tomllib.loads((ROOT / 'integration/hook_manifest.toml').read_text(encoding='utf-8'))['hook']


def validate(entries, upstream):
    ids, sites = set(), set()
    for h in entries:
        if h['id'] in ids or (h['file'], h['anchor']) in sites:
            raise ValueError('Duplicate hook id or site: ' + h['id'])
        ids.add(h['id']); sites.add((h['file'], h['anchor']))
        source = (upstream / h['file']).read_text(encoding='utf-8')
        if source.count(h['anchor']) != 1:
            raise ValueError('Expected unique original source at hook ' + h['id'])
        if not h.get('abi') or not h.get('owner'):
            raise ValueError('Missing hook ownership/ABI')


def prepare(profile, qa_cycles=0, qa_match=False, qa_ui=False, qa_matches=20, qa_specials=False, qa_special_start=0, qa_special_count=104, qa_lifecycle=False, debug_launch=None):
    clean = ensure('melee')
    entries = hooks()
    validate(entries, clean)
    digest = hashlib.sha256((profile + str(qa_cycles) + str(qa_match) + str(qa_ui) + str(qa_matches) + str(qa_specials) + str(qa_special_start) + str(qa_special_count) + str(qa_lifecycle)).encode())
    digest.update(json.dumps(debug_launch,sort_keys=True).encode())
    for path in sorted((ROOT/'integration').rglob('*')) + sorted((ROOT / 'src').rglob('*')) + sorted((ROOT/'tools/lib').glob('*.py')):
        if path.is_file():
            digest.update(path.relative_to(ROOT).as_posix().encode())
            digest.update(path.read_bytes())
    work = ROOT / 'build/work' / digest.hexdigest()[:16]
    if not work.exists():
        run(['git', 'worktree', 'add', '--detach', work, 'HEAD'], clean)
    for name in {h['file'] for h in entries}:
        shutil.copyfile(clean/name,work/name)
    from .special_adapters import apply
    apply(clean, work)
    from .native_mode import apply as register_mode
    register_mode(clean, work)
    fixes = tomllib.loads((ROOT/'integration/platform_fixes.toml').read_text(encoding='utf-8'))['fix']
    adapted_paths = json.loads((ROOT/'integration/special_adapters.json').read_text(encoding='utf-8'))['files']
    for name in {fix['file'] for fix in fixes} - adapted_paths.keys():
        shutil.copyfile(clean/name, work/name)
    for fix in fixes:
        path = work/fix['file']
        source = path.read_text(encoding='utf-8')
        if source.count(fix['anchor']) != fix.get('occurrences', 1):
            raise ValueError('Platform anchor drift: ' + fix['id'])
        path.write_text(source.replace(fix['anchor'], fix['replacement']), encoding='utf-8')
    for name in {fix['file'] for fix in fixes if fix.get('fighter_api')}:
        path = work/name
        path.write_text('#include <melee/rogue/platform/melee/melee_fighter.h>\n' + path.read_text(encoding='utf-8'), encoding='utf-8')
    for name in {h['file'] for h in entries}:
        p = work / name
        # Earlier stages reset their inputs; preserve any named adapters/fixes
        # on the same file while applying each hook exactly once.
        source = p.read_text(encoding='utf-8')
        for same in entries:
            if same['file'] == name:
                if source.count(same['anchor']) != 1:
                    raise ValueError('Hook conflicts with a platform adapter: '+same['id'])
                source = source.replace(same['anchor'], same['replacement'], 1)
        source = '#include <melee/rogue/platform/melee/rogue_hooks.h>\n' + source
        p.write_text(source, encoding='utf-8')
    shutil.copytree(ROOT / 'src', work / 'src/melee/rogue', dirs_exist_ok=True)
    # MWCC's -cwd source resolves nested relative includes from the translation
    # unit. Normalize our owned headers for the generated target tree only.
    for owned in (ROOT / 'src').rglob('*'):
        if owned.suffix not in ('.c', '.h'):
            continue
        def normalize(match):
            target = (owned.parent / match.group(1)).resolve()
            if target.is_file() and target.is_relative_to(ROOT / 'src'):
                return '#include <melee/rogue/' + target.relative_to(ROOT / 'src').as_posix() + '>'
            return match.group(0)
        text = re.sub(r'#include "([^"]+)"', normalize, owned.read_text(encoding='utf-8'))
        (work / 'src/melee/rogue' / owned.relative_to(ROOT / 'src')).write_text(text)
    from .debug_launch import header
    (work/'src/melee/rogue/platform/melee/debug_launch.h').write_text(header(debug_launch))
    (work/'src/melee/rogue/build_id.h').write_text('#define ROGUE_BUILD_ID "'+work.name+'"\n')
    source = (clean / 'configure.py').read_text(encoding='utf-8')
    objects = ',\n'.join('            Object(Equivalent, "melee/rogue/' + p.relative_to(ROOT / 'src').as_posix() + '")' for p in sorted((ROOT / 'src').rglob('*.c')))
    source = source.replace('config.libs = [', 'config.libs = [\n    MeleeLib("rogueMelee", [\n' + objects + '\n    ]),', 1)
    source = source.replace('config.libs = [', 'cflags_base.append("-DROGUE_DEBUG=' + ('1' if profile == 'debug' else '0') + '")\nconfig.libs = [', 1)
    source = source.replace('config.libs = [', 'cflags_base.append("-DROGUE_QA_CYCLES=' + str(qa_cycles) + '")\nconfig.libs = [', 1)
    source = source.replace('config.libs = [', 'cflags_base.append("-DROGUE_QA_MODE=' + str(4 if qa_specials else 3 if qa_ui else 2 if qa_match else 1 if qa_cycles else 0) + '")\nconfig.libs = [', 1)
    source = source.replace('config.libs = [', 'cflags_base.append("-DROGUE_QA_MATCHES=' + str(qa_matches) + '")\nconfig.libs = [', 1)
    source = source.replace('config.libs = [', 'cflags_base.append("-DROGUE_QA_LIFECYCLE=' + str(int(qa_lifecycle)) + '")\nconfig.libs = [', 1)
    for key, value in [('START', qa_special_start), ('COUNT', qa_special_count)]:
        source = source.replace('config.libs = [', 'cflags_base.append("-DROGUE_QA_SPECIAL_' + key + '=' + str(value) + '")\nconfig.libs = [', 1)
    source = source.replace('Object(Debug, "Runtime/eabi_save_restore.s")',
                            'Object(Equivalent, "Runtime/eabi_save_restore.s")')
    adapted = json.loads((ROOT/'integration/special_adapters.json').read_text(encoding='utf-8'))['files']
    units = [p.removeprefix('src/') for p in adapted]
    setup = '\nrogue_adapted_units = ' + repr(units) + '\n'
    setup += '''for library in config.libs:
    for obj in library["objects"]:
        if obj.name.startswith("melee/rogue/") or obj.name in rogue_adapted_units:
            obj.completed = True
            obj.options["mw_version"] = "Wii/1.7"
            obj.options["extra_cflags"].append("-lang c99")

'''
    source = source.replace('if args.mode == "configure":', setup + 'if args.mode == "configure":', 1)
    (work / 'configure.py').write_text(source,encoding='utf-8')
    target = work / 'orig/GALE01/sys/main.dol'
    target.parent.mkdir(parents=True,exist_ok=True)
    shutil.copyfile(clean / 'orig/GALE01/sys/main.dol', target)
    return work
