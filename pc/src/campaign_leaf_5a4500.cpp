// campaign_leaf_5a4500.cpp -- thiscall method at VA 0x10ea4500: passes its argument to the method at
// VA 0x10ea4470 on the same object, then clears the member at 0x10. The class and method names are
// invented.

class UnkType_10ea4500
{
public:
    void Unk_10ea4470(int Value);
    void Unk_10ea4500(int Value);

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
};

// UnkType_10ea4500::Unk_10ea4500
void UnkType_10ea4500::Unk_10ea4500(int Value)
{
    Unk_10ea4470(Value);
    unk_10 = 0;
}
