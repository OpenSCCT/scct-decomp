// campaign_leaf_351630.cpp -- one function at file offset 0x351630, preferred VA 0x10c51630. It
// returns 0 when the method at 0x10bee910 fails for (First, Second); otherwise it passes each of
// the 0x20-byte blocks at 0x3fc, 0x41c, 0x43c and 0x45c with First to the function at 0x10bee990
// and returns 1. The class, function, structure, member and parameter names are invented; the
// offsets and the bytes are the binary's.

struct UnkType_10c51630_Block
{
    unsigned char unk_0[0x20];
};

void Unk_10bee990(UnkType_10c51630_Block* Block, int First);

class UnkType_10c51630
{
public:
    int Unk_10bee910(int First, int Second);
    int Unk_10c51630(int First, int Second);

    unsigned char unk_0[0x3fc];
    UnkType_10c51630_Block unk_3fc;
    UnkType_10c51630_Block unk_41c;
    UnkType_10c51630_Block unk_43c;
    UnkType_10c51630_Block unk_45c;
};

// UnkType_10c51630::Unk_10c51630
int UnkType_10c51630::Unk_10c51630(int First, int Second)
{
    if ( Unk_10bee910(First, Second) )
    {
        Unk_10bee990(&unk_3fc, First);
        Unk_10bee990(&unk_41c, First);
        Unk_10bee990(&unk_43c, First);
        Unk_10bee990(&unk_45c, First);
        return 1;
    }
    return 0;
}
