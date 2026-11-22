// campaign_leaf_1a4800.cpp -- free function at VA 0x10aa4800: calls the method at VA 0x10b068e0 on
// the object the global at VA 0x111fa6dc points to, with its two arguments, and returns nothing. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_111fa6dc
{
public:
    void Unk_10b068e0(int, int);
};

extern UnkType_111fa6dc* GUnk_111fa6dc;

// Unk_10aa4800
void Unk_10aa4800(int Arg0, int Arg1)
{
    GUnk_111fa6dc->Unk_10b068e0(Arg0, Arg1);
}
