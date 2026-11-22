// campaign_leaf_08dd00.cpp -- one function at file offset 0x8dd00, preferred VA 0x1098dd00. It
// stores its argument in the word at offset 0x40 of the object that the pointer at offset 0x33c
// designates, when that pointer is not null. The class, struct and method names are invented; the
// offset and the bytes are the binary's.

struct UnkType_1098dd00_Target
{
    unsigned char unk_00[0x40];     // not read by these functions
    int unk_40;
};

class UnkType_1098dd00
{
public:
    void UnkSet40(int Value);

private:
    unsigned char unk_00[0x33c];    // not read by this function
    UnkType_1098dd00_Target *unk_33c;
};

// UnkType_1098dd00::UnkSet40
void UnkType_1098dd00::UnkSet40(int Value)
{
    if ( unk_33c != 0 )
    {
        unk_33c->unk_40 = Value;
    }
}
