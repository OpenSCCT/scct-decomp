// campaign_leaf_4d8f60.cpp -- one function at file offset 0x4d8f60, preferred VA 0x10dd8f60.
// It calls the method at 0x10dae370 of the object at offset 0x94 and then the method at
// 0x10dc14d0 with 4. The class, method and member names are invented; the offset and the bytes
// are the binary's.

class UnkType_10dd8f60_Callee
{
public:
    void Unk_10dae370();
};

class UnkType_10dd8f60
{
public:
    unsigned char unk_0[0x94];
    UnkType_10dd8f60_Callee* unk_94;

    void Unk_10dc14d0(int Value);
    void Unk_10dd8f60();
};

// UnkType_10dd8f60::Unk_10dd8f60
void UnkType_10dd8f60::Unk_10dd8f60()
{
    unk_94->Unk_10dae370();
    Unk_10dc14d0(4);
}
