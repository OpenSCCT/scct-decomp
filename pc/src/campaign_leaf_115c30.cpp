// campaign_leaf_115c30.cpp -- returns the value at offset 0x48 of this, or the value at offset 0x4c
// or 0x50 when the argument's kind at offset 0x18 selects it and that value is set, otherwise 0.
// File offset 0x115c30, VA 0x10a15c30. The class and method names are invented; the offsets are
// the binary's, and the argument type is a guess.

class UnkArg_10a15c30;

class UnkType_10a15c30
{
public:
    int UnkMethod_10a15c30(UnkArg_10a15c30 *Arg);

private:
    unsigned char unk_00[0x48];     // not read by this function
    int unk_48;
    int unk_4c;
    int unk_50;
};

class UnkArg_10a15c30
{
public:
    unsigned char unk_00[0x18];     // not read by this function
    int unk_18;                     // selects the value
};

// UnkType_10a15c30::UnkMethod_10a15c30
int UnkType_10a15c30::UnkMethod_10a15c30(UnkArg_10a15c30 *Arg)
{
    int value;

    switch ( Arg->unk_18 )
    {
    case 0:
        return unk_48;

    case 1:
        value = unk_4c;
        break;

    case 2:
        value = unk_50;
        break;

    default:
        return 0;
    }

    if ( value != 0 )
    {
        return value;
    }
    return unk_48;
}
