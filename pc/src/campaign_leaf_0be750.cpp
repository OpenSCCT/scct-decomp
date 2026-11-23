// campaign_leaf_0be750.cpp -- method at VA 0x109be750 of a dynamic array of 3-float vectors (data
// pointer at 0x00, count at 0x04) taking a vector: returns the index of the first element equal to
// it; otherwise raises the count, calls the method at VA 0x10ccb3c0 with the element size, stores
// the vector in the new last element and returns its index. guess: an instance of the engine's
// TArray<FVector>::AddUniqueItem. The class, member and method names are invented; the offsets and
// the address are the binary's.

struct UnkType_109be750_Vector
{
    int operator==(const UnkType_109be750_Vector& Other) const
    {
        return unk_00 == Other.unk_00 && unk_04 == Other.unk_04 && unk_08 == Other.unk_08;
    }

    float unk_00;
    float unk_04;
    float unk_08;
};

class UnkType_109be750
{
public:
    int Unk_109be750(const UnkType_109be750_Vector& Item);
    void Unk_10ccb3c0(int ElementSize);

private:
    int Add()
    {
        int Index = unk_04;
        unk_04++;
        Unk_10ccb3c0(sizeof(UnkType_109be750_Vector));
        return Index;
    }

    UnkType_109be750_Vector* unk_00;
    int unk_04;
};

// UnkType_109be750::Unk_109be750
int UnkType_109be750::Unk_109be750(const UnkType_109be750_Vector& Item)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        if ( unk_00[i] == Item )
        {
            return i;
        }
    }
    int Index = Add();
    unk_00[Index] = Item;
    return Index;
}
