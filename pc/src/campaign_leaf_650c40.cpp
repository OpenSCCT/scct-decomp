// campaign_leaf_650c40.cpp -- stdcall function at VA 0x10f50c40 taking two structures of the same
// shape (values at 0x00 and 0x04, a count at 0x08, an array of pointers from 0x0c): for every index
// below the first's count, passes the first value of each structure's element, then its values at
// 0x04 and 0x00, to the function at VA 0x10f57b80. The array's length is not known. The type,
// function and member names are invented; the offsets and addresses are the binary's.

struct UnkType_10f50c40_Element
{
    int unk_0;
};

struct UnkType_10f50c40
{
    int unk_0;
    int unk_4;
    int unk_8;
    UnkType_10f50c40_Element* unk_c[1];
};

void __cdecl Unk_10f57b80(int First, int Second, int Third, int Fourth, int Fifth, int Sixth);

// Unk_10f50c40
void __stdcall Unk_10f50c40(UnkType_10f50c40* Target, UnkType_10f50c40* Source)
{
    int i;

    for ( i = 0; i < Target->unk_8; i++ )
    {
        Unk_10f57b80(Target->unk_c[i]->unk_0, Target->unk_4, Target->unk_0,
                     Source->unk_c[i]->unk_0, Source->unk_4, Source->unk_0);
    }
}
