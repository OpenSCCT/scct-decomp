// campaign_leaf_1371c0.cpp -- returns true at once when the flag at offset 0x144 of this is set and
// the dword at offset 0x140 equals the value the second argument points to. Otherwise it records
// the flag and the value, stores the value in the entry chosen by the first argument modulo 40, and
// returns true. File offset 0x1371c0, VA 0x10a371c0. The class and method names are invented; the
// offsets are the binary's, and the types of the arguments are guesses.

class UnkEntry_10a371c0
{
public:
    unsigned char unk_00;
    int unk_04;
};

class UnkType_10a371c0
{
public:
    bool UnkMethod_10a371c0(unsigned int *Index, int *Value);

private:
    UnkEntry_10a371c0 unk_00[40];
    int unk_140;
    unsigned char unk_144;
};

// UnkType_10a371c0::UnkMethod_10a371c0
bool UnkType_10a371c0::UnkMethod_10a371c0(unsigned int *Index, int *Value)
{
    UnkEntry_10a371c0 *entry;

    if ( unk_144 != 0 && unk_140 == *Value )
    {
        return true;
    }
    unk_144 = 1;
    unk_140 = *Value;
    entry = &unk_00[ *Index % 40 ];
    entry->unk_00 = 1;
    entry->unk_04 = *Value;
    return true;
}
