// campaign_leaf_1a4780.cpp -- free function at VA 0x10aa4780: calls the method at VA 0x10b06860 on
// the object the global at VA 0x111fa6dc points to, with its two arguments, and returns nothing. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_10aa4780_111fa6dc
{
public:
    void Unk_10b06860(int, int);
};

extern UnkType_10aa4780_111fa6dc* GUnk_111fa6dc;

// Unk_10aa4780
void Unk_10aa4780(int Arg0, int Arg1)
{
    GUnk_111fa6dc->Unk_10b06860(Arg0, Arg1);
}
