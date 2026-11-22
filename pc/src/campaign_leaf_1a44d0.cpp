// campaign_leaf_1a44d0.cpp -- free function at VA 0x10aa44d0: calls the method at VA 0x10b06250 on
// the object the global at VA 0x111fa6dc points to, with its two arguments, and returns nothing. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_111fa6dc
{
public:
    void Unk_10b06250(int, int);
};

extern UnkType_111fa6dc* GUnk_111fa6dc;

// Unk_10aa44d0
void Unk_10aa44d0(int Arg0, int Arg1)
{
    GUnk_111fa6dc->Unk_10b06250(Arg0, Arg1);
}
