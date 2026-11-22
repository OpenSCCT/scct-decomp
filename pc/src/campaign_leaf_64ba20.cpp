// campaign_leaf_64ba20.cpp -- cdecl function at VA 0x10f4ba20: ignores its first argument and passes the
// other two to the cdecl function at VA 0x10974400. All names are invented.

int Unk_10974400(int First, int Second);

// Unk_10f4ba20
int Unk_10f4ba20(int Unused, int First, int Second)
{
    return Unk_10974400(First, Second);
}
