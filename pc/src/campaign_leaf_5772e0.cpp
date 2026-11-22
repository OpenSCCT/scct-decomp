// campaign_leaf_5772e0.cpp -- free function at VA 0x10e772e0: passes the member at 0x0c of its
// argument and the argument itself to the cdecl function at VA 0x10e77070. All names are invented.

struct UnkType_10e772e0
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

void Unk_10e77070(int Value, UnkType_10e772e0* Object);

// Unk_10e772e0
void Unk_10e772e0(UnkType_10e772e0* Object)
{
    Unk_10e77070(Object->unk_0c, Object);
}
