// campaign_leaf_593a30.cpp -- one function at file offset 0x593a30, preferred VA 0x10e93a30.
// It orders the three pointers at offsets 0x10, 0x14 and 0x18 by the unsigned shorts they point
// to, smallest first, with three compare-and-exchange steps. The class, method and member names
// are invented; the offset and the bytes are the binary's.

template<class T> inline void Exchange(T& A, T& B)
{
    const T Temp = A;
    A = B;
    B = Temp;
}

class UnkType_10e93a30
{
public:
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    unsigned short* unk_10;
    unsigned short* unk_14;
    unsigned short* unk_18;

    void Unk_10e93a30();
};

// UnkType_10e93a30::Unk_10e93a30
void UnkType_10e93a30::Unk_10e93a30()
{
    if ( *unk_10 > *unk_14 )
    {
        Exchange(unk_10, unk_14);
    }
    if ( *unk_14 > *unk_18 )
    {
        Exchange(unk_14, unk_18);
    }
    if ( *unk_10 > *unk_14 )
    {
        Exchange(unk_10, unk_14);
    }
}
