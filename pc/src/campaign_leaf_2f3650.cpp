// campaign_leaf_2f3650.cpp -- method at VA 0x10bf3650: with Total the float at 0x4b4 times the
// float at 0x4b0, returns whether Total, less the float at 0x4cc times the float at 0x4b0, less
// the float at 0x4d0, over Total, exceeds 1 less the float at 0x4bc. The class, member and method
// names are invented; the offsets are the binary's.

class UnkType_10bf3650
{
public:
    int Unk_10bf3650();

private:
    char unk_0[0x4b0];
    float unk_4b0;
    float unk_4b4;
    char unk_4b8[0x4bc - 0x4b8];
    float unk_4bc;
    char unk_4c0[0x4cc - 0x4c0];
    float unk_4cc;
    float unk_4d0;
};

// UnkType_10bf3650::Unk_10bf3650
int UnkType_10bf3650::Unk_10bf3650()
{
    float Total = unk_4b4 * unk_4b0;

    return ( Total - unk_4cc * unk_4b0 - unk_4d0 ) / Total > 1.0f - unk_4bc;
}
