// campaign_leaf_4a0d00.cpp -- one function at file offset 0x4a0d00, preferred VA 0x10da0d00.
// The constructor runs the base constructor at 0x10da0670 with Value, installs the vtable at
// 0x1113e4c8 and stores at offsets 0x18, 0x1a and 0x1c the numbers the function at 0x10da4220
// returns for the names "AddDuplicaLocation", "DeleteDuplica" and
// "RemoveFromCachedDuplicationSet". The class, function, member and parameter names are invented;
// the offset and the bytes are the binary's.

class UnkType_10da0d00_Name
{
public:
    int unk_0;

    UnkType_10da0d00_Name(const char* Text);
    UnkType_10da0d00_Name(const UnkType_10da0d00_Name& Other);
};

unsigned short Unk_10da4220(UnkType_10da0d00_Name Name);

class UnkType_10da0d00_Base
{
public:
    unsigned char unk_4[0x14];

    UnkType_10da0d00_Base(int Value);

    virtual void VirtualSlot0();
};

class UnkType_10da0d00 : public UnkType_10da0d00_Base
{
public:
    unsigned short unk_18;
    unsigned short unk_1a;
    unsigned short unk_1c;

    UnkType_10da0d00(int Value);

    virtual void VirtualSlot0();
};

// UnkType_10da0d00::UnkType_10da0d00
UnkType_10da0d00::UnkType_10da0d00(int Value)
    : UnkType_10da0d00_Base(Value)
{
    unk_18 = Unk_10da4220(UnkType_10da0d00_Name("AddDuplicaLocation"));
    unk_1a = Unk_10da4220(UnkType_10da0d00_Name("DeleteDuplica"));
    unk_1c = Unk_10da4220(UnkType_10da0d00_Name("RemoveFromCachedDuplicationSet"));
}
