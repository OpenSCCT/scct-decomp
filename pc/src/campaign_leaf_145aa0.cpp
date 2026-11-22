// campaign_leaf_145aa0.cpp -- when the byte argument is below the count at offset 0x04 of this,
// sets bits in the link objects of the entry at that index in the array at offset 0x00, and stores
// the second argument at offset 0x01 of the entry. File offset 0x145aa0, VA 0x10a45aa0. The class
// and method names are invented; the offsets are the binary's, and the object types are guesses.

class UnkLink_10a45aa0;
class UnkNode_10a45aa0;
class UnkEntry_10a45aa0;

class UnkType_10a45aa0
{
public:
    void UnkMethod_10a45aa0(unsigned char Index, unsigned char Value);

private:
    UnkEntry_10a45aa0 **unk_00;     // guess: array of pointers to entries
    int unk_04;                     // count of entries
};

class UnkEntry_10a45aa0
{
public:
    unsigned char unk_00;           // not written by this function
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;           // not written by this function
    UnkLink_10a45aa0 *unk_04;       // guess: pointer to a link object
};

class UnkLink_10a45aa0
{
public:
    unsigned char unk_00[0x2b4];    // not read by this function
    UnkNode_10a45aa0 *unk_2b4;      // guess: pointer to a node
    unsigned char unk_2b8[0x1c4];   // not read by this function
    unsigned int unk_47c;
};

class UnkNode_10a45aa0
{
public:
    unsigned char unk_00[0x30];     // not read by this function
    unsigned int unk_30;
};

// UnkType_10a45aa0::UnkMethod_10a45aa0
void UnkType_10a45aa0::UnkMethod_10a45aa0(unsigned char Index, unsigned char Value)
{
    if ( Index < unk_04 )
    {
        unk_00[Index]->unk_04->unk_47c |= 4;
        unk_00[Index]->unk_04->unk_2b4->unk_30 |= 0x80;
        unk_00[Index]->unk_02 |= 2;
        unk_00[Index]->unk_01 = Value;
    }
}
