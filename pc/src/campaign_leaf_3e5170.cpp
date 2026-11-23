// campaign_leaf_3e5170.cpp -- one function at file offset 0x3e5170, preferred VA 0x10ce5170. It
// returns whether the word at 0x8 equals the value the function at 0x10ccb7b0 gives for the text
// of the object at 0x34 of the object at 0x0 (data at 0x34, count at 0x38, an empty string when
// the count is zero), or equals 0 when there is no such object. The class, function, member and
// local names are invented; the offsets and the bytes are the binary's.

int Unk_10ccb7b0(const unsigned short* Text);

class UnkType_10ce5170_Named
{
public:
    unsigned char unk_0[0x34];
    const unsigned short* unk_34;
    int unk_38;
};

class UnkType_10ce5170_Owner
{
public:
    unsigned char unk_0[0x34];
    UnkType_10ce5170_Named* unk_34;
};

class UnkType_10ce5170
{
public:
    int Unk_10ce5170();

    UnkType_10ce5170_Owner* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10ce5170::Unk_10ce5170
int UnkType_10ce5170::Unk_10ce5170()
{
    UnkType_10ce5170_Named* Named = unk_0->unk_34;

    return (Named != 0 ? Unk_10ccb7b0(Named->unk_38 ? Named->unk_34 : L"") : 0) == unk_8;
}
