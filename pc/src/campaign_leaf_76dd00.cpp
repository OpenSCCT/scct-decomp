// campaign_leaf_76dd00.cpp -- one function at file offset 0x76dd00, preferred VA 0x1106dd00. When
// its argument differs from the float at 0x2c it stores it there and calls the method at VA
// 0x1106dc80. The class, method and member names are invented; the offsets and the callee's
// address are the binary's.

class UnkType_1106dd00
{
public:
    void Unk_1106dc80();
    void Unk_1106dd00(float Value);

    unsigned char unk_0[0x2c];
    float unk_2c;
};

// UnkType_1106dd00::Unk_1106dd00
void UnkType_1106dd00::Unk_1106dd00(float Value)
{
    if ( unk_2c != Value )
    {
        unk_2c = Value;
        Unk_1106dc80();
    }
}
