// campaign_leaf_4cd9e0.cpp -- one function at file offset 0x4cd9e0, preferred VA 0x10dcd9e0.
// It adds the result of the method at 0x10dcddb0 of First to the int at offset 8 and that of
// Second to the int at offset 0xc. The class, method, member and parameter names are invented; the
// offset and the bytes are the binary's.

class UnkType_10dcd9e0_Callee
{
public:
    int Unk_10dcddb0();
};

class UnkType_10dcd9e0
{
public:
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;

    void Unk_10dcd9e0(UnkType_10dcd9e0_Callee* First, UnkType_10dcd9e0_Callee* Second);
};

// UnkType_10dcd9e0::Unk_10dcd9e0
void UnkType_10dcd9e0::Unk_10dcd9e0(UnkType_10dcd9e0_Callee* First,
                                    UnkType_10dcd9e0_Callee* Second)
{
    unk_8 += First->Unk_10dcddb0();
    unk_c += Second->Unk_10dcddb0();
}
