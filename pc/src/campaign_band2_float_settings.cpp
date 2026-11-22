// campaign_band2_float_settings.cpp -- get and set methods for three floats at 0x20-0x28 of the
// class whose constructor is at VA 0x10e07c30. The setter of 0x28, at VA 0x10e07bd0, is matched
// elsewhere. The class and method names are invented; the offsets, and the default values quoted
// below, are the binary's.

class UnkType_10e07c30
{
public:
    virtual ~UnkType_10e07c30();    // guess: the vtable's one slot is the destructor

    float GetUnk28();
    void SetUnk20(float Value);
    float GetUnk20();
    void SetUnk24(float Value);
    float GetUnk24();

private:
    unsigned char unk_04[0xc];      // not touched by the constructor
    float unk_10;                   // the constructor sets 0.05
    float unk_14;                   // the constructor sets 0.05
    float unk_18;                   // the constructor sets 0.05
    int unk_1c;                     // the constructor sets 0
    float unk_20;                   // the constructor sets 0.4
    float unk_24;                   // the constructor sets 0.1
    float unk_28;                   // the constructor sets 0.3
    unsigned char unk_2c;           // the constructor sets 1
    unsigned char unk_2d;           // the constructor sets 1
};

// UnkType_10e07c30::GetUnk28
float UnkType_10e07c30::GetUnk28()
{
    return unk_28;
}

// UnkType_10e07c30::SetUnk20
void UnkType_10e07c30::SetUnk20(float Value)
{
    unk_20 = Value;
}

// UnkType_10e07c30::GetUnk20
float UnkType_10e07c30::GetUnk20()
{
    return unk_20;
}

// UnkType_10e07c30::SetUnk24
void UnkType_10e07c30::SetUnk24(float Value)
{
    unk_24 = Value;
}

// UnkType_10e07c30::GetUnk24
float UnkType_10e07c30::GetUnk24()
{
    return unk_24;
}
