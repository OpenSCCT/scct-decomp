// campaign_leaf_00d670.cpp -- method at VA 0x1090d670: empties an array of 0xc-byte elements (data
// at 0x00, count at 0x04, capacity at 0x08): destroys each element with the destructor at VA
// 0x1090ba70, sets the count to 0 and the capacity to its argument, and passes the element size to
// the method at VA 0x10909660 to reallocate the data. The class, member and method names are
// invented; the offsets, the size and the addresses are the binary's.

class UnkType_1090ba70_00d670
{
public:
    ~UnkType_1090ba70_00d670();

private:
    unsigned char unk_00[0xc];
};

class UnkType_1090d670
{
public:
    void Unk_1090d670(int Slack);
    void Unk_10909660(int ElementSize);

private:
    UnkType_1090ba70_00d670* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_1090d670::Unk_1090d670
void UnkType_1090d670::Unk_1090d670(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_1090ba70_00d670();
    }
    unk_04 = 0;
    unk_08 = Slack;
    Unk_10909660(sizeof(UnkType_1090ba70_00d670));
}
