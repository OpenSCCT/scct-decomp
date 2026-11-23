// campaign_leaf_222890.cpp -- a member function at VA 0x10b22890 of an iterator over an array of
// 4-byte elements: it removes the element at the current index (the later elements move down with
// the free function at VA 0x10ccad30, and the block shrinks to the new count through virtual slot
// 1 of the allocator the global at VA 0x111c88a0 points to, tagged L"FArray::INT", when enough of
// it is unused) and steps the index back by one. guess: removes the current element. The class,
// method and member names are invented; the offsets, addresses, string and slot are the binary's.

#include "campaign_global_111c88a0.h"

void __cdecl Unk_10ccad30(void* Dest, const void* Source, int Count);

class UnkType_10b22890_Array
{
public:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b22890
{
public:
    void Unk_10b22890();

private:
    UnkType_10b22890_Array* unk_00;
    int unk_04;
};

// UnkType_10b22890::Unk_10b22890
void UnkType_10b22890::Unk_10b22890()
{
    UnkType_10b22890_Array* Array = unk_00;
    int Index = unk_04--;
    Unk_10ccad30((int*)Array->unk_00 + Index, (int*)Array->unk_00 + Index + 1,
                 ( Array->unk_04 - Index - 1 ) * 4);
    Array->unk_04--;
    if ( ( 3 * Array->unk_04 < 2 * Array->unk_08
           || ( Array->unk_08 - Array->unk_04 ) * 4 >= 0x4000 )
         &&( Array->unk_08 - Array->unk_04 > 64 || Array->unk_04 == 0 ) )
    {
        Array->unk_08 = Array->unk_04;
        Array->unk_00 = GUnk_111c88a0->Realloc(Array->unk_00, Array->unk_08 * 4,
                                                    L"FArray::INT");
    }
}
