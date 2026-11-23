// campaign_leaf_1d4440.cpp -- thiscall method at VA 0x10ad4440. When the words at 0x30 and 0x3c
// are both set, it takes the object at 0x04 of the object at 0x44; when that is set it asks it for
// an object (method at VA 0x10a0e220), and when that object and its member at 0x58 are set calls
// slot 37 of the member with 1 and then its slot 34. It then clears the words at 0x3c and 0x30. The
// class, method and member names are invented.

class UnkType_10ad4440_Target
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
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37(int Value);
};

struct UnkType_10ad4440_Owner
{
    char unk_00[0x58];
    UnkType_10ad4440_Target* unk_58;
};

class UnkType_10ad4440_Source
{
public:
    UnkType_10ad4440_Owner* Unk_10a0e220();
};

struct UnkType_10ad4440_Holder
{
    int unk_0;
    UnkType_10ad4440_Source* unk_4;
};

class UnkType_10ad4440
{
public:
    void Unk_10ad4440();

private:
    char unk_00[0x30];
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
    int unk_40;
    UnkType_10ad4440_Holder* unk_44;
};

// UnkType_10ad4440::Unk_10ad4440
void UnkType_10ad4440::Unk_10ad4440()
{
    if ( unk_30 != 0 && unk_3c != 0 )
    {
        if ( unk_44->unk_4 != 0 )
        {
            UnkType_10ad4440_Owner* Owner = unk_44->unk_4->Unk_10a0e220();
            if ( Owner != 0 && Owner->unk_58 != 0 )
            {
                Owner->unk_58->VirtualSlot37(1);
                Owner->unk_58->VirtualSlot34();
            }
        }
        unk_3c = 0;
        unk_30 = 0;
    }
}
