// campaign_leaf_220010.cpp -- a member function at VA 0x10b20010 that walks the array of pointers
// at 0x98 (count at 0x9c) and stores in the pointer at 0x40 each entry whose object, found through
// it (the member at VA 0x10a0e220 of its pointer at 0x04 with its byte at 0x0c, then the member at
// VA 0x10a45b50 of the result's pointer at 0x64), is its argument. It returns true. The class,
// method and member names are invented; the offsets and addresses are the binary's.

class UnkType_10b20010_Owner;

class UnkType_10b20010_Lookup
{
public:
    UnkType_10b20010_Owner* Unk_10a45b50();
};

class UnkType_10b20010_Entry
{
public:
    unsigned char unk_00[0x64];
    UnkType_10b20010_Lookup* unk_64;
};

class UnkType_10b20010_Table
{
public:
    UnkType_10b20010_Entry* Unk_10a0e220(unsigned char Index);
};

class UnkType_10b20010_Item
{
public:
    int unk_00;
    UnkType_10b20010_Table* unk_04;
    int unk_08;
    unsigned char unk_0c;
};

class UnkType_10b20010
{
public:
    bool Unk_10b20010(UnkType_10b20010_Owner* Owner);

private:
    unsigned char unk_00[0x40];
    UnkType_10b20010_Item* unk_40;
    unsigned char unk_44[0x98 - 0x44];
    UnkType_10b20010_Item** unk_98;
    int unk_9c;
};

// UnkType_10b20010::Unk_10b20010
bool UnkType_10b20010::Unk_10b20010(UnkType_10b20010_Owner* Owner)
{
    for ( int i = 0; i < unk_9c; i++ )
    {
        UnkType_10b20010_Item* Item = unk_98[i];
        if ( Item && Item->unk_04->Unk_10a0e220(Item->unk_0c)->unk_64->Unk_10a45b50() == Owner )
        {
            unk_40 = unk_98[i];
        }
    }
    return true;
}
