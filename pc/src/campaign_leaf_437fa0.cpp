// campaign_leaf_437fa0.cpp -- method at VA 0x10d37fa0: multiplies the float at 0x188 by 0.01, by
// the kind at 0x130 of the entry on top of the byte stack depth at 0x12c saves the value at 0x180
// in the entry's value at 0x18c (kind 0) and also loads 0x180 from 0x184 (kind 2), then pushes a
// copy of the top entry's kind and a cleared value at 0x158, and sets the byte at 0x1b4. The
// class, member and method names are invented; the offsets and the constant are the binary's.

class UnkType_10d37fa0
{
public:
    void Unk_10d37fa0();

private:
    char unk_0[0x12c];
    unsigned char unk_12c;
    char unk_12d[0x130 - 0x12d];
    int unk_130[0xa];
    int unk_158[0xa];
    int unk_180;
    int unk_184;
    float unk_188;
    int unk_18c[0xa];
    unsigned char unk_1b4;
};

// UnkType_10d37fa0::Unk_10d37fa0
void UnkType_10d37fa0::Unk_10d37fa0()
{
    unk_188 *= 0.01f;
    switch ( unk_130[unk_12c] )
    {
    case 0:
        unk_18c[unk_12c] = unk_180;
        break;
    case 2:
        unk_18c[unk_12c] = unk_180;
        unk_180 = unk_184;
        break;
    }
    unk_130[unk_12c + 1] = unk_130[unk_12c];
    unk_158[unk_12c + 1] = unk_158[unk_12c];
    unk_12c++;
    unk_158[unk_12c] = 0;
    unk_1b4 = 1;
}
