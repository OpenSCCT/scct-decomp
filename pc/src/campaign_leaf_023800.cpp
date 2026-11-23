// campaign_leaf_023800.cpp -- method at VA 0x10923800: empties an array of 0x1c-byte elements (data
// at 0x00, count at 0x04, capacity at 0x08): destroys each element with the destructor at VA
// 0x1090c6b0, sets the count to 0 and the capacity to its argument, and passes the element size to
// the method at VA 0x10909390 to reallocate the data. The class, member and method names are
// invented; the offsets, the size and the addresses are the binary's.

class UnkType_1090c6b0_023800
{
public:
    ~UnkType_1090c6b0_023800();

private:
    unsigned char unk_00[0x1c];
};

class UnkType_10923800
{
public:
    void Unk_10923800(int Slack);
    void Unk_10909390(int ElementSize);

private:
    UnkType_1090c6b0_023800* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10923800::Unk_10923800
void UnkType_10923800::Unk_10923800(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_1090c6b0_023800();
    }
    unk_04 = 0;
    unk_08 = Slack;
    Unk_10909390(sizeof(UnkType_1090c6b0_023800));
}
