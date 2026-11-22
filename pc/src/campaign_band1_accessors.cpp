// campaign_band1_accessors.cpp -- one-line member accessors of classes not yet identified.
// Each class is named UnkType_<VA of its first method here>: the owning classes are unknown, so
// the class names are placeholders and the method names describe only what the code does.
// Members are named by their retail offsets.

// ---------------------------------------------------------------------------------------------

class UnkType_1092b9a0
{
public:
    int GetUnk28Bit2();

    unsigned char unk_00[0x28];     // not read by any function in this unit
    unsigned int  unk_28_bits0 : 2;
    unsigned int  unk_28_bit2 : 1;
};

// UnkType_1092b9a0::GetUnk28Bit2
int UnkType_1092b9a0::GetUnk28Bit2()
{
    return unk_28_bit2;
}

// ---------------------------------------------------------------------------------------------

class UnkType_1092bb70
{
public:
    int GetUnk28Bit22();

    unsigned char unk_00[0x28];     // not read by any function in this unit
    unsigned int  unk_28_bits0 : 22;
    unsigned int  unk_28_bit22 : 1;
};

// UnkType_1092bb70::GetUnk28Bit22
int UnkType_1092bb70::GetUnk28Bit22()
{
    return unk_28_bit22;
}

// ---------------------------------------------------------------------------------------------

class UnkType_109690e0
{
public:
    int GetUnk3cTimes12();

    unsigned char unk_00[0x3c];     // not read by any function in this unit
    int           unk_3c;
};

// UnkType_109690e0::GetUnk3cTimes12
// guess: a count at 0x3c times a 12-byte element size.
int UnkType_109690e0::GetUnk3cTimes12()
{
    return unk_3c * 12;
}

// ---------------------------------------------------------------------------------------------

class UnkType_109693b0
{
public:
    int GetUnk3cTimes44();

    unsigned char unk_00[0x3c];     // not read by any function in this unit
    int           unk_3c;
};

// UnkType_109693b0::GetUnk3cTimes44
// guess: a count at 0x3c times a 44-byte element size.
int UnkType_109693b0::GetUnk3cTimes44()
{
    return unk_3c * 44;
}

// ---------------------------------------------------------------------------------------------

class UnkType_109696c0
{
public:
    int GetUnk3cTimes4();

    unsigned char unk_00[0x3c];     // not read by any function in this unit
    int           unk_3c;
};

// UnkType_109696c0::GetUnk3cTimes4
// guess: a count at 0x3c times a 4-byte element size.
int UnkType_109696c0::GetUnk3cTimes4()
{
    return unk_3c * 4;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10969910
{
public:
    int GetUnk3cTimes8();

    unsigned char unk_00[0x3c];     // not read by any function in this unit
    int           unk_3c;
};

// UnkType_10969910::GetUnk3cTimes8
// guess: a count at 0x3c times an 8-byte element size.
int UnkType_10969910::GetUnk3cTimes8()
{
    return unk_3c * 8;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10969b40
{
public:
    int GetUnk3cTimes40();

    unsigned char unk_00[0x3c];     // not read by any function in this unit
    int           unk_3c;
};

// UnkType_10969b40::GetUnk3cTimes40
// guess: a count at 0x3c times a 40-byte element size.
int UnkType_10969b40::GetUnk3cTimes40()
{
    return unk_3c * 40;
}

// ---------------------------------------------------------------------------------------------

class UnkType_1098a2f0
{
public:
    int IsUnk00Set();

    unsigned char unk_00;
};

// UnkType_1098a2f0::IsUnk00Set
int UnkType_1098a2f0::IsUnk00Set()
{
    return unk_00 != 0;
}

// ---------------------------------------------------------------------------------------------

class UnkType_109b0430
{
public:
    int GetUnk2cBit5();

    unsigned char unk_00[0x2c];     // not read by any function in this unit
    unsigned int  unk_2c_bits0 : 5;
    unsigned int  unk_2c_bit5 : 1;
};

// UnkType_109b0430::GetUnk2cBit5
int UnkType_109b0430::GetUnk2cBit5()
{
    return unk_2c_bit5;
}

// ---------------------------------------------------------------------------------------------

class UnkType_109cd740
{
public:
    void SetUnk5c(int Value);

    unsigned char unk_00[0x5c];     // not read by any function in this unit
    int           unk_5c;
};

// UnkType_109cd740::SetUnk5c
void UnkType_109cd740::SetUnk5c(int Value)
{
    unk_5c = Value;
}

// ---------------------------------------------------------------------------------------------

class UnkType_109db640
{
public:
    void ClearUnk23c();

    unsigned char unk_00[0x23c];    // not read by any function in this unit
    int           unk_23c;
};

// UnkType_109db640::ClearUnk23c
void UnkType_109db640::ClearUnk23c()
{
    unk_23c = 0;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10a10640
{
public:
    int IsUnk50Set();

    unsigned char unk_00[0x50];     // not read by any function in this unit
    int           unk_50;
};

// UnkType_10a10640::IsUnk50Set
int UnkType_10a10640::IsUnk50Set()
{
    return unk_50 != 0;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10a113d0
{
public:
    int GetUnk64Bit1();

    unsigned char unk_00[0x64];     // not read by any function in this unit
    unsigned int  unk_64_bit0 : 1;
    unsigned int  unk_64_bit1 : 1;
};

// UnkType_10a113d0::GetUnk64Bit1
int UnkType_10a113d0::GetUnk64Bit1()
{
    return unk_64_bit1;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10a11580
{
public:
    int GetUnk5cBit0();
    int IsUnk5cBit0Clear();

    unsigned char unk_00[0x5c];     // not read by any function in this unit
    unsigned int  unk_5c_bit0 : 1;
};

// UnkType_10a11580::GetUnk5cBit0
int UnkType_10a11580::GetUnk5cBit0()
{
    return unk_5c_bit0;
}

// UnkType_10a11580::IsUnk5cBit0Clear
int UnkType_10a11580::IsUnk5cBit0Clear()
{
    return !unk_5c_bit0;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10a12800
{
public:
    int IsUnk51Clear();
    int IsUnk51Set();

    unsigned char unk_00[0x51];     // not read by any function in this unit
    unsigned char unk_51;
};

// UnkType_10a12800::IsUnk51Clear
int UnkType_10a12800::IsUnk51Clear()
{
    return unk_51 == 0;
}

// UnkType_10a12800::IsUnk51Set
int UnkType_10a12800::IsUnk51Set()
{
    return unk_51 != 0;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10a13e40
{
public:
    void SetUnk4c(int Value);
    void SetUnk50(int Value);

    unsigned char unk_00[0x4c];     // not read by any function in this unit
    int           unk_4c;
    int           unk_50;
};

// UnkType_10a13e40::SetUnk4c
void UnkType_10a13e40::SetUnk4c(int Value)
{
    unk_4c = Value;
}

// UnkType_10a13e40::SetUnk50
void UnkType_10a13e40::SetUnk50(int Value)
{
    unk_50 = Value;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10a45e10
{
public:
    unsigned char GetUnk04();

    unsigned char unk_00[4];        // not read by any function in this unit
    unsigned char unk_04;
};

// UnkType_10a45e10::GetUnk04
unsigned char UnkType_10a45e10::GetUnk04()
{
    return unk_04;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10a470e0
{
public:
    void SetUnk28(int Value);

    unsigned char unk_00[0x28];     // not read by any function in this unit
    int           unk_28;
};

// UnkType_10a470e0::SetUnk28
void UnkType_10a470e0::SetUnk28(int Value)
{
    unk_28 = Value;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10a48b60
{
public:
    void SetUnk9c(int Value);

    unsigned char unk_00[0x9c];     // not read by any function in this unit
    int           unk_9c;
};

// UnkType_10a48b60::SetUnk9c
void UnkType_10a48b60::SetUnk9c(int Value)
{
    unk_9c = Value;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10a54550
{
public:
    int GetUnk54();

    unsigned char unk_00[0x54];     // not read by any function in this unit
    int           unk_54;
};

// UnkType_10a54550::GetUnk54
int UnkType_10a54550::GetUnk54()
{
    return unk_54;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10a896d0
{
public:
    void SetUnk300Flag2000();

    unsigned char unk_00[0x300];    // not read by any function in this unit
    unsigned int  unk_300;
};

// UnkType_10a896d0::SetUnk300Flag2000
void UnkType_10a896d0::SetUnk300Flag2000()
{
    unk_300 |= 0x2000;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10ab7630
{
public:
    UnkType_10ab7630 *GetThis();
};

// UnkType_10ab7630::GetThis
UnkType_10ab7630 *UnkType_10ab7630::GetThis()
{
    return this;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10ac4130
{
public:
    void SetUnk13c(unsigned char Value);

    unsigned char unk_00[0x13c];    // not read by any function in this unit
    unsigned char unk_13c;
};

// UnkType_10ac4130::SetUnk13c
void UnkType_10ac4130::SetUnk13c(unsigned char Value)
{
    unk_13c = Value;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10ad0c20
{
public:
    void IncrementUnk10();
    void DecrementUnk10();

    unsigned char unk_00[0x10];     // not read by any function in this unit
    int           unk_10;
};

// UnkType_10ad0c20::IncrementUnk10
void UnkType_10ad0c20::IncrementUnk10()
{
    unk_10++;
}

// UnkType_10ad0c20::DecrementUnk10
void UnkType_10ad0c20::DecrementUnk10()
{
    unk_10--;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10aedf50
{
public:
    unsigned int GetUnk08Flag1();
    unsigned int GetUnk08Flag4();
    unsigned int GetUnk08Flag8();
    unsigned int GetUnk08Flag40();

    unsigned char unk_00[8];        // not read by any function in this unit
    unsigned int  unk_08;
};

// UnkType_10aedf50::GetUnk08Flag1
unsigned int UnkType_10aedf50::GetUnk08Flag1()
{
    return unk_08 & 0x1;
}

// UnkType_10aedf50::GetUnk08Flag4
unsigned int UnkType_10aedf50::GetUnk08Flag4()
{
    return unk_08 & 0x4;
}

// UnkType_10aedf50::GetUnk08Flag8
unsigned int UnkType_10aedf50::GetUnk08Flag8()
{
    return unk_08 & 0x8;
}

// UnkType_10aedf50::GetUnk08Flag40
unsigned int UnkType_10aedf50::GetUnk08Flag40()
{
    return unk_08 & 0x40;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10b09110
{
public:
    void ClearUnk23e8();

    unsigned char unk_00[0x23e8];   // not read by any function in this unit
    unsigned char unk_23e8;
};

// UnkType_10b09110::ClearUnk23e8
void UnkType_10b09110::ClearUnk23e8()
{
    unk_23e8 = 0;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10b5ab60
{
public:
    int GetUnk40();

    unsigned char unk_00[0x40];     // not read by any function in this unit
    int           unk_40;
};

// UnkType_10b5ab60::GetUnk40
int UnkType_10b5ab60::GetUnk40()
{
    return unk_40;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10b7bc10
{
public:
    void ClearUnk748Flag100000();

    unsigned char unk_00[0x748];    // not read by any function in this unit
    unsigned int  unk_748;
};

// UnkType_10b7bc10::ClearUnk748Flag100000
void UnkType_10b7bc10::ClearUnk748Flag100000()
{
    unk_748 &= ~0x100000;
}

// ---------------------------------------------------------------------------------------------

class UnkType_10bef850
{
public:
    void ClearUnk400();

    unsigned char unk_00[0x400];    // not read by any function in this unit
    unsigned char unk_400;
};

// UnkType_10bef850::ClearUnk400
void UnkType_10bef850::ClearUnk400()
{
    unk_400 = 0;
}
