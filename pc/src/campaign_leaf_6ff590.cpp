// campaign_leaf_6ff590.cpp -- thiscall method at VA 0x10fff590 taking a target: calls the method at
// VA 0x10e0f570 with it, then appends each of the 16-byte values from 0x10 (as many as the count
// at 0x0c) to the array at 0x04 of the target, growing it through the cdecl function at VA
// 0x10dfc430 when full. The length of the value array is not known. The type, method and member
// names are invented; the offsets and addresses are the binary's.

struct UnkType_10fff590_Value
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;

    UnkType_10fff590_Value& operator=(const UnkType_10fff590_Value& Other)
    {
        unk_0 = Other.unk_0;
        unk_4 = Other.unk_4;
        unk_8 = Other.unk_8;
        unk_c = Other.unk_c;
        return *this;
    }
};

struct UnkType_10fff590_Array;

void __cdecl Unk_10dfc430(UnkType_10fff590_Array* Array, int ElementSize);

struct UnkType_10fff590_Array
{
    UnkType_10fff590_Value* unk_0;
    int unk_4;
    int unk_8;

    // UnkType_10fff590_Array::Add
    // guess: appends one value, growing the storage through VA 0x10dfc430 when it is full.
    void Add(const UnkType_10fff590_Value& Value)
    {
        if ( unk_4 == ( unk_8 & 0x7fffffff ) )
        {
            Unk_10dfc430(this, sizeof(UnkType_10fff590_Value));
        }
        UnkType_10fff590_Value* Element = &unk_0[unk_4++];

        *Element = Value;
    }
};

struct UnkType_10fff590_Target
{
    int unk_0;
    UnkType_10fff590_Array unk_4;
};

class UnkType_10fff590
{
public:
    void Unk_10fff590(UnkType_10fff590_Target* Target);
    void Unk_10e0f570(UnkType_10fff590_Target* Target);

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    UnkType_10fff590_Value unk_10[1];
};

// UnkType_10fff590::Unk_10fff590
void UnkType_10fff590::Unk_10fff590(UnkType_10fff590_Target* Target)
{
    int i;

    Unk_10e0f570(Target);
    for ( i = 0; i < unk_0c; i++ )
    {
        Target->unk_4.Add(unk_10[i]);
    }
}
