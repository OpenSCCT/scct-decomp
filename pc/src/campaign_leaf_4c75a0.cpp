// campaign_leaf_4c75a0.cpp -- one function at file offset 0x4c75a0, preferred VA 0x10dc75a0.
// When the int at offset 0x64 is positive it calls the method at 0x10dc14d0 with 0 and copies that
// int to offset 0x1c; otherwise it calls the method with 4. The class, method and member names are
// invented; the offset and the bytes are the binary's.

class UnkType_10dc75a0
{
public:
    unsigned char unk_0[0x1c];
    int unk_1c;
    unsigned char unk_20[0x44];
    int unk_64;

    void Unk_10dc14d0(int State);
    void Unk_10dc75a0();
};

// UnkType_10dc75a0::Unk_10dc75a0
void UnkType_10dc75a0::Unk_10dc75a0()
{
    if ( unk_64 > 0 )
    {
        Unk_10dc14d0(0);
        unk_1c = unk_64;
    }
    else
    {
        Unk_10dc14d0(4);
    }
}
