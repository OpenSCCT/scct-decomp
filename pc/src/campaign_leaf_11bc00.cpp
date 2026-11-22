// campaign_leaf_11bc00.cpp -- method at VA 0x10a1bc00: passes this object, by reference, to the
// method at VA 0x1096f1e0 of the object its argument points to (that method searches an array of
// pointers for the referenced value) and returns its result. The class and method names are
// invented; the addresses are the binary's.

class UnkType_10a1bc00;

class UnkType_10a1bc00_1096f1e0
{
public:
    int Unk_1096f1e0(UnkType_10a1bc00* const& Item);
};

class UnkType_10a1bc00
{
public:
    int Unk_10a1bc00(UnkType_10a1bc00_1096f1e0* Array);
};

// UnkType_10a1bc00::Unk_10a1bc00
int UnkType_10a1bc00::Unk_10a1bc00(UnkType_10a1bc00_1096f1e0* Array)
{
    return Array->Unk_1096f1e0(this);
}
