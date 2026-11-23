// campaign_leaf_6fe8f0.cpp -- thiscall method at VA 0x10ffe8f0 of an array of 48-byte elements (data at
// 0x00, count at 0x04, capacity in the low 31 bits of 0x08): when the array is full, calls the cdecl
// function at VA 0x10dfc430 with the array and the element size, then returns the address of the
// next element and increments the count. The type, method and member names are invented; the
// offsets and addresses are the binary's.

struct UnkType_10ffe8f0_Element
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
};

class UnkType_10ffe8f0;

void __cdecl Unk_10dfc430(UnkType_10ffe8f0* Array, int ElementSize);

class UnkType_10ffe8f0
{
public:
    UnkType_10ffe8f0_Element* Unk_10ffe8f0();

private:
    UnkType_10ffe8f0_Element* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10ffe8f0::Unk_10ffe8f0
UnkType_10ffe8f0_Element* UnkType_10ffe8f0::Unk_10ffe8f0()
{
    if ( unk_4 == ( unk_8 & 0x7fffffff ) )
    {
        Unk_10dfc430(this, sizeof(UnkType_10ffe8f0_Element));
    }
    return &unk_0[unk_4++];
}
