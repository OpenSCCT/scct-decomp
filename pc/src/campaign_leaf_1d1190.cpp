// campaign_leaf_1d1190.cpp -- method at VA 0x10ad1190: takes the object the free function at VA
// 0x10acde60 returns; when the byte at 0x0 is set, calls the object's method at VA 0x10b115e0 with
// the values at 0x24 and 0x20 of the object at 0x4 and clears the byte; then calls the object's
// method at VA 0x10b12210 with its arguments, and sets the byte at 0x1 when Rate is above 1e-6.
// The class, member, method and parameter names are invented; the offsets, the constants and the
// addresses are the binary's.

class UnkType_10ad1190_Settings
{
public:
    char unk_0[0x20];
    int unk_20;
    int unk_24;
};

class UnkType_10ad1190_Target
{
public:
    void Unk_10b115e0(int First, int Handle, int Second, int Flag1, int Flag2);
    void Unk_10b12210(int Handle, int A, int B, int C, int Flag1, float Rate, int Flag2,
        int Flag3);

    int unk_0;
};

UnkType_10ad1190_Target& Unk_10acde60();

class UnkType_10ad1190
{
public:
    void Unk_10ad1190(int A, int B, int C, float Rate);

private:
    unsigned char unk_0;
    unsigned char unk_1;
    char unk_2[0x4 - 0x2];
    UnkType_10ad1190_Settings* unk_4;
};

// UnkType_10ad1190::Unk_10ad1190
void UnkType_10ad1190::Unk_10ad1190(int A, int B, int C, float Rate)
{
    UnkType_10ad1190_Target& Target = Unk_10acde60();

    if ( unk_0 )
    {
        Target.Unk_10b115e0(unk_4->unk_24, Target.unk_0, unk_4->unk_20, 1, 1);
        unk_0 = 0;
    }
    Target.Unk_10b12210(Target.unk_0, A, B, C, 1, Rate, 0, 0);
    if ( Rate > 1e-6f )
    {
        unk_1 = 1;
    }
}
