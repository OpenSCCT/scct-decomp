// campaign_leaf_4d9cf0.cpp -- one function at file offset 0x4d9cf0, preferred VA 0x10dd9cf0.
// It passes the address of a local int holding 0x10001 to the method at 0x10dab010 of Target and
// returns Target; the same bytes as 0x4d9cc0. The class, method and parameter names are invented;
// the offset and the bytes are the binary's.

class UnkType_10dd9cf0_Target
{
public:
    void Unk_10dab010(int* Value);
};

class UnkType_10dd9cf0
{
public:
    UnkType_10dd9cf0_Target& Unk_10dd9cf0(UnkType_10dd9cf0_Target& Target);
};

// UnkType_10dd9cf0::Unk_10dd9cf0
UnkType_10dd9cf0_Target& UnkType_10dd9cf0::Unk_10dd9cf0(UnkType_10dd9cf0_Target& Target)
{
    int Value = 0x10001;

    Target.Unk_10dab010(&Value);
    return Target;
}
