// campaign_leaf_280220.cpp -- method at VA 0x10b80220 taking a float: when the object at 0x184 is
// set and its virtual slot 33 (vtable offset 0x84) returns an object for this one, stores the
// double at 0xc4 of the object at 0x7c as a float at 0x7b4 and, unless that object's method at VA
// 0x109d53b0 returns 0 for 9, calls its method at VA 0x109d5740 with 9, 0, the float and 1; in
// every case clears bit 20 of the word at 0x744. The class, member and method names are invented;
// the offsets, the slot and the addresses are the binary's.

class UnkType_10b80220;

class UnkType_10b80220_Found
{
public:
    float Unk_109d53b0(int Channel);
    void Unk_109d5740(int Channel, int Mode, float Rate, int Flag);
};

class UnkType_10b80220_184
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
    virtual UnkType_10b80220_Found* VirtualSlot33(UnkType_10b80220* Owner);
};

#pragma pack(push, 4)

class UnkType_10b80220_7c
{
public:
    unsigned char unk_00[0xc4];
    double unk_c4;
};

#pragma pack(pop)

class UnkType_10b80220
{
public:
    void Unk_10b80220(float Rate);

private:
    unsigned char unk_00[0x7c];
    UnkType_10b80220_7c* unk_7c;
    unsigned char unk_80[0x184 - 0x80];
    UnkType_10b80220_184* unk_184;
    unsigned char unk_188[0x744 - 0x188];
    unsigned int unk_744;
    unsigned char unk_748[0x7b4 - 0x748];
    float unk_7b4;
};

// UnkType_10b80220::Unk_10b80220
void UnkType_10b80220::Unk_10b80220(float Rate)
{
    if ( unk_184 )
    {
        UnkType_10b80220_Found* Found = unk_184->VirtualSlot33(this);
        if ( Found )
        {
            unk_7b4 = (float)unk_7c->unk_c4;
            if ( Found->Unk_109d53b0(9) != 0.0f )
            {
                Found->Unk_109d5740(9, 0, Rate, 1);
            }
        }
    }
    unk_744 &= ~0x100000;
}
