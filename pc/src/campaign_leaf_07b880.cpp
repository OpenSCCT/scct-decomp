// campaign_leaf_07b880.cpp -- method at VA 0x1097b880: calls the method at VA 0x10aac730 of its
// base class; empties the map at 0x38 (passes 0 to the method at VA 0x1097b8c0 of its pair array,
// sets its bucket count at 0x10 to 8 and rebuilds its hash with the method at VA 0x109762c0), then
// passes 0 to the methods at VA 0x1097b8e0 and 0x1097b950 of the members at 0x4c and 0x58. The
// class, member and method names are invented; the offsets, the constants and the addresses are
// the binary's.

class UnkType_1097b8c0_07b880
{
public:
    void Unk_1097b8c0(int Slack);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109762c0_07b880
{
public:
    void Empty()
    {
        unk_00.Unk_1097b8c0(0);
        unk_10 = 8;
        Unk_109762c0();
    }

    void Unk_109762c0();

private:
    UnkType_1097b8c0_07b880 unk_00;
    int* unk_0c;
    int unk_10;
};

class UnkType_1097b8e0_07b880
{
public:
    void Unk_1097b8e0(int Slack);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1097b950_07b880
{
public:
    void Unk_1097b950(int Slack);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1097b880_Base
{
public:
    void Unk_10aac730();

private:
    unsigned char unk_00[0x38];
};

class UnkType_1097b880 : public UnkType_1097b880_Base
{
public:
    void Unk_1097b880();

private:
    UnkType_109762c0_07b880 unk_38;
    UnkType_1097b8e0_07b880 unk_4c;
    UnkType_1097b950_07b880 unk_58;
};

// UnkType_1097b880::Unk_1097b880
void UnkType_1097b880::Unk_1097b880()
{
    Unk_10aac730();
    unk_38.Empty();
    unk_4c.Unk_1097b8e0(0);
    unk_58.Unk_1097b950(0);
}
