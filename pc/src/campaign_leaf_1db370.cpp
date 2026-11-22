// campaign_leaf_1db370.cpp -- free function at VA 0x10adb370: if the flag at VA 0x1120b700 is set,
// calls the free function at VA 0x10d38ec0; then clears the flag. The function and global names are
// invented; the addresses are the binary's.

extern bool GUnk_1120b700;

void Unk_10d38ec0();

// Unk_10adb370
void Unk_10adb370()
{
    if ( GUnk_1120b700 )
    {
        Unk_10d38ec0();
    }
    GUnk_1120b700 = false;
}
