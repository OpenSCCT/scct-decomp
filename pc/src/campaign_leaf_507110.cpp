// campaign_leaf_507110.cpp -- thiscall at VA 0x10e07110: calls the method at VA 0x10e06fd0 of its
// argument with zero and the address of the member at offset 0x18. All names are invented.

class UnkType_10e06fd0
{
public:
    void Unk_10e06fd0(int Value, void* Member);
};

class UnkType_10e07110
{
public:
    void Unk_10e07110(UnkType_10e06fd0* Object);

private:
    unsigned char unk_00[0x18];
    int unk_18;
};

// UnkType_10e07110::Unk_10e07110
void UnkType_10e07110::Unk_10e07110(UnkType_10e06fd0* Object)
{
    Object->Unk_10e06fd0(0, &unk_18);
}
