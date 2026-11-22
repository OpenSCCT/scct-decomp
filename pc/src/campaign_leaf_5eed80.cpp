// campaign_leaf_5eed80.cpp -- thiscall method at VA 0x10eeed80: masks the value returned by its
// third virtual method to its low byte, widens it to a 64-bit integer and passes it to the stdcall
// function at VA 0x10ef2560. The class, method and function names are invented.

void __stdcall Unk_10ef2560(__int64 Value);

class UnkType_10eeed80
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual int VirtualSlot2();

    void Unk_10eeed80();
};

// UnkType_10eeed80::Unk_10eeed80
void UnkType_10eeed80::Unk_10eeed80()
{
    Unk_10ef2560(VirtualSlot2() & 0xff);
}
