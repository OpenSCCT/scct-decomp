// campaign_leaf_145a20.cpp -- when the entry at the index given by the first argument is set,
// stores the second argument at its offset 0x04 and 0 at its offset 0x00. File offset 0x145a20, VA
// 0x10a45a20. The class and method names are invented; the offsets are the binary's, and the entry
// type is a guess.

class UnkEntry_10a45a20;

class UnkType_10a45a20
{
public:
    void UnkMethod_10a45a20(unsigned char Index, int Value);

private:
    UnkEntry_10a45a20 **unk_00;     // guess: array of pointers to entries
};

class UnkEntry_10a45a20
{
public:
    unsigned char unk_00;
    int unk_04;
};

// UnkType_10a45a20::UnkMethod_10a45a20
void UnkType_10a45a20::UnkMethod_10a45a20(unsigned char Index, int Value)
{
    if ( unk_00[Index] != 0 )
    {
        unk_00[Index]->unk_04 = Value;
        unk_00[Index]->unk_00 = 0;
    }
}
