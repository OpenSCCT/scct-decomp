// campaign_leaf_01ab10.cpp -- method at VA 0x1091ab10: calls the method at VA 0x10918d10 and then
// the method at VA 0x109155e0 on the same object. The class and method names are invented; the
// addresses are the binary's.

class UnkType_1091ab10
{
public:
    void Unk_1091ab10();
    void Unk_10918d10();
    void Unk_109155e0();
};

// UnkType_1091ab10::Unk_1091ab10
void UnkType_1091ab10::Unk_1091ab10()
{
    Unk_10918d10();
    Unk_109155e0();
}
