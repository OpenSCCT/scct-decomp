// Work item 0095: UObject::ConditionalRegister, UObject::~UObject and
// UObject::Serialize (RVA 0x15ea0-0x16168), Core UnObj.cpp.
// LTCG unit: UnhashObject (0x1d2d0) takes `this` in EDX, the compact-index
// serializer (0x1ea40) takes the archive in ESI and the index in EDI, and the
// FStateFrame constructor (0x159f0) takes `this` in EAX and the object in ECX.
// They are defined here so the link gives them those conventions.
// Layout follows Unreal Engine 2 UObject (Index 4, HashNext 8, StateFrame 0xc,
// _Linker 0x10, _LinkerIndex 0x14, Outer 0x18, ObjectFlags 0x1c, Name 0x20,
// Class 0x24).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned __int64 QWORD;
typedef unsigned char BYTE;

// Core is built with 4-byte packing (FStateFrame::ProbeMask sits at 0x1c).
#pragma pack(push, 4)

#define INDEX_NONE -1
enum { RF_HasStack = 0x02000000, RF_DebugSerialize = 0x40000000 };

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int Size, const TCHAR *Tag)
{
    return GMalloc->Malloc(Size, Tag);
}
inline void operator delete(void *Ptr)
{
    GMalloc->Free(Ptr);
}

// Retail shares this literal; bound as an extern array.
extern const TCHAR ObjectStateFrameTag[];

class UObject;
class UClass;
class UStruct;
class UState;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);   // 0x44e0
};

template <class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT AddItem(const T &Item)
    {
        INT Index = Add(1, sizeof(T));
        (*this)(Index) = Item;
        return Index;
    }
};

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
    virtual FArchive &operator<<(INT &N);                   // +0x1c, FName
    virtual FArchive &operator<<(UObject *&Res);            // +0x18

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }
    UBOOL IsTrans() { return ArIsTrans; }

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

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event);
};

struct FFrame : public FOutputDevice
{
    UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    FFrame(UObject *InObject);
    virtual void Serialize(const TCHAR *V, INT Event);
};

struct FStateFrame : public FFrame
{
    FFrame *CurrentFrame;
    UState *StateNode;
    QWORD ProbeMask;
    INT LatentAction;

    FStateFrame(UObject *InObject);
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
    virtual void Serialize(FArchive &Ar);

    INT Index;
    UObject *HashNext;
    FStateFrame *StateFrame;
    UObject *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;
    UClass *Class;

    void SetFlags(DWORD NewFlags) { ObjectFlags |= NewFlags; }
    DWORD GetFlags() const { return ObjectFlags; }
    UClass *GetClass() const { return Class; }
    UBOOL ConditionalDestroy();              // 0x15e70
    void ConditionalRegister();
    void UnhashObject(INT OuterIndex);

    static TArray<UObject *> GObjObjects;
    static TArray<INT> GObjAvailable;
    static TArray<UObject *> GObjRegistrants;
    static UObject *GObjHash[4096];
    static UBOOL GObjInitialized;
};
extern UBOOL GIsCriticalError;

class UStruct : public UObject
{
public:
    virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25();
    virtual INT GetPropertiesSize();                                          // +0x68
    virtual void V27(); virtual void V28();
    virtual void SerializeBin(FArchive &Ar, BYTE *Data, INT MaxReadBytes);    // +0x74
    virtual void SerializeTaggedProperties(FArchive &Ar, BYTE *Data, UClass *DefaultsClass); // +0x78
    BYTE Pad[0x3c - 0x28];
    TArray<BYTE> Script;
};

class UState : public UStruct
{
};

class UClass : public UState
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

inline FFrame::FFrame(UObject *InObject)
    : Node(InObject ? (UStruct *)InObject->Class : 0), Object(InObject), Code(0), Locals(0)
{
}

// RVA 0x159f0 (item 0096).
FStateFrame::FStateFrame(UObject *InObject)
    : FFrame(InObject), CurrentFrame(0), StateNode((UState *)InObject->Class), ProbeMask(~(QWORD)0)
{
}

// RVA 0x1d2d0 (item 0111). The hash only uses the name.
void UObject::UnhashObject(INT OuterIndex)
{
    UObject **Hash = &GObjHash[Name & 4095];
    while (*Hash != 0) {
        if (*Hash != this)
            Hash = &(*Hash)->HashNext;
        else
            *Hash = (*Hash)->HashNext;
    }
}

// RVA 0x1ea40 (item 0116).
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
        return Ar;
    }
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
    return Ar;
}

// RVA 0x15ea0.
void UObject::ConditionalRegister()
{
    if (Index == INDEX_NONE) {
        // Verify it is in the registrant list (check() compiled out).
        INT i;
        for (i = 0; i < GObjRegistrants.Num(); i++)
            if (GObjRegistrants(i) == this)
                break;
        Register();
    }
}

// RVA 0x15ee0.
UObject::~UObject()
{
    if (Index != INDEX_NONE && GObjInitialized && !GIsCriticalError) {
        ConditionalDestroy();
        UnhashObject(_LinkerIndex);
        GObjObjects(Index) = 0;
        GObjAvailable.AddItem(Index);
    }
    if (StateFrame)
        delete StateFrame;
}

// RVA 0x15f50.
void UObject::Serialize(FArchive &Ar)
{
    SetFlags(RF_DebugSerialize);

    // Make sure this object's class is loaded.
    if (Class != UClass::StaticClass())
        Ar.Preload(Class);

    // Special info.
    if (Ar.Ver() == 175) {
        if (!Ar.IsLoading() && !Ar.IsSaving())
            Ar << Name << Outer << *(UObject **)&Class;
        if (!Ar.IsLoading() && !Ar.IsSaving())
            Ar << _Linker;
    } else if (Ar.Ver() == 300) {
        if (!Ar.IsLoading() && !Ar.IsSaving())
            Ar << _Linker;
        if (!Ar.IsLoading() && !Ar.IsSaving())
            Ar << Name << Outer << *(UObject **)&Class;
    }

    // Execution stack.
    if (!Ar.IsTrans()) {
        if (GetFlags() & RF_HasStack) {
            if (!StateFrame)
                StateFrame = new(ObjectStateFrameTag) FStateFrame(this);
            Ar << *(UObject **)&StateFrame->Node << *(UObject **)&StateFrame->StateNode;
            Ar.Serialize(&StateFrame->ProbeMask, 8);
            Ar.Serialize(&StateFrame->LatentAction, 4);
            if (StateFrame->Node) {
                Ar.Preload(StateFrame->Node);
                INT Offset = StateFrame->Code ? StateFrame->Code - &StateFrame->Node->Script(0) : INDEX_NONE;
                Ar << AR_INDEX(Offset);
                StateFrame->Code = Offset != INDEX_NONE ? &StateFrame->Node->Script(Offset) : 0;
            } else {
                StateFrame->Code = 0;
            }
        } else if (StateFrame) {
            delete StateFrame;
            StateFrame = 0;
        }
    }

    // Serialize the object's properties.
    if (Class != UClass::StaticClass()) {
        if ((Ar.IsLoading() || Ar.IsSaving()) && !Ar.IsTrans())
            GetClass()->SerializeTaggedProperties(Ar, (BYTE *)this, Class);
        else
            GetClass()->SerializeBin(Ar, (BYTE *)this, 0);
    }

    // Memory counting.
    INT Size = GetClass()->GetPropertiesSize();
    Ar.CountBytes(Size, Size);
}

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
// The three functions are reached through the vtable in retail; constructing
// a local object emits the vtable, which keeps their standard conventions.
void Driver_15ea0(UObject *Obj, FArchive *Ar)
{
    Escape(&GMalloc); Escape(&UObject::GObjObjects); Escape(&UObject::GObjAvailable);
    Escape(&UObject::GObjRegistrants); Escape(&UObject::GObjInitialized);
    Escape(&GIsCriticalError); Escape(UObject::GObjHash);
    // ConditionalRegister is reached through a function pointer so it stays out of line.
    void (UObject::*Reg)() = &UObject::ConditionalRegister;
    Escape(&Reg);
    (Obj->*Reg)();
    Obj->Serialize(*Ar);
    delete Obj;
    UObject Local;
    Escape(&Local);
}
