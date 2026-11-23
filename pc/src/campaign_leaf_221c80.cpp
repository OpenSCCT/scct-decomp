// campaign_leaf_221c80.cpp -- a member function at VA 0x10b21c80 that does not read its object,
// taking a target and a settings record: when the target exists and its pointer at 0x920 is set,
// it passes the record to the member at VA 0x10992290 of the member at 0x2b4 of the object at
// 0x920, copies the record's byte at 0x30 to that object's byte at 0x2c0, stores the record's byte
// at 0x33 as a float at 0x2c of the object the target's pointer at 0x488 refers to and its byte at
// 0x32 in that object's first flag bit at 0x28, and stores the record's ints at 0x7c and 0x80 as
// floats at 0x3d0 and 0x3d4 of the target. The class, method, member and parameter names are
// invented; the offsets and addresses are the binary's.

class UnkType_10b21c80_Record
{
public:
    unsigned char unk_00[0x30];
    unsigned char unk_30;
    unsigned char unk_31;
    unsigned char unk_32;
    unsigned char unk_33;
    unsigned char unk_34[0x7c - 0x34];
    int unk_7c;
    int unk_80;
};

class UnkType_10b21c80_Settings
{
public:
    void Unk_10992290(const UnkType_10b21c80_Record& Record);

private:
    int unk_00;
};

class UnkType_10b21c80_View
{
public:
    unsigned char unk_000[0x2b4];
    UnkType_10b21c80_Settings unk_2b4;
    unsigned char unk_2b8[0x2c0 - 0x2b8];
    unsigned char unk_2c0;
};

class UnkType_10b21c80_State
{
public:
    unsigned char unk_00[0x28];
    unsigned int unk_28 : 1;
    float unk_2c;
};

class UnkType_10b21c80_Target
{
public:
    unsigned char unk_000[0x3d0];
    float unk_3d0;
    float unk_3d4;
    unsigned char unk_3d8[0x488 - 0x3d8];
    UnkType_10b21c80_State* unk_488;
    unsigned char unk_48c[0x920 - 0x48c];
    UnkType_10b21c80_View* unk_920;
};

class UnkType_10b21c80
{
public:
    void Unk_10b21c80(UnkType_10b21c80_Target* Target, UnkType_10b21c80_Record* Record);
};

// UnkType_10b21c80::Unk_10b21c80
void UnkType_10b21c80::Unk_10b21c80(UnkType_10b21c80_Target* Target,
                                    UnkType_10b21c80_Record* Record)
{
    if ( Target && Target->unk_920 )
    {
        Target->unk_920->unk_2b4.Unk_10992290(*Record);
        Target->unk_920->unk_2c0 = Record->unk_30;
        Target->unk_488->unk_2c = Record->unk_33;
        Target->unk_488->unk_28 = Record->unk_32;
        Target->unk_3d0 = Record->unk_7c;
        Target->unk_3d4 = Record->unk_80;
    }
}
