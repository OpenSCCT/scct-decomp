// campaign_leaf_1a4020.cpp -- free function at VA 0x10aa4020: returns true when the global at VA
// 0x111fa6dc is null; otherwise calls the method at VA 0x10b05c70 on the object it points to and
// returns whether its byte result is nonzero. The class, method and function names are invented;
// the addresses are the binary's.

class UnkType_111fa6dc
{
public:
    unsigned char Unk_10b05c70();
};

extern UnkType_111fa6dc* GUnk_111fa6dc;

// Unk_10aa4020
bool Unk_10aa4020()
{
    if ( GUnk_111fa6dc )
    {
        return GUnk_111fa6dc->Unk_10b05c70();
    }
    return true;
}
