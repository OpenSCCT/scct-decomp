/* Work item 0005: FString members (Unreal Engine 2 UnTemplate.h shapes).
   Strings: L"Farray::protectedcstor", L"FString::=", L"FArray". */
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
void __cdecl appMemcpy(void *Dest, const void *Src, INT Count);

inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
inline TCHAR *appStrcpy(TCHAR *D, const TCHAR *S) { return wcscpy(D, S); }

class FArray
{
public:
    FArray(INT InNum, INT ElementSize)
        : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (!ArrayMax)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, L"Farray::protectedcstor");
    }
    ~FArray();
    INT Add(INT Count, INT ElementSize);

    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

class FString : public FArray
{
public:
    FString(const FString &Other);
    FString(const TCHAR *In);
    ~FString();
    FString &operator=(const FString &Other);
    FString &operator+=(const TCHAR *Str);

    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
};

FString::FString(const FString &Other)
    : FArray(Other.ArrayNum, sizeof(TCHAR))
{
    if (ArrayNum)
        appMemcpy(Data, Other.Data, ArrayNum * sizeof(TCHAR));
}

FString::FString(const TCHAR *In)
    : FArray(*In ? appStrlen(In) + 1 : 0, sizeof(TCHAR))
{
    if (ArrayNum)
        appMemcpy(Data, In, ArrayNum * sizeof(TCHAR));
}

FString &FString::operator=(const FString &Other)
{
    if ((Other.Data || Data) && this != &Other)
    {
        ArrayMax = ArrayNum = Other.ArrayNum;
        if (!ArrayNum)
        {
            if (Data)
            {
                ArrayMax = ArrayNum;
                GMalloc->Free(Data);
                Data = 0;
                return *this;
            }
        }
        if (ArrayNum && !Data)
            Data = GMalloc->Malloc(ArrayMax * sizeof(TCHAR), L"FString::=");
        else
            Data = GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), L"FArray");
        appMemcpy(Data, *Other, ArrayNum * sizeof(TCHAR));
    }
    return *this;
}

FString::~FString()
{
    ArrayNum = 0;
    if (Data)
    {
        GMalloc->Free(Data);
        Data = 0;
        ArrayMax = 0;
    }
}

FString &FString::operator+=(const TCHAR *Str)
{
    if (*Str)
    {
        INT Num = ArrayNum;
        INT Len = appStrlen(Str);
        if (Num)
        {
            Add(Len, sizeof(TCHAR));
            appStrcpy((TCHAR *)Data + Num - 1, Str);
        }
        else
        {
            Add(Len + 1, sizeof(TCHAR));
            appStrcpy((TCHAR *)Data, Str);
        }
    }
    return *this;
}
