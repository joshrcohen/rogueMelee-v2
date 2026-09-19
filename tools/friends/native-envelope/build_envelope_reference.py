#!/usr/bin/env python3
"""Build the Windows x64 launcher envelope using Clang/LLD (no Windows SDK).
The embedded WinForms app is prepared with Windows' .NET Framework csc on first run.
The developer Build-Launcher.ps1 instead emits a conventional precompiled .NET EXE.
"""
from pathlib import Path
import hashlib, struct, subprocess
from PIL import Image, ImageDraw, ImageFont
ROOT=Path(__file__).resolve().parent
SRC=ROOT.parent; BUILD=ROOT/'.build'; BUILD.mkdir(exist_ok=True)
cs=(SRC/'Launcher.cs').read_text().replace('Icon = Icon.ExtractAssociatedIcon','Icon = System.Drawing.Icon.ExtractAssociatedIcon')
(SRC/'Launcher.cs').write_text(cs)
icon=Image.new('RGBA',(256,256),(20,29,48,255)); d=ImageDraw.Draw(icon)
d.rounded_rectangle((10,10,246,246),radius=45,outline=(242,197,57),width=12)
font=ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf',142)
d.text((128,110),'R',font=font,anchor='mm',fill=(242,197,57))
font2=ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf',35)
d.text((128,206),'V2',font=font2,anchor='mm',fill=(255,255,255))
icon.save(SRC/'launcher.ico',sizes=[(16,16),(24,24),(32,32),(48,48),(64,64),(128,128),(256,256)])
blobs={ 'cs':(SRC/'Launcher.cs').read_bytes(), 'icon':(SRC/'launcher.ico').read_bytes(), 'manifest':(SRC/'app.manifest').read_bytes(), 'config':(ROOT/'launcher.config').read_bytes() }
digest=hashlib.sha256(b''.join(blobs.values())).hexdigest()[:16]
with (BUILD/'payload.h').open('w') as f:
 f.write('#define PAYLOAD_FOLDER L"\\\\1.0.0-'+digest+'"\n')
 for name,data in blobs.items():
  f.write('static const unsigned char payload_'+name+'[] = {\n')
  for start in range(0,len(data),24): f.write(','.join(str(x) for x in data[start:start+24])+',\n')
  f.write('};\n')
# Minimal import libraries. Every runtime import comes from Windows system DLLs.
exports={
 'kernel32': ['GetEnvironmentVariableW','GetWindowsDirectoryW','GetModuleFileNameW','GetCommandLineW','CreateDirectoryW','CreateFileW','WriteFile','FlushFileBuffers','CloseHandle','GetFileAttributesW','CreateProcessW','WaitForSingleObject','GetExitCodeProcess','CreateMutexW','GetLastError','FormatMessageW','ExitProcess'],
 'user32':['MessageBoxW'] }
for dll,names in exports.items():
 path=BUILD/(dll+'.def'); path.write_text('LIBRARY '+dll+'.dll\nEXPORTS\n'+'\n'.join(names)+'\n')
 subprocess.run(['lld-link','/lib','/machine:x64','/def:'+str(path),'/out:'+str(BUILD/(dll+'.lib'))],check=True)
def resource(kind, ident, data):
 header=struct.pack('<IIHHHHIHHII',len(data),32,0xffff,kind,0xffff,ident,0,0x30,0x409,0,0)
 return header+data+b'\0'*((-len(data))%4)
res=resource(0,0,b'')+resource(24,1,blobs['manifest'])
ico=blobs['icon']; reserved,kind,n=struct.unpack_from('<HHH',ico)
group=struct.pack('<HHH',0,1,n)
for i in range(n):
 w,h,cc,r,planes,bits,size,off=struct.unpack_from('<BBBBHHII',ico,6+16*i)
 res+=resource(3,i+1,ico[off:off+size])
 group+=struct.pack('<BBBBHHIH',w,h,cc,r,planes,bits,size,i+1)
res+=resource(14,1,group); (BUILD/'launcher.res').write_bytes(res)
subprocess.run(['clang','--target=x86_64-pc-windows-msvc','-std=c11','-Os','-ffreestanding','-fno-builtin','-fno-stack-protector','-Wall','-Wextra','-Werror','-I'+str(BUILD),'-c',str(ROOT/'bootstrap.c'),'-o',str(BUILD/'bootstrap.obj')],check=True)
subprocess.run(['lld-link','/subsystem:windows,6.02','/entry:mainCRTStartup','/nodefaultlib','/machine:x64','/dynamicbase','/nxcompat','/highentropyva','/out:'+str(ROOT/'RogueMelee-v2.exe'),str(BUILD/'bootstrap.obj'),str(BUILD/'kernel32.lib'),str(BUILD/'user32.lib'),str(BUILD/'launcher.res')],check=True)
print('Built',ROOT/'RogueMelee-v2.exe','embedded app:',digest)
