// campaign_leaf_11bbe0.cpp -- method at VA 0x10a1bbe0: passes this object, by reference, to the
// method at VA 0x1096f1e0 of the object its argument points to (that method searches an array of
// pointers for the referenced value) and returns its result. The class and method names are
// invented; the addresses are the binary's.

class UnkType_10a1bbe0;

class UnkType_1096f1e0
{
public:
    int Unk_1096f1e0(UnkType_10a1bbe0* const& Item);
};

class UnkType_10a1bbe0
{
public:
    int Unk_10a1bbe0(UnkType_1096f1e0* Array);
};

// UnkType_10a1bbe0::Unk_10a1bbe0
int UnkType_10a1bbe0::Unk_10a1bbe0(UnkType_1096f1e0* Array)
{
    return Array->Unk_1096f1e0(this);
}
