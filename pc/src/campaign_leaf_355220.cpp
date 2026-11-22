// campaign_leaf_355220.cpp -- one function at file offset 0x355220, preferred VA 0x10c55220.
// When the object reached through the pointers at 0x7c and 0x38 has its word at 0xa8 set and its
// word at 0xa4 clear, it sets Offset to (150, 53.7, 10) and Turn to (500, -6500, 0). The class,
// method, structure, member and parameter names are invented; the offsets, the constants and the
// bytes are the binary's.

struct UnkType_10c55220_Vector
{
    UnkType_10c55220_Vector(float InX, float InY, float InZ)
        : unk_0(InX), unk_4(InY), unk_8(InZ)
    {
    }

    float unk_0;
    float unk_4;
    float unk_8;
};

struct UnkType_10c55220_Rotator
{
    UnkType_10c55220_Rotator(int InPitch, int InYaw, int InRoll)
        : unk_0(InPitch), unk_4(InYaw), unk_8(InRoll)
    {
    }

    int unk_0;
    int unk_4;
    int unk_8;
};

struct UnkType_10c55220_State
{
    unsigned char unk_0[0xa4];
    int unk_a4;
    int unk_a8;
};

struct UnkType_10c55220_Owner
{
    unsigned char unk_0[0x38];
    UnkType_10c55220_State* unk_38;
};

class UnkType_10c55220
{
public:
    void Unk_10c55220(UnkType_10c55220_Vector& Offset, UnkType_10c55220_Rotator& Turn) const;

    unsigned char unk_0[0x7c];
    UnkType_10c55220_Owner* unk_7c;
};

// UnkType_10c55220::Unk_10c55220
void UnkType_10c55220::Unk_10c55220(UnkType_10c55220_Vector& Offset,
                                    UnkType_10c55220_Rotator& Turn) const
{
    UnkType_10c55220_State* State = unk_7c->unk_38;

    if ( State->unk_a8 != 0 && State->unk_a4 == 0 )
    {
        Offset = UnkType_10c55220_Vector(150.0f, 53.7f, 10.0f);
        Turn = UnkType_10c55220_Rotator(500, -6500, 0);
    }
}
