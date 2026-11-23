// campaign_leaf_4d2d50.cpp -- one function at file offset 0x4d2d50, preferred VA 0x10dd2d50.
// It passes the address of each of the two ints Pair points to to the method at 0x10d9df90 of
// Target; the other three arguments are unused. The class, method and parameter names are
// invented; the offset and the bytes are the binary's.

class UnkType_10dd2d50_Target
{
public:
    void Unk_10d9df90(int* Value);
};

class UnkType_10dd2d50
{
public:
    void Unk_10dd2d50(int Unused1, int* Pair, int Unused2, UnkType_10dd2d50_Target* Target,
                      int Unused3);
};

// UnkType_10dd2d50::Unk_10dd2d50
void UnkType_10dd2d50::Unk_10dd2d50(int Unused1, int* Pair, int Unused2,
                                    UnkType_10dd2d50_Target* Target, int Unused3)
{
    Target->Unk_10d9df90(Pair);
    Target->Unk_10d9df90(Pair + 1);
}
