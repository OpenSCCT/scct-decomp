// campaign_leaf_74b9c0.cpp -- one function at file offset 0x74b9c0, preferred VA 0x1104b9c0. It
// seeds a generator with the current time: it passes the result of the runtime's time(0) (VA
// 0x10f34495, named in library-functions.tsv) to the runtime function at VA 0x10f31b54, which
// stores its argument in the per-thread data (srand's shape; not named by the evidence list). The
// function names other than time are invented; the offset and the addresses are the binary's.

extern "C" long __cdecl time(long* Timer);
extern "C" void __cdecl Unk_10f31b54(unsigned int Seed);

// Unk_1104b9c0
void Unk_1104b9c0()
{
    Unk_10f31b54(time(0));
}
