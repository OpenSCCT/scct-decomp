// campaign_leaf_4342f0.cpp -- thiscall at VA 0x10d342f0: stores at offset 4 the result of the
// method at VA 0x10d65530 of the object the global at VA 0x11317bf8 points to, called with its
// argument. All names are invented.

class UnkType_10d65530
{
public:
    int Unk_10d65530(int Value);
};

extern UnkType_10d65530* GUnk_11317bf8;

class UnkType_10d342f0
{
public:
    void Unk_10d342f0(int Value);

private:
    int unk_00;
    int unk_04;
};

// UnkType_10d342f0::Unk_10d342f0
void UnkType_10d342f0::Unk_10d342f0(int Value)
{
    unk_04 = GUnk_11317bf8->Unk_10d65530(Value);
}
