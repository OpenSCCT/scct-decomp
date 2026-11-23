// campaign_leaf_3c7280.cpp -- one function at file offset 0x3c7280, preferred VA 0x10cc7280. It
// fills a six-word block (0x18, 0x10, Object's word at 0x18, 2, -32768, 32767) and passes 4 and
// its address to stdcall virtual slot 6 of Device, returning 1 when the result is not negative.
// It never reads its this pointer. The class, method, structure, member and parameter names are
// invented; the offsets, the constants, the slot and the bytes are the binary's.

struct UnkType_10cc7280_Range
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
};

class UnkType_10cc7280_Object
{
public:
    unsigned char unk_0[0x18];
    int unk_18;
};

class UnkType_10cc7280_Device
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual long __stdcall VirtualSlot6(int Property, UnkType_10cc7280_Range* Range);
};

class UnkType_10cc7280
{
public:
    int Unk_10cc7280(UnkType_10cc7280_Object* Object, UnkType_10cc7280_Device* Device) const;
};

// UnkType_10cc7280::Unk_10cc7280
int UnkType_10cc7280::Unk_10cc7280(UnkType_10cc7280_Object* Object,
                                   UnkType_10cc7280_Device* Device) const
{
    UnkType_10cc7280_Range Range;

    Range.unk_0 = 0x18;
    Range.unk_4 = 0x10;
    Range.unk_8 = Object->unk_18;
    Range.unk_c = 2;
    Range.unk_10 = -32768;
    Range.unk_14 = 32767;
    return Device->VirtualSlot6(4, &Range) >= 0;
}
