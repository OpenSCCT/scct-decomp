// Work item 0251: RVA 0xf3ce0. Neutral names: the owner object at +0xc and
// the global at 0x10c9245c are not yet identified (texture LOD clamping by shape:
// the owner keeps a bias at +0x90 and a [min,max] level range at +0x94/+0x98).
typedef int INT;
typedef unsigned char BYTE;

struct UnnamedSettings_f24e0
{
    char Pad00[0x34];
    INT Value34;           // +0x34
};

struct UnnamedGlobal_f24e0
{
    char Pad00[0x7c];
    INT LevelBias[9];      // +0x7c, indexed by owner byte at +0xb8
    UnnamedSettings_f24e0 *Settings;   // +0xa0
};

extern UnnamedGlobal_f24e0 *GUnnamed_10c9245c;

struct UnnamedOwner_f3ce0
{
    char Pad00[0x90];
    INT Bias;              // +0x90
    INT MinLevel;          // +0x94
    INT MaxLevel;          // +0x98
    char Pad9C[0xb8 - 0x9c];
    BYTE Group;            // +0xb8
};

inline INT Clamp(INT X, INT Min, INT Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

// RVA 0xf24e0 (item 0244); defined here so the LTCG link gives it its
// register calling convention (owner in EAX).
INT UnnamedHelper_f24e0(UnnamedOwner_f3ce0 *Owner)
{
    INT Level;
    if (GUnnamed_10c9245c == 0)
        Level = Owner->Bias;
    else
        Level = GUnnamed_10c9245c->LevelBias[Owner->Group]
              - GUnnamed_10c9245c->Settings->Value34 / 2 + Owner->Bias;
    return Clamp(Level, Owner->MinLevel, Owner->MaxLevel);
}

class UnnamedClass_f3ce0
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0C();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual INT GetUSize();   // +0x1c
    virtual INT GetVSize();   // +0x20

    char Pad04[8];
    UnnamedOwner_f3ce0 *Owner;   // +0x0c

    INT ComputeLevel();
};

INT UnnamedClass_f3ce0::ComputeLevel()
{
    INT Level = UnnamedHelper_f24e0(Owner);
    while ((GetUSize() >> Level) < 64 && (GetVSize() >> Level) < 64 && Level > 0)
        Level--;
    INT Min = Owner->MinLevel;
    return Level < Min ? Min : Level;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
typedef INT (UnnamedClass_f3ce0::*LevelFn)();
void Driver_f3ce0(UnnamedOwner_f3ce0 *O)
{
    Escape(&GUnnamed_10c9245c);
    LevelFn F = &UnnamedClass_f3ce0::ComputeLevel;
    Escape(&F);
    Escape((void *)UnnamedHelper_f24e0(O));
    Escape((void *)UnnamedHelper_f24e0(O + 1));
    Escape((void *)UnnamedHelper_f24e0(O + 2));
    Escape((void *)UnnamedHelper_f24e0(O + 3));
    Escape((void *)UnnamedHelper_f24e0(O + 4));
}
