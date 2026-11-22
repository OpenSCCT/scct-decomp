// campaign_leaf_1458a0.cpp -- returns 1 or 0 from the kind at offset 0x428 of the object that the
// pointer at offset 0x30 of this points to, and from a dword reached through the pointers at
// offsets 0x7c and 0x80 of that object. File offset 0x1458a0, VA 0x10a458a0. The class and method
// names are invented; the offsets are the binary's, and the object types are guesses.

class UnkA_1458a0;
class UnkB_1458a0;
class UnkC_1458a0;

class UnkType_1458a0
{
public:
    int UnkMethod_1458a0();

private:
    unsigned char unk_00[0x30];
    UnkA_1458a0 *unk_30;
};

class UnkA_1458a0
{
public:
    unsigned char unk_00[0x7c];
    UnkB_1458a0 *unk_7c;
    unsigned char unk_80[0x3a8];
    int unk_428;
};

class UnkB_1458a0
{
public:
    unsigned char unk_00[0x80];
    UnkC_1458a0 *unk_80;
};

class UnkC_1458a0
{
public:
    unsigned char unk_00[0x5c];
    int unk_5c;
};

int UnkType_1458a0::UnkMethod_1458a0()
{
    UnkA_1458a0 *a;

    a = unk_30;
    if ( a == 0 )
    {
        return 0;
    }
    if ( a->unk_7c->unk_80->unk_5c == 0 || a->unk_428 == 0xd || a->unk_428 == 0xe
         || a->unk_428 == 0xf || a->unk_428 == 1 )
    {
        if ( a->unk_428 == 0x12 || a->unk_428 == 0x14 || a->unk_428 == 0x13 || a->unk_428 == 0x1a
             || a->unk_428 == 0x20 || a->unk_428 == 0x15 || a->unk_428 == 0x10 )
        {
            return 0;
        }
        return 1;
    }
    return 0;
}
