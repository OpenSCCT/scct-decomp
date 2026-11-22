// campaign_leaf_3dbd90.cpp -- a member function at VA 0x10cdbd90 that passes a reference to its
// this pointer to the member at VA 0x10cd9e20 of the global object at VA 0x113120a8. guess: adds
// the object to a global list. The class, method and global names are invented; the addresses are
// the binary's.

class UnkType_10cdbd90;

class UnkType_10cd9e20
{
public:
    void Unk_10cd9e20(UnkType_10cdbd90* const& Item);
};

extern UnkType_10cd9e20 GUnk_113120a8;

class UnkType_10cdbd90
{
public:
    void Unk_10cdbd90();
};

// UnkType_10cdbd90::Unk_10cdbd90
void UnkType_10cdbd90::Unk_10cdbd90()
{
    GUnk_113120a8.Unk_10cd9e20(this);
}
