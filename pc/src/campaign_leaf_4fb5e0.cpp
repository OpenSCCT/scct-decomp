// campaign_leaf_4fb5e0.cpp -- function at VA 0x10dfb5e0: writes a record to a stream: the 128 bytes
// at 0x04 and the 128 at 0x84 (method at VA 0x10d9e7f0 for each byte), the word at 0x104 (method at
// VA 0x10d9e850), the 256 bytes at 0x108, then the words at 0x208, 0x20c and 0x210. The function,
// class and member names are invented; the offsets, the counts and the addresses are the binary's.

class UnkType_10dfb5e0_Writer
{
public:
    void Unk_10d9e7f0(unsigned char Value);
    void Unk_10d9e850(int Value);
};

class UnkType_10dfb5e0_Record
{
public:
    int unk_00;
    unsigned char unk_04[128];
    unsigned char unk_84[128];
    int unk_104;
    unsigned char unk_108[256];
    int unk_208;
    int unk_20c;
    int unk_210;
};

// Unk_10dfb5e0
void Unk_10dfb5e0(UnkType_10dfb5e0_Writer* Writer, const UnkType_10dfb5e0_Record* Record)
{
    unsigned int i;
    for ( i = 0; i < 128; i++ )
    {
        Writer->Unk_10d9e7f0(Record->unk_04[i]);
    }
    for ( i = 0; i < 128; i++ )
    {
        Writer->Unk_10d9e7f0(Record->unk_84[i]);
    }
    Writer->Unk_10d9e850(Record->unk_104);
    for ( i = 0; i < 256; i++ )
    {
        Writer->Unk_10d9e7f0(Record->unk_108[i]);
    }
    Writer->Unk_10d9e850(Record->unk_208);
    Writer->Unk_10d9e850(Record->unk_20c);
    Writer->Unk_10d9e850(Record->unk_210);
}
