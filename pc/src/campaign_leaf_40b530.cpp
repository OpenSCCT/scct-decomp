// campaign_leaf_40b530.cpp -- thiscall at VA 0x10d0b530: calls the method at VA 0x10d0a8e0 on the
// same object, then the method at VA 0x10d07700 of the object at offset 0x4c when it is not
// null. All names are invented.

class UnkType_10d07700
{
public:
    void Unk_10d07700();
};

class UnkType_10d0b530
{
public:
    void Unk_10d0a8e0();
    void Unk_10d0b530();

private:
    unsigned char unk_00[0x4c];
    UnkType_10d07700* unk_4c;
};

// UnkType_10d0b530::Unk_10d0b530
void UnkType_10d0b530::Unk_10d0b530()
{
    Unk_10d0a8e0();
    if (unk_4c) {
        unk_4c->Unk_10d07700();
    }
}
