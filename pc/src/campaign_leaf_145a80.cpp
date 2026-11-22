// campaign_leaf_145a80.cpp -- stores Value at offset 0x04 and Flag at offset 0x00 of the entry at
// Index in the array at offset 0x00 of this, when that entry is set. File offset 0x145a80, VA
// 0x10a45a80. The class and method names are invented; the offsets are the binary's, and the entry
// type and the argument types are guesses.

class UnkEntry_10a45a80;

class UnkType_10a45a80
{
public:
    void UnkMethod_10a45a80(unsigned char Index, int Value, unsigned char Flag);

private:
    UnkEntry_10a45a80 **unk_00;     // guess: array of pointers to entries
};

class UnkEntry_10a45a80
{
public:
    unsigned char unk_00;
    int unk_04;
};

// UnkType_10a45a80::UnkMethod_10a45a80
void UnkType_10a45a80::UnkMethod_10a45a80(unsigned char Index, int Value, unsigned char Flag)
{
    UnkEntry_10a45a80 *entry = unk_00[Index];

    if ( entry )
    {
        entry->unk_04 = Value;
        entry->unk_00 = Flag;
    }
}
