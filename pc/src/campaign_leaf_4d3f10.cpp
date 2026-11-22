// campaign_leaf_4d3f10.cpp -- one function at file offset 0x4d3f10, preferred VA 0x10dd3f10. It
// orders two pairs of unsigned words, first word first: it returns 1 when the first pair sorts
// before the second. It never reads its this pointer. The class, method, structure and member
// names are invented; the offsets and the bytes are the binary's.

struct UnkType_10dd3f10_Key
{
    unsigned int unk_0;
    unsigned int unk_4;
};

class UnkType_10dd3f10
{
public:
    int Unk_10dd3f10(const UnkType_10dd3f10_Key& First, const UnkType_10dd3f10_Key& Second) const;
};

// UnkType_10dd3f10::Unk_10dd3f10
int UnkType_10dd3f10::Unk_10dd3f10(const UnkType_10dd3f10_Key& First,
                                   const UnkType_10dd3f10_Key& Second) const
{
    return First.unk_0 < Second.unk_0
        || ( !( Second.unk_0 < First.unk_0 ) && First.unk_4 < Second.unk_4 );
}
