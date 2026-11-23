// campaign_leaf_4f7340.cpp -- method at VA 0x10df7340: once the slot count at VA 0x111ca7c8 is set
// (the function at VA 0x10974200 sets it when it is still -1), allocates an array of that many
// words (functions at VA 0x10d8b460 and 0x10d8b4e0, tagged with the file name
// "src\\Core/PseudoGlobalVariable.h" and line 119), stores it at 0x08 and fills every slot with the
// value at 0x10. The class, method and member names are invented; the strings, the offsets and the
// addresses are the binary's.

#include "campaign_global_111ca7c8.h"

inline void* operator new(unsigned int Size, void* Where)
{
    return Where;
}

void Unk_10974200(int Value);
void* Unk_10d8b460(unsigned int Size, const unsigned short* File, int Line, int Tag);
void* Unk_10d8b4e0(void* Data);

class UnkType_10df7340
{
public:
    void Unk_10df7340();

    unsigned char unk_00[0x08];
    int* unk_08;
    unsigned char unk_0c[0x04];
    int unk_10;
};

// UnkType_10df7340::Unk_10df7340
void UnkType_10df7340::Unk_10df7340()
{
    if ( GUnk_111ca7c8 == (unsigned int)-1 )
    {
        Unk_10974200(-4);
    }
    unsigned int Size = GUnk_111ca7c8 * sizeof(int);
    unk_08 = (int*)Unk_10d8b4e0(Unk_10d8b460(Size, L"../../.././src\\Core/PseudoGlobalVariable.h",
                                             119, 10));
    for ( unsigned int i = 0; i < GUnk_111ca7c8; i++ )
    {
        new (&unk_08[i]) int(unk_10);
    }
}
