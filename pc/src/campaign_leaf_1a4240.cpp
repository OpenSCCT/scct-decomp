// campaign_leaf_1a4240.cpp -- free function at VA 0x10aa4240: calls the method at VA 0x10b06080 on
// the object the global at VA 0x111fa6dc points to, with its one argument, and returns nothing. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_10aa4240_111fa6dc
{
public:
    void Unk_10b06080(int);
};

extern UnkType_10aa4240_111fa6dc* GUnk_111fa6dc;

// Unk_10aa4240
void Unk_10aa4240(int Arg0)
{
    GUnk_111fa6dc->Unk_10b06080(Arg0);
}
