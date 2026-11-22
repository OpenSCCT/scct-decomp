// campaign_leaf_462280.cpp -- thiscall at VA 0x10d62280: when the pointer at offset 0x1c is set,
// calls its method at VA 0x10d308c0 with the dword at offset 0x50 and 0, then calls the method at
// VA 0x10d5a5f0. All names are invented.

class UnkType_10d308c0
{
public:
    void Unk_10d308c0(int Value, int Flags);
};

class UnkType_10d62280
{
public:
    void Unk_10d5a5f0();
    void Unk_10d62280();

private:
    unsigned char unk_00[0x1c];
    UnkType_10d308c0* unk_1c;
    unsigned char unk_20[0x30];
    int unk_50;
};

// UnkType_10d62280::Unk_10d62280
void UnkType_10d62280::Unk_10d62280()
{
    if (unk_1c) {
        unk_1c->Unk_10d308c0(unk_50, 0);
    }
    Unk_10d5a5f0();
}
