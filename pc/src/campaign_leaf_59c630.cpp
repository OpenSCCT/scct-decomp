// campaign_leaf_59c630.cpp -- thiscall method at VA 0x10e9c630: copies the base part through the
// method at VA 0x10ea3540, then copies its members at 0x150 and 0x18c-0x1af into the record it is
// given. All names are invented.

struct UnkType_10e9c630_Record
{
    int unk_00[0x28 / 4];
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4c;
};

class UnkType_10e9c630_Base
{
public:
    void Unk_10ea3540(UnkType_10e9c630_Record* Record);
};

class UnkType_10e9c630 : public UnkType_10e9c630_Base
{
public:
    void Unk_10e9c630(UnkType_10e9c630_Record* Record);

private:
    int unk_00[0x150 / 4];
    int unk_150;
    int unk_154[0x38 / 4];
    int unk_18c;
    int unk_190;
    int unk_194;
    int unk_198;
    int unk_19c;
    int unk_1a0;
    int unk_1a4;
    int unk_1a8;
    int unk_1ac;
};

// UnkType_10e9c630::Unk_10e9c630
void UnkType_10e9c630::Unk_10e9c630(UnkType_10e9c630_Record* Record)
{
    Unk_10ea3540(Record);
    Record->unk_28 = unk_1ac;
    Record->unk_2c = unk_18c;
    Record->unk_30 = unk_190;
    Record->unk_34 = unk_194;
    Record->unk_38 = unk_198;
    Record->unk_3c = unk_19c;
    Record->unk_44 = unk_1a0;
    Record->unk_48 = unk_1a4;
    Record->unk_4c = unk_1a8;
    Record->unk_40 = unk_150;
}
