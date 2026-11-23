// campaign_leaf_12f4a0.cpp -- one function at file offset 0x12f4a0, preferred VA 0x10a2f4a0.
// A constructor taking one argument: it runs the object base constructor at VA 0x10cd7930,
// installs its virtual table, clears its arrays at offsets 0x28 to 0x58, 0x8c and 0x98 and the
// blocks at offsets 0x7c and 0xa4, constructs the member at offset 0xcc (constructor at
// VA 0x10adea00), clears the array at offset 0x178 and passes the argument to its method at
// VA 0x10aacaa0. Its class is the one destroyed by the destructor at VA 0x10a2f590.
// The class and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a2f4a0_Object
{
public:
    UnkType_10a2f4a0_Object();
    virtual ~UnkType_10a2f4a0_Object();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a2f4a0_Array
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    UnkType_10a2f4a0_Array()
        : Data(0), ArrayNum(0), ArrayMax(0)
    {
    }
};

class UnkType_10a2f4a0_Block
{
public:
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;

    UnkType_10a2f4a0_Block()
        : unk_0(0), unk_4(0), unk_8(0), unk_c(0)
    {
    }
};

class UnkType_10a2f4a0_Member
{
public:
    int unk_0;

    UnkType_10a2f4a0_Member();
};

class UnkType_10a2f4a0 : public UnkType_10a2f4a0_Object
{
public:
    UnkType_10a2f4a0_Array unk_28;
    UnkType_10a2f4a0_Array unk_34;
    UnkType_10a2f4a0_Array unk_40;
    UnkType_10a2f4a0_Array unk_4c;
    UnkType_10a2f4a0_Array unk_58;
    unsigned char unk_64[0x7c - 0x64];
    UnkType_10a2f4a0_Block unk_7c;
    UnkType_10a2f4a0_Array unk_8c;
    UnkType_10a2f4a0_Array unk_98;
    UnkType_10a2f4a0_Block unk_a4;
    unsigned char unk_b4[0xcc - 0xb4];
    UnkType_10a2f4a0_Member unk_cc;
    unsigned char unk_d0[0x178 - 0xd0];
    UnkType_10a2f4a0_Array unk_178;

    UnkType_10a2f4a0(void* Arg);
    virtual ~UnkType_10a2f4a0();

    void Unk_10aacaa0(void* Arg);
};

// UnkType_10a2f4a0::UnkType_10a2f4a0
UnkType_10a2f4a0::UnkType_10a2f4a0(void* Arg)
{
    Unk_10aacaa0(Arg);
}
