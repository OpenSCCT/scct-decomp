// campaign_leaf_747230.cpp -- free function at VA 0x11047230: calls the function at VA 0x11046a10,
// then clears the global at VA 0x1132bc5c. The function and global names are invented.

void Unk_11046a10();
extern int GUnk_1132bc5c;

// Unk_11047230
void Unk_11047230()
{
    Unk_11046a10();
    GUnk_1132bc5c = 0;
}
