// campaign_leaf_2d5f40.cpp -- one function at file offset 0x2d5f40, preferred VA 0x10bd5f40. It
// returns 1 when the array of words its first argument describes (data pointer, count) contains
// its second argument, else 0. It does not read its this pointer. The class, method and member
// names are invented; the offset and the bytes are the binary's.

struct UnkIntArray
{
    int* unk_0;
    int unk_4;
};

class UnkType_10bd5f40
{
public:
    int Unk_10bd5f40(const UnkIntArray& Array, int Value);
};

// UnkType_10bd5f40::Unk_10bd5f40
int UnkType_10bd5f40::Unk_10bd5f40(const UnkIntArray& Array, int Value)
{
    for ( int i = 0; i < Array.unk_4; i++ )
    {
        if ( Array.unk_0[i] == Value )
        {
            return 1;
        }
    }
    return 0;
}
