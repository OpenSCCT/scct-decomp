// campaign_leaf_35dab0.cpp -- method at VA 0x10c5dab0: calls the method at VA 0x10c5d910, then
// stores at 0x418 the result of the free function at VA 0x10ccab60 applied to that of the free
// function at VA 0x10cf8470 for half the integer at 0x414. The class, member and function names
// are invented; the offsets, the constant and the addresses are the binary's.

float Unk_10cf8470(float Value);
double Unk_10ccab60(double Value);

class UnkType_10c5dab0
{
public:
    void Unk_10c5d910();
    void Unk_10c5dab0();

private:
    char unk_0[0x414];
    int unk_414;
    float unk_418;
};

// UnkType_10c5dab0::Unk_10c5dab0
void UnkType_10c5dab0::Unk_10c5dab0()
{
    Unk_10c5d910();
    unk_418 = Unk_10ccab60(Unk_10cf8470(unk_414 * 0.5));
}
