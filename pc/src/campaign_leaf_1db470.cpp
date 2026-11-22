// campaign_leaf_1db470.cpp -- stores the pointer argument at offset 0x38 of this and returns true,
// when the pointer at offset 0x34 of this, its pointer at offset 0x44 and the argument are all set;
// otherwise returns false. File offset 0x1db470, VA 0x10adb470. The class and method names are
// invented; the offsets are the binary's. The types and the meanings are guesses.

class UnkType_10adb470Target
{
public:
    unsigned char unk_00[0x44];     // not read by this function
    void *unk_44;
};

class UnkType_10adb470
{
public:
    bool UnkMethod_10adb470(void *value);

private:
    unsigned char unk_00[0x34];     // not read by this function
    UnkType_10adb470Target *unk_34;
    void *unk_38;
};

// UnkType_10adb470::UnkMethod_10adb470
bool UnkType_10adb470::UnkMethod_10adb470(void *value)
{
    if (unk_34 == 0 || unk_34->unk_44 == 0 || value == 0)
        return false;
    unk_38 = value;
    return true;
}
