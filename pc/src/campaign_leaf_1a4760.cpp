// campaign_leaf_1a4760.cpp -- free function at VA 0x10aa4760: calls the method at VA 0x10b06840 on
// the object the global at VA 0x111fa6dc points to, with its two arguments, and returns nothing. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_111fa6dc
{
public:
    void Unk_10b06840(int, int);
};

extern UnkType_111fa6dc* GUnk_111fa6dc;

// Unk_10aa4760
void Unk_10aa4760(int Arg0, int Arg1)
{
    GUnk_111fa6dc->Unk_10b06840(Arg0, Arg1);
}
