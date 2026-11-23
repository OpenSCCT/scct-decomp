// campaign_leaf_02df70.cpp -- method at VA 0x1092df70: passes its argument, this object and a local
// 12-byte value to the free function at VA 0x1092dca0, which fills the value, and returns it. The
// class and function names are invented; the size and the address are the binary's.

class UnkType_1092df70_Vector
{
public:
    float X;
    float Y;
    float Z;
};

class UnkType_1092df70;

void Unk_1092dca0(int Value, const UnkType_1092df70* Object, UnkType_1092df70_Vector* Result);

class UnkType_1092df70
{
public:
    UnkType_1092df70_Vector Unk_1092df70(int Value) const;
};

// UnkType_1092df70::Unk_1092df70
UnkType_1092df70_Vector UnkType_1092df70::Unk_1092df70(int Value) const
{
    UnkType_1092df70_Vector Result;
    Unk_1092dca0(Value, this, &Result);
    return Result;
}
