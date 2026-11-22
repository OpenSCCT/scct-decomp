// campaign_leaf_4daa90.cpp -- one function at file offset 0x4daa90, preferred VA 0x10ddaa90.
// It passes the byte at offset 0 of the object to the method at 0x10d9e7a0 of
// Target; the other three arguments are unused. The class, method and parameter names are
// invented; the offset and the bytes are the binary's.

class UnkType_10d9e7a0
{
public:
    void Unk_10d9e7a0(unsigned char Value);
};

class UnkType_10ddaa90
{
public:
    unsigned char unk_0;

    void Unk_10ddaa90(UnkType_10d9e7a0* Target, int Unused1, int Unused2, int Unused3);
};

// UnkType_10ddaa90::Unk_10ddaa90
void UnkType_10ddaa90::Unk_10ddaa90(UnkType_10d9e7a0* Target, int Unused1, int Unused2,
                                    int Unused3)
{
    Target->Unk_10d9e7a0(unk_0);
}
