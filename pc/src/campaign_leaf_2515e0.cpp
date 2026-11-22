// campaign_leaf_2515e0.cpp -- a member function at VA 0x10b515e0 that passes its argument to the
// member at VA 0x10b75bb0 of the object at 0x14 and then the pointer at 0x08 to the free function
// at VA 0x10b75e90. The class, method and member names are invented; the offsets and addresses are
// the binary's.

void Unk_10b75e90(void* Item);

class UnkType_10b75bb0
{
public:
    void Unk_10b75bb0(int Value);
};

class UnkType_10b515e0
{
public:
    void Unk_10b515e0(int Value);

private:
    int unk_00;
    int unk_04;
    void* unk_08;
    int unk_0c;
    int unk_10;
    UnkType_10b75bb0 unk_14;
};

// UnkType_10b515e0::Unk_10b515e0
void UnkType_10b515e0::Unk_10b515e0(int Value)
{
    unk_14.Unk_10b75bb0(Value);
    Unk_10b75e90(unk_08);
}
