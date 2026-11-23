// campaign_leaf_4ab240.cpp -- one function at file offset 0x4ab240, preferred VA 0x10dab240.
// It stores the current value of the performance counter from QueryPerformanceCounter in Count.
// The function and parameter names are invented; the offset and the bytes are the binary's.

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64* Count);

// Unk_10dab240
void Unk_10dab240(__int64* Count)
{
    __int64 Now;

    QueryPerformanceCounter(&Now);
    *Count = Now;
}
