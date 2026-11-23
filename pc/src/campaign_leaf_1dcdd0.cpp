// campaign_leaf_1dcdd0.cpp -- thiscall method at VA 0x10adcdd0. It deletes every object the
// pointer list at 0x08 holds (through each object's virtual slot 0 with 1), then empties the list.
// The class, method and member names are invented; the list is the compiler's library.

#include <list>

class UnkType_10adcdd0_Item
{
public:
    virtual ~UnkType_10adcdd0_Item();
};

class UnkType_10adcdd0
{
public:
    void Unk_10adcdd0();

private:
    char unk_00[8];
    std::list<UnkType_10adcdd0_Item*> unk_08;
};

// UnkType_10adcdd0::Unk_10adcdd0
void UnkType_10adcdd0::Unk_10adcdd0()
{
    std::list<UnkType_10adcdd0_Item*>::iterator It;

    for ( It = unk_08.begin(); It != unk_08.end(); ++It )
    {
        delete *It;
    }
    unk_08.clear();
}
