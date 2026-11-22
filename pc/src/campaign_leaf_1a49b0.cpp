// campaign_leaf_1a49b0.cpp -- free function at VA 0x10aa49b0: calls the method at VA 0x10b06c20 on
// the object the global at VA 0x111fa6dc points to, with its one argument, and returns nothing. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_10aa49b0_111fa6dc
{
public:
    void Unk_10b06c20(int);
};

extern UnkType_10aa49b0_111fa6dc* GUnk_111fa6dc;

// Unk_10aa49b0
void Unk_10aa49b0(int Arg0)
{
    GUnk_111fa6dc->Unk_10b06c20(Arg0);
}
