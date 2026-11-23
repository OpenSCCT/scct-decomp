// campaign_leaf_02dfb0.cpp -- method at VA 0x1092dfb0: passes its argument, this object and a local
// 12-byte value to the free function at VA 0x1092df00, which fills the value, and returns it. The
// class and function names are invented; the size and the address are the binary's.

class UnkType_1092dfb0_Vector
{
public:
    float X;
    float Y;
    float Z;
};

class UnkType_1092dfb0;

void Unk_1092df00(int Value, const UnkType_1092dfb0* Object, UnkType_1092dfb0_Vector* Result);

class UnkType_1092dfb0
{
public:
    UnkType_1092dfb0_Vector Unk_1092dfb0(int Value) const;
};

// UnkType_1092dfb0::Unk_1092dfb0
UnkType_1092dfb0_Vector UnkType_1092dfb0::Unk_1092dfb0(int Value) const
{
    UnkType_1092dfb0_Vector Result;
    Unk_1092df00(Value, this, &Result);
    return Result;
}
