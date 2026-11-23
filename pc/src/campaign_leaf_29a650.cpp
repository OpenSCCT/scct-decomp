// campaign_leaf_29a650.cpp -- method at VA 0x10b9a650: returns whether the float at 0x430 of the
// object at 0x78, less the float at 0x50 of the object at 0x41c, is below 0.2. The class, member
// and method names are invented; the offsets and the constant are the binary's.

class UnkType_10b9a650_78
{
public:
    char unk_0[0x430];
    float unk_430;
};

class UnkType_10b9a650_41c
{
public:
    char unk_0[0x50];
    float unk_50;
};

class UnkType_10b9a650
{
public:
    int Unk_10b9a650();

private:
    char unk_0[0x78];
    UnkType_10b9a650_78* unk_78;
    char unk_7c[0x41c - 0x7c];
    UnkType_10b9a650_41c* unk_41c;
};

// UnkType_10b9a650::Unk_10b9a650
int UnkType_10b9a650::Unk_10b9a650()
{
    return unk_78->unk_430 - unk_41c->unk_50 < 0.2f;
}
