// campaign_leaf_76c8f0.cpp -- thiscall method at VA 0x1106c8f0: calls the method at VA 0x1106cdf0
// on the object at 0x30, then the method at VA 0x110712d0 on the object at 0x24. All names are
// invented.

class UnkType_1106cdf0
{
public:
    void Unk_1106cdf0();
};

class UnkType_110712d0
{
public:
    void Unk_110712d0();
};

class UnkType_1106c8f0
{
public:
    void Unk_1106c8f0();

private:
    int unk_00[9];
    UnkType_110712d0* unk_24;
    int unk_28;
    int unk_2c;
    UnkType_1106cdf0* unk_30;
};

// UnkType_1106c8f0::Unk_1106c8f0
void UnkType_1106c8f0::Unk_1106c8f0()
{
    unk_30->Unk_1106cdf0();
    unk_24->Unk_110712d0();
}
