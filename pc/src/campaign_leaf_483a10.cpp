// campaign_leaf_483a10.cpp -- thiscall at VA 0x10d83a10: calls the method at VA 0x10d8ed00 of the
// member at offset 8, then the method at VA 0x10d98ff0 of the member at offset 0x18 with 1. All
// names are invented.

class UnkType_10d8ed00
{
public:
    void Unk_10d8ed00();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

class UnkType_10d98ff0
{
public:
    void Unk_10d98ff0(int Value);
};

class UnkType_10d83a10
{
public:
    void Unk_10d83a10();

private:
    int unk_00;
    int unk_04;
    UnkType_10d8ed00 unk_08;
    UnkType_10d98ff0 unk_18;
};

// UnkType_10d83a10::Unk_10d83a10
void UnkType_10d83a10::Unk_10d83a10()
{
    unk_08.Unk_10d8ed00();
    unk_18.Unk_10d98ff0(1);
}
