// campaign_leaf_1a7d00.cpp -- returns 1 when the pointer at offset 0x4c4 of this is set and bit
// 0x01 of the byte at offset 0x2c of the object it points to is set, otherwise 0. File offset
// 0x1a7d00, VA 0x10aa7d00. The class and method names are invented; the offsets are the binary's,
// and the pointee type is a guess.

class UnkTarget_10aa7d00;

class UnkType_10aa7d00
{
public:
    int UnkMethod_10aa7d00();

private:
    unsigned char unk_00[0x4c4];    // not read by this function
    UnkTarget_10aa7d00 *unk_4c4;    // guess: pointer to another object
};

class UnkTarget_10aa7d00
{
public:
    unsigned char unk_00[0x2c];     // not read by this function
    unsigned char unk_2c;
};

// UnkType_10aa7d00::UnkMethod_10aa7d00
int UnkType_10aa7d00::UnkMethod_10aa7d00()
{
    if ( unk_4c4 && ( unk_4c4->unk_2c & 1 ) )
    {
        return 1;
    }
    return 0;
}
