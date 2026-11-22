// campaign_leaf_4978c0.cpp -- free function at VA 0x10d978c0: calls the method at VA 0x10d976f0
// on the global objects at VA 0x1131a6cc and 0x1131a6e4. All names are invented.

class UnkType_10d976f0
{
public:
    void Unk_10d976f0();
};

extern UnkType_10d976f0 GUnk_1131a6cc;
extern UnkType_10d976f0 GUnk_1131a6e4;

// Unk_10d978c0
void Unk_10d978c0()
{
    GUnk_1131a6cc.Unk_10d976f0();
    GUnk_1131a6e4.Unk_10d976f0();
}
