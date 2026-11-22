// campaign_leaf_370910.cpp -- a member function at VA 0x10c70910 that passes the address of its
// member at 0xe8 to the member at VA 0x10929980 of the object its first argument points to. The
// class, method and member names are invented; the offsets and addresses are the binary's.

class UnkType_10929980
{
public:
    void Unk_10929980(void* Data);
};

class UnkType_10c70910
{
public:
    void Unk_10c70910(UnkType_10929980* Target);

private:
    unsigned char unk_000[0xe8];
    int unk_e8;
};

// UnkType_10c70910::Unk_10c70910
void UnkType_10c70910::Unk_10c70910(UnkType_10929980* Target)
{
    Target->Unk_10929980(&unk_e8);
}
