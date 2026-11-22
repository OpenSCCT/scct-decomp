// campaign_leaf_27ef90.cpp -- one function at file offset 0x27ef90, preferred VA 0x10b7ef90. Unless
// bit 0x20 of the flags at offset 0x2c is set while the object at offset 0x78 exists and lacks bit
// 0x1 in its byte at offset 0x5cc, it takes a non-null argument whose word at offset 0x3c is zero:
// it sets bit field 17 of the word at offset 0x2b0, stores the argument at offset 0x984, clears
// the words at 0x988 and 0x98c and bit field 30 of the word at offset 0x748. The class, method and
// member names are invented; the offset and the bytes are the binary's.

class UnkType_10b7ef90_Item
{
public:
    unsigned char unk_0[0x3c];
    int unk_3c;
};

class UnkType_10b7ef90_Owner
{
public:
    unsigned char unk_0[0x5cc];
    unsigned char unk_5cc;
};

class UnkType_10b7ef90
{
public:
    unsigned char unk_0[0x2c];
    int unk_2c;
    unsigned char unk_30[0x78 - 0x30];
    UnkType_10b7ef90_Owner* unk_78;
    unsigned char unk_7c[0x2b0 - 0x7c];
    unsigned int unk_2b0_0 : 17;
    unsigned int unk_2b0_17 : 1;
    unsigned char unk_2b4[0x748 - 0x2b4];
    unsigned int unk_748_0 : 30;
    unsigned int unk_748_30 : 1;
    unsigned char unk_74c[0x984 - 0x74c];
    UnkType_10b7ef90_Item* unk_984;
    int unk_988;
    int unk_98c;

    void Unk_10b7ef90(UnkType_10b7ef90_Item* Item);
};

// UnkType_10b7ef90::Unk_10b7ef90
void UnkType_10b7ef90::Unk_10b7ef90(UnkType_10b7ef90_Item* Item)
{
    if ( ( !( unk_2c & 0x20 ) || !unk_78 || ( unk_78->unk_5cc & 1 ) ) && Item && !Item->unk_3c )
    {
        unk_2b0_17 = 1;
        unk_984 = Item;
        unk_988 = 0;
        unk_748_30 = 0;
        unk_98c = 0;
    }
}
