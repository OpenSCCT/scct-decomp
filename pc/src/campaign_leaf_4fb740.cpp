// campaign_leaf_4fb740.cpp -- one function at file offset 0x4fb740, preferred VA 0x10dfb740.
// It returns the current value of the performance counter from QueryPerformanceCounter. The
// function name is invented; the offset and the bytes are the binary's.

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64* Count);

// Unk_10dfb740
__int64 Unk_10dfb740()
{
    __int64 Count;

    QueryPerformanceCounter(&Count);
    return Count;
}
