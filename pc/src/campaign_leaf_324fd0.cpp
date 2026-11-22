// campaign_leaf_324fd0.cpp -- one function at file offset 0x324fd0, preferred VA 0x10c24fd0. It
// searches its array of 8-byte entries (data pointer at offset 0, count at 4) for one whose first
// word equals the word its first argument points to, keeping the running index in the word its
// second argument points to; it returns 1 when found, else 0. The class, method and member names
// are invented; the offset and the bytes are the binary's.

struct UnkPair
{
    int unk_0;
    int unk_4;
};

class UnkType_10c24fd0
{
public:
    UnkPair* unk_0;
    int unk_4;

    int Unk_10c24fd0(const int& Key, int& Index);
};

// UnkType_10c24fd0::Unk_10c24fd0
int UnkType_10c24fd0::Unk_10c24fd0(const int& Key, int& Index)
{
    for ( Index = 0; Index < unk_4; Index++ )
    {
        if ( unk_0[Index].unk_0 == Key )
        {
            return 1;
        }
    }
    return 0;
}
