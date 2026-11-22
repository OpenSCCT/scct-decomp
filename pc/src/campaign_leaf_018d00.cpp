// campaign_leaf_018d00.cpp -- method at VA 0x10918d00: calls the method at VA 0x10918d10 and then
// the method at VA 0x109155e0 on the same object. The class and method names are invented; the
// addresses are the binary's.

class UnkType_10918d00
{
public:
    void Unk_10918d00();
    void Unk_10918d10();
    void Unk_109155e0();
};

// UnkType_10918d00::Unk_10918d00
void UnkType_10918d00::Unk_10918d00()
{
    Unk_10918d10();
    Unk_109155e0();
}
