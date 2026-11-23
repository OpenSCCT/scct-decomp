// campaign_leaf_1ded50.cpp -- thiscall method at VA 0x10aded50. With three arguments, the second
// and third pointing at three-float vectors: when the object at 0x04 is set and the second
// argument's float at 0x4 is below the float at 0x0c, it calls slot 1 of that object with the three
// arguments; when the object at 0x08 is set and the third argument's float at 0x4 is not below the
// float at 0x0c, it calls slot 1 of that object with them. The class, method and member names are
// invented.

struct UnkType_10aded50_Vector
{
    float unk_0;
    float unk_4;
    float unk_8;
};

class UnkType_10aded50_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(int Value, const UnkType_10aded50_Vector* First,
                              const UnkType_10aded50_Vector* Second);
};

class UnkType_10aded50
{
public:
    void Unk_10aded50(int Value, const UnkType_10aded50_Vector* First,
                 const UnkType_10aded50_Vector* Second);

private:
    int unk_00;
    UnkType_10aded50_Target* unk_04;
    UnkType_10aded50_Target* unk_08;
    float unk_0c;
};

// UnkType_10aded50::Unk_10aded50
void UnkType_10aded50::Unk_10aded50(int Value, const UnkType_10aded50_Vector* First,
                                const UnkType_10aded50_Vector* Second)
{
    if ( unk_04 != 0 && First->unk_4 < unk_0c )
    {
        unk_04->VirtualSlot1(Value, First, Second);
    }
    if ( unk_08 != 0 && Second->unk_4 >= unk_0c )
    {
        unk_08->VirtualSlot1(Value, First, Second);
    }
}
