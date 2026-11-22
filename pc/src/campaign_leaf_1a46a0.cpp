// campaign_leaf_1a46a0.cpp -- free function at VA 0x10aa46a0: calls the method at VA 0x10b066f0 on
// the object the global at VA 0x111fa6dc points to, with its one argument, and returns whether its byte result is nonzero. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_10aa46a0_111fa6dc
{
public:
    unsigned char Unk_10b066f0(int);
};

extern UnkType_10aa46a0_111fa6dc* GUnk_111fa6dc;

// Unk_10aa46a0
bool Unk_10aa46a0(int Arg0)
{
    return GUnk_111fa6dc->Unk_10b066f0(Arg0);
}
