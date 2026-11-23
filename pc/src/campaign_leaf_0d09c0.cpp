// campaign_leaf_0d09c0.cpp -- method at VA 0x109d09c0 taking an index: returns 0 unless the index
// is in 0..256; otherwise grows the array of 0x80-byte records at 0x94 (count at 0x98) one zeroed
// record at a time (method at VA 0x10ccb3c0 with the element size) until the index is inside it,
// and returns 1. The class, member and method names are invented; the offsets and the address are
// the binary's.

extern "C" void* __cdecl memset(void* Dest, int Value, unsigned int Count);
#pragma intrinsic(memset)

struct UnkType_109d09c0_Record
{
    unsigned char unk_00[0x80];
};

class UnkType_109d09c0_Array
{
public:
    void Unk_10ccb3c0(int ElementSize);

    void AddZeroed()
    {
        int Index = unk_04;
        unk_04 += 1;
        Unk_10ccb3c0(sizeof(UnkType_109d09c0_Record));
        memset(&unk_00[Index], 0, sizeof(UnkType_109d09c0_Record));
    }

    UnkType_109d09c0_Record* unk_00;
    int unk_04;
};

class UnkType_109d09c0
{
public:
    int Unk_109d09c0(int Index);

private:
    unsigned char unk_00[0x94];
    UnkType_109d09c0_Array unk_94;
};

// UnkType_109d09c0::Unk_109d09c0
int UnkType_109d09c0::Unk_109d09c0(int Index)
{
    if ( Index > 256 || Index < 0 )
    {
        return 0;
    }
    while ( unk_94.unk_04 <= Index )
    {
        unk_94.AddZeroed();
    }
    return 1;
}
