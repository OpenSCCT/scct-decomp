// campaign_leaf_4ade80.cpp -- thiscall at VA 0x10dade80: when the byte at offset 8 is set, calls
// the method at VA 0x10dad960 of the object at offset 0 with the dword at offset 4. All names
// are invented.

class UnkType_10dad960
{
public:
    void Unk_10dad960(int Value);
};

class UnkType_10dade80
{
public:
    void Unk_10dade80();

private:
    UnkType_10dad960* unk_00;
    int unk_04;
    bool unk_08;
};

// UnkType_10dade80::Unk_10dade80
void UnkType_10dade80::Unk_10dade80()
{
    if (unk_08) {
        unk_00->Unk_10dad960(unk_04);
    }
}
