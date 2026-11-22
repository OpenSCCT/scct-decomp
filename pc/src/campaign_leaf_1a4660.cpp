// campaign_leaf_1a4660.cpp -- free function at VA 0x10aa4660: calls the method at VA 0x10b089d0 on
// the object the global at VA 0x111fa6dc points to, with no arguments, and returns whether its byte result is nonzero. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_111fa6dc
{
public:
    unsigned char Unk_10b089d0();
};

extern UnkType_111fa6dc* GUnk_111fa6dc;

// Unk_10aa4660
bool Unk_10aa4660()
{
    return GUnk_111fa6dc->Unk_10b089d0();
}
