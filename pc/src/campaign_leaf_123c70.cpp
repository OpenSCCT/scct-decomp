// campaign_leaf_123c70.cpp -- returns 1 when the pointer at offset 0x360 of this is set and the byte
// at offset 0x1e2 of the object it points to is nonzero, otherwise 0. File offset 0x123c70, VA
// 0x10a23c70. The class and method names are invented; the offsets are the binary's, and the
// pointee type is a guess.

class UnkTarget_10a23c70;

class UnkType_10a23c70
{
public:
    int TestUnk360Unk1E2();

private:
    unsigned char unk_00[0x360];    // not read by this function
    UnkTarget_10a23c70 *unk_360;    // guess: pointer to another object
};

class UnkTarget_10a23c70
{
public:
    unsigned char unk_00[0x1e2];    // not read by this function
    unsigned char unk_1e2;
};

// UnkType_10a23c70::TestUnk360Unk1E2
int UnkType_10a23c70::TestUnk360Unk1E2()
{
    if ( unk_360 && unk_360->unk_1e2 )
    {
        return 1;
    }
    return 0;
}
