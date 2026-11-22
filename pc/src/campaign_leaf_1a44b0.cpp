// campaign_leaf_1a44b0.cpp -- free function at VA 0x10aa44b0: calls the method at VA 0x10b06230 on
// the object the global at VA 0x111fa6dc points to, with its two arguments, and returns nothing. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_10aa44b0_111fa6dc
{
public:
    void Unk_10b06230(int, int);
};

extern UnkType_10aa44b0_111fa6dc* GUnk_111fa6dc;

// Unk_10aa44b0
void Unk_10aa44b0(int Arg0, int Arg1)
{
    GUnk_111fa6dc->Unk_10b06230(Arg0, Arg1);
}
