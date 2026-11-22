// campaign_leaf_3e9160.cpp -- one function at file offset 0x3e9160, preferred VA 0x10ce9160. It
// returns 1 when the byte First points to equals the byte Second points to, a null Second
// standing for 0. It never reads its this pointer. The class, method and parameter names are
// invented; the bytes are the binary's.

class UnkType_10ce9160
{
public:
    int Unk_10ce9160(const unsigned char* First, const unsigned char* Second) const;
};

// UnkType_10ce9160::Unk_10ce9160
int UnkType_10ce9160::Unk_10ce9160(const unsigned char* First,
                                   const unsigned char* Second) const
{
    return *First == ( Second != 0 ? *Second : 0 );
}
