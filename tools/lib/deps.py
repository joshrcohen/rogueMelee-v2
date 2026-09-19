import json
import shutil
import subprocess
import tomllib
from .config import ROOT
from .hash import file_hash
from .process import run


def manifest():
    return tomllib.loads((ROOT / 'deps/manifest.toml').read_text(encoding='utf-8'))['dependency']


def checkout(dep):
    return ROOT / ('.cache/legacy/rogueMelee' if dep['name'] == 'legacy-specials' else '.cache/deps/' + dep['name'])


def ensure(name):
    dep = next(d for d in manifest() if d['name'] == name)
    lock = json.loads((ROOT / 'deps/lock.json').read_text())
    if lock['commits'].get(name) != dep['rev']:
        raise ValueError(f'Dependency manifest/lock mismatch: {name}')
    dest = checkout(dep)
    if not (dest / '.git').exists():
        run(['git', 'clone', '--no-checkout', dep['url'], dest])
        run(['git', 'checkout', '--detach', dep['rev']], dest)
    actual = subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=dest, text=True).strip()
    if actual != dep['rev']:
        raise ValueError(f'{name} checkout is {actual}; expected {dep["rev"]}')
    return dest


def rust_tool(name):
    dest = ensure(name)
    pinned = ROOT / 'deps' / (name + '.Cargo.lock')
    shutil.copyfile(pinned, dest / 'Cargo.lock')
    run(['cargo', 'build', '--release', '--locked'], dest)
    return dest / 'target/release' / (name + '.exe')


def ninja():
    found = shutil.which('ninja')
    if found:
        return found
    # A local configuration path is preferred to modifying global PATH.
    from .config import load
    found = load()['paths'].get('ninja')
    if found:
        return found
    raise ValueError('Ninja missing; install ninja or set paths.ninja in config/local.toml')
