// campaign_leaf_1032b0.cpp -- returns the pointer at offset 0x2b4 of this if it is set, otherwise
// this. File offset 0x1032b0, VA 0x10a032b0. The class and method names are invented; the offsets
// are the binary's, and the pointer's type is a guess.

class UnkType_10a032b0
{
public:
    UnkType_10a032b0 *UnkMethod_10a032b0();

private:
    unsigned char unk_00[0x2b4];    // not read by this function
    UnkType_10a032b0 *unk_2b4;      // guess: pointer to the same class
};

// UnkType_10a032b0::UnkMethod_10a032b0
UnkType_10a032b0 *UnkType_10a032b0::UnkMethod_10a032b0()
{
    return unk_2b4 ? unk_2b4 : this;
}
