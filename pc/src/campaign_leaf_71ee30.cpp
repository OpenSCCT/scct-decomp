// campaign_leaf_71ee30.cpp -- one function at file offset 0x71ee30, preferred VA 0x1101ee30. When
// the byte at 0x30 is set it negates both floats its arguments point to; then, if the first is
// greater than the second, it swaps them. The class, method and member names are invented; the
// offset and the bytes are the binary's.

class UnkType_1101ee30
{
public:
    void Unk_1101ee30(float* First, float* Second);

    unsigned char unk_0[0x30];
    bool unk_30;
};

// UnkType_1101ee30::Unk_1101ee30
void UnkType_1101ee30::Unk_1101ee30(float* First, float* Second)
{
    float Temp;

    if ( unk_30 )
    {
        *First = -*First;
    }
    if ( unk_30 )
    {
        *Second = -*Second;
    }
    if ( *First > *Second )
    {
        Temp = *First;
        *First = *Second;
        *Second = Temp;
    }
}
