// campaign_leaf_64ba00.cpp -- cdecl function at VA 0x10f4ba00: ignores its first argument and
// passes the other two to the cdecl function at VA 0x109743f0. All names are invented.

int Unk_109743f0(int First, int Second);

// Unk_10f4ba00
int Unk_10f4ba00(int Unused, int First, int Second)
{
    return Unk_109743f0(First, Second);
}
