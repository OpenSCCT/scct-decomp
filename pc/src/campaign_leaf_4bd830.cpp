// campaign_leaf_4bd830.cpp -- one function at file offset 0x4bd830, preferred VA 0x10dbd830.
// It converts the null-terminated wide Text into Buffer, of Capacity bytes in the default code
// page, with WideCharToMultiByte, and returns its result. The function and parameter names are
// invented; the offset and the bytes are the binary's.

extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(unsigned int CodePage,
                                                                   unsigned long Flags,
                                                                   const unsigned short* Text,
                                                                   int Length, char* Buffer,
                                                                   int Capacity,
                                                                   const char* DefaultChar,
                                                                   int* UsedDefaultChar);

// Unk_10dbd830
int Unk_10dbd830(const unsigned short* Text, char* Buffer, int Capacity)
{
    return WideCharToMultiByte(0, 0, Text, -1, Buffer, Capacity, 0, 0);
}
