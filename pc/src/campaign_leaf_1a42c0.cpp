// campaign_leaf_1a42c0.cpp -- free function at VA 0x10aa42c0: passes the character data at 0x2416
// in the object the global at VA 0x111fa6dc points to to the free function at VA 0x10cccd30, and
// returns its result. The class, member and function names are invented; the offsets and the
// addresses are the binary's.

class UnkType_111fa6dc
{
public:
    char unk_0000[0x2416];
    char unk_2416[1];
};

extern UnkType_111fa6dc* GUnk_111fa6dc;

int Unk_10cccd30(char* Text);

// Unk_10aa42c0
int Unk_10aa42c0()
{
    return Unk_10cccd30(GUnk_111fa6dc->unk_2416);
}
