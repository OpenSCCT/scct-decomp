// campaign_leaf_498020.cpp -- thiscall at VA 0x10d98020: when the method at VA 0x10d97e40 of the
// global object at VA 0x1131a714 returns an object, calls its method at VA 0x10dc2140 with the
// dword at offset 0. All names are invented.

class UnkType_10dc2140
{
public:
    void Unk_10dc2140(int Value);
};

class UnkType_1131a714
{
public:
    UnkType_10dc2140* Unk_10d97e40();
};

extern UnkType_1131a714 GUnk_1131a714;

class UnkType_10d98020
{
public:
    void Unk_10d98020();

private:
    int unk_00;
};

// UnkType_10d98020::Unk_10d98020
void UnkType_10d98020::Unk_10d98020()
{
    UnkType_10dc2140* Object = GUnk_1131a714.Unk_10d97e40();
    if (Object) {
        Object->Unk_10dc2140(unk_00);
    }
}
