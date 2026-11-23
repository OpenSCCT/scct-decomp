// campaign_leaf_4b4590.cpp -- one function at file offset 0x4b4590, preferred VA 0x10db4590.
// The constructor runs the base constructor at 0x10da0d00 with Value, installs the vtable at
// 0x1113fdd8 and stores at offsets 0x20, 0x22 and 0x24 the numbers the function at 0x10da4220
// returns for the names "ConfirmElection", "DeclinePromotion" and "ElectNewMaster". The class,
// function, member and parameter names are invented; the offset and the bytes are the binary's.

class UnkType_10db4590_Name
{
public:
    int unk_0;

    UnkType_10db4590_Name(const char* Text);
    UnkType_10db4590_Name(const UnkType_10db4590_Name& Other);
};

unsigned short Unk_10da4220(UnkType_10db4590_Name Name);

class UnkType_10db4590_Base
{
public:
    unsigned char unk_4[0x1c];

    UnkType_10db4590_Base(int Value);

    virtual void VirtualSlot0();
};

class UnkType_10db4590 : public UnkType_10db4590_Base
{
public:
    unsigned short unk_20;
    unsigned short unk_22;
    unsigned short unk_24;

    UnkType_10db4590(int Value);

    virtual void VirtualSlot0();
};

// UnkType_10db4590::UnkType_10db4590
UnkType_10db4590::UnkType_10db4590(int Value)
    : UnkType_10db4590_Base(Value)
{
    unk_20 = Unk_10da4220(UnkType_10db4590_Name("ConfirmElection"));
    unk_22 = Unk_10da4220(UnkType_10db4590_Name("DeclinePromotion"));
    unk_24 = Unk_10da4220(UnkType_10db4590_Name("ElectNewMaster"));
}
