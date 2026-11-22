// campaign_leaf_4801b0.cpp -- thiscall at VA 0x10d801b0: passes its four-byte by-value argument to the
// method at VA 0x10d8ef70 on the same object, and returns the object. All names are invented.

class UnkType_10d801b0_Param
{
public:
    UnkType_10d801b0_Param(const UnkType_10d801b0_Param& Other) : unk_00(Other.unk_00) {}

private:
    int unk_00;
};

class UnkType_10d801b0
{
public:
    void Unk_10d8ef70(UnkType_10d801b0_Param Value);
    UnkType_10d801b0& Unk_10d801b0(UnkType_10d801b0_Param Value);
};

// UnkType_10d801b0::Unk_10d801b0
UnkType_10d801b0& UnkType_10d801b0::Unk_10d801b0(UnkType_10d801b0_Param Value)
{
    Unk_10d8ef70(Value);
    return *this;
}
