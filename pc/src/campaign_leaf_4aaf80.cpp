// campaign_leaf_4aaf80.cpp -- one function at file offset 0x4aaf80, preferred VA 0x10daaf80.
// It calls the method at 0x10daaec0 of the same object with the result of the method at 0x10d91090
// of Source. The class, method and parameter names are invented; the offset and the bytes are the
// binary's.

class UnkType_10daaf80_Callee
{
public:
    int Unk_10d91090();
};

class UnkType_10daaf80
{
public:
    void Unk_10daaec0(int Value);
    void Unk_10daaf80(UnkType_10daaf80_Callee* Source);
};

// UnkType_10daaf80::Unk_10daaf80
void UnkType_10daaf80::Unk_10daaf80(UnkType_10daaf80_Callee* Source)
{
    Unk_10daaec0(Source->Unk_10d91090());
}
