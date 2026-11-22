// campaign_leaf_1d4770.cpp -- method at VA 0x10ad4770: fetches an object from the function at VA
// 0x10adb390, which takes no arguments, and calls the method at VA 0x10adb970 on it with the value
// at 0x0c of this object. The class, member and function names are invented; the offsets and the
// addresses are the binary's.

class UnkType_10ad4770_10adb970
{
public:
    void Unk_10adb970(int Value);
};

UnkType_10ad4770_10adb970* Unk_10adb390();

class UnkType_10ad4770
{
public:
    void Unk_10ad4770();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

// UnkType_10ad4770::Unk_10ad4770
void UnkType_10ad4770::Unk_10ad4770()
{
    Unk_10adb390()->Unk_10adb970(unk_0c);
}
