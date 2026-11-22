// campaign_leaf_64df90.cpp -- free function at VA 0x10f4df90: calls the cdecl function at
// VA 0x10f4ba00 with its first argument, then its third, then its second. All names are invented.

void Unk_10f4ba00(int First, int Second, int Third);

// Unk_10f4df90
void Unk_10f4df90(int First, int Second, int Third)
{
    Unk_10f4ba00(First, Third, Second);
}
