// campaign_leaf_47db50.cpp -- free function at VA 0x10d7db50: passes its argument to the method
// at VA 0x10d7cfe0 of the global object at VA 0x1131a5f4. All names are invented.

class UnkType_10d7cfe0
{
public:
    void Unk_10d7cfe0(int Value);
};

extern UnkType_10d7cfe0 GUnk_1131a5f4;

// Unk_10d7db50
void Unk_10d7db50(int Value)
{
    GUnk_1131a5f4.Unk_10d7cfe0(Value);
}
