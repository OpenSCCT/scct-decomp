// campaign_leaf_35d9e0.cpp -- a member function at VA 0x10c5d9e0 that passes the address of its
// member at 0x3fc to the member at VA 0x10ab5970 of the object its first argument points to. It
// does not read its second argument. The class, method and member names are invented; the offsets
// and addresses are the binary's.

class UnkType_10ab5970
{
public:
    void Unk_10ab5970(void* Data);
};

class UnkType_10c5d9e0
{
public:
    void Unk_10c5d9e0(UnkType_10ab5970* Target, int Unused);

private:
    unsigned char unk_000[0x3fc];
    int unk_3fc;
};

// UnkType_10c5d9e0::Unk_10c5d9e0
void UnkType_10c5d9e0::Unk_10c5d9e0(UnkType_10ab5970* Target, int Unused)
{
    Target->Unk_10ab5970(&unk_3fc);
}
