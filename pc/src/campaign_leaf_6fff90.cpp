// campaign_leaf_6fff90.cpp -- thiscall method at VA 0x10ffff90 taking a target: calls the method at
// VA 0x10e0f570 with it, then for each of the 32-byte pairs the pointer at 0x10 addresses (count at
// 0x14) appends both 16-byte halves to the array at 0x04 of the target, growing it through the
// cdecl function at VA 0x10dfc430 when full. The type, method and member names are invented; the
// offsets and addresses are the binary's.

struct UnkType_10ffff90_Value
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;

    UnkType_10ffff90_Value& operator=(const UnkType_10ffff90_Value& Other)
    {
        unk_0 = Other.unk_0;
        unk_4 = Other.unk_4;
        unk_8 = Other.unk_8;
        unk_c = Other.unk_c;
        return *this;
    }
};

struct UnkType_10ffff90_Array;

void __cdecl Unk_10dfc430(UnkType_10ffff90_Array* Array, int ElementSize);

struct UnkType_10ffff90_Array
{
    UnkType_10ffff90_Value* unk_0;
    int unk_4;
    int unk_8;

    // UnkType_10ffff90_Array::Add
    // guess: appends one value, growing the storage through VA 0x10dfc430 when it is full.
    void Add(const UnkType_10ffff90_Value& Value)
    {
        if ( unk_4 == ( unk_8 & 0x7fffffff ) )
        {
            Unk_10dfc430(this, sizeof(UnkType_10ffff90_Value));
        }
        UnkType_10ffff90_Value* Element = &unk_0[unk_4++];

        *Element = Value;
    }
};

struct UnkType_10ffff90_Target
{
    int unk_0;
    UnkType_10ffff90_Array unk_4;
};

struct UnkType_10ffff90_Pair
{
    UnkType_10ffff90_Value unk_00;
    UnkType_10ffff90_Value unk_10;
};

class UnkType_10ffff90
{
public:
    void Unk_10ffff90(UnkType_10ffff90_Target* Target);
    void Unk_10e0f570(UnkType_10ffff90_Target* Target);

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    UnkType_10ffff90_Pair* unk_10;
    int unk_14;
};

// UnkType_10ffff90::Unk_10ffff90
void UnkType_10ffff90::Unk_10ffff90(UnkType_10ffff90_Target* Target)
{
    int Count;
    int i;

    Unk_10e0f570(Target);
    Count = unk_14;
    for ( i = 0; i < Count; i++ )
    {
        Target->unk_4.Add(unk_10[i].unk_00);
        Target->unk_4.Add(unk_10[i].unk_10);
    }
}
