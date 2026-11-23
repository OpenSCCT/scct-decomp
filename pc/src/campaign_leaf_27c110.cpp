// campaign_leaf_27c110.cpp -- method at VA 0x10b7c110: returns the mean of the ten floats at 0x780
// (their sum times 0.1). The class, member and method names are invented; the offsets and the
// constant are the binary's.

class UnkType_10b7c110
{
public:
    float Unk_10b7c110();

private:
    char unk_0[0x780];
    float unk_780[10];
};

// UnkType_10b7c110::Unk_10b7c110
float UnkType_10b7c110::Unk_10b7c110()
{
    float Sum = 0.0f;
    int i;

    for ( i = 0; i < 10; i++ )
    {
        Sum += unk_780[i];
    }
    return Sum * 0.1f;
}
