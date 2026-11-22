// campaign_leaf_400b40.cpp -- thiscall at VA 0x10d00b40: calls the method at VA 0x10cfde10 on the
// same object with its int argument times the float at offset 0x14, and its second argument. All
// names are invented.

class UnkType_10d00b40
{
public:
    void Unk_10cfde10(float Value, int Extra);
    void Unk_10d00b40(int Count, int Extra);

private:
    unsigned char unk_00[0x14];
    float unk_14;
};

// UnkType_10d00b40::Unk_10d00b40
void UnkType_10d00b40::Unk_10d00b40(int Count, int Extra)
{
    Unk_10cfde10(Count * unk_14, Extra);
}
