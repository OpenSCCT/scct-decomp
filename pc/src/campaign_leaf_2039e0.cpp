// campaign_leaf_2039e0.cpp -- free function at VA 0x10b039e0: calls the method at VA 0x10d9df90 on
// the object its first argument points to, passing the address of offset 0x04 in the object its
// second argument points to. The class, member and function names are invented; the offsets and the
// addresses are the binary's.

class UnkType_10b039e0_10d9df90
{
public:
    void Unk_10d9df90(int* Value);
};

class UnkType_10b039e0
{
public:
    int unk_00;
    int unk_04;
};

// Unk_10b039e0
void Unk_10b039e0(UnkType_10b039e0_10d9df90* Target, UnkType_10b039e0* Source)
{
    Target->Unk_10d9df90(&Source->unk_04);
}
