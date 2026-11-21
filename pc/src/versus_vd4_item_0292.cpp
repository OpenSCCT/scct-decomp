// Work item 0292: Versus RVA 0x77750 (LTCG custom convention:
// this in ECX, bEnabled in AL, Flag in DL, Owner and Value on the stack, ret 8).
// Class names are neutral: no vtable label or string identifies them.
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef int INT;
typedef float FLOAT;

// Float constants in retail .rdata (0x10c109f8, 0x10c109fc, 0x10c10a20).
extern const FLOAT UnnamedClass_77750_Min;
extern const FLOAT UnnamedClass_77750_Max;
extern const FLOAT UnnamedClass_77750_Scale;

// Object at +0x534 of the owner's sub-object; +0x1c is a packed grey colour.
// SetGrey is an out-of-line helper that the LTCG linker inlined into Set.
struct UnnamedTarget_77750
{
    BYTE Pad[0x1c];
    DWORD Color;
};

struct UnnamedSub_77750
{
    BYTE Pad[0x534];
    UnnamedTarget_77750* Target;
};

struct UnnamedOwner_77750
{
    BYTE Pad[0x2af10];
    UnnamedSub_77750* Sub;

    void SetGrey(INT C);
};

void UnnamedOwner_77750::SetGrey(INT C)
{
    UnnamedTarget_77750* Target = Sub->Target;
    if (Target)
        Target->Color = (C & 0xff) | ((C & 0xff) << 8) | ((C & 0xff) << 16);
}

inline FLOAT Clamp(FLOAT X, FLOAT Min, FLOAT Max)
{
    return X < Min ? Min : X > Max ? Max : X;
}

struct UnnamedClass_77750
{
    DWORD Field0;
    BYTE bDisabled;
    BYTE Flag;

    void Set(UnnamedOwner_77750* Owner, FLOAT Value, bool bEnabled, BYTE InFlag);
};

void UnnamedClass_77750::Set(UnnamedOwner_77750* Owner, FLOAT Value, bool bEnabled, BYTE InFlag)
{
    Flag = InFlag;
    bDisabled = !bEnabled;
    if (bEnabled)
        Value = Clamp(Value, UnnamedClass_77750_Min, UnnamedClass_77750_Max);
    else
        Value = UnnamedClass_77750_Min;
    Owner->SetGrey((INT)((UnnamedClass_77750_Max - Value) * UnnamedClass_77750_Scale));
}

// Scaffolding for the link, not part of the unit.
void Escape(void*);
void Driver_77750(UnnamedClass_77750* C, UnnamedOwner_77750* O, FLOAT V, bool E, BYTE F)
{
    Escape((void*)&UnnamedClass_77750_Min);
    Escape((void*)&UnnamedClass_77750_Max);
    Escape((void*)&UnnamedClass_77750_Scale);
    C->Set(O, V, E, F);
}
