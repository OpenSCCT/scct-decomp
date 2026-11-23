// campaign_leaf_19d670.cpp -- one function at file offset 0x19d670, preferred VA 0x10a9d670.
// guess: passes its argument to six of its members (at offsets 0x48, 0x2f4, 0xaf0, 0x1550, 0x19d4
// and 0x13f8, methods at VA 0x10ae69e0, 0x10b037b0, 0x10b02c70, 0x10b01030, 0x10b00180 and
// VA 0x10affc40) and returns true only when all of them succeed. Every member is called.
// The class, member, parameter and callee names are invented; the offset and the bytes are the
// binary's.

class UnkType_10a9d670_PartA
{
public:
    bool Unk_10ae69e0(void* Arg);
};

class UnkType_10a9d670_PartB
{
public:
    bool Unk_10b037b0(void* Arg);
};

class UnkType_10a9d670_PartC
{
public:
    bool Unk_10b02c70(void* Arg);
};

class UnkType_10a9d670_PartD
{
public:
    bool Unk_10b01030(void* Arg);
};

class UnkType_10a9d670_PartE
{
public:
    bool Unk_10b00180(void* Arg);
};

class UnkType_10a9d670_PartF
{
public:
    bool Unk_10affc40(void* Arg);
};

class UnkType_10a9d670
{
public:
    unsigned char unk_0[0x48];
    UnkType_10a9d670_PartA unk_48;
    unsigned char unk_49[0x2f4 - 0x49];
    UnkType_10a9d670_PartB unk_2f4;
    unsigned char unk_2f5[0xaf0 - 0x2f5];
    UnkType_10a9d670_PartC unk_af0;
    unsigned char unk_af1[0x13f8 - 0xaf1];
    UnkType_10a9d670_PartF unk_13f8;
    unsigned char unk_13f9[0x1550 - 0x13f9];
    UnkType_10a9d670_PartD unk_1550;
    unsigned char unk_1551[0x19d4 - 0x1551];
    UnkType_10a9d670_PartE unk_19d4;

    bool Unk_10a9d670(void* Arg);
};

// UnkType_10a9d670::Unk_10a9d670
bool UnkType_10a9d670::Unk_10a9d670(void* Arg)
{
    bool Result = true;
    Result &= unk_48.Unk_10ae69e0(Arg);
    Result &= unk_2f4.Unk_10b037b0(Arg);
    Result &= unk_af0.Unk_10b02c70(Arg);
    Result &= unk_1550.Unk_10b01030(Arg);
    Result &= unk_19d4.Unk_10b00180(Arg);
    Result &= unk_13f8.Unk_10affc40(Arg);
    return Result;
}
