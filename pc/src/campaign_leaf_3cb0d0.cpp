// campaign_leaf_3cb0d0.cpp -- a variadic free function at VA 0x10ccb0d0 that passes its destination
// buffer, the count 0x400, its format and the address of the arguments after the format to the free
// function at VA 0x10f33887, returning its result. guess: a wide-character sprintf over a
// 1024-character buffer. The function and parameter names are invented; the addresses are the
// binary's.

int Unk_10f33887(unsigned short* Dest, int Count, const unsigned short* Format, char* Args);

// Unk_10ccb0d0
int Unk_10ccb0d0(unsigned short* Dest, const unsigned short* Format, ...)
{
    return Unk_10f33887(Dest, 0x400, Format, (char*)( &Format + 1 ));
}
