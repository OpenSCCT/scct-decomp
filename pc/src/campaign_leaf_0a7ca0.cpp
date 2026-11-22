// campaign_leaf_0a7ca0.cpp -- one function at file offset 0xa7ca0, preferred VA 0x109a7ca0. It
// returns true when the word at offset 0x20 of its argument equals one of the first count words of
// the array at offset 0x2c0, the count being at 0x2c4. The class and method names are invented;
// the offset and the bytes are the binary's.

struct UnkType_109a7ca0_Obj
{
    unsigned char unk_00[0x20];     // not read by this function
    int unk_20;
};

class UnkType_109a7ca0
{
public:
    bool UnkContains(const UnkType_109a7ca0_Obj *Other) const;

private:
    unsigned char unk_00[0x2c0];    // not read by this function
    int *unk_2c0;
    int unk_2c4;
};

// UnkType_109a7ca0::UnkContains
bool UnkType_109a7ca0::UnkContains(const UnkType_109a7ca0_Obj *Other) const
{
    for ( int i = 0; i < unk_2c4; ++i )
    {
        if ( Other->unk_20 == unk_2c0[i] )
        {
            return true;
        }
    }
    return false;
}
