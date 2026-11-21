// Work item w3 0343: Versus RVA 0x10fe50-0x1100ac (LTCG object).
//   0x10fe50 UnnamedClass_10fe50::Broadcast_10fe50  (this in EDI)
//   0x10ff00 TArray<UObject*>::TArray(const TArray&) (Other in EBX, this on stack)
//   0x10ffa0 UnnamedClass_10fe50::Notify_10ffa0      (this on stack)
//   0x110060 FParms_10ffa0::~FParms_10ffa0           (this on stack)
// The owning class and its event are unlabelled, so they carry neutral names.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned int size_t;
typedef float FLOAT;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

extern const TCHAR FArray_ProtectedCstorTag[]; // 0x10c10944

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize) : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (!ArrayMax)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArray_ProtectedCstorTag);
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
    INT Add(INT Count, INT ElementSize);                // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);             // RVA 0x4550
    void Remove(INT Index, INT Count, INT ElementSize); // RVA 0x119c0
};

template <class T> class TArray;
template <class T> inline void *operator new(size_t Size, TArray<T> &Array);

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    __declspec(noinline) TArray(const TArray &Other) : FArray(Other.ArrayNum, sizeof(T))
    {
        ArrayNum = 0;
        for (INT i = 0; i < Other.ArrayNum; i++)
            new (*this) T(((T *)Other.Data)[i]);
    }
    __declspec(noinline) ~TArray() // RVA 0x17bf30 (not in this item)
    {
        FArray::Remove(0, ArrayNum, sizeof(T));
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    __declspec(noinline) TArray &operator=(const TArray &Other) // RVA 0x1100b0 (next item)
    {
        if (this != &Other)
        {
            FArray::Empty(sizeof(T), Other.ArrayNum);
            for (INT i = 0; i < Other.ArrayNum; i++)
                new (*this) T(((T *)Other.Data)[i]);
        }
        return *this;
    }
};

template <class T> inline void *operator new(size_t Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

class FString : public TArray<TCHAR>
{
public:
    FString() {}
    FString(const FString &Other);            // RVA 0x4640
    ~FString();                               // RVA 0x48b0
    FString &operator=(const FString &Other); // RVA 0x4800
};

struct FName
{
    INT Index;
    FName(INT N) : Index(N) {}
    // A user-written copy constructor: retail builds the by-value FName in
    // the argument slot rather than pushing a plain DWORD.
    FName(const FName &Other) : Index(Other.Index) {}
};

class UObject
{
public:
    virtual void VFunc00();
    virtual void VFunc04();
    virtual void VFunc08();
    virtual void VFunc0C();
    virtual void VFunc10(void *Arg);
};

// Elements of the second list: flag 8 at +0x28 gates a virtual at +0x58.
class UnnamedListener_10fe50 : public UObject
{
public:
    virtual void VFunc14();
    virtual void VFunc18();
    virtual void VFunc1C();
    virtual void VFunc20();
    virtual void VFunc24();
    virtual void VFunc28();
    virtual void VFunc2C();
    virtual void VFunc30();
    virtual void VFunc34();
    virtual void VFunc38();
    virtual void VFunc3C();
    virtual void VFunc40();
    virtual void VFunc44();
    virtual void VFunc48();
    virtual void VFunc4C();
    virtual void VFunc50();
    virtual void VFunc54();
    virtual void Receive_58(FString Name, FLOAT Value);
    char Pad04[0x24];
    DWORD Flags; // +0x28
};

// Element of the group list: carries its own list at +0x58.
class UnnamedMember_10fe50
{
public:
    char Pad00[0x58];
    TArray<UObject *> List; // +0x58
};

class UnnamedGroup_10fe50
{
public:
    char Pad00[0x2c];
    TArray<UnnamedMember_10fe50 *> Members; // +0x2c
};

struct FParms_10ffa0
{
    FString Name;
    FLOAT Value;
    TArray<UObject *> List;
    __declspec(noinline) ~FParms_10ffa0() {}
};

class UnnamedClass_10fe50 : public UObject
{
public:
    char Pad04[0x24];
    UnnamedGroup_10fe50 *Group;                   // +0x28
    char Pad2C[0x8];
    TArray<UObject *> Listeners;                  // +0x34 (UnnamedListener_10fe50)

    void *Func_16830(FName Event, INT A, void *Parms, INT B); // RVA 0x16830
    void Notify_10ffa0(const FString &Name, FLOAT Value, TArray<UObject *> List);
    void Broadcast_10fe50(const FString &Name, FLOAT Value);
};

// RVA 0x10ffa0
void UnnamedClass_10fe50::Notify_10ffa0(const FString &Name, FLOAT Value, TArray<UObject *> List)
{
    FParms_10ffa0 Parms;
    Parms.Name = Name;
    Parms.Value = Value;
    Parms.List = List;
    VFunc10(Func_16830(FName(0x1404), 0, &Parms, 0));
}

// RVA 0x10fe50
void UnnamedClass_10fe50::Broadcast_10fe50(const FString &Name, FLOAT Value)
{
    Notify_10ffa0(Name, Value, Listeners);
    for (INT i = 0; i < Group->Members.ArrayNum; i++)
        Notify_10ffa0(Name, Value, Group->Members(i)->List);
    for (INT j = 0; j < Listeners.ArrayNum; j++)
        if (((UnnamedListener_10fe50 *)Listeners(j))->Flags & 8)
            ((UnnamedListener_10fe50 *)Listeners(j))->Receive_58(Name, Value);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_10fe50(UnnamedClass_10fe50 *O, const FString *N, FLOAT V)
{
    Escape(&GMalloc);
    O->Broadcast_10fe50(*N, V);
}
