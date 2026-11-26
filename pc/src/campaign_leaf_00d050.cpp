// campaign_leaf_00d050.cpp -- method at VA 0x1090d050: removes elements from an array of 0xc-byte
// elements (data at 0x00): destroys the elements from the index its first argument gives, as many
// as its second argument, with the destructor at VA 0x1090ba70, then passes both arguments and the
// element size to the method at VA 0x10909690. The class, member and method names are invented; the
// offsets, the size and the addresses are the binary's.
#include "campaign_array_type_1090d050.h"

class UnkType_1090ba70_00d050
{
public:
    ~UnkType_1090ba70_00d050();

private:
    unsigned char unk_00[0xc];
};

// UnkType_1090d050::Unk_1090d050
void UnkType_1090d050::Unk_1090d050(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_1090ba70_00d050();
    }
    Unk_10909690(Index, Count, sizeof(UnkType_1090ba70_00d050));
}
