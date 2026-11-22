// campaign_leaf_40eb70.cpp -- thiscall at VA 0x10d0eb70: passes the dwords at offsets 0x150 and 0x154
// in turn to the free function at VA 0x11042e50. All names are invented.

void Unk_11042e50(int Value);

class UnkType_10d0eb70
{
public:
    void Unk_10d0eb70();

private:
    unsigned char unk_00[0x150];
    int unk_150;
    int unk_154;
};

// UnkType_10d0eb70::Unk_10d0eb70
void UnkType_10d0eb70::Unk_10d0eb70()
{
    Unk_11042e50(unk_150);
    Unk_11042e50(unk_154);
}
