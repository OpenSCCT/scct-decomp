// campaign_leaf_09bb30.cpp -- method at VA 0x1099bb30: passes this object, by reference, to the
// method at VA 0x1099b960 of the member at 0x728 in the object the pointer at 0x78 points to, and
// returns the result. The class, member and method names are invented; the offsets and the
// addresses are the binary's.

class UnkType_1099bb30;

class UnkType_1099bb30_1099b960
{
public:
    int Unk_1099b960(UnkType_1099bb30* const& Item);
};

class UnkType_1099bb30_78
{
public:
    unsigned char unk_000[0x728];
    UnkType_1099bb30_1099b960 unk_728;
};

class UnkType_1099bb30
{
public:
    int Unk_1099bb30();

private:
    unsigned char unk_00[0x78];
    UnkType_1099bb30_78* unk_78;
};

// UnkType_1099bb30::Unk_1099bb30
int UnkType_1099bb30::Unk_1099bb30()
{
    return unk_78->unk_728.Unk_1099b960(this);
}
