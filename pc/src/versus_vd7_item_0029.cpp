// Work item 0029: Versus RVA 0x127a40-0x127d77, 2 functions, 814 bytes.
//
// Actor-list script iterator helpers on AActor (VC7.0 /GL /LTCG):
//   0x127a40 AActor::IterateAllActors     (called by execAllActors, execAllPawns,
//                                          execAllPlayerControllers, execAllObjectives,
//                                          execAllInfos; Stack in ESI, this/Actors/Result on stack)
//   0x127be0 AActor::IterateDynamicActors (called by execDynamicActors, execDynamicPawns,
//                                          execDynamicPlayerControllers, execDynamicInfos;
//                                          Stack in ESI, this/Actors/StartIndex/Result on stack)
// Helper method names are inferred from their callers; exact original names are unknown.

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

#define NULL 0
#define RESULT_DECL void *const Result
#define MAX_SIMPLE_RETURN_VALUE_SIZE 32

enum EName { NAME_None = 0 };
enum EExprToken
{
    EX_IteratorPop  = 0x30,
    EX_IteratorNext = 0x31,
};

struct FName
{
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
};

template <class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;

    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

class __single_inheritance UObject;
class UClass;
class UStruct;
class UProperty;
class AActor;
struct FFrame;

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);

extern Native GNatives[];       // 0x10c819d8
extern BYTE *GPropAddr;         // 0x10c78b9c
extern UObject *GPropObject;    // 0x10c78ba4
extern UProperty *GProperty;    // 0x10c78b64

struct FFrame
{
    void *VfTable;
    UStruct *Node;              // +0x04
    UObject *Object;            // +0x08
    BYTE *Code;                 // +0x0c

    __forceinline void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }

    __forceinline INT ReadWord()
    {
        INT Result = *(WORD *)Code;
        Code += sizeof(WORD);
        return Result;
    }
};

class UObject
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20();
    virtual void NetDirty(UProperty *Property);     // +0x54

    INT Index;                                      // +0x04
    UObject *HashNext;                              // +0x08
    void *StateFrame;                               // +0x0c
    void *_Linker;                                  // +0x10
    INT _LinkerIndex;                               // +0x14
    UObject *Outer;                                 // +0x18
    DWORD ObjectFlags;                              // +0x1c
    FName Name;                                     // +0x20
    UClass *Class;                                  // +0x24

    inline UBOOL IsA(const UClass *SomeBase) const;
};

class UStruct : public UObject
{
public:
    BYTE unk_28[0x3c - 0x28];
    TArray<BYTE> Script;                            // +0x3c
};

class UClass : public UStruct
{
public:
    BYTE unk_48[0x10c - 0x48];
    DWORD ParentDivisor;                            // +0x10c
    DWORD ClassProduct;                             // +0x110
};

inline UBOOL UObject::IsA(const UClass *SomeBase) const
{
    if (!SomeBase || Class == SomeBase)
        return 1;
    return Class->ClassProduct % SomeBase->ParentDivisor == 0;
}

class AActor : public UObject
{
public:
    static UClass PrivateStaticClass;               // 0x10cc52a8
    static UClass *StaticClass() { return &PrivateStaticClass; }

    BYTE unk_28[0x2bc - 0x28];
    FName Tag;                                      // +0x2bc

    void IterateAllActors(TArray<AActor *> &ActorArray, FFrame &Stack, RESULT_DECL);
    void IterateDynamicActors(
        TArray<AActor *> &ActorArray, INT FirstIndex, FFrame &Stack, RESULT_DECL);
};

#define P_GET_OBJECT(cls, var) \
    cls *var = NULL; \
    Stack.Step(Stack.Object, &var);

#define P_GET_OBJECT_REF(cls, var) \
    cls *var##T = NULL; \
    GPropAddr = 0; \
    Stack.Step(Stack.Object, &var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    cls *&var = GPropAddr ? *(cls **)GPropAddr : var##T;

#define P_GET_NAME_OPTX(var, def) \
    FName var = def; \
    Stack.Step(Stack.Object, &var);

#define P_FINISH \
    Stack.Code++;

#define PRE_ITERATOR \
    INT wEndOffset = Stack.ReadWord(); \
    BYTE B = 0, Buffer[MAX_SIMPLE_RETURN_VALUE_SIZE]; \
    BYTE *StartCode = Stack.Code; \
    do {

#define POST_ITERATOR \
        while ((B = *Stack.Code) != EX_IteratorPop && B != EX_IteratorNext) \
            Stack.Step(Stack.Object, Buffer); \
        if (*Stack.Code++ == EX_IteratorNext) \
            Stack.Code = StartCode; \
    } while (B != EX_IteratorPop);

// RVA 0x127a40
void AActor::IterateAllActors(TArray<AActor *> &ActorArray, FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UClass, BaseClass);
    P_GET_OBJECT_REF(AActor, OutActor);
    P_GET_NAME_OPTX(MatchTag, NAME_None);
    P_FINISH;

    BaseClass = BaseClass ? BaseClass : AActor::StaticClass();
    INT iActor = 0;

    PRE_ITERATOR;
        OutActor = NULL;
        while (iActor < ActorArray.Num())
        {
            AActor *TestActor = ActorArray(iActor++);
            if (TestActor &&
                TestActor->IsA(BaseClass) &&
                (MatchTag == NAME_None || TestActor->Tag == MatchTag))
            {
                OutActor = TestActor;
                break;
            }
        }
        if (OutActor == NULL)
        {
            Stack.Code = &Stack.Node->Script(wEndOffset + 1);
            break;
        }
    POST_ITERATOR;
}

// RVA 0x127be0
void AActor::IterateDynamicActors(
    TArray<AActor *> &ActorArray, INT FirstIndex, FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UClass, BaseClass);
    P_GET_OBJECT_REF(AActor, OutActor);
    P_GET_NAME_OPTX(MatchTag, NAME_None);
    P_FINISH;

    BaseClass = BaseClass ? BaseClass : AActor::StaticClass();
    INT iActor = FirstIndex;

    PRE_ITERATOR;
        OutActor = NULL;
        while (iActor < ActorArray.Num())
        {
            AActor *TestActor = ActorArray(iActor++);
            if (TestActor &&
                TestActor->IsA(BaseClass) &&
                (MatchTag == NAME_None || TestActor->Tag == MatchTag))
            {
                OutActor = TestActor;
                break;
            }
        }
        if (OutActor == NULL)
        {
            Stack.Code = &Stack.Node->Script(wEndOffset + 1);
            break;
        }
    POST_ITERATOR;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);

void Driver_127a40(
    AActor *Self, FFrame &Stack, RESULT_DECL, TArray<AActor *> &Arr1, TArray<AActor *> &Arr2)
{
    Escape(GNatives);
    Escape(&AActor::PrivateStaticClass);
    Self->IterateAllActors(Arr1, Stack, Result);
    Self->IterateAllActors(Arr2, Stack, Result);
}

void Driver_127be0(
    AActor *Self, FFrame &Stack, RESULT_DECL,
    TArray<AActor *> &Arr1, TArray<AActor *> &Arr2, INT FirstIndex)
{
    Escape(GNatives);
    Escape(&AActor::PrivateStaticClass);
    Self->IterateDynamicActors(Arr1, FirstIndex, Stack, Result);
    Self->IterateDynamicActors(Arr2, 0, Stack, Result);
}
