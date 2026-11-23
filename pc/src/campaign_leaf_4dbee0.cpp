// campaign_leaf_4dbee0.cpp -- one function at file offset 0x4dbee0, preferred VA 0x10ddbee0.
// It passes the object to the method at 0x10db00e0 of what the function at 0x10daf690 returns and
// then sets the byte at offset 0x88. The class, function, method and member names are invented;
// the offset and the bytes are the binary's.

class UnkType_10ddbee0;

class UnkType_10ddbee0_Callee
{
public:
    void Unk_10db00e0(UnkType_10ddbee0* Item);
};

UnkType_10ddbee0_Callee* Unk_10daf690();

class UnkType_10ddbee0
{
public:
    unsigned char unk_0[0x88];
    bool unk_88;

    void Unk_10ddbee0();
};

// UnkType_10ddbee0::Unk_10ddbee0
void UnkType_10ddbee0::Unk_10ddbee0()
{
    Unk_10daf690()->Unk_10db00e0(this);
    unk_88 = true;
}
