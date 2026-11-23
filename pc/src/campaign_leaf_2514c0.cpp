// campaign_leaf_2514c0.cpp -- a member function at VA 0x10b514c0 that calls the member at VA
// 0x10b75be0 of the member at 0x14 with the address of the int at 0x30, fills the record its
// argument points to (the ints at 0x7c, 0x84, 0x80 and 0x88 into 0x458, 0x460, 0x45c and 0x468,
// whether the int at 0x94 is set into 0x474, and 2 into 0x450), copies the narrow strings at 0x34
// and 0x5c to the record's 0x400 and 0x428 with the free function at VA 0x10ccae50, sets the int at
// 0x04 to 1 and returns 1. The class, method, member and parameter names are invented; the offsets
// and addresses are the binary's.

void Unk_10ccae50(char* Dest, const char* Source);

class UnkType_10b514c0_Record
{
public:
    unsigned char unk_000[0x400];
    char unk_400[0x28];
    char unk_428[0x28];
    int unk_450;
    int unk_454;
    int unk_458;
    int unk_45c;
    int unk_460;
    int unk_464;
    int unk_468;
    int unk_46c;
    int unk_470;
    int unk_474;
};

class UnkType_10b514c0_Part
{
public:
    void Unk_10b75be0(int* Value);

private:
    int unk_00;
};

class UnkType_10b514c0
{
public:
    int Unk_10b514c0(UnkType_10b514c0_Record* Record);

private:
    int unk_00;
    int unk_04;
    unsigned char unk_08[0x14 - 0x08];
    UnkType_10b514c0_Part unk_14;
    unsigned char unk_18[0x30 - 0x18];
    int unk_30;
    char unk_34[0x5c - 0x34];
    char unk_5c[0x7c - 0x5c];
    int unk_7c;
    int unk_80;
    int unk_84;
    int unk_88;
    unsigned char unk_8c[0x94 - 0x8c];
    int unk_94;
};

// UnkType_10b514c0::Unk_10b514c0
int UnkType_10b514c0::Unk_10b514c0(UnkType_10b514c0_Record* Record)
{
    unk_14.Unk_10b75be0(&unk_30);
    Record->unk_458 = unk_7c;
    Record->unk_474 = unk_94 != 0;
    Record->unk_460 = unk_84;
    Record->unk_450 = 2;
    Record->unk_45c = unk_80;
    Record->unk_468 = unk_88;
    Unk_10ccae50(Record->unk_400, unk_34);
    Unk_10ccae50(Record->unk_428, unk_5c);
    unk_04 = 1;
    return 1;
}
