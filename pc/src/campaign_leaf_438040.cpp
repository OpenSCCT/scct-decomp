// campaign_leaf_438040.cpp -- method at VA 0x10d38040: multiplies the float at 0x188 by 100, pops
// the byte stack depth at 0x12c and, by the kind at 0x130 of the entry now on top, copies the
// value at 0x180 to 0x184 (kind 0) or also loads 0x180 from the entry's value at 0x18c (kind 2);
// then sets the byte at 0x1b4. The class, member and method names are invented; the offsets and
// the constants are the binary's.

class UnkType_10d38040
{
public:
    void Unk_10d38040();

private:
    char unk_0[0x12c];
    unsigned char unk_12c;
    char unk_12d[0x130 - 0x12d];
    int unk_130[0x14];
    int unk_180;
    int unk_184;
    float unk_188;
    int unk_18c[0xa];
    unsigned char unk_1b4;
};

// UnkType_10d38040::Unk_10d38040
void UnkType_10d38040::Unk_10d38040()
{
    unk_188 *= 100.0f;
    unk_12c--;
    switch ( unk_130[unk_12c] )
    {
    case 0:
        unk_184 = unk_180;
        break;
    case 2:
        unk_184 = unk_180;
        unk_180 = unk_18c[unk_12c];
        break;
    }
    unk_1b4 = 1;
}
