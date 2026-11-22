// campaign_leaf_74b9c0.cpp -- free function at VA 0x1104b9c0: passes the C runtime time(0)
// (VA 0x10f34495, named in pc/evidence/library-functions.tsv) to the cdecl function at
// VA 0x10f31b54. guess: srand(time(0)). The function names other than time are invented.

typedef long time_t;
extern "C" time_t __cdecl time(time_t* Timer);
void Unk_10f31b54(unsigned int Seed);

// Unk_1104b9c0
void Unk_1104b9c0()
{
    Unk_10f31b54(time(0));
}
