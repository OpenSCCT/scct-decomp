// campaign_leaf_4a2370.cpp -- one function at file offset 0x4a2370, preferred VA 0x10da2370.
// It stores at offset 0x38 the result of the method at 0x10da8d80, called with this object on the
// object the function at 0x10da9120 returns. The class, function, method and member names are
// invented; the offset and the bytes are the binary's.

class UnkType_10da2370;

class UnkType_10da2370_Callee
{
public:
    int Unk_10da8d80(UnkType_10da2370* Item);
};

UnkType_10da2370_Callee* Unk_10da9120();

class UnkType_10da2370
{
public:
    unsigned char unk_0[0x38];
    int unk_38;

    void Unk_10da2370();
};

// UnkType_10da2370::Unk_10da2370
void UnkType_10da2370::Unk_10da2370()
{
    unk_38 = Unk_10da9120()->Unk_10da8d80(this);
}
