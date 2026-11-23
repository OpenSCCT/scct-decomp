// campaign_leaf_125150.cpp -- one function at file offset 0x125150, preferred VA 0x10a25150.
// guess: passes its argument to its method at VA 0x10a1f1e0, stores at offset 0x370 the vector
// that the value at 0x364 yields (method at VA 0x10cf96b0), and sets the first flag at 0x23c
// when the byte at 0x360 is zero.
// The class, member, parameter and callee names are invented; the offset and the bytes are the
// binary's.

class UnkType_10a25150_Vector
{
public:
    float X;
    float Y;
    float Z;
};

class UnkType_10a25150_Value
{
public:
    int unk_0;
    int unk_4;
    int unk_8;

    UnkType_10a25150_Vector Unk_10cf96b0() const;
};

class UnkType_10a25150
{
public:
    unsigned char unk_0[0x23c];
    unsigned int unk_23c_0 : 1;
    unsigned char unk_240[0x360 - 0x240];
    unsigned char unk_360;
    unsigned char unk_361[0x364 - 0x361];
    UnkType_10a25150_Value unk_364;
    UnkType_10a25150_Vector unk_370;

    void Unk_10a25150(void* Arg);
    void Unk_10a1f1e0(void* Arg);
};

// UnkType_10a25150::Unk_10a25150
void UnkType_10a25150::Unk_10a25150(void* Arg)
{
    Unk_10a1f1e0(Arg);
    unk_370 = unk_364.Unk_10cf96b0();
    unk_23c_0 = unk_23c_0 || !unk_360;
}
