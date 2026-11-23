// campaign_leaf_015cb0.cpp -- method at VA 0x10915cb0: removes every value in the array at 0x00
// (count at 0x04) equal to the one its argument refers to, one four-byte element at a time through
// the method at VA 0x10915cf0, and returns how many it removed. The class, member and method names
// are invented; the offsets, the size and the address are the binary's.

class UnkType_10915cb0
{
public:
    int Unk_10915cb0(const int& Item);
    void Unk_10915cf0(int Index, int Count, int ElementSize);

private:
    int* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10915cb0::Unk_10915cb0
int UnkType_10915cb0::Unk_10915cb0(const int& Item)
{
    int OriginalCount = unk_04;
    for ( int i = 0; i < unk_04; i++ )
    {
        if ( unk_00[i] == Item )
        {
            Unk_10915cf0(i--, 1, sizeof(int));
        }
    }
    return OriginalCount - unk_04;
}
