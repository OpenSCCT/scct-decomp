// campaign_leaf_358120.cpp -- one function at file offset 0x358120, preferred VA 0x10c58120. It
// looks for the object at 0x488 in the array of 8-byte entries at 0x4bc (count at 0x4c0); when it
// is missing it adds a zeroed entry through the array's method at 0x10c57700 and stores the
// object in it. Either way it copies the object's byte at 0x235 to the entry's byte at 0x4 and
// returns 0. The class, method, structure, member and local names are invented; the offsets and
// the bytes are the binary's.

class UnkType_10c58120_Object
{
public:
    unsigned char unk_0[0x235];
    unsigned char unk_235;
};

struct UnkType_10c58120_Entry
{
    UnkType_10c58120_Object* unk_0;
    unsigned char unk_4;
};

class UnkType_10c58120_Array
{
public:
    int Unk_10c57700(int ElementSize, int Count);

    UnkType_10c58120_Entry* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c58120
{
public:
    int Unk_10c58120();

    unsigned char unk_0[0x488];
    UnkType_10c58120_Object* unk_488;
    unsigned char unk_48c[0x30];
    UnkType_10c58120_Array unk_4bc;
};

// UnkType_10c58120::Unk_10c58120
int UnkType_10c58120::Unk_10c58120()
{
    int Index;

    for ( Index = 0; Index < unk_4bc.unk_4; Index++ )
    {
        UnkType_10c58120_Entry& Entry = unk_4bc.unk_0[Index];

        if ( Entry.unk_0 == unk_488 )
        {
            Entry.unk_4 = unk_488->unk_235;
            return 0;
        }
    }
    UnkType_10c58120_Entry& Added = unk_4bc.unk_0[unk_4bc.Unk_10c57700(8, 1)];

    Added.unk_0 = unk_488;
    Added.unk_4 = unk_488->unk_235;
    return 0;
}
