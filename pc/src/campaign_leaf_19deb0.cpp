// campaign_leaf_19deb0.cpp -- one function at file offset 0x19deb0, preferred VA 0x10a9deb0.
// guess: passes its three arguments to six of its members (at offsets 0x48, 0x2f4, 0xaf0, 0x1550,
// 0x19d4 and 0x13f8, methods at VA 0x10a9d730, 0x10a9d7d0, 0x10a9d880, 0x10a9d9e0, 0x10a9da90
// and 0x10a9d930).
// The class, member, parameter and callee names are invented; the offset and the bytes are the
// binary's.

class UnkType_10a9deb0_PartA
{
public:
    void Unk_10a9d730(void* First, void* Second, void* Third);
};

class UnkType_10a9deb0_PartB
{
public:
    void Unk_10a9d7d0(void* First, void* Second, void* Third);
};

class UnkType_10a9deb0_PartC
{
public:
    void Unk_10a9d880(void* First, void* Second, void* Third);
};

class UnkType_10a9deb0_PartD
{
public:
    void Unk_10a9d9e0(void* First, void* Second, void* Third);
};

class UnkType_10a9deb0_PartE
{
public:
    void Unk_10a9da90(void* First, void* Second, void* Third);
};

class UnkType_10a9deb0_PartF
{
public:
    void Unk_10a9d930(void* First, void* Second, void* Third);
};

class UnkType_10a9deb0
{
public:
    unsigned char unk_0[0x48];
    UnkType_10a9deb0_PartA unk_48;
    unsigned char unk_49[0x2f4 - 0x49];
    UnkType_10a9deb0_PartB unk_2f4;
    unsigned char unk_2f5[0xaf0 - 0x2f5];
    UnkType_10a9deb0_PartC unk_af0;
    unsigned char unk_af1[0x13f8 - 0xaf1];
    UnkType_10a9deb0_PartF unk_13f8;
    unsigned char unk_13f9[0x1550 - 0x13f9];
    UnkType_10a9deb0_PartD unk_1550;
    unsigned char unk_1551[0x19d4 - 0x1551];
    UnkType_10a9deb0_PartE unk_19d4;

    void Unk_10a9deb0(void* First, void* Second, void* Third);
};

// UnkType_10a9deb0::Unk_10a9deb0
void UnkType_10a9deb0::Unk_10a9deb0(void* First, void* Second, void* Third)
{
    unk_48.Unk_10a9d730(First, Second, Third);
    unk_2f4.Unk_10a9d7d0(First, Second, Third);
    unk_af0.Unk_10a9d880(First, Second, Third);
    unk_1550.Unk_10a9d9e0(First, Second, Third);
    unk_19d4.Unk_10a9da90(First, Second, Third);
    unk_13f8.Unk_10a9d930(First, Second, Third);
}
