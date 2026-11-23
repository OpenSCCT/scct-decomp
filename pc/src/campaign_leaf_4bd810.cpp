// campaign_leaf_4bd810.cpp -- one function at file offset 0x4bd810, preferred VA 0x10dbd810.
// It converts the null-terminated multibyte Text in the default code page into Buffer, of
// Capacity wide characters, with MultiByteToWideChar, and returns its result. The function and
// parameter names are invented; the offset and the bytes are the binary's.

extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(unsigned int CodePage,
                                                                   unsigned long Flags,
                                                                   const char* Text, int Length,
                                                                   unsigned short* Buffer,
                                                                   int Capacity);

// Unk_10dbd810
int Unk_10dbd810(const char* Text, unsigned short* Buffer, int Capacity)
{
    return MultiByteToWideChar(0, 0, Text, -1, Buffer, Capacity);
}
