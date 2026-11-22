// campaign_leaf_4380b0.cpp -- one function at file offset 0x4380b0, preferred VA 0x10d380b0. It
// changes the state in the slot selected by the byte at 0x12c (states at 0x130), keeping the old
// state at 0x158. Setting the current state, or 2 over 0, does nothing. State 1 also moves the
// float at 0x180 to 0x184 and subtracts the float at 0x188 from it. Any change sets the byte at
// 0x1b4. The class, method, member and parameter names are invented; the offsets and the bytes
// are the binary's.

class UnkType_10d380b0
{
public:
    void Unk_10d380b0(int State);

    unsigned char unk_0[0x12c];
    unsigned char unk_12c;
    unsigned char unk_12d[3];
    int unk_130[10];
    int unk_158[10];
    float unk_180;
    float unk_184;
    float unk_188;
    unsigned char unk_18c[0x28];
    unsigned char unk_1b4;
};

// UnkType_10d380b0::Unk_10d380b0
void UnkType_10d380b0::Unk_10d380b0(int State)
{
    int Old = unk_130[unk_12c];

    if ( State == Old )
    {
        return;
    }
    if ( State == 2 && Old == 0 )
    {
        return;
    }
    unk_158[unk_12c] = Old;
    unk_130[unk_12c] = State;
    if ( State == 1 )
    {
        unk_184 = unk_180;
        unk_180 = unk_180 - unk_188;
    }
    unk_1b4 = 1;
}
