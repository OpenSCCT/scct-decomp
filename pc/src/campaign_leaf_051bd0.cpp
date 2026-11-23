// campaign_leaf_051bd0.cpp -- method at VA 0x10951bd0: destroys each 0x98-byte element of the array
// at 0x00 (count at 0x04) with the destructor at VA 0x10951330 and sets the count to 0. The class,
// member and method names are invented; the offsets, the size and the address are the binary's.

class UnkType_10951330_051bd0
{
public:
    ~UnkType_10951330_051bd0();

private:
    unsigned char unk_00[0x98];
};

class UnkType_10951bd0
{
public:
    void Unk_10951bd0();

private:
    UnkType_10951330_051bd0* unk_00;
    int unk_04;
};

// UnkType_10951bd0::Unk_10951bd0
void UnkType_10951bd0::Unk_10951bd0()
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_10951330_051bd0();
    }
    unk_04 = 0;
}
