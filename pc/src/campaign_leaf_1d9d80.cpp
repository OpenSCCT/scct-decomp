// campaign_leaf_1d9d80.cpp -- thiscall method at VA 0x10ad9d80 taking a flag, a value and an unused
// word. When the object at 0xd0 is set: with the flag, it first passes the value (through the
// function at VA 0x10cccd20) to the method at VA 0x10ad8c90 of the object at 0xd4 when that is set,
// then calls the method at VA 0x10ad5820 with the object at 0xd0, 1, 0 and 0 unless the method at
// VA 0x10ad58d0 finds "P_Progress"; without it, it makes that call with 0 instead of 1 only when
// "P_Progress" is found. The class, method and member names are invented.

const char* Unk_10cccd20(const char* Value);

class UnkType_10ad9d80_Item
{
public:
    void Unk_10ad8c90(const char* Value);
};

class UnkType_10ad9d80_Target;

class UnkType_10ad9d80
{
public:
    void Unk_10ad9d80(bool Flag, const char* Value, int Unused);
    bool Unk_10ad58d0(const char* Name);
    void Unk_10ad5820(UnkType_10ad9d80_Target* Target, int Show, int First, int Second);

private:
    char unk_00[0xd0];
    UnkType_10ad9d80_Target* unk_d0;
    UnkType_10ad9d80_Item* unk_d4;
};

// UnkType_10ad9d80::Unk_10ad9d80
void UnkType_10ad9d80::Unk_10ad9d80(bool Flag, const char* Value, int Unused)
{
    if ( !unk_d0 )
    {
        return;
    }
    if ( Flag )
    {
        if ( unk_d4 )
        {
            unk_d4->Unk_10ad8c90(Unk_10cccd20(Value));
        }
        if ( !Unk_10ad58d0("P_Progress") )
        {
            Unk_10ad5820(unk_d0, 1, 0, 0);
        }
    }
    else
    {
        if ( Unk_10ad58d0("P_Progress") )
        {
            Unk_10ad5820(unk_d0, 0, 0, 0);
        }
    }
}
