// Work item 0239: RVA 0x59730 (LTCG: this in ESI, ret 4).
// Class and member names are neutral: no vtable label or string identifies them.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

// Element held by pointer; slot 0 is a reset/cleanup virtual.
class UnnamedElement_59730
{
public:
    virtual void Reset();
    INT Field4;
    INT Field8;
};

class UnnamedClass_59730
{
public:
    char Pad[0x4ec];
    UnnamedElement_59730 **Data; // TArray<UnnamedElement_59730*> at 0x4ec
    INT ArrayNum;
    INT ArrayMax;

    void EmptyElements(UBOOL bReset);
};

void UnnamedClass_59730::EmptyElements(UBOOL bReset)
{
    for (INT i = 0; i < ArrayNum; i++)
    {
        UnnamedElement_59730 *E = Data[i];
        if (bReset)
            E->Reset();
        E->Field4 = 0;
        E->Field8 = 0;
    }
    ArrayNum = 0;
    if (Data)
    {
        GMalloc->Free(Data);
        Data = 0;
        ArrayMax = 0;
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_59730(UnnamedClass_59730 *Obj, UBOOL b)
{
    Escape(&GMalloc);
    Obj->EmptyElements(b);
}
