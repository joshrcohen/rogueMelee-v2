/* MIT. A small native Windows x64 launcher. No PowerShell, admin rights, PATH
 * lookup, startup task, or downloaded source is used. On first launch, it uses
 * Windows' .NET Framework compiler to prepare the embedded C# UI locally.
 * Later launches reuse that versioned UI. All game downloads occur in the UI.
 */
typedef unsigned short WCHAR;
typedef unsigned int DWORD;
typedef int BOOL;
typedef unsigned long long SIZE_T;
typedef void* HANDLE;
typedef void* LPVOID;
typedef const WCHAR* LPCWSTR;
#define DLL __declspec(dllimport)
#define WINAPI __stdcall
#define NULL ((void*)0)
#define INVALID_HANDLE_VALUE ((HANDLE)(long long)-1)
typedef struct { DWORD nLength; void* lpSecurityDescriptor; BOOL bInheritHandle; } SECURITY_ATTRIBUTES;
typedef struct { DWORD cb; WCHAR* reserved; WCHAR* desktop; WCHAR* title; DWORD x,y,xs,ys,xc,yc,fill,flags; unsigned short show,reserved2; unsigned char* reserved3; HANDLE input,output,error; } STARTUPINFOW;
typedef struct { HANDLE process, thread; DWORD pid, tid; } PROCESS_INFORMATION;
_Static_assert(sizeof(DWORD)==4, "DWORD ABI");
_Static_assert(sizeof(STARTUPINFOW)==104, "STARTUPINFOW ABI");
_Static_assert(sizeof(PROCESS_INFORMATION)==24, "PROCESS_INFORMATION ABI");
_Static_assert(sizeof(SECURITY_ATTRIBUTES)==24, "SECURITY_ATTRIBUTES ABI");
DLL DWORD WINAPI GetEnvironmentVariableW(LPCWSTR,WCHAR*,DWORD);
DLL DWORD WINAPI GetWindowsDirectoryW(WCHAR*,DWORD);
DLL DWORD WINAPI GetModuleFileNameW(HANDLE,WCHAR*,DWORD);
DLL WCHAR* WINAPI GetCommandLineW(void);
DLL BOOL WINAPI CreateDirectoryW(LPCWSTR,SECURITY_ATTRIBUTES*);
DLL HANDLE WINAPI CreateFileW(LPCWSTR,DWORD,DWORD,SECURITY_ATTRIBUTES*,DWORD,DWORD,HANDLE);
DLL BOOL WINAPI WriteFile(HANDLE,const void*,DWORD,DWORD*,void*);
DLL BOOL WINAPI FlushFileBuffers(HANDLE);
DLL BOOL WINAPI CloseHandle(HANDLE);
DLL DWORD WINAPI GetFileAttributesW(LPCWSTR);
DLL BOOL WINAPI CreateProcessW(LPCWSTR,WCHAR*,SECURITY_ATTRIBUTES*,SECURITY_ATTRIBUTES*,BOOL,DWORD,LPVOID,LPCWSTR,STARTUPINFOW*,PROCESS_INFORMATION*);
DLL DWORD WINAPI WaitForSingleObject(HANDLE,DWORD);
DLL BOOL WINAPI GetExitCodeProcess(HANDLE,DWORD*);
DLL HANDLE WINAPI CreateMutexW(SECURITY_ATTRIBUTES*,BOOL,LPCWSTR);
DLL DWORD WINAPI GetLastError(void);
DLL DWORD WINAPI FormatMessageW(DWORD,const void*,DWORD,DWORD,WCHAR*,DWORD,void*);
DLL void WINAPI ExitProcess(DWORD);
DLL int WINAPI MessageBoxW(HANDLE,LPCWSTR,LPCWSTR,unsigned int);

#include "payload.h"
static WCHAR base[32768], dir[32768], exe[32768], cs[32768], compiler[32768], cmd[32768], origin[32768], logfile[32768], iconfile[32768], manifestfile[32768], tmp[32768], error[32768];
static STARTUPINFOW si;
static PROCESS_INFORMATION pi;
static SECURITY_ATTRIBUTES sa;
static void copy(WCHAR* out, const WCHAR* in) { while ((*out++ = *in++)) {} }
static void add(WCHAR* out, const WCHAR* in) { while (*out) ++out; copy(out,in); }
static void quote(WCHAR* out,const WCHAR* in) { add(out,(LPCWSTR)L"\""); add(out,in); add(out,(LPCWSTR)L"\""); }
static int exists(const WCHAR* path) { DWORD a=GetFileAttributesW(path); return a != 0xFFFFFFFF && !(a & 16); }
static void die(const WCHAR* message) {
    DWORD code=GetLastError(); copy(error,message); add(error,(LPCWSTR)L"\r\n\r\n");
    if (code) { FormatMessageW(0x1000|0x200,NULL,code,0,tmp,4096,NULL); add(error,tmp); }
    if (logfile[0]) { add(error,(LPCWSTR)L"\r\nPreparation log:\r\n"); add(error,logfile); }
    MessageBoxW(NULL,error,(LPCWSTR)L"RogueMelee v2 launcher",0x10); ExitProcess(1);
}
static void write(const WCHAR* path,const unsigned char* data,DWORD length) {
    HANDLE file=CreateFileW(path,0x40000000,1,NULL,2,0x80,NULL); DWORD done=0;
    if (file==INVALID_HANDLE_VALUE) die((LPCWSTR)L"Cannot create the launcher files in your local application folder.");
    if (!WriteFile(file,data,length,&done,NULL) || done!=length) { CloseHandle(file); die((LPCWSTR)L"Cannot write the launcher files."); }
    FlushFileBuffers(file); CloseHandle(file);
}
static const WCHAR* tail(void) {
    const WCHAR* p=GetCommandLineW(); while (*p==' ' || *p=='\t') ++p;
    if (*p=='"') { ++p; while (*p && *p!='"') ++p; if (*p) ++p; } else while (*p && *p!=' ' && *p!='\t') ++p;
    while (*p==' ' || *p=='\t') ++p; return p;
}
void mainCRTStartup(void) {
    DWORD n=GetEnvironmentVariableW((LPCWSTR)L"LOCALAPPDATA",base,32000);
    if (!n || n>=1024) die((LPCWSTR)L"Windows did not provide a valid LOCALAPPDATA directory.");
    add(base,(LPCWSTR)L"\\RogueMelee-v2"); CreateDirectoryW(base,NULL);
    copy(dir,base); add(dir,(LPCWSTR)L"\\Launcher"); CreateDirectoryW(dir,NULL);
    add(dir,(LPCWSTR)PAYLOAD_FOLDER); CreateDirectoryW(dir,NULL);
    copy(exe,dir); add(exe,(LPCWSTR)L"\\RogueMelee.UI.exe");
    copy(cs,dir); add(cs,(LPCWSTR)L"\\Launcher.cs"); copy(logfile,dir); add(logfile,(LPCWSTR)L"\\prepare.log");
    copy(iconfile,dir); add(iconfile,(LPCWSTR)L"\\launcher.ico"); copy(manifestfile,dir); add(manifestfile,(LPCWSTR)L"\\app.manifest");
    HANDLE lock=CreateMutexW(NULL,1,(LPCWSTR)L"Local\\RogueMelee-v2-Prepare"); if (!lock) die((LPCWSTR)L"Cannot create the launcher preparation lock.");
    if (GetLastError()==183) { MessageBoxW(NULL,(LPCWSTR)L"RogueMelee v2 is already starting. Please wait for its window.",(LPCWSTR)L"RogueMelee v2",0x40); ExitProcess(0); }
    if (!exists(exe)) {
        write(cs,payload_cs,(DWORD)sizeof(payload_cs)); write(iconfile,payload_icon,(DWORD)sizeof(payload_icon)); write(manifestfile,payload_manifest,(DWORD)sizeof(payload_manifest));
        n=GetWindowsDirectoryW(compiler,31000); if (!n || n>=1024) die((LPCWSTR)L"Cannot find Windows.");
        add(compiler,(LPCWSTR)L"\\Microsoft.NET\\Framework64\\v4.0.30319\\csc.exe");
        if (!exists(compiler)) { n=GetWindowsDirectoryW(compiler,31000); add(compiler,(LPCWSTR)L"\\Microsoft.NET\\Framework\\v4.0.30319\\csc.exe"); }
        if (!exists(compiler)) die((LPCWSTR)L"This launcher needs the Windows .NET Framework 4.x components. Use Windows 10/11 with .NET Framework 4.8 enabled. Do not download compilers from unofficial sites.");
        quote(cmd,compiler); add(cmd,(LPCWSTR)L" /nologo /target:winexe /platform:x64 /optimize+ /r:System.dll /r:System.Core.dll /r:System.Windows.Forms.dll /r:System.Drawing.dll /r:System.Web.Extensions.dll /r:System.IO.Compression.dll /r:System.IO.Compression.FileSystem.dll /out:"); quote(cmd,exe); add(cmd,(LPCWSTR)L" /win32icon:"); quote(cmd,iconfile); add(cmd,(LPCWSTR)L" /win32manifest:"); quote(cmd,manifestfile); add(cmd,(LPCWSTR)L" "); quote(cmd,cs);
        sa.nLength=sizeof(sa); sa.bInheritHandle=1;
        HANDLE log=CreateFileW(logfile,0x40000000,1,&sa,2,0x80,NULL);
        HANDLE input=CreateFileW((LPCWSTR)L"NUL",0x80000000,3,&sa,3,0x80,NULL);
        if (log==INVALID_HANDLE_VALUE || input==INVALID_HANDLE_VALUE) die((LPCWSTR)L"Cannot open the launcher preparation log.");
        si.cb=sizeof(si); si.flags=0x100|1; si.show=0; si.input=input; si.output=log; si.error=log;
        if (!CreateProcessW(compiler,cmd,NULL,NULL,1,0x08000000,NULL,dir,&si,&pi)) die((LPCWSTR)L"Windows could not prepare the embedded launcher interface.");
        DWORD result=WaitForSingleObject(pi.process,120000); DWORD exitcode=1; GetExitCodeProcess(pi.process,&exitcode);
        CloseHandle(pi.thread); CloseHandle(pi.process); CloseHandle(log); CloseHandle(input);
        if (result!=0 || exitcode!=0 || !exists(exe)) die((LPCWSTR)L"The embedded launcher interface could not be prepared. The preparation log contains the exact error. No game files were modified.");
        copy(tmp,exe); add(tmp,(LPCWSTR)L".config"); write(tmp,payload_config,(DWORD)sizeof(payload_config));
    }
    n=GetModuleFileNameW(NULL,origin,32000); if (!n || n>=12000) die((LPCWSTR)L"The launcher path is too long.");
    cmd[0]=0; quote(cmd,exe); const WCHAR* arguments=tail();
    unsigned int argslen=0; while(arguments[argslen]) ++argslen; if(argslen>4000) die((LPCWSTR)L"Too many command-line arguments.");
    if (*arguments) { add(cmd,(LPCWSTR)L" "); add(cmd,arguments); }
    add(cmd,(LPCWSTR)L" --launcher "); quote(cmd,origin);
    si.flags=0; si.show=1; si.input=NULL; si.output=NULL; si.error=NULL; si.cb=sizeof(si);
    if (!CreateProcessW(exe,cmd,NULL,NULL,0,0,NULL,base,&si,&pi)) die((LPCWSTR)L"Windows could not start the launcher interface.");
    CloseHandle(pi.thread); CloseHandle(pi.process); CloseHandle(lock); ExitProcess(0);
}
