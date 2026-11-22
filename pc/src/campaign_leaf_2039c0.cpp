// campaign_leaf_2039c0.cpp -- free function at VA 0x10b039c0: calls the method at VA 0x10d9e850 on
// the object its first argument points to, passing the value at 0x04 of the object its second
// argument points to. The class, member and function names are invented; the offsets and the
// addresses are the binary's.

class UnkType_10d9e850
{
public:
    void Unk_10d9e850(int Value);
};

class UnkType_10b039c0
{
public:
    int unk_00;
    int unk_04;
};

// Unk_10b039c0
void Unk_10b039c0(UnkType_10d9e850* Target, UnkType_10b039c0* Source)
{
    Target->Unk_10d9e850(Source->unk_04);
}
