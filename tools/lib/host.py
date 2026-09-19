import os
import shutil
import subprocess
from .config import ROOT
from .process import run


def compile_test(name, sources):
    output = ROOT / 'build/tests' / name
    output.parent.mkdir(parents=True, exist_ok=True)
    compiler = shutil.which('cc') or shutil.which('gcc') or shutil.which('clang')
    if compiler:
        run([compiler, '-std=c99', '-Wall', '-Wextra', '-Werror', *sources, '-o', output])
    elif os.name == 'nt':
        vswhere = os.path.join(os.environ.get('ProgramFiles(x86)', ''), 'Microsoft Visual Studio/Installer/vswhere.exe')
        install = subprocess.check_output([vswhere, '-latest', '-products', '*', '-requires', 'Microsoft.VisualStudio.Component.VC.Tools.x86.x64', '-property', 'installationPath'], text=True).strip()
        if not install:
            raise ValueError('Install a host C compiler (MSVC, GCC or Clang)')
        vcvars = install + '/VC/Auxiliary/Build/vcvars64.bat'
        output = output.with_suffix('.exe')
        args = ['cl', '/nologo', '/W4', '/WX', '/std:c11', *map(str,sources), '/Fe:' + str(output)]
        # All values are discovered paths and repo-owned source names, never user shell fragments.
        script = output.with_suffix('.cmd')
        script.write_text('@echo off\ncall "' + vcvars + '" >nul\n' + subprocess.list2cmdline(args) + '\n', encoding='utf-8')
        run(['cmd', '/c', script], output.parent)
    else:
        raise ValueError('Install a host C compiler')
    run([output])
