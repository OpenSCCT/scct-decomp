// campaign_leaf_0d19a0.cpp -- method at VA 0x109d19a0 taking a source and a target index: when the
// source is inside the array of 0x80-byte records at 0x94 (count at 0x98), the target is not
// negative and the method at VA 0x109d09c0 makes room for it, copies the source record over the
// target record, and when the source index is 0 stores 1.0 in the float at 0x30 of the target. The
// class, member and method names are invented; the offsets and the address are the binary's.

struct UnkType_109d19a0_Record
{
    unsigned char unk_00[0x30];
    float unk_30;
    unsigned char unk_34[0x80 - 0x34];
};

class UnkType_109d19a0
{
public:
    void Unk_109d19a0(int Source, int Target);
    int Unk_109d09c0(int Index);

private:
    unsigned char unk_00[0x94];
    UnkType_109d19a0_Record* unk_94;
    int unk_98;
};

// UnkType_109d19a0::Unk_109d19a0
void UnkType_109d19a0::Unk_109d19a0(int Source, int Target)
{
    if ( Source >= 0 && Source < unk_98 && Target >= 0 && Unk_109d09c0(Target) )
    {
        unk_94[Target] = unk_94[Source];
        if ( Source == 0 )
        {
            unk_94[Target].unk_30 = 1.0f;
        }
    }
}
