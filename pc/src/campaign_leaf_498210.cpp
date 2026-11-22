// campaign_leaf_498210.cpp -- free function at VA 0x10d98210: passes its argument to the method
// at VA 0x10dc74f0 of the global object at VA 0x1131a730. All names are invented.

class UnkType_1131a730
{
public:
    void Unk_10dc74f0(int Value);
};

extern UnkType_1131a730 GUnk_1131a730;

// Unk_10d98210
void Unk_10d98210(int Value)
{
    GUnk_1131a730.Unk_10dc74f0(Value);
}
