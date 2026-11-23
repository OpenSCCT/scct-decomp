// campaign_leaf_764310.cpp -- one function at file offset 0x764310, preferred VA 0x11064310. It has
// the stdcall function at VA 0x1105cb40 fill a four-word local from its argument, the method at VA
// 0x11056ce0 of the object returned by the function at VA 0x11056900 and the record at 0x4; it adds
// the record's word at 0x8 to the local's second word, raises it to at least 0xffa00000 and passes
// the local to the method at VA 0x11063c10. The class, method and member names are invented; the
// offsets and the addresses are the binary's.

struct UnkType_11064310_Record
{
    int unk_0;
    int unk_4;
    int unk_8;
};

struct UnkType_11064310_Block
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
};

class UnkType_11064310_Manager
{
public:
    int Unk_11056ce0();
};

UnkType_11064310_Manager* Unk_11056900();
void __stdcall Unk_1105cb40(int Value, UnkType_11064310_Block* Block, int Mode,
                            UnkType_11064310_Record* Record);

class UnkType_11064310
{
public:
    void Unk_11063c10(UnkType_11064310_Block* Block);
    void Unk_11064310(int Value);

    int unk_0;
    UnkType_11064310_Record* unk_4;
};

// UnkType_11064310::Unk_11064310
void UnkType_11064310::Unk_11064310(int Value)
{
    UnkType_11064310_Block Block;

    Unk_1105cb40(Value, &Block, Unk_11056900()->Unk_11056ce0(), unk_4);
    Block.unk_4 += unk_4->unk_8;
    if ( Block.unk_4 < (int)0xffa00000 )
    {
        Block.unk_4 = 0xffa00000;
    }
    Unk_11063c10(&Block);
}
