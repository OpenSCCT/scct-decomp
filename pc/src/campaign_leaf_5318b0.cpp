// campaign_leaf_5318b0.cpp -- thiscall method at VA 0x10e318b0: for every object in the array at
// 0x0c (count at 0x10), fills a four-word context (the first word of the matching pair in the list
// its first argument points to, the index, the argument's member at 0x08 and the argument itself)
// and passes it with the other three arguments to the object's virtual method at slot 4. All names
// are invented.

struct UnkType_10e318b0_Pair
{
    int unk_00;
    int unk_04;
};

struct UnkType_10e318b0_List
{
    int unk_00;
    int unk_04;
    int unk_08;
    UnkType_10e318b0_Pair* unk_0c;
};

struct UnkType_10e318b0_Source
{
    UnkType_10e318b0_List* unk_00;
    int unk_04;
    int unk_08;
};

struct UnkType_10e318b0_Context
{
    int unk_00;
    int unk_04;
    int unk_08;
    UnkType_10e318b0_Source* unk_0c;
};

class UnkType_10e318b0_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4(UnkType_10e318b0_Context* Context, int First, int Second, int Third);
};

class UnkType_10e318b0
{
public:
    void Unk_10e318b0(UnkType_10e318b0_Source* Source, int First, int Second, int Third);

private:
    int unk_00;
    int unk_04;
    int unk_08;
    UnkType_10e318b0_Item** unk_0c;
    int unk_10;
};

// UnkType_10e318b0::Unk_10e318b0
void UnkType_10e318b0::Unk_10e318b0(UnkType_10e318b0_Source* Source,
                                    int First, int Second, int Third)
{
    int Count = unk_10;
    UnkType_10e318b0_List* List = Source->unk_00;
    UnkType_10e318b0_Item** Items = unk_0c;
    UnkType_10e318b0_Context Context;
    Context.unk_0c = Source;
    Context.unk_08 = Source->unk_08;
    for ( int Index = 0; Index < Count; Items++, Index++ )
    {
        Context.unk_00 = List->unk_0c[Index].unk_00;
        Context.unk_04 = Index;
        (*Items)->VirtualSlot4(&Context, First, Second, Third);
    }
}
