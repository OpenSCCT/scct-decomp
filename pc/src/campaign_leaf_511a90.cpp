// campaign_leaf_511a90.cpp -- method at VA 0x10e11a90: calls the method at VA 0x10e0a180 with its
// argument, then copies the twelve words at 0x10-0x3c into the argument. The class, method and
// member names are invented; the offsets and the address are the binary's.

class UnkType_10e11a90
{
public:
    void Unk_10e11a90(UnkType_10e11a90* Other);
    void Unk_10e0a180(UnkType_10e11a90* Other);

    unsigned char unk_00[0x10];
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
};

// UnkType_10e11a90::Unk_10e11a90
void UnkType_10e11a90::Unk_10e11a90(UnkType_10e11a90* Other)
{
    Unk_10e0a180(Other);
    Other->unk_10 = unk_10;
    Other->unk_14 = unk_14;
    Other->unk_18 = unk_18;
    Other->unk_1c = unk_1c;
    Other->unk_20 = unk_20;
    Other->unk_24 = unk_24;
    Other->unk_28 = unk_28;
    Other->unk_2c = unk_2c;
    Other->unk_30 = unk_30;
    Other->unk_34 = unk_34;
    Other->unk_38 = unk_38;
    Other->unk_3c = unk_3c;
}
