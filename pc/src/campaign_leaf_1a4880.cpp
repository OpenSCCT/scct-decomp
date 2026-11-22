// campaign_leaf_1a4880.cpp -- free function at VA 0x10aa4880: calls the method at VA 0x10b0a010 on
// the object the global at VA 0x111fa6dc points to, with its one argument, and returns nothing. The class, method
// and function names are invented; the addresses are the binary's.

class UnkType_111fa6dc
{
public:
    void Unk_10b0a010(int);
};

extern UnkType_111fa6dc* GUnk_111fa6dc;

// Unk_10aa4880
void Unk_10aa4880(int Arg0)
{
    GUnk_111fa6dc->Unk_10b0a010(Arg0);
}
