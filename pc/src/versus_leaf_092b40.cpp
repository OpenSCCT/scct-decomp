// versus_leaf_092b40.cpp -- the function at file offset 0x92b40, VA 0x10992b40, 50 bytes. It returns 1
// when its argument is null or is the object at +0x24, and otherwise 1 when the value at +0x110 of
// that object leaves no remainder when divided by the dword at +0x10c of the argument, else 0
// (ret 4).
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkInner_10992b40
{
public:
    unsigned char unk_00[0x110];    // not read by this function
    unsigned int unk_110;
};

class UnkOther_10992b40
{
public:
    unsigned char unk_00[0x10c];    // not read by this function
    unsigned int unk_10c;
};

class UnkType_10992b40
{
public:
    int UnkFunc_10992b40(UnkOther_10992b40 *Other);

private:
    unsigned char unk_00[0x24];     // not read by this function
    UnkInner_10992b40 *unk_24;
};

// UnkType_10992b40::UnkFunc_10992b40
int UnkType_10992b40::UnkFunc_10992b40(UnkOther_10992b40 *Other)
{
    unsigned int Remainder;
    if ( Other == 0 || (void *)unk_24 == (void *)Other )
    {
        return 1;
    }
    Remainder = unk_24->unk_110 % Other->unk_10c;
    return Remainder == 0;
}
