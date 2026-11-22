// campaign_leaf_493d70.cpp -- thiscall at VA 0x10d93d70: passes the member at offset 8 of its
// argument by reference to the method at VA 0x10d939b0 of the member at offset 8, and returns the
// object. All names are invented.

class UnkType_10d939b0
{
public:
    void Unk_10d939b0(const UnkType_10d939b0& Other);

private:
    int unk_00;
};

class UnkType_10d93d70
{
public:
    UnkType_10d93d70& Unk_10d93d70(const UnkType_10d93d70& Other);

private:
    int unk_00;
    int unk_04;
    UnkType_10d939b0 unk_08;
};

// UnkType_10d93d70::Unk_10d93d70
UnkType_10d93d70& UnkType_10d93d70::Unk_10d93d70(const UnkType_10d93d70& Other)
{
    unk_08.Unk_10d939b0(Other.unk_08);
    return *this;
}
