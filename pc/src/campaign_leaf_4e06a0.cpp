// campaign_leaf_4e06a0.cpp -- one function at file offset 0x4e06a0, preferred VA 0x10de06a0.
// It returns 0x10 plus the result of the method at 0x10dcddb0 of the object at offset 0x1c, or
// 0x10 alone when there is no such object. The class, method and member names are invented; the
// offset and the bytes are the binary's.

class UnkType_10de06a0_Callee
{
public:
    int Unk_10dcddb0();
};

class UnkType_10de06a0
{
public:
    unsigned char unk_0[0x1c];
    UnkType_10de06a0_Callee* unk_1c;

    unsigned short Unk_10de06a0();
};

// UnkType_10de06a0::Unk_10de06a0
unsigned short UnkType_10de06a0::Unk_10de06a0()
{
    if ( unk_1c != 0 )
    {
        return (unsigned short)(unk_1c->Unk_10dcddb0() + 0x10);
    }
    return 0x10;
}
