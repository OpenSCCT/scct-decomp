// Work item 0038: Versus RVA 0x97e0.
// Releases a handle and a VirtualAlloc'd block owned by an unnamed class
// (UnnamedClass_97e0: no vtable label or string evidence for a real name).
typedef void *HANDLE;
typedef void *LPVOID;
typedef unsigned long DWORD;
typedef int BOOL;
typedef unsigned long SIZE_T;

extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE hObject);
extern "C" __declspec(dllimport) BOOL __stdcall VirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType);

#define MEM_RELEASE 0x8000

class UnnamedClass_97e0
{
public:
    char Pad00[0x2c];
    int Pending;          // +0x2c
    char Pad30[0x10];
    HANDLE Handle;        // +0x40
    char Pad44[0x14];
    LPVOID Buffer;        // +0x58

    bool Release();
};

bool UnnamedClass_97e0::Release()
{
    if (Handle)
        CloseHandle(Handle);
    Handle = 0;
    if (Buffer)
    {
        VirtualFree(Buffer, 0, MEM_RELEASE);
        Buffer = 0;
    }
    return Pending == 0;
}
