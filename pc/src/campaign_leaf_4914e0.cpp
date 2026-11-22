// campaign_leaf_4914e0.cpp -- constructor at VA 0x10d914e0: clears the dword at offset 0, then
// passes its argument to the method at VA 0x10d91210 on the same object. All names are invented.

class UnkType_10d914e0
{
public:
    UnkType_10d914e0(int Value);
    void Unk_10d91210(int Value);

private:
    int unk_00;
};

// UnkType_10d914e0::UnkType_10d914e0
UnkType_10d914e0::UnkType_10d914e0(int Value)
{
    unk_00 = 0;
    Unk_10d91210(Value);
}
