// campaign_leaf_25c0c0.cpp -- the constructor at VA 0x10b5c0c0 taking an int: it runs the base
// constructor at VA 0x10b64560 with the int, installs the class's virtual tables at 0x00, 0x08 and
// 0x10, clears the two arrays of four ints at 0x44 and 0x54 and the ints at 0x64, 0x68, 0x70 and
// 0x74, and clears the byte at 0x78. The class and member names are invented; the offsets and
// addresses are the binary's.

class UnkType_10b5c0c0_Face0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b5c0c0_Face8
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b5c0c0_Face10
{
public:
    virtual void VirtualSlot0();
};

class UnkType_10b5c0c0_Base : public UnkType_10b5c0c0_Face0,
                              public UnkType_10b5c0c0_Face8,
                              public UnkType_10b5c0c0_Face10
{
public:
    UnkType_10b5c0c0_Base(int Value);

private:
    unsigned char unk_14[0x44 - 0x14];
};

class UnkType_10b5c0c0 : public UnkType_10b5c0c0_Base
{
public:
    UnkType_10b5c0c0(int Value);

private:
    int unk_44[4];
    int unk_54[4];
    int unk_64;
    int unk_68;
    int unk_6c;
    int unk_70;
    int unk_74;
    bool unk_78;
};

// UnkType_10b5c0c0::UnkType_10b5c0c0
UnkType_10b5c0c0::UnkType_10b5c0c0(int Value)
    : UnkType_10b5c0c0_Base(Value),
      unk_64(0),
      unk_68(0),
      unk_70(0),
      unk_74(0),
      unk_78(false)
{
    for ( int i = 0; i < 4; i++ )
    {
        unk_44[i] = 0;
        unk_54[i] = 0;
    }
}
