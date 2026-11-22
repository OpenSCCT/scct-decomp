// campaign_leaf_1dbd10.cpp -- method at VA 0x10adbd10: passes the result of the method at VA
// 0x10adb9d0 to the method at VA 0x10adb970, both on the same object. The class and method names
// are invented; the addresses are the binary's.

class UnkType_10adbd10
{
public:
    void Unk_10adbd10();
    void Unk_10adb970(int Value);
    int Unk_10adb9d0();
};

// UnkType_10adbd10::Unk_10adbd10
void UnkType_10adbd10::Unk_10adbd10()
{
    Unk_10adb970(Unk_10adb9d0());
}
