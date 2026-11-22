// campaign_leaf_1e9a40.cpp -- returns the address of the entry at the index argument of one of two
// 56-byte entry arrays of this, chosen by the flag argument, or null when the index is negative or
// not below the count of the chosen array. File offset 0x1e9a40, VA 0x10ae9a40. The class and
// method names are invented; the offsets are the binary's. The entry type and the meanings of the
// arrays are guesses.

class UnkType_10ae9a40Entry
{
public:
    unsigned char unk_00[0x38];
};

class UnkType_10ae9a40
{
public:
    UnkType_10ae9a40Entry *UnkMethod_10ae9a40(int index, bool flag);

private:
    unsigned char unk_00[0x94];     // not read by this function
    UnkType_10ae9a40Entry *unk_94;
    int unk_98;
    unsigned char unk_9c[0x04];     // not read by this function
    UnkType_10ae9a40Entry *unk_a0;
    int unk_a4;
};

// UnkType_10ae9a40::UnkMethod_10ae9a40
UnkType_10ae9a40Entry *UnkType_10ae9a40::UnkMethod_10ae9a40(int index, bool flag)
{
    if (index >= 0)
    {
        if (flag)
        {
            if (index < unk_a4)
                return &unk_a0[index];
        }
        else
        {
            if (index < unk_98)
                return &unk_94[index];
        }
    }
    return 0;
}
