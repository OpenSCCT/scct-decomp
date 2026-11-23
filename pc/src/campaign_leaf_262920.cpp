// campaign_leaf_262920.cpp -- a member function at VA 0x10b62920 that sets the ints at 0xac and
// 0xb0 to 0 and those at 0xb4 and 0xb8 to -1, clears the int at 0xe4 of the object the pointer at
// 0x14 refers to and calls its member at VA 0x10ad5820 with the int at 0x78 and three zeros, then
// looks up an object through it (the member at VA 0x10a0e220 of its pointer at 0x04 with its byte
// at 0x0c, then the member at VA 0x10a45b50 of the result's pointer at 0x64) and clears bit 8 of
// that object's flags at 0x398. The class, method and member names are invented; the offsets and
// addresses are the binary's.

class UnkType_10b62920_Owner
{
public:
    unsigned char unk_000[0x398];
    unsigned int unk_398;
};

class UnkType_10b62920_Lookup
{
public:
    UnkType_10b62920_Owner* Unk_10a45b50();
};

class UnkType_10b62920_Entry
{
public:
    unsigned char unk_00[0x64];
    UnkType_10b62920_Lookup* unk_64;
};

class UnkType_10b62920_Table
{
public:
    UnkType_10b62920_Entry* Unk_10a0e220(unsigned char Index);
};

class UnkType_10b62920_Item
{
public:
    void Unk_10ad5820(int Value, int Second, int Third, int Fourth);

    int unk_00;
    UnkType_10b62920_Table* unk_04;
    int unk_08;
    unsigned char unk_0c;
    unsigned char unk_0d[0xe4 - 0x0d];
    int unk_e4;
};

class UnkType_10b62920
{
public:
    void Unk_10b62920();

private:
    unsigned char unk_00[0x14];
    UnkType_10b62920_Item* unk_14;
    unsigned char unk_18[0x78 - 0x18];
    int unk_78;
    unsigned char unk_7c[0xac - 0x7c];
    int unk_ac;
    int unk_b0;
    int unk_b4;
    int unk_b8;
};

// UnkType_10b62920::Unk_10b62920
void UnkType_10b62920::Unk_10b62920()
{
    unk_ac = 0;
    unk_b0 = 0;
    unk_b4 = -1;
    unk_b8 = -1;
    unk_14->unk_e4 = 0;
    unk_14->Unk_10ad5820(unk_78, 0, 0, 0);
    UnkType_10b62920_Item* Item = unk_14;
    UnkType_10b62920_Owner* Owner =
        Item->unk_04->Unk_10a0e220(Item->unk_0c)->unk_64->Unk_10a45b50();
    Owner->unk_398 &= ~0x100;
}
