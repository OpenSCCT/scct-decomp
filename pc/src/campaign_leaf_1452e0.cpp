// campaign_leaf_1452e0.cpp -- returns 1 when the pointer at offset 0x30 of this is set and the
// dword at offset 0x428 of the object it points to is 0x27, otherwise 0. File offset 0x1452e0, VA
// 0x10a452e0. The class and method names are invented; the offsets are the binary's, and the
// pointee type is a guess.

class UnkTarget_10a452e0;

class UnkType_10a452e0
{
public:
    int TestUnk30Unk428Is27();

private:
    unsigned char unk_00[0x30];     // not read by this function
    UnkTarget_10a452e0 *unk_30;     // guess: pointer to another object
};

class UnkTarget_10a452e0
{
public:
    unsigned char unk_00[0x428];    // not read by this function
    int unk_428;
};

// UnkType_10a452e0::TestUnk30Unk428Is27
int UnkType_10a452e0::TestUnk30Unk428Is27()
{
    if ( unk_30 && unk_30->unk_428 == 0x27 )
    {
        return 1;
    }
    return 0;
}
