// Work item w3 0156: Versus RVA 0xc6790-0xc6a1a.
// AProjector natives (UnProjector.cpp): execAbandonProjector, execAttachActor,
// execDetachActor, and AProjector::ShouldTrace (vtable slot 43).

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;
typedef double DOUBLE;

#define NULL 0
#define INDEX_NONE -1
#define RESULT_DECL void *const Result

enum ETraceFlags { TRACE_Projectors = 0x4000 };

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);                 // 0x44e0
    void Remove(INT Index, INT Count, INT ElementSize);  // 0x119c0
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
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
    INT FindItemIndex(const T &Item)
    {
        for (INT Index = 0; Index < ArrayNum; Index++)
            if ((*this)(Index) == Item)
                return Index;
        return INDEX_NONE;
    }
    UBOOL FindItem(const T &Item, INT &Index)
    {
        for (Index = 0; Index < ArrayNum; Index++)
            if ((*this)(Index) == Item)
                return 1;
        return 0;
    }
    INT AddUniqueItem(const T &Item);  // 0xc9bb0 (LTCG: this in ESI, Item in EBX)
    INT RemoveItem(const T &Item);     // 0x10bd60 (LTCG: this in EDI, Item on the stack)
};

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class UObject;
struct FFrame;

struct FFrame
{
    void *VfTable;
    void *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;
    void Step(UObject *Context, RESULT_DECL);
};

class UObject
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42();
};

typedef void (UObject::*Native)(FFrame &TheStack, RESULT_DECL);
extern Native GNatives[];

inline void FFrame::Step(UObject *Context, RESULT_DECL)
{
    INT B = *Code++;
    (Context->*GNatives[B])(*this, Result);
}

#define P_GET_FLOAT(var) FLOAT var = 0.f; Stack.Step(Stack.Object, &var);
#define P_GET_ACTOR(var) AActor *var = NULL; Stack.Step(Stack.Object, &var);
#define P_FINISH Stack.Code++;

class FProjectorRenderInfo
{
public:
    INT Pad00;
    INT ReferenceCount;
    DOUBLE LastRenderTime;  // 0x08
    DOUBLE Expires;         // 0x10
    FProjectorRenderInfo *AddReference() { ReferenceCount++; return this; }
    UBOOL Render(DOUBLE CurrentTime);  // 0x9e510 (LTCG: this in EDX), another object
    void RemoveReference()
    {
        if (--ReferenceCount == 0)
            GMalloc->Free(this);
    }
};

class ALevelInfo;
class ULevel;

class AActor : public UObject
{
public:
    virtual UBOOL ShouldTrace(AActor *SourceActor, DWORD TraceFlags);  // slot 43
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
    virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
    virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
    virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
    virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
    virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
    virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
    virtual void Abandon();  // slot 80 (0x140); name is a guess

    BYTE Pad004[0x1a0 - 0x004];
    ALevelInfo *Level;                         // 0x1a0
    ULevel *XLevel;                            // 0x1a4
    BYTE Pad1a8[0x210 - 0x1a8];
    TArray<FProjectorRenderInfo *> Projectors; // 0x210
};

class ALevelInfo : public AActor
{
public:
    BYTE Pad21c[0x3b0 - 0x21c];
    FLOAT TimeSeconds;  // 0x3b0
};

class ULevel
{
public:
    BYTE Pad000[0x4ac8];
    TArray<TArray<FProjectorRenderInfo *> *> ProjectorLists;  // 0x4ac8 (name is a guess)
};

class AProjector : public AActor
{
public:
    BYTE Pad21c[0x464 - 0x21c];
    FProjectorRenderInfo *RenderInfo;  // 0x464

    void execAbandonProjector(FFrame &Stack, RESULT_DECL);
    void execAttachActor(FFrame &Stack, RESULT_DECL);
    void execDetachActor(FFrame &Stack, RESULT_DECL);
    UBOOL ShouldTrace(AActor *SourceActor, DWORD TraceFlags);
};

// RVA 0xc6790
void AProjector::execAbandonProjector(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(Lifetime);
    P_FINISH;
    if (RenderInfo && Lifetime != 0.f)
        RenderInfo->Expires = Lifetime + Level->TimeSeconds;
    Abandon();
}

// RVA 0xc6800
void AProjector::execAttachActor(FFrame &Stack, RESULT_DECL)
{
    P_GET_ACTOR(Actor);
    P_FINISH;
    if (RenderInfo && Actor)
    {
        for (INT i = 0; i < Actor->Projectors.Num(); i++)
        {
            if (!Actor->Projectors(i)->Render(Level->TimeSeconds))
            {
                Actor->Projectors.Remove(i);
                i--;
            }
        }
        if (Actor->Projectors.FindItemIndex(RenderInfo) == INDEX_NONE)
            Actor->Projectors.AddItem(RenderInfo->AddReference());
        XLevel->ProjectorLists.AddUniqueItem(&Actor->Projectors);
    }
}

// RVA 0xc6930
void AProjector::execDetachActor(FFrame &Stack, RESULT_DECL)
{
    P_GET_ACTOR(Actor);
    P_FINISH;
    if (RenderInfo && Actor)
    {
        INT Index = Actor->Projectors.FindItemIndex(RenderInfo);
        if (Index != INDEX_NONE)
        {
            RenderInfo->RemoveReference();
            Actor->Projectors.Remove(Index);
        }
        if (Projectors.Num() == 0)
            XLevel->ProjectorLists.RemoveItem(&Actor->Projectors);
    }
}

// RVA 0xc6a00
UBOOL AProjector::ShouldTrace(AActor *SourceActor, DWORD TraceFlags)
{
    if (TraceFlags & TRACE_Projectors)
        return 1;
    return AActor::ShouldTrace(SourceActor, TraceFlags);
}

// Out-of-line callees from other objects. Retail compiled them in the same
// LTCG link, so they are defined here only so the linker gives their call
// sites retail's register conventions; they are stand-ins, not matched units.
template <class T> __declspec(noinline) INT TArray<T>::AddUniqueItem(const T &Item)
{
    for (INT Index = 0; Index < ArrayNum; Index++)
        if ((*this)(Index) == Item)
            return Index;
    return AddItem(Item);
}

template <class T> __declspec(noinline) INT TArray<T>::RemoveItem(const T &Item)
{
    INT OriginalNum = ArrayNum;
    for (INT Index = 0; Index < ArrayNum; Index++)
        if ((*this)(Index) == Item)
            Remove(Index--);
    return OriginalNum - ArrayNum;
}

// Global at retail 0x10c9245c read by Render (layout from work item 0360).
struct FUnnamed_9e510_Inner { BYTE Pad[0x58]; INT Flag; };
struct FUnnamed_9e510_Mid { BYTE Pad[0x38]; FUnnamed_9e510_Inner *Inner; };
struct FUnnamed_9e510_Global
{
    BYTE Pad0[0x28];
    FUnnamed_9e510_Mid *Mid;    // 0x28
    BYTE Pad2C[0x4c - 0x2c];
    INT A;                      // 0x4c
    BYTE Pad50[4];
    INT B;                      // 0x54
};
extern FUnnamed_9e510_Global *GUnnamed_c9245c;

// RVA 0x9e510 (decoded in work item 0360).
__declspec(noinline) UBOOL FProjectorRenderInfo::Render(DOUBLE CurrentTime)
{
    if (Expires != 0.0 && !(GUnnamed_c9245c->A && GUnnamed_c9245c->B && GUnnamed_c9245c->Mid->Inner->Flag))
        goto Expired;
    if (Expires != 0.0)
    {
        if (Expires <= CurrentTime)
            goto Expired;
        if (LastRenderTime != 0.0 && CurrentTime - LastRenderTime > 1.0)
            goto Expired;
    }
    LastRenderTime = CurrentTime;
    return 1;
Expired:
    RemoveReference();
    return 0;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_c6800()
{
    Escape(&GNatives);
    Escape(&GMalloc);
    Escape(&GUnnamed_c9245c);
    Native Table[3] = { (Native)&AProjector::execAbandonProjector, (Native)&AProjector::execAttachActor,
                        (Native)&AProjector::execDetachActor };
    Escape(Table);
}
UBOOL Driver_9e510(FProjectorRenderInfo *R, DOUBLE T) { return R->Render(T) + R[1].Render(T + 1.0); }
