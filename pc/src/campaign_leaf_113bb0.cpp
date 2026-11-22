// campaign_leaf_113bb0.cpp -- clears bit 0x800 of the dword at offset 0x98 of the object that the
// pointer at offset 0x48 of this points to, when that pointer is set. File offset 0x113bb0, VA
// 0x10a13bb0. The class and method names are invented; the offsets are the binary's, and the
// pointee type is a guess.

class UnkTarget_10a13bb0;

class UnkType_10a13bb0
{
public:
    void ClearUnk48Unk98Bit800();

private:
    unsigned char unk_00[0x48];     // not read by this function
    UnkTarget_10a13bb0 *unk_48;     // guess: pointer to another object
};

class UnkTarget_10a13bb0
{
public:
    unsigned char unk_00[0x98];     // not read by this function
    unsigned int unk_98;            // guess: a flag word
};

// UnkType_10a13bb0::ClearUnk48Unk98Bit800
void UnkType_10a13bb0::ClearUnk48Unk98Bit800()
{
    if ( unk_48 )
    {
        unk_48->unk_98 &= 0xfffff7ff;
    }
}
