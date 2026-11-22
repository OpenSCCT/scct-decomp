// campaign_leaf_3d0df0.cpp -- a free function at VA 0x10cd0df0: when its argument is not zero it
// calls the Win32 ExitProcess with 1; it then sets the global at VA 0x112327bc to 1. The function,
// parameter and global names are invented; ExitProcess is the import's name.

extern "C" __declspec(dllimport) void __stdcall ExitProcess(unsigned int ExitCode);

extern int GUnk_112327bc;

// Unk_10cd0df0
void Unk_10cd0df0(int Value)
{
    if ( Value )
    {
        ExitProcess(1);
    }
    GUnk_112327bc = 1;
}
