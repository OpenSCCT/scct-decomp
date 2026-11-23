// campaign_leaf_09cc80.cpp -- constructor at VA 0x1099cc80 (vtable at VA 0x110c9850): runs the base
// class constructor at VA 0x10cd7930, zeroes the word at 0x28 and passes the 16 bytes at 0x2c, 0
// and 16 to the function at VA 0x10ccad40. The class, member and function names are invented; the
// offsets and the addresses are the binary's.

void Unk_10ccad40(void* Dest, int Value, int Count);

class UnkType_1099cc80_Base
{
public:
    UnkType_1099cc80_Base();
    virtual ~UnkType_1099cc80_Base();

protected:
    unsigned char unk_04[0x28 - 0x04];
};

class UnkType_1099cc80 : public UnkType_1099cc80_Base
{
public:
    UnkType_1099cc80();
    virtual ~UnkType_1099cc80();

private:
    int unk_28;
    unsigned char unk_2c[0x10];
};

// UnkType_1099cc80::UnkType_1099cc80
UnkType_1099cc80::UnkType_1099cc80() : unk_28(0)
{
    Unk_10ccad40(unk_2c, 0, sizeof(unk_2c));
}
