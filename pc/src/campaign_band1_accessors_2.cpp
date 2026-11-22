// campaign_band1_accessors_2.cpp -- more one-line member accessors of classes not yet identified.
// Each class is named UnkType_<VA of its first method here>: the owning classes are unknown, so
// the class names are placeholders and the method names describe only what the code does.
// Members are named by their retail offsets.

// ---------------------------------------------------------------------------------------------

class UnkType_109a6040
{
public:
    int GetUnk2d4Bit0();

    unsigned char unk_00[0x2d4];    // not read by any function in this unit
    unsigned int  unk_2d4_bit0 : 1;
};

// UnkType_109a6040::GetUnk2d4Bit0
int UnkType_109a6040::GetUnk2d4Bit0()
{
    return unk_2d4_bit0;
}

// ---------------------------------------------------------------------------------------------

class UnkType_109a7610
{
public:
    int GetUnk354Bit0();

    unsigned char unk_00[0x354];    // not read by any function in this unit
    unsigned int  unk_354_bit0 : 1;
};

// UnkType_109a7610::GetUnk354Bit0
int UnkType_109a7610::GetUnk354Bit0()
{
    return unk_354_bit0;
}

// ---------------------------------------------------------------------------------------------

class UnkType_109a7690
{
public:
    int GetUnk338Bit6();

    unsigned char unk_00[0x338];    // not read by any function in this unit
    unsigned int  unk_338_bits0 : 6;
    unsigned int  unk_338_bit6 : 1;
};

// UnkType_109a7690::GetUnk338Bit6
int UnkType_109a7690::GetUnk338Bit6()
{
    return unk_338_bit6;
}

// ---------------------------------------------------------------------------------------------

class UnkType_109b02d0
{
public:
    int GetUnk42cBit0();

    unsigned char unk_00[0x42c];    // not read by any function in this unit
    unsigned int  unk_42c_bit0 : 1;
};

// UnkType_109b02d0::GetUnk42cBit0
int UnkType_109b02d0::GetUnk42cBit0()
{
    return unk_42c_bit0;
}

// ---------------------------------------------------------------------------------------------

class UnkType_109c3ff0
{
public:
    int GetUnk338Bit0();
    int GetUnk2f8Bit0();
    bool IsUnk33cSet();

    unsigned char unk_00[0x2f8];    // not read by any function in this unit
    unsigned int  unk_2f8_bit0 : 1;
    unsigned char unk_2fc[0x3c];    // not read by any function in this unit
    unsigned int  unk_338_bit0 : 1;
    void         *unk_33c;
};

// UnkType_109c3ff0::GetUnk338Bit0
int UnkType_109c3ff0::GetUnk338Bit0()
{
    return unk_338_bit0;
}

// UnkType_109c3ff0::GetUnk2f8Bit0
int UnkType_109c3ff0::GetUnk2f8Bit0()
{
    return unk_2f8_bit0;
}

// UnkType_109c3ff0::IsUnk33cSet
bool UnkType_109c3ff0::IsUnk33cSet()
{
    return unk_33c ? true : false;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10b9c080
{
public:
    int GetUnkaecBit0();

    unsigned char unk_00[0xaec];    // not read by any function in this unit
    unsigned int  unk_aec_bit0 : 1;
};

// UnkType_10b9c080::GetUnkaecBit0
int UnkType_10b9c080::GetUnkaecBit0()
{
    return unk_aec_bit0;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10bee680
{
public:
    int GetUnk3d0Bit0();

    unsigned char unk_00[0x3d0];    // not read by any function in this unit
    unsigned int  unk_3d0_bit0 : 1;
};

// UnkType_10bee680::GetUnk3d0Bit0
int UnkType_10bee680::GetUnk3d0Bit0()
{
    return unk_3d0_bit0;
}
