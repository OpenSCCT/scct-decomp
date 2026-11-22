// campaign_leaf_4ffc00.cpp -- one function at file offset 0x4ffc00, preferred VA 0x10dffc00. It
// compares two byte strings through the compiler's inline strcmp and returns -1, 0 or 1. It has
// no this pointer. The function and parameter names are invented; the bytes are the binary's.

extern "C" int __cdecl strcmp(const char* First, const char* Second);
#pragma intrinsic(strcmp)

// Unk_10dffc00
int Unk_10dffc00(const char* First, const char* Second)
{
    return strcmp(First, Second);
}
