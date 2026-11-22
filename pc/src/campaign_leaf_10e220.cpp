// campaign_leaf_10e220.cpp -- returns unk_2c of this when it is nonzero. Otherwise it returns the
// dword that the pointers unk_30, then unk_28, then unk_2c lead to. File offset 0x10e220, VA
// 0x10a0e220. The class and method names are invented; the pointee types are guesses.

class UnkTarget_10a0e220_30;

class UnkType_10a0e220
{
public:
    int GetUnk2COrChainValue();

private:
    unsigned char unk_00[0x2c];     // not read by this function
    int unk_2c;
    UnkTarget_10a0e220_30 *unk_30;  // guess: pointer to another object
};

class UnkTarget_10a0e220_28;

class UnkTarget_10a0e220_30
{
public:
    unsigned char unk_00[0x28];     // not read by this function
    UnkTarget_10a0e220_28 *unk_28;  // guess: pointer to another object
};

class UnkTarget_10a0e220_28
{
public:
    unsigned char unk_00[0x2c];     // not read by this function
    int *unk_2c;                    // guess: pointer to a dword
};

// UnkType_10a0e220::GetUnk2COrChainValue
int UnkType_10a0e220::GetUnk2COrChainValue()
{
    if ( unk_2c != 0 )
    {
        return unk_2c;
    }
    return *unk_30->unk_28->unk_2c;
}
