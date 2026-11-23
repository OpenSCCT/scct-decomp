// campaign_leaf_0cd3c0.cpp -- method at VA 0x109cd3c0 taking twelve argument words: calls virtual
// slot 34 (vtable offset 0x88), then passes every argument unchanged to virtual slot 25 (vtable
// offset 0x64) of the object it returns and returns that call's result. The class, structure and
// method names are invented; the slots are the binary's.

struct UnkType_109cd3c0_Vector
{
    float unk_00;
    float unk_04;
    float unk_08;
};

class UnkType_109cd3c0_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual int VirtualSlot25(int Arg0, int Arg1, UnkType_109cd3c0_Vector Start,
                              UnkType_109cd3c0_Vector End,
                              UnkType_109cd3c0_Vector Extent, int Arg4);
};

class UnkType_109cd3c0
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual UnkType_109cd3c0_Target* VirtualSlot34();

    int Unk_109cd3c0(int Arg0, int Arg1, UnkType_109cd3c0_Vector Start,
                     UnkType_109cd3c0_Vector End, UnkType_109cd3c0_Vector Extent, int Arg4);
};

// UnkType_109cd3c0::Unk_109cd3c0
int UnkType_109cd3c0::Unk_109cd3c0(int Arg0, int Arg1, UnkType_109cd3c0_Vector Start,
                                   UnkType_109cd3c0_Vector End, UnkType_109cd3c0_Vector Extent,
                                   int Arg4)
{
    return VirtualSlot34()->VirtualSlot25(Arg0, Arg1, Start, End, Extent, Arg4);
}
