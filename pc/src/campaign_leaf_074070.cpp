// campaign_leaf_074070.cpp -- method at VA 0x10974070: passes its archive argument to the method at
// VA 0x10972710 of its base class, then serialises the members at 0x54, 0x60 and 0x6c through the
// free functions at VA 0x10973f10, 0x10973d10 and 0x109724f0, each on the archive the previous one
// returns. The class, member and function names are invented; the offsets and the addresses are the
// binary's.

class UnkType_10974070_Archive
{
public:
    virtual ~UnkType_10974070_Archive();
};

class UnkType_10974070_54
{
public:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10974070_60
{
public:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10974070_6c
{
public:
    void* unk_00;
    int unk_04;
    int unk_08;
};

UnkType_10974070_Archive& Unk_10973f10(UnkType_10974070_Archive& Archive,
                                       UnkType_10974070_54& Value);
UnkType_10974070_Archive& Unk_10973d10(UnkType_10974070_Archive& Archive,
                                       UnkType_10974070_60& Value);
UnkType_10974070_Archive& Unk_109724f0(UnkType_10974070_Archive& Archive,
                                       UnkType_10974070_6c& Value);

class UnkType_10974070_Base
{
public:
    void Unk_10972710(UnkType_10974070_Archive& Archive);

private:
    unsigned char unk_00[0x54];
};

class UnkType_10974070 : public UnkType_10974070_Base
{
public:
    void Unk_10974070(UnkType_10974070_Archive& Archive);

private:
    UnkType_10974070_54 unk_54;
    UnkType_10974070_60 unk_60;
    UnkType_10974070_6c unk_6c;
};

// UnkType_10974070::Unk_10974070
void UnkType_10974070::Unk_10974070(UnkType_10974070_Archive& Archive)
{
    Unk_10972710(Archive);
    Unk_109724f0(Unk_10973d10(Unk_10973f10(Archive, unk_54), unk_60), unk_6c);
}
