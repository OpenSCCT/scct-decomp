// campaign_leaf_4c1ae0.cpp -- one function at file offset 0x4c1ae0, preferred VA 0x10dc1ae0.
// It passes the unsigned short at offset 0 of the object to the method at
// 0x10d9e810 of Target; the other three arguments are unused. The class, method and parameter
// names are invented; the offset and the bytes are the binary's.

class UnkType_10d9e810
{
public:
    void Unk_10d9e810(unsigned short Value);
};

class UnkType_10dc1ae0
{
public:
    unsigned short unk_0;

    void Unk_10dc1ae0(UnkType_10d9e810* Target, int Unused1, int Unused2, int Unused3);
};

// UnkType_10dc1ae0::Unk_10dc1ae0
void UnkType_10dc1ae0::Unk_10dc1ae0(UnkType_10d9e810* Target, int Unused1, int Unused2,
                                    int Unused3)
{
    Target->Unk_10d9e810(unk_0);
}
