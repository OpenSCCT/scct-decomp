// campaign_leaf_10f320.cpp -- method at VA 0x10a0f320: finds the element of an owner's pointer
// vector whose member at 0x04 equals an identifier, deletes it, erases it from the vector and
// returns true; returns false when the owner is null or no element has the identifier. It never
// reads its this pointer. The class, member and method names are invented; the offsets, the
// virtual destructor in slot 0 and the vector of the compiler's library are the binary's.

#include <vector>

class UnkType_10a0f320_Element
{
public:
    virtual ~UnkType_10a0f320_Element();

    int unk_04;
};

struct UnkType_10a0f320_Owner
{
    char unk_00[0x14];
    std::vector<UnkType_10a0f320_Element *> unk_14;
};

class UnkType_10a0f320
{
public:
    bool Unk_10a0f320(UnkType_10a0f320_Owner *Owner, const int &Id);
};

// UnkType_10a0f320::Unk_10a0f320
bool UnkType_10a0f320::Unk_10a0f320(UnkType_10a0f320_Owner *Owner, const int &Id)
{
    std::vector<UnkType_10a0f320_Element *>::iterator It;

    if ( Owner == NULL )
    {
        return false;
    }
    for ( It = Owner->unk_14.begin(); It != Owner->unk_14.end(); ++It )
    {
        if ( (*It)->unk_04 == Id )
        {
            delete *It;
            Owner->unk_14.erase(It);
            return true;
        }
    }
    return false;
}
