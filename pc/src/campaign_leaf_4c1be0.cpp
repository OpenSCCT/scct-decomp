// campaign_leaf_4c1be0.cpp -- one function at file offset 0x4c1be0, preferred VA 0x10dc1be0.
// It passes the ints at offsets 0 and 4 to the method at 0x10d9e850 of Target; the other three
// arguments are unused. The class, method and parameter names are invented; the offset and the
// bytes are the binary's.

class UnkType_10dc1be0_Target
{
public:
    void Unk_10d9e850(int Value);
};

class UnkType_10dc1be0
{
public:
    int unk_0;
    int unk_4;

    void Unk_10dc1be0(UnkType_10dc1be0_Target* Target, int Unused1, int Unused2, int Unused3);
};

// UnkType_10dc1be0::Unk_10dc1be0
void UnkType_10dc1be0::Unk_10dc1be0(UnkType_10dc1be0_Target* Target, int Unused1, int Unused2,
                                    int Unused3)
{
    Target->Unk_10d9e850(unk_0);
    Target->Unk_10d9e850(unk_4);
}
