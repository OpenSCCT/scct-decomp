// campaign_leaf_757fb0.cpp -- one function at file offset 0x757fb0, preferred VA 0x11057fb0. It
// copies selected words of one record into another of a different layout, member by member. It
// has no this pointer. The class, function and member names are invented; the offset and the bytes
// are the binary's.

struct UnkType_11057fb0_Source
{
    int unk_0;
    int unk_4;
    unsigned char unk_8[0x14 - 0x8];
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
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4c;
    int unk_50;
    int unk_54;
    int unk_58;
};

struct UnkType_11057fb0_Target
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
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
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4c;
    int unk_50;
};

// Unk_11057fb0
void Unk_11057fb0(const UnkType_11057fb0_Source* Source, UnkType_11057fb0_Target* Target)
{
    Target->unk_0 = Source->unk_0;
    Target->unk_4 = Source->unk_4;
    Target->unk_8 = Source->unk_14;
    Target->unk_18 = Source->unk_20;
    Target->unk_1c = Source->unk_24;
    Target->unk_10 = Source->unk_18;
    Target->unk_14 = Source->unk_1c;
    Target->unk_34 = Source->unk_3c;
    Target->unk_38 = Source->unk_40;
    Target->unk_3c = Source->unk_44;
    Target->unk_20 = Source->unk_28;
    Target->unk_24 = Source->unk_2c;
    Target->unk_28 = Source->unk_30;
    Target->unk_2c = Source->unk_34;
    Target->unk_30 = Source->unk_38;
    Target->unk_40 = Source->unk_48;
    Target->unk_44 = Source->unk_4c;
    Target->unk_48 = Source->unk_50;
    Target->unk_4c = Source->unk_54;
    Target->unk_50 = Source->unk_58;
}
