// campaign_leaf_75be80.cpp -- one function at file offset 0x75be80, preferred VA 0x1105be80. It
// calls the method at VA 0x1105af50; then, when the word at 0x4 is not 0x13 and the word at 0x1c
// is set, it stores 4 at 0x4 and calls the method at VA 0x1105bdd0. The class, method and member
// names are invented; the offsets and the addresses are the binary's.

class UnkType_1105be80
{
public:
    void Unk_1105af50();
    void Unk_1105bdd0();
    void Unk_1105be80();

    int unk_0;
    int unk_4;
    unsigned char unk_8[0x1c - 0x8];
    int unk_1c;
};

// UnkType_1105be80::Unk_1105be80
void UnkType_1105be80::Unk_1105be80()
{
    Unk_1105af50();
    if ( unk_4 != 0x13 && unk_1c != 0 )
    {
        unk_4 = 4;
        Unk_1105bdd0();
    }
}
