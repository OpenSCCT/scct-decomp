// campaign_leaf_1decf0.cpp -- thiscall method at VA 0x10adecf0. With three arguments, the second
// and third pointing at floats: when the object at 0x04 is set and the second argument's float is
// below the float at 0x0c, it calls slot 1 of that object with the three arguments; when the object
// at 0x08 is set and the third argument's float is not below the float at 0x0c, it calls slot 1 of
// that object with them. The class, method and member names are invented.

class UnkType_10adecf0_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(int Value, const float* First, const float* Second);
};

class UnkType_10adecf0
{
public:
    void Unk_10adecf0(int Value, const float* First, const float* Second);

private:
    int unk_00;
    UnkType_10adecf0_Target* unk_04;
    UnkType_10adecf0_Target* unk_08;
    float unk_0c;
};

// UnkType_10adecf0::Unk_10adecf0
void UnkType_10adecf0::Unk_10adecf0(int Value, const float* First, const float* Second)
{
    if ( unk_04 != 0 && *First < unk_0c )
    {
        unk_04->VirtualSlot1(Value, First, Second);
    }
    if ( unk_08 != 0 && *Second >= unk_0c )
    {
        unk_08->VirtualSlot1(Value, First, Second);
    }
}
