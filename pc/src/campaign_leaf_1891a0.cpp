// campaign_leaf_1891a0.cpp -- method at VA 0x10a891a0: calls the method at VA 0x10929980 on the
// object its argument points to, passing the address of offset 0xe8 in this object. The class,
// member and method names are invented; the offsets and the addresses are the binary's.

class UnkType_10929980
{
public:
    void Unk_10929980(int* Value);
};

class UnkType_10a891a0
{
public:
    void Unk_10a891a0(UnkType_10929980* Target);

private:
    unsigned char unk_00[0xe8];
    int unk_e8;
};

// UnkType_10a891a0::Unk_10a891a0
void UnkType_10a891a0::Unk_10a891a0(UnkType_10929980* Target)
{
    Target->Unk_10929980(&unk_e8);
}
