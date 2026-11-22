// campaign_leaf_123c50.cpp -- returns 1 when the pointer at offset 0x360 of this is set and the
// byte at offset 0x1e1 of the object it points to is nonzero, otherwise 0. File offset 0x123c50, VA
// 0x10a23c50. The class and method names are invented; the offsets are the binary's, and the
// pointee type is a guess.

class UnkTarget_10a23c50;

class UnkType_10a23c50
{
public:
    int TestUnk360Unk1E1();

private:
    unsigned char unk_00[0x360];    // not read by this function
    UnkTarget_10a23c50 *unk_360;    // guess: pointer to another object
};

class UnkTarget_10a23c50
{
public:
    unsigned char unk_00[0x1e1];    // not read by this function
    unsigned char unk_1e1;
};

// UnkType_10a23c50::TestUnk360Unk1E1
int UnkType_10a23c50::TestUnk360Unk1E1()
{
    if ( unk_360 && unk_360->unk_1e1 )
    {
        return 1;
    }
    return 0;
}
