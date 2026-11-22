// campaign_leaf_5eb7a0.cpp -- stdcall function at VA 0x10eeb7a0: passes its three arguments to the
// stdcall function at VA 0x10eec280 and returns the low byte of its result. All names are
// invented.

int __stdcall Unk_10eec280(int First, int Second, int Third);

// Unk_10eeb7a0
int __stdcall Unk_10eeb7a0(int First, int Second, int Third)
{
    return Unk_10eec280(First, Second, Third) & 0xff;
}
