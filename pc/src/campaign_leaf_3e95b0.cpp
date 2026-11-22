// campaign_leaf_3e95b0.cpp -- one function at file offset 0x3e95b0, preferred VA 0x10ce95b0. It
// returns 1 when the word First points to equals the word Second points to, a null Second
// standing for 0. It never reads its this pointer. The class, method and parameter names are
// invented; the bytes are the binary's.

class UnkType_10ce95b0
{
public:
    int Unk_10ce95b0(const int* First, const int* Second) const;
};

// UnkType_10ce95b0::Unk_10ce95b0
int UnkType_10ce95b0::Unk_10ce95b0(const int* First, const int* Second) const
{
    return *First == ( Second != 0 ? *Second : 0 );
}
