// campaign_leaf_1e9a90.cpp -- returns the first dword of the entry at the index argument of one of
// two 8-byte entry arrays of this, chosen by the flag argument, or -1 when the index is negative or
// not below the count of the chosen array. File offset 0x1e9a90, VA 0x10ae9a90. The class and
// method names are invented; the offsets are the binary's. The entry layout and the meanings of the
// arrays are guesses.

class UnkType_10ae9a90Entry
{
public:
    int unk_00;
    unsigned char unk_04[0x04];
};

class UnkType_10ae9a90
{
public:
    int UnkMethod_10ae9a90(int index, bool flag);

private:
    unsigned char unk_00[0x7c];     // not read by this function
    UnkType_10ae9a90Entry *unk_7c;
    int unk_80;
    unsigned char unk_84[0x04];     // not read by this function
    UnkType_10ae9a90Entry *unk_88;
    int unk_8c;
};

// UnkType_10ae9a90::UnkMethod_10ae9a90
int UnkType_10ae9a90::UnkMethod_10ae9a90(int index, bool flag)
{
    if (index < 0)
        return -1;
    if (flag)
    {
        if (index >= unk_8c)
            return -1;
        return unk_88[index].unk_00;
    }
    if (index >= unk_80)
        return -1;
    return unk_7c[index].unk_00;
}
