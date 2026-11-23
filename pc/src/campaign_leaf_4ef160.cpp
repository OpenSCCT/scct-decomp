// campaign_leaf_4ef160.cpp -- one function at file offset 0x4ef160, preferred VA 0x10def160.
// It calls the method at 0x10dcdd50 of the object at offset 4 and clears the ints at offsets 0x10,
// 8 and 0xc. The class, method and member names are invented; the offset and the bytes are the
// binary's.

class UnkType_10def160_Callee
{
public:
    void Unk_10dcdd50();
};

class UnkType_10def160
{
public:
    int unk_0;
    UnkType_10def160_Callee* unk_4;
    int unk_8;
    int unk_c;
    int unk_10;

    void Unk_10def160();
};

// UnkType_10def160::Unk_10def160
void UnkType_10def160::Unk_10def160()
{
    unk_4->Unk_10dcdd50();
    unk_10 = 0;
    unk_8 = 0;
    unk_c = 0;
}
