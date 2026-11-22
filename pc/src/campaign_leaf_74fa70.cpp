// campaign_leaf_74fa70.cpp -- free function at VA 0x1104fa70: follows the pointer at 0x3c of its
// argument and passes that object's members at 0x14 and 0x00 to the stdcall function at
// VA 0x1104b1f0. All names are invented.

struct UnkType_1104fa70_3c
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
};

struct UnkType_1104fa70
{
    int unk_00[15];
    UnkType_1104fa70_3c* unk_3c;
};

void __stdcall Unk_1104b1f0(int First, int Second);

// Unk_1104fa70
void Unk_1104fa70(UnkType_1104fa70* Object)
{
    Unk_1104b1f0(Object->unk_3c->unk_14, Object->unk_3c->unk_00);
}
