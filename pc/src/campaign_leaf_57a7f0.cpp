// campaign_leaf_57a7f0.cpp -- thiscall method at VA 0x10e7a7f0: copies the base part through the
// method at VA 0x11018c60, then copies its members at 0x30-0x5d into the record it is given. All
// names are invented.

struct UnkType_10e7a7f0_Record
{
    int unk_00[4];
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    char unk_3c;
    char unk_3d;
};

class UnkType_10e7a7f0_Base
{
public:
    void Unk_11018c60(UnkType_10e7a7f0_Record* Record);
};

class UnkType_10e7a7f0 : public UnkType_10e7a7f0_Base
{
public:
    void Unk_10e7a7f0(UnkType_10e7a7f0_Record* Record);

private:
    int unk_00[12];
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4c;
    int unk_50;
    int unk_54;
    int unk_58;
    char unk_5c;
    char unk_5d;
};

// UnkType_10e7a7f0::Unk_10e7a7f0
void UnkType_10e7a7f0::Unk_10e7a7f0(UnkType_10e7a7f0_Record* Record)
{
    Unk_11018c60(Record);
    Record->unk_30 = unk_50;
    Record->unk_34 = unk_54;
    Record->unk_38 = unk_58;
    Record->unk_10 = unk_30;
    Record->unk_14 = unk_34;
    Record->unk_18 = unk_38;
    Record->unk_1c = unk_3c;
    Record->unk_20 = unk_40;
    Record->unk_24 = unk_44;
    Record->unk_28 = unk_48;
    Record->unk_2c = unk_4c;
    Record->unk_3c = unk_5c;
    Record->unk_3d = unk_5d;
}
