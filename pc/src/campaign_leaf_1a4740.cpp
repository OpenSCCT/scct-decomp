// campaign_leaf_1a4740.cpp -- free function at VA 0x10aa4740: calls the method at VA 0x10b06820 on
// the object the global at VA 0x111fa6dc points to, with its two arguments, and returns nothing. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_111fa6dc
{
public:
    void Unk_10b06820(int, int);
};

extern UnkType_111fa6dc* GUnk_111fa6dc;

// Unk_10aa4740
void Unk_10aa4740(int Arg0, int Arg1)
{
    GUnk_111fa6dc->Unk_10b06820(Arg0, Arg1);
}
