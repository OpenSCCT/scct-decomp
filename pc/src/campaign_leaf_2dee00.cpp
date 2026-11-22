// campaign_leaf_2dee00.cpp -- a member function at VA 0x10bdee00 that appends its argument to the
// array at 0x2f0: the array's member at VA 0x10bdbfb0, given 4 and 1, returns the new index, and
// the argument is stored in the array's data at that index. The class, method and member names are
// invented; the offsets and addresses are the binary's.

class UnkType_10bdbfb0
{
public:
    int Unk_10bdbfb0(int First, int Second);

    int* unk_00;
};

class UnkType_10bdee00
{
public:
    void Unk_10bdee00(int Value);

private:
    unsigned char unk_000[0x2f0];
    UnkType_10bdbfb0 unk_2f0;
};

// UnkType_10bdee00::Unk_10bdee00
void UnkType_10bdee00::Unk_10bdee00(int Value)
{
    int Index = unk_2f0.Unk_10bdbfb0(4, 1);
    unk_2f0.unk_00[Index] = Value;
}
