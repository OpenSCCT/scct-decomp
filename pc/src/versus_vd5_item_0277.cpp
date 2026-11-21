// Work item 0277: Versus RVA 0xfc8e0 and 0xfc940.
// Unnamed class: vtable 0x10c03e64 at +0, an FString at +4. Its base class
// (vtable 0x10c03dc0) has a trivial destructor that only resets the vtable.
// Neutral names (UnnamedClass_fc8e0 / UnnamedBase_fc8e0): no string or symbol
// evidence names them. The constructor was built with /GL and linked with
// /LTCG: this arrives on the stack (ret 4) and the string in EDI.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
void appMemcpy(void *Dest, const void *Src, INT Count);

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FString();
    FString &operator=(const TCHAR *Other);
    void Empty()
    {
        ArrayNum = 0;
        if (Data) { GMalloc->Free(Data); Data = 0; ArrayMax = 0; }
    }
};

FString &FString::operator=(const TCHAR *Other)
{
    if (Other != Data) {
        if (*Other == 0) {
            if (Data) { ArrayNum = 0; ArrayMax = 0; GMalloc->Free(Data); Data = 0; }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), L"FString::=");
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), L"FArray");
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}

class UnnamedBase_fc8e0
{
public:
    virtual ~UnnamedBase_fc8e0() {}
};

class UnnamedClass_fc8e0 : public UnnamedBase_fc8e0
{
public:
    FString Text;
    UnnamedClass_fc8e0(const TCHAR *InText);
    virtual ~UnnamedClass_fc8e0();
};

UnnamedClass_fc8e0::UnnamedClass_fc8e0(const TCHAR *InText)
{
    Text = InText;
}

UnnamedClass_fc8e0::~UnnamedClass_fc8e0()
{
    Text.Empty();
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
void Driver_fc8e0(void *Mem, const TCHAR *T, FString *S)
{
    Escape(&GMalloc);
    new (Mem) UnnamedClass_fc8e0(T);
    *S = T;
}
