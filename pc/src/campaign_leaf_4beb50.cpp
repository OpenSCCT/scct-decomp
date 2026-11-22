// campaign_leaf_4beb50.cpp -- thiscall at VA 0x10dbeb50: passes the result of the method at
// VA 0x10dbfa10 to the method at VA 0x10dbeb10, both on the same object. All names are invented.

class UnkType_10dbeb50
{
public:
    int Unk_10dbfa10();
    void Unk_10dbeb10(int Value);
    void Unk_10dbeb50();
};

// UnkType_10dbeb50::Unk_10dbeb50
void UnkType_10dbeb50::Unk_10dbeb50()
{
    Unk_10dbeb10(Unk_10dbfa10());
}
