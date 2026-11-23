// campaign_leaf_095dd0.cpp -- method at VA 0x10995dd0: calls the method at VA 0x109957c0, then, if
// the pointer at 0x190 is set, the method at VA 0x1097e310 on the object it points to. The class,
// member and method names are invented; the offsets and the addresses are the binary's.

class UnkType_10995dd0_1097e310
{
public:
    void Unk_1097e310();
};

class UnkType_10995dd0
{
public:
    void Unk_10995dd0();
    void Unk_109957c0();

private:
    unsigned char unk_000[0x190];
    UnkType_10995dd0_1097e310* unk_190;
};

// UnkType_10995dd0::Unk_10995dd0
void UnkType_10995dd0::Unk_10995dd0()
{
    Unk_109957c0();
    if ( unk_190 )
    {
        unk_190->Unk_1097e310();
    }
}
