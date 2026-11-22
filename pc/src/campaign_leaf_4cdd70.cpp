// campaign_leaf_4cdd70.cpp -- one function at file offset 0x4cdd70, preferred VA 0x10dcdd70. It
// compares two objects that each hold a byte pointer at 0x8 and a length at 0xc: they are equal
// when the lengths agree and the bytes do. The class, method and member names are invented; the
// offsets and the bytes are the binary's.

extern "C" int __cdecl memcmp(const void* First, const void* Second, unsigned int Count);
#pragma intrinsic(memcmp)

class UnkType_10dcdd70
{
public:
    bool Unk_10dcdd70(const UnkType_10dcdd70& Other) const;

    unsigned char unk_0[0x8];
    const unsigned char* unk_8;
    unsigned int unk_c;
};

// UnkType_10dcdd70::Unk_10dcdd70
bool UnkType_10dcdd70::Unk_10dcdd70(const UnkType_10dcdd70& Other) const
{
    if ( unk_c == Other.unk_c )
    {
        return memcmp(Other.unk_8, unk_8, unk_c) == 0;
    }
    return false;
}
