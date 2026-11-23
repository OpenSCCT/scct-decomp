// campaign_leaf_10e310.cpp -- method at VA 0x10a0e310: finds an object as the pointer at 0x2c or,
// when that is null, through the chain at 0x30, and returns the float at 0x3d4 of the object at
// its 0x30, or 480 when there is none. The class, member and method names are invented; the
// offsets and the constant are the binary's.

class UnkType_10a0e310_Target
{
public:
    char unk_0[0x3d4];
    float unk_3d4;
};

class UnkType_10a0e310_Owner
{
public:
    char unk_0[0x30];
    UnkType_10a0e310_Target* unk_30;
};

class UnkType_10a0e310_Link2
{
public:
    char unk_0[0x2c];
    UnkType_10a0e310_Owner** unk_2c;
};

class UnkType_10a0e310_Link1
{
public:
    char unk_0[0x28];
    UnkType_10a0e310_Link2* unk_28;
};

class UnkType_10a0e310
{
public:
    UnkType_10a0e310_Owner* GetOwner()
    {
        return unk_2c ? unk_2c : *unk_30->unk_28->unk_2c;
    }
    float Unk_10a0e310();

private:
    char unk_0[0x2c];
    UnkType_10a0e310_Owner* unk_2c;
    UnkType_10a0e310_Link1* unk_30;
};

// UnkType_10a0e310::Unk_10a0e310
float UnkType_10a0e310::Unk_10a0e310()
{
    if ( GetOwner() )
    {
        UnkType_10a0e310_Target* Target = GetOwner()->unk_30;

        if ( Target )
        {
            return Target->unk_3d4;
        }
    }
    return 480.0f;
}
