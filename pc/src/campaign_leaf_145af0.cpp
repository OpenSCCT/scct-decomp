// campaign_leaf_145af0.cpp -- returns the dword at offset 0x04 of the object that the pointer at
// offset 0x00 of the object at offset 0x00 of this points to. File offset 0x145af0, VA 0x10a45af0.
// The class and method names are invented; the offsets are the binary's, and the pointee types are
// guesses.

class UnkTarget_10a45af0;
class UnkLink_10a45af0;

class UnkType_10a45af0
{
public:
    int UnkMethod_10a45af0();

private:
    UnkLink_10a45af0 *unk_00;       // guess: pointer to a link object
};

class UnkLink_10a45af0
{
public:
    UnkTarget_10a45af0 *unk_00;     // guess: pointer to another object
};

class UnkTarget_10a45af0
{
public:
    unsigned char unk_00[4];        // not read by this function
    int unk_04;
};

// UnkType_10a45af0::UnkMethod_10a45af0
int UnkType_10a45af0::UnkMethod_10a45af0()
{
    return unk_00->unk_00->unk_04;
}
