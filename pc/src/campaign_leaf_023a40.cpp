// campaign_leaf_023a40.cpp -- method at VA 0x10923a40: empties an array of 0x24-byte elements (data
// at 0x00, count at 0x04, capacity at 0x08): destroys each element with the destructor at VA
// 0x10921410, sets the count to 0 and the capacity to its argument, and passes the element size to
// the method at VA 0x109093c0 to reallocate the data. The class, member and method names are
// invented; the offsets, the size and the addresses are the binary's.

class UnkType_10921410_023a40
{
public:
    ~UnkType_10921410_023a40();

private:
    unsigned char unk_00[0x24];
};

class UnkType_10923a40
{
public:
    void Unk_10923a40(int Slack);
    void Unk_109093c0(int ElementSize);

private:
    UnkType_10921410_023a40* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10923a40::Unk_10923a40
void UnkType_10923a40::Unk_10923a40(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_10921410_023a40();
    }
    unk_04 = 0;
    unk_08 = Slack;
    Unk_109093c0(sizeof(UnkType_10921410_023a40));
}
