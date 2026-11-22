// campaign_leaf_1a45c0.cpp -- free function at VA 0x10aa45c0: calls the method at VA 0x10b06410 on
// the object the global at VA 0x111fa6dc points to, with no arguments, and returns whether its byte result is nonzero. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_10aa45c0_111fa6dc
{
public:
    unsigned char Unk_10b06410();
};

extern UnkType_10aa45c0_111fa6dc* GUnk_111fa6dc;

// Unk_10aa45c0
bool Unk_10aa45c0()
{
    return GUnk_111fa6dc->Unk_10b06410();
}
