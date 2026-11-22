// campaign_leaf_1a45e0.cpp -- free function at VA 0x10aa45e0: calls the method at VA 0x10b06270 on
// the object the global at VA 0x111fa6dc points to, with its two arguments, and returns nothing. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_10aa45e0_111fa6dc
{
public:
    void Unk_10b06270(int, int);
};

extern UnkType_10aa45e0_111fa6dc* GUnk_111fa6dc;

// Unk_10aa45e0
void Unk_10aa45e0(int Arg0, int Arg1)
{
    GUnk_111fa6dc->Unk_10b06270(Arg0, Arg1);
}
