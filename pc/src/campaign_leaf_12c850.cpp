// campaign_leaf_12c850.cpp -- returns 1 when the kind at offset 0x428 of the object that the pointer
// at offset 0x30 of this points to is one of 0x05, 0x0c, 0x07, 0x1e or 0x26, or is 0x10 with the
// dword at offset 0x410 set. Otherwise 0. File offset 0x12c850, VA 0x10a2c850. The class and method
// names are invented; the offsets are the binary's, and the pointee type is a guess.

class UnkTarget_12c850;

class UnkType_12c850
{
public:
    int UnkMethod_12c850();

private:
    unsigned char unk_00[0x30];
    UnkTarget_12c850 *unk_30;
};

class UnkTarget_12c850
{
public:
    unsigned char unk_00[0x410];
    int unk_410;
    unsigned char unk_414[0x14];
    int unk_428;
};

int UnkType_12c850::UnkMethod_12c850()
{
    int kind;

    if ( unk_30 != 0 )
    {
        kind = unk_30->unk_428;
        if ( kind == 5 || kind == 0xc || kind == 7 || kind == 0x1e || kind == 0x26
             || ( kind == 0x10 && unk_30->unk_410 != 0 ) )
        {
            return 1;
        }
    }
    return 0;
}
