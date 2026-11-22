// campaign_leaf_474890.cpp -- one function at file offset 0x474890, preferred VA 0x10d74890. It
// looks up the pair (First, Second) in a packed upper-triangular table of three-word entries
// (data at 0x8, dimension at 0xc) and returns the entry's word at 0x4 when First is the larger
// index, its word at 0x0 otherwise. The class, method, structure, member and parameter names are
// invented; the offsets and the bytes are the binary's.

struct UnkType_10d74890_Entry
{
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10d74890
{
public:
    int Unk_10d74890(unsigned int First, unsigned int Second) const;

    int unk_0;
    int unk_4;
    UnkType_10d74890_Entry* unk_8;
    unsigned int unk_c;
};

// UnkType_10d74890::Unk_10d74890
int UnkType_10d74890::Unk_10d74890(unsigned int First, unsigned int Second) const
{
    unsigned int Low;
    unsigned int High;
    unsigned int Index;

    if ( (int)First > (int)Second )
    {
        Low = Second;
        High = First;
    }
    else
    {
        Low = First;
        High = Second;
    }
    Index = unk_c * (unk_c + 1) / 2 - (unk_c - Low) * (unk_c - Low + 1) / 2 - Low + High;
    if ( First > Second )
    {
        return unk_8[Index].unk_4;
    }
    return unk_8[Index].unk_0;
}
