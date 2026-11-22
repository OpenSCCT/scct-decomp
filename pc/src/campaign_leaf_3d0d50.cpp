// campaign_leaf_3d0d50.cpp -- a free function at VA 0x10cd0d50 that returns one more than the
// function at VA 0x10f32740 returns for its argument, or 1 when the argument is null. guess: the
// length of a string with its terminator. The function names are invented; the addresses are the
// binary's.

int Unk_10f32740(const char* Text);

// Unk_10cd0d50
int Unk_10cd0d50(const char* Text)
{
    if ( Text )
    {
        return Unk_10f32740(Text) + 1;
    }
    return 1;
}
