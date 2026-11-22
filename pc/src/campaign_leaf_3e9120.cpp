// campaign_leaf_3e9120.cpp -- one function at file offset 0x3e9120, preferred VA 0x10ce9120. It
// copies an element whose byte size is the halfword at 0x34 from Source to Dest, a one-byte
// element by a single store. Its third parameter is unused. The class, method, member and
// parameter names are invented; the offsets and the bytes are the binary's.

extern "C" void* __cdecl memcpy(void* Dest, const void* Source, unsigned int Count);
#pragma intrinsic(memcpy)

class UnkType_10ce9120
{
public:
    void Unk_10ce9120(void* Dest, const void* Source, int) const;

    unsigned char unk_0[0x34];
    unsigned short unk_34;
};

// UnkType_10ce9120::Unk_10ce9120
void UnkType_10ce9120::Unk_10ce9120(void* Dest, const void* Source, int) const
{
    if ( unk_34 == 1 )
    {
        *(unsigned char*)Dest = *(const unsigned char*)Source;
    }
    else
    {
        memcpy(Dest, Source, unk_34);
    }
}
