// campaign_leaf_1a4260.cpp -- free function at VA 0x10aa4260: calls the method at VA 0x10b060b0 on
// the object the global at VA 0x111fa6dc points to, with its one argument, and returns nothing. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_111fa6dc
{
public:
    void Unk_10b060b0(int);
};

extern UnkType_111fa6dc* GUnk_111fa6dc;

// Unk_10aa4260
void Unk_10aa4260(int Arg0)
{
    GUnk_111fa6dc->Unk_10b060b0(Arg0);
}
