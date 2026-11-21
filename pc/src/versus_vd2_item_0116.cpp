// Work item 0116 (RVA 0x1ea00-0x1ed48), Core: UEnum::Serialize, the compact
// index serializer, and UCommandlet's constructor, Main and execMain.
// Core was built with /GL and linked with /LTCG: the compact-index serializer
// (0x1ea40) takes the archive in ESI and the index in EDI, the TArray<FName>
// serializer (0x1fd80) takes the array in EBX and the archive in EAX, and
// UCommandlet's constructor (0x1ebc0) takes `this` on the stack.
// Evidence for UCommandlet: its vtable (0x30d0b8) holds Main at +0x58, which
// execMain calls; the constructor builds two FStringNoInit[16] arrays
// (HelpParm at 0x58, HelpDesc at 0x118) after four single strings.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

#pragma pack(push, 4)

class UObject;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int, void *Mem) { return Mem; }

struct FCompactIndex
{
    INT Value;
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(UObject *Object);                  // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    // MSVC lays overloaded virtuals out in reverse order.
    virtual FArchive &operator<<(class FName &N);           // +0x1c
    virtual FArchive &operator<<(UObject *&Res);            // +0x18

    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B)
    {
        Ar.Serialize(&B, 1);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    UBOOL ArIsTrans;
};

class FName
{
public:
    INT Index;
    FName() {}
};

enum ENoInit { E_NoInit = 0 };

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(ENoInit) {}
    INT Add(INT Count, INT ElementSize);        // 0x44e0
    void Empty(INT ElementSize, INT Slack);     // 0x4550
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    TArray(ENoInit) : FArray(E_NoInit) {}
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack) { FArray::Empty(sizeof(T), Slack); }

    friend FArchive &operator<<(FArchive &Ar, TArray &A)
    {
        A.CountBytes(Ar);
        if (Ar.IsLoading()) {
            INT NewNum;
            Ar << AR_INDEX(NewNum);
            A.Empty(NewNum);
            for (INT i = 0; i < NewNum; i++)
                Ar << *new(&((T *)A.Data)[A.Add(1, sizeof(T))]) T;
        } else {
            Ar << AR_INDEX(A.ArrayNum);
            for (INT i = 0; i < A.ArrayNum; i++)
                Ar << A(i);
        }
        return Ar;
    }
};

class FString : public TArray<TCHAR>
{
public:
    FString() {}
    FString(ENoInit) : TArray<TCHAR>(E_NoInit) {}
    FString(const TCHAR *In);                   // 0x46c0
    ~FString();                                 // 0x48b0
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
};

class FStringNoInit : public FString
{
public:
    FStringNoInit() : FString(E_NoInit) {}
};

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event);
};

class UObject
{
public:
    UObject() {}
    virtual ~UObject();
    virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04();
    virtual void V05(); virtual void V06(); virtual void V07(); virtual void V08();
    virtual void V09(); virtual void V10(); virtual void V11(); virtual void V12();
    virtual void V13(); virtual void V14(); virtual void V15(); virtual void V16();
    virtual void V17(); virtual void V18();
    virtual void Register();                 // +0x4c
    virtual void Serialize(FArchive &Ar);    // +0x50, 0x15f50
    virtual void V21();

    INT Index;
    UObject *HashNext;
    void *StateFrame;
    UObject *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;
    class UClass *Class;
};

struct FFrame;
typedef void (UObject::*Native)(FFrame &TheStack, void *const Result);
extern Native GNatives[];

struct FFrame : public FOutputDevice
{
    class UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    void Step(UObject *Context, void *const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define RESULT_DECL void *const Result
#define P_GET_STR(var) FString var; Stack.Step(Stack.Object, &var);
#define P_FINISH Stack.Code++;

class UField : public UObject
{
public:
    UField *SuperField;
    UField *Next;
    void Serialize(FArchive &Ar);
};

class UEnum : public UField
{
public:
    TArray<FName> Names;
    void Serialize(FArchive &Ar);
};

class UCommandlet : public UObject
{
public:
    FStringNoInit HelpCmd;
    FStringNoInit HelpOneLiner;
    FStringNoInit HelpUsage;
    FStringNoInit HelpWebLink;
    FStringNoInit HelpParm[16];
    FStringNoInit HelpDesc[16];
    DWORD Flags;

    UCommandlet();
    virtual INT Main(const TCHAR *Parms);    // +0x58
    INT eventMain(const FString &InParms);   // 0x15730
    void execMain(FFrame &Stack, RESULT_DECL);
};

// RVA 0x1ea40.
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
    } else {
        INT Original = I.Value;
        DWORD V = Original >= 0 ? Original : -Original;
        BYTE B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
        I.Value = 0;
        Ar << B0;
        if (B0 & 0x40) {
            V >>= 6;
            BYTE B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar << B1;
            if (B1 & 0x80) {
                V >>= 7;
                BYTE B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar << B2;
                if (B2 & 0x80) {
                    V >>= 7;
                    BYTE B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                    Ar << B3;
                    if (B3 & 0x80) {
                        V >>= 7;
                        BYTE B4 = V;
                        Ar << B4;
                        I.Value = B4;
                    }
                    I.Value = (I.Value << 7) + (B3 & 0x7f);
                }
                I.Value = (I.Value << 7) + (B2 & 0x7f);
            }
            I.Value = (I.Value << 7) + (B1 & 0x7f);
        }
        I.Value = (I.Value << 6) + (B0 & 0x3f);
        if (B0 & 0x80)
            I.Value = -I.Value;
    }
    return Ar;
}

void UField::Serialize(FArchive &Ar)
{
    UObject::Serialize(Ar);
    Ar << *(UObject **)&SuperField;
    Ar << *(UObject **)&Next;
}

// RVA 0x1ea00.
void UEnum::Serialize(FArchive &Ar)
{
    UField::Serialize(Ar);
    Ar << Names;
}

// RVA 0x1ebc0.
UCommandlet::UCommandlet()
{
}

// RVA 0x1ec40.
INT UCommandlet::Main(const TCHAR *Parms)
{
    return eventMain(Parms);
}

// RVA 0x1ecb0.
void UCommandlet::execMain(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(InParms);
    P_FINISH;
    *(INT *)Result = Main(*InParms);
}

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_1ea00(UEnum *E, FArchive *Ar, FFrame *Stack, void *Result, void *Mem)
{
    Escape(&GMalloc); Escape(GNatives);
    E->Serialize(*Ar);
    UCommandlet *C = new(Mem) UCommandlet;
    Escape(C);
    // execMain is reached through the native table in retail.
    void (UCommandlet::*Exec)(FFrame &, void *const) = &UCommandlet::execMain;
    Escape(&Exec);
    (C->*Exec)(*Stack, Result);
    UEnum Local;
    Escape(&Local);
}
