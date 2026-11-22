// campaign_leaf_157fd0.cpp -- returns the index of the first entry in the array at offset 0x120 of
// this, whose first dword equals the argument, or -1. An argument of zero gives -1 at once. File
// offset 0x157fd0, VA 0x10a57fd0. The class and method names are invented; the offsets are the
// binary's, and the entry type is a guess.

class UnkEntry_10a57fd0;

class UnkType_10a57fd0
{
public:
    int UnkMethod_10a57fd0(int Key);

private:
    unsigned char unk_00[0x120];    // not read by this function
    UnkEntry_10a57fd0 *unk_120;     // guess: array of entries
    int unk_124;                    // count of entries
};

class UnkEntry_10a57fd0
{
public:
    int unk_00;
    unsigned char unk_04[0x10];     // not read by this function
};

// UnkType_10a57fd0::UnkMethod_10a57fd0
int UnkType_10a57fd0::UnkMethod_10a57fd0(int Key)
{
    int i;
    int result;

    result = -1;
    if ( Key != 0 )
    {
        for ( i = 0; i < unk_124; i++ )
        {
            if ( unk_120[i].unk_00 == Key )
            {
                result = i;
                break;
            }
        }
    }
    return result;
}
