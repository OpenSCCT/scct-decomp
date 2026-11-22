// campaign_leaf_3d19a0.cpp -- a free function at VA 0x10cd19a0 that stores the address of the
// function at VA 0x10cd1980 in the global at VA 0x111c8d40 and copies the global at VA 0x112d7160
// to the one at VA 0x112d716c. The names are invented; the addresses are the binary's.

void Unk_10cd1980();

extern void (*GUnk_111c8d40)();
extern int GUnk_112d7160;
extern int GUnk_112d716c;

// Unk_10cd19a0
void Unk_10cd19a0()
{
    GUnk_111c8d40 = Unk_10cd1980;
    GUnk_112d716c = GUnk_112d7160;
}
