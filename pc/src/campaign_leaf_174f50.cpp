// campaign_leaf_174f50.cpp -- one function at file offset 0x174f50, preferred VA 0x10a74f50.
// A constructor: it runs the object base constructor at VA 0x10cd7930, installs its virtual
// table, sets up its three four-float values at offsets 0x1cc (its base class's), 0x2d8 and 0x2e8
// (zero except the third float, 1e-8) and clears the member at 0x30c.
// The class and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a74f50_Object
{
public:
    UnkType_10a74f50_Object();
    virtual ~UnkType_10a74f50_Object();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a74f50_Value
{
public:
    float unk_0;
    float unk_4;
    float unk_8;
    float unk_c;

    UnkType_10a74f50_Value()
        : unk_0(0.0f), unk_4(0.0f), unk_8(1.e-8f), unk_c(0.0f)
    {
    }
};

class UnkType_10a74f50_Base : public UnkType_10a74f50_Object
{
public:
    unsigned char unk_28[0x1cc - 0x28];
    UnkType_10a74f50_Value unk_1cc;
    unsigned char unk_1dc[0x2d8 - 0x1dc];

    virtual ~UnkType_10a74f50_Base();
};

class UnkType_10a74f50 : public UnkType_10a74f50_Base
{
public:
    UnkType_10a74f50_Value unk_2d8;
    UnkType_10a74f50_Value unk_2e8;
    unsigned char unk_2f8[0x30c - 0x2f8];
    int unk_30c;

    UnkType_10a74f50();
    virtual ~UnkType_10a74f50();
};

// UnkType_10a74f50::UnkType_10a74f50
UnkType_10a74f50::UnkType_10a74f50()
{
    unk_30c = 0;
}
