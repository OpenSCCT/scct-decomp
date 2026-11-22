// campaign_leaf_179de0.cpp -- stores 0x182 in the dword at offset 0x28 of the object that the
// pointer at offset 0x0c of this points to. File offset 0x179de0, VA 0x10a79de0. The class and
// method names are invented; the offsets are the binary's, and the pointee type is a guess.

class UnkTarget_10a79de0;

class UnkType_10a79de0
{
public:
    void SetUnk0CUnk28();

private:
    unsigned char unk_00[0x0c];     // not read by this function
    UnkTarget_10a79de0 *unk_0c;     // guess: pointer to another object
};

class UnkTarget_10a79de0
{
public:
    unsigned char unk_00[0x28];     // not read by this function
    int unk_28;
};

// UnkType_10a79de0::SetUnk0CUnk28
void UnkType_10a79de0::SetUnk0CUnk28()
{
    unk_0c->unk_28 = 0x182;
}
