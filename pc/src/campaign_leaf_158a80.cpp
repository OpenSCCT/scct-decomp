// campaign_leaf_158a80.cpp -- returns 0 when an entry of the array at offset 0x1bc of this has no
// sub-object, or its sub-object's byte at offset 0x28 has bit 0x04, and 1 otherwise. File offset
// 0x158a80, VA 0x10a58a80. The class and method names are invented; the offsets are the binary's,
// and the entry and sub-object types are guesses.

class UnkItem_10a58a80;
class UnkSub_10a58a80;

class UnkType_10a58a80
{
public:
    int UnkMethod_10a58a80();

private:
    unsigned char unk_00[0x1bc];    // not read by this function
    UnkItem_10a58a80 *unk_1bc;      // guess: array of items
    int unk_1c0;                    // count of items
};

class UnkItem_10a58a80
{
public:
    UnkSub_10a58a80 *unk_00;        // guess: pointer to a sub-object
    unsigned char unk_04[0xc];      // not read by this function
};

class UnkSub_10a58a80
{
public:
    unsigned char unk_00[0x28];     // not read by this function
    unsigned char unk_28;
};

// UnkType_10a58a80::UnkMethod_10a58a80
int UnkType_10a58a80::UnkMethod_10a58a80()
{
    int i;
    UnkSub_10a58a80 *sub;

    for ( i = 0; i < unk_1c0; i++ )
    {
        sub = unk_1bc[i].unk_00;
        if ( sub == 0 || ( sub->unk_28 & 4 ) )
        {
            return 0;
        }
    }
    return 1;
}
