// campaign_leaf_06f1e0.cpp -- method at VA 0x1096f1e0: returns the index of the first value in the
// array at 0x00 (count at 0x04) equal to the one its argument refers to; when there is none, adds
// one element of four bytes through the method at VA 0x1096f220, stores the value there and returns
// its index. The class, member and method names are invented; the offsets, the size and the address
// are the binary's.

class UnkType_1096f1e0
{
public:
    int Unk_1096f1e0(const int& Item);
    int Unk_1096f220(int Count, int ElementSize);

private:
    int* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_1096f1e0::Unk_1096f1e0
int UnkType_1096f1e0::Unk_1096f1e0(const int& Item)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        if ( unk_00[i] == Item )
        {
            return i;
        }
    }
    int Index = Unk_1096f220(1, sizeof(int));
    unk_00[Index] = Item;
    return Index;
}
