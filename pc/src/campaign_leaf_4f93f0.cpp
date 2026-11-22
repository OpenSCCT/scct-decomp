// campaign_leaf_4f93f0.cpp -- one function at file offset 0x4f93f0, preferred VA 0x10df93f0.
// It passes the unsigned short at offset 0 of the object to the method at
// 0x10d9e810 of Target; the other three arguments are unused. The same bytes as 0x4c1ae0. The
// class, method and parameter names are invented; the offset and the bytes are the binary's.

class UnkType_10d9e810
{
public:
    void Unk_10d9e810(unsigned short Value);
};

class UnkType_10df93f0
{
public:
    unsigned short unk_0;

    void Unk_10df93f0(UnkType_10d9e810* Target, int Unused1, int Unused2, int Unused3);
};

// UnkType_10df93f0::Unk_10df93f0
void UnkType_10df93f0::Unk_10df93f0(UnkType_10d9e810* Target, int Unused1, int Unused2,
                                    int Unused3)
{
    Target->Unk_10d9e810(unk_0);
}
