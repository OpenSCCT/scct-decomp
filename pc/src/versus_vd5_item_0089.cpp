// Work item 0089: USound::GetDuration (0xac250) and an LTCG constructor of a
// small buffer object (0xac280).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
};
extern FMalloc *GMalloc;

// USound::Data (FSoundData) at +0x28.
class FSoundData {
public:
    FLOAT GetPeriod();
    char Pad[0x30];
};

class USound {
public:
    virtual ~USound();
    FLOAT GetDuration();
    char UObjectData[0x24];
    FSoundData Data;   // +0x28
    FLOAT Duration;    // +0x58
};

FLOAT USound::GetDuration()
{
    if (Duration < 0.f)
        Duration = Data.GetPeriod();
    return Duration;
}

// Neutral names: base with vtable 0x10c09f9c, derived with vtable 0x10c08b00.
class UnnamedBase_ac280 {
public:
    UnnamedBase_ac280() : Field4(0), Field8(0) {}
    virtual void Unused();
    INT Field4;
    INT Field8;
};

extern const TCHAR UnnamedBuffer_ac280_Tag[];

class __declspec(novtable) UnnamedMid_ac280 : public UnnamedBase_ac280 {
public:
    UnnamedMid_ac280(INT InSize)
    {
        Size = InSize;
        Max = InSize;
        if (InSize == 0)
            Data = 0;
        else
            Data = GMalloc->Malloc(InSize, UnnamedBuffer_ac280_Tag);
    }
    void *Data;  // +0xc
    INT Size;    // +0x10
    INT Max;     // +0x14
};

class UnnamedBuffer_ac280 : public UnnamedMid_ac280 {
public:
    UnnamedBuffer_ac280(INT InSize);
    virtual void Unused();
};

__declspec(noinline) UnnamedBuffer_ac280::UnnamedBuffer_ac280(INT InSize)
    : UnnamedMid_ac280(InSize)
{
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *P) { return P; }
UnnamedBuffer_ac280 *Driver_ac280(void *Mem, INT N)
{
    Escape(&GMalloc);
    return new(Mem) UnnamedBuffer_ac280(N);
}
