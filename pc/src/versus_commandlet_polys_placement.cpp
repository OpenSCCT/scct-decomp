#include "versus_build.h"
#include "unreal_object.h"
#include "unreal_math.h"
#include "versus_poly.h"

enum EInternal { EC_Internal };
enum ENoInit { E_NoInit };

inline void *operator new(unsigned int, EInternal *Storage) { return Storage; }
inline void operator delete(void *, EInternal *) {}

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray(ENoInit) {}
    FArray(INT InNum, INT ElementSize) : ArrayNum(InNum), ArrayMax(InNum)
    {
        Data = 0;
        if (ArrayMax)
            Realloc(ElementSize);
    }
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);
    void Realloc(INT ElementSize);
};

template <class T> class TArray : public FArray
{
public:
    ~TArray()
    {
        Remove(0, ArrayNum);
    }
    T &operator()(INT Index) { return ((T *)Data)[Index]; }
    void Remove(INT Index, INT Count)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
    TArray(INT Num = 0) : FArray(Num, sizeof(T)) {}
    TArray(ENoInit) : FArray(E_NoInit) {}
};

class FString : public TArray<TCHAR>
{
public:
    FString(ENoInit) : TArray<TCHAR>(E_NoInit) {}
    ~FString();
};

class FStringNoInit : public FString
{
public:
    FStringNoInit() : FString(E_NoInit) {}
};

class UCommandlet : public UObject
{
public:
    UCommandlet();
    virtual ~UCommandlet();
    virtual INT Main(const TCHAR *Parms);
    static void InternalConstructor(void *Storage);

    FStringNoInit HelpCmd;
    FStringNoInit HelpOneLiner;
    FStringNoInit HelpUsage;
    FStringNoInit HelpWebLink;
    FStringNoInit HelpParm[16];
    FStringNoInit HelpDesc[16];
    DWORD Flags;
};

UCommandlet::UCommandlet() {}

void UCommandlet::InternalConstructor(void *Storage)
{
    new ((EInternal *)Storage) UCommandlet;
}

class UServerCommandlet : public UCommandlet
{
public:
    virtual ~UServerCommandlet();
    virtual INT Main(const TCHAR *Parms);
    static void InternalConstructor(void *Storage);
};

void UServerCommandlet::InternalConstructor(void *Storage)
{
    new ((EInternal *)Storage) UServerCommandlet;
}

template <class T> class TTransArray : public TArray<T>
{
public:
    UObject *Owner;
    TTransArray(UObject *InOwner, INT Num = 0) : TArray<T>(Num), Owner(InOwner) {}
};

class UPolys : public UObject
{
public:
    UPolys() : Element(this) {}
    virtual ~UPolys();
    static void InternalConstructor(void *Storage);
    TTransArray<FPoly> Element;
};

void UPolys::InternalConstructor(void *Storage)
{
    new ((EInternal *)Storage) UPolys;
}

UPolys::~UPolys()
{
    ConditionalDestroy();
}
