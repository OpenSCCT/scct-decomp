// campaign_leaf_1a4450.cpp -- free function at VA 0x10aa4450: calls the method at VA 0x10b08f60 on
// the object the global at VA 0x111fa6dc points to, with its two arguments, and returns nothing. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_111fa6dc
{
public:
    void Unk_10b08f60(int, int);
};

extern UnkType_111fa6dc* GUnk_111fa6dc;

// Unk_10aa4450
void Unk_10aa4450(int Arg0, int Arg1)
{
    GUnk_111fa6dc->Unk_10b08f60(Arg0, Arg1);
}
