// campaign_leaf_491500.cpp -- constructor at VA 0x10d91500: clears the dword at offset 0, then
// passes the dword its argument refers to to the method at VA 0x10d91210 on the same object. All
// names are invented.

class UnkType_10d91500
{
public:
    UnkType_10d91500(const int& Value);
    void Unk_10d91210(int Value);

private:
    int unk_00;
};

// UnkType_10d91500::UnkType_10d91500
UnkType_10d91500::UnkType_10d91500(const int& Value)
{
    unk_00 = 0;
    Unk_10d91210(Value);
}
