// campaign_leaf_3d1a20.cpp -- a free function at VA 0x10cd1a20 that calls the Win32 Sleep with its
// argument times 1000, converted to an integer: it sleeps for a number of seconds. The function and
// parameter names are invented; Sleep is the import's name.

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long Milliseconds);

// Unk_10cd1a20
void Unk_10cd1a20(float Seconds)
{
    Sleep((unsigned long)(Seconds * 1000.0));
}
