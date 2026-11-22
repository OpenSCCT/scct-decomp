// campaign_leaf_36ee60.cpp -- one function at file offset 0x36ee60, preferred VA 0x10c6ee60. It
// steps the float at 0x274 of the object at 0x2b4 to 0.01 when Up is set and that object's word
// at 0x26c exceeds 2, or to -0.01 when Up is clear and its word at 0x270 is below the word at
// 0x370 here; it returns 1 when it set a step. The class, method, structure, member and
// parameter names are invented; the offsets, the constants and the bytes are the binary's.

struct UnkObject
{
    unsigned char unk_0[0x26c];
    int unk_26c;
    int unk_270;
    float unk_274;
};

class UnkType_10c6ee60
{
public:
    int Unk_10c6ee60(int Up);

    unsigned char unk_0[0x2b4];
    UnkObject* unk_2b4;
    unsigned char unk_2b8[0xb8];
    int unk_370;
};

// UnkType_10c6ee60::Unk_10c6ee60
int UnkType_10c6ee60::Unk_10c6ee60(int Up)
{
    if ( Up != 0 )
    {
        if ( unk_2b4->unk_26c > 2 )
        {
            unk_2b4->unk_274 = 0.01f;
            return 1;
        }
    }
    else if ( unk_2b4->unk_270 < unk_370 )
    {
        unk_2b4->unk_274 = -0.01f;
        return 1;
    }
    return 0;
}
