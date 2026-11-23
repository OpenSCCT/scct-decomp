// campaign_leaf_6ffe70.cpp -- thiscall method at VA 0x10fffe70 of an array of 32-byte elements (data
// at 0x00, count at 0x04, capacity in the low 31 bits of 0x08): when the array is full, calls the
// cdecl function at VA 0x10dfc430 with the array and the element size, then copies its argument
// into the next element and increments the count. The type, method and member names are invented;
// the offsets and addresses are the binary's.

struct UnkType_10fffe70_Element
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;

    UnkType_10fffe70_Element& operator=(const UnkType_10fffe70_Element& Other)
    {
        unk_00 = Other.unk_00;
        unk_04 = Other.unk_04;
        unk_08 = Other.unk_08;
        unk_0c = Other.unk_0c;
        unk_10 = Other.unk_10;
        unk_14 = Other.unk_14;
        unk_18 = Other.unk_18;
        unk_1c = Other.unk_1c;
        return *this;
    }
};

class UnkType_10fffe70;

void __cdecl Unk_10dfc430(UnkType_10fffe70* Array, int ElementSize);

class UnkType_10fffe70
{
public:
    void Unk_10fffe70(const UnkType_10fffe70_Element& Element);

private:
    UnkType_10fffe70_Element* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10fffe70::Unk_10fffe70
void UnkType_10fffe70::Unk_10fffe70(const UnkType_10fffe70_Element& Element)
{
    UnkType_10fffe70_Element* Slot;

    if ( unk_4 == ( unk_8 & 0x7fffffff ) )
    {
        Unk_10dfc430(this, sizeof(UnkType_10fffe70_Element));
    }
    Slot = &unk_0[unk_4++];
    *Slot = Element;
}
