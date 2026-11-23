// campaign_leaf_5319e0.cpp -- thiscall method at VA 0x10e319e0: for every object in the array at
// 0x0c (count at 0x10), fills a four-word context (the first word of the matching pair in the list
// its first argument points to, the index, the argument's member at 0x08 and the argument itself)
// and passes it with the other three arguments to the object's second virtual method, stopping
// once the byte at 0x04 of the last argument is set. All names are invented.

struct UnkType_10e319e0_Pair
{
    int unk_00;
    int unk_04;
};

struct UnkType_10e319e0_List
{
    int unk_00;
    int unk_04;
    int unk_08;
    UnkType_10e319e0_Pair* unk_0c;
};

struct UnkType_10e319e0_Source
{
    UnkType_10e319e0_List* unk_00;
    int unk_04;
    int unk_08;
};

struct UnkType_10e319e0_Context
{
    int unk_00;
    int unk_04;
    int unk_08;
    UnkType_10e319e0_Source* unk_0c;
};

struct UnkType_10e319e0_Result
{
    int unk_00;
    char unk_04;
};

class UnkType_10e319e0_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(UnkType_10e319e0_Context* Context, int First, int Second,
                              UnkType_10e319e0_Result* Result);
};

class UnkType_10e319e0
{
public:
    void Unk_10e319e0(UnkType_10e319e0_Source* Source, int First, int Second,
                      UnkType_10e319e0_Result* Result);

private:
    int unk_00;
    int unk_04;
    int unk_08;
    UnkType_10e319e0_Item** unk_0c;
    int unk_10;
};

// UnkType_10e319e0::Unk_10e319e0
void UnkType_10e319e0::Unk_10e319e0(UnkType_10e319e0_Source* Source, int First, int Second,
                                    UnkType_10e319e0_Result* Result)
{
    UnkType_10e319e0_List* List = Source->unk_00;
    UnkType_10e319e0_Context Context;
    Context.unk_0c = Source;
    Context.unk_08 = Source->unk_08;
    for ( int Index = 0; Index < unk_10; Index++ )
    {
        Context.unk_00 = List->unk_0c[Index].unk_00;
        Context.unk_04 = Index;
        unk_0c[Index]->VirtualSlot1(&Context, First, Second, Result);
        if ( Result->unk_04 )
        {
            break;
        }
    }
}
