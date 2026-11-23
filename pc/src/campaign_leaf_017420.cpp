// campaign_leaf_017420.cpp -- method at VA 0x10917420: returns the index of the first value in the
// array at 0x00 (count at 0x04) equal to the one its argument refers to; when there is none, adds
// one element of four bytes through the method at VA 0x10917460, stores the value there and returns
// its index. The class, member and method names are invented; the offsets, the size and the address
// are the binary's.

class UnkType_10917420
{
public:
    int Unk_10917420(const int& Item);
    int Unk_10917460(int Count, int ElementSize);

private:
    int* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10917420::Unk_10917420
int UnkType_10917420::Unk_10917420(const int& Item)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        if ( unk_00[i] == Item )
        {
            return i;
        }
    }
    int Index = Unk_10917460(1, sizeof(int));
    unk_00[Index] = Item;
    return Index;
}
