// campaign_leaf_1a4a10.cpp -- free function at VA 0x10aa4a10: calls the method at VA 0x10b06f00 on
// the object the global at VA 0x111fa6dc points to, with its one argument, and returns whether its byte result is nonzero. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_111fa6dc
{
public:
    unsigned char Unk_10b06f00(int);
};

extern UnkType_111fa6dc* GUnk_111fa6dc;

// Unk_10aa4a10
bool Unk_10aa4a10(int Arg0)
{
    return GUnk_111fa6dc->Unk_10b06f00(Arg0);
}
