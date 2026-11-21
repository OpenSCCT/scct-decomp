// Work item 0316: Versus RVA 0x86560-0x8667d.

typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;

// Unnamed piecewise float mapping at 0x86560 (name unknown; neutral name).
// Wraps values beyond +-0.65 by 0.15, clamps +-0.55 to +-0.5, and pulls
// values toward zero by 0.05 with a dead zone.
FLOAT UnnamedDeadZone_86560(FLOAT Value)
{
    if (Value < -0.65f)
        return Value + 0.15f;
    if (Value > 0.65f)
        return Value - 0.15f;
    if (Value < -0.55f)
        return -0.5f;
    if (Value > 0.55f)
        return 0.5f;
    if (Value < -0.05f)
        return Value + 0.05f;
    if (Value > 0.05f)
        return Value - 0.05f;
    return 0.0f;
}

// Unnamed class constructed at 0x86620 (vtable 0x10c0bd48; neutral name).
extern unsigned __int64 UnnamedClass_86620_NextId; // 0x10c96930

#pragma pack(push, 4)
class UnnamedClass_86620
{
public:
    UnnamedClass_86620();
    virtual void Slot0();

    INT A;              // +04
    INT B;              // +08
    INT C;              // +0c
    INT D;              // +10
    unsigned __int64 Id;// +14
    INT E;              // +1c
    INT F;              // +20
    INT G;              // +24
};
#pragma pack(pop)

UnnamedClass_86620::UnnamedClass_86620()
{
    B = 0;
    C = 0;
    D = 0;
    A = 0;
    Id = UnnamedClass_86620_NextId++ * 256 + 0xe1;
    E = 0;
    F = 0;
    G = 0;
}

// Scaffolding for the link, not part of the unit.

inline void *operator new(unsigned int, void *Mem) { return Mem; }
UnnamedClass_86620 *Driver_86620(void *Mem)
{
    return new (Mem) UnnamedClass_86620;
}
