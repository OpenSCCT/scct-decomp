// campaign_leaf_6f4430.cpp -- thiscall method at VA 0x10ff4430 of an array of 16-byte elements (data at
// 0x00, count at 0x04, capacity in the low 31 bits of 0x08): when the array is full, calls the cdecl
// function at VA 0x10dfc430 with the array and the element size, then returns the address of the
// next element and increments the count. The type, method and member names are invented; the
// offsets and addresses are the binary's.

struct UnkType_10ff4430_Element
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

class UnkType_10ff4430;

void __cdecl Unk_10dfc430(UnkType_10ff4430* Array, int ElementSize);

class UnkType_10ff4430
{
public:
    UnkType_10ff4430_Element* Unk_10ff4430();

private:
    UnkType_10ff4430_Element* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10ff4430::Unk_10ff4430
UnkType_10ff4430_Element* UnkType_10ff4430::Unk_10ff4430()
{
    if ( unk_4 == ( unk_8 & 0x7fffffff ) )
    {
        Unk_10dfc430(this, sizeof(UnkType_10ff4430_Element));
    }
    return &unk_0[unk_4++];
}
