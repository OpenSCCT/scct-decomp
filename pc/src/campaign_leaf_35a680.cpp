// campaign_leaf_35a680.cpp -- one function at file offset 0x35a680, preferred VA 0x10c5a680. It
// takes 0x10000 off a value above 0x7d00, then clamps it between the words at 0x59c and 0x598.
// The class, method, member and parameter names are invented; the offsets and the bytes are the
// binary's.

template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

class UnkType_10c5a680
{
public:
    void Unk_10c5a680(int& Value) const;

    unsigned char unk_0[0x598];
    int unk_598;
    int unk_59c;
};

// UnkType_10c5a680::Unk_10c5a680
void UnkType_10c5a680::Unk_10c5a680(int& Value) const
{
    if ( Value > 0x7d00 )
    {
        Value -= 0x10000;
    }
    Value = Clamp(Value, unk_59c, unk_598);
}
