// campaign_leaf_22bb60.cpp -- a member function at VA 0x10b2bb60 that looks up an object through
// the pointer at 0x10 (the member at VA 0x10a0e220 of its pointer at 0x04 with its byte at 0x0c,
// then the member at VA 0x10a45b50 of the result's pointer at 0x64); when that object and its
// pointer at 0x5c0 are set it calls that pointer's members at VA 0x10c2a400 and VA 0x10c29c20 (with
// the address of the int at 0x1c and the int at 0x28). It then calls the member at VA 0x10b2b8b0
// with the ints at 0x40 and 0x3c. The class, method and member names are invented; the offsets and
// addresses are the binary's.

class UnkType_10b2bb60_Child
{
public:
    void Unk_10c2a400();
    void Unk_10c29c20(int* Value, int Second);
};

class UnkType_10b2bb60_Owner
{
public:
    unsigned char unk_000[0x5c0];
    UnkType_10b2bb60_Child* unk_5c0;
};

class UnkType_10b2bb60_Lookup
{
public:
    UnkType_10b2bb60_Owner* Unk_10a45b50();
};

class UnkType_10b2bb60_Entry
{
public:
    unsigned char unk_00[0x64];
    UnkType_10b2bb60_Lookup* unk_64;
};

class UnkType_10b2bb60_Table
{
public:
    UnkType_10b2bb60_Entry* Unk_10a0e220(unsigned char Index);
};

class UnkType_10b2bb60_Item
{
public:
    int unk_00;
    UnkType_10b2bb60_Table* unk_04;
    int unk_08;
    unsigned char unk_0c;
};

class UnkType_10b2bb60
{
public:
    void Unk_10b2b8b0(int First, int Second);
    void Unk_10b2bb60();

private:
    unsigned char unk_00[0x10];
    UnkType_10b2bb60_Item* unk_10;
    unsigned char unk_14[0x1c - 0x14];
    int unk_1c;
    unsigned char unk_20[0x28 - 0x20];
    int unk_28;
    unsigned char unk_2c[0x3c - 0x2c];
    int unk_3c;
    int unk_40;
};

// UnkType_10b2bb60::Unk_10b2bb60
void UnkType_10b2bb60::Unk_10b2bb60()
{
    UnkType_10b2bb60_Owner* Owner =
        unk_10->unk_04->Unk_10a0e220(unk_10->unk_0c)->unk_64->Unk_10a45b50();
    if ( Owner && Owner->unk_5c0 )
    {
        Owner->unk_5c0->Unk_10c2a400();
        Owner->unk_5c0->Unk_10c29c20(&unk_1c, unk_28);
    }
    Unk_10b2b8b0(unk_40, unk_3c);
}
