// w4_item_0030.cpp -- Versus AActor radius-actor iterator helper (RVA 0x127d80)

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

#define NULL 0
#define MAX_CONST_SIZE 32
#define EX_IteratorPop 0x30
#define EX_IteratorNext 0x31
#define RESULT_DECL void *const Result

struct FGuid;
struct FFrame;
class UObject;
class UProperty;
class UStruct;
class UClass;
class AActor;

template<class T> inline T Square(const T A)
{
    return A * A;
}

struct FVector {
    FLOAT X, Y, Z;

    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator-(const FVector &V) const
    {
        return FVector(X - V.X, Y - V.Y, Z - V.Z);
    }
    FLOAT SizeSquared() const
    {
        return X * X + Y * Y + Z * Z;
    }
};

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    INT Num() const { return ArrayNum; }
};

template<class T> class TArray : public FArray {
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
};

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void NetDirty(UProperty *Property);

    INT Index;
    BYTE unk_8[0x1c];
    UClass *Class;

    UBOOL IsA(UClass *SomeBase) const;
};

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

extern BYTE *GPropAddr;
extern UObject *GPropObject;
extern UProperty *GProperty;

struct FFrame : public FOutputDevice {
    UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
    INT ReadWord()
    {
        INT Res = *(_WORD *)Code;
        Code += sizeof(_WORD);
        return Res;
    }
};

class UField : public UObject {
public:
    virtual ~UField();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();

    BYTE unk_28[0x8];
};

class UStruct : public UField {
public:
    virtual ~UStruct();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();

    BYTE unk_30[0xc];
    TArray<BYTE> Script;
    BYTE unk_48[0x20];
};

class UState : public UStruct {
public:
    virtual ~UState();

    BYTE unk_68[0x20];
};

class UClass : public UState {
public:
    virtual ~UClass();

    BYTE unk_88[0x84];
    DWORD ClassPrime;   // inferred name: divisor used by Versus fast IsA
    DWORD ClassProduct; // inferred name: dividend used by Versus fast IsA
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    return (!SomeBase || Class == SomeBase)
        ? 1
        : ((Class->ClassProduct % SomeBase->ClassPrime) == 0);
}

class ULevelBase : public UObject {
public:
    BYTE unk_28[0x4];
    TArray<AActor *> Actors;
    BYTE unk_38[0x24];
    TArray<AActor *> Pawns;
    BYTE unk_68[0x14];
    TArray<AActor *> GamePlayObjects;
    BYTE unk_88[0x14];
    TArray<AActor *> Alarms;
};

class AActor : public UObject {
public:
    BYTE unk_28[0x58];
    FVector Location;
    BYTE unk_8c[0x118];
    ULevelBase *XLevel;
    BYTE unk_1a8[0xc0];
    FLOAT CollisionRadius;

    void RadiusActorsHelper(TArray<AActor *> &ActorList, FFrame &Stack, RESULT_DECL);
    void execRadiusActors(FFrame &Stack, RESULT_DECL);
    void execRadiusPawns(FFrame &Stack, RESULT_DECL);
    void execRadiusAlarms(FFrame &Stack, RESULT_DECL);
    void execRadiusGamePlayObjects(FFrame &Stack, RESULT_DECL);
};

#define P_GET_FLOAT(Var) FLOAT Var = 0.0f; Stack.Step(Stack.Object, &Var)
#define P_GET_OBJECT(Cls, Var) Cls *Var = NULL; Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR_OPTX(Var, Def) FVector Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_ACTOR_REF(Var) \
    AActor *Var##T = NULL; \
    GPropAddr = 0; \
    Stack.Step(Stack.Object, &Var##T); \
    if (GPropObject) \
        GPropObject->NetDirty(GProperty); \
    AActor **Var = GPropAddr ? (AActor **)GPropAddr : &Var##T
#define P_FINISH Stack.Code++

#define PRE_ITERATOR \
    INT wEndOffset = Stack.ReadWord(); \
    BYTE B = 0, Buffer[MAX_CONST_SIZE]; \
    BYTE *StartCode = Stack.Code; \
    do {

#define POST_ITERATOR \
        while ((B = *Stack.Code) != EX_IteratorPop && B != EX_IteratorNext) \
            Stack.Step(Stack.Object, Buffer); \
        if (*Stack.Code++ == EX_IteratorNext) \
            Stack.Code = StartCode; \
    } while (B != EX_IteratorPop);

// AActor::RadiusActorsHelper (RVA 0x127d80; inferred name for the shared helper called by
// the RadiusActors / RadiusPawns / RadiusAlarms / RadiusGamePlayObjects script iterators)
void AActor::RadiusActorsHelper(TArray<AActor *> &ActorList, FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UClass, BaseClass);
    P_GET_ACTOR_REF(Actor);
    P_GET_FLOAT(Radius);
    P_GET_VECTOR_OPTX(BaseLoc, Location);
    P_FINISH;

    INT iActor = 0;
    if (BaseClass)
    {
        PRE_ITERATOR;
            *Actor = NULL;
            while (iActor < ActorList.Num())
            {
                AActor *TestActor = ActorList(iActor++);
                if (TestActor && TestActor->IsA(BaseClass) &&
                    (TestActor->Location - BaseLoc).SizeSquared() <
                        Square(Radius + TestActor->CollisionRadius))
                {
                    *Actor = TestActor;
                    break;
                }
            }
            if (*Actor == NULL)
            {
                Stack.Code = &Stack.Node->Script(wEndOffset + 1);
                break;
            }
        POST_ITERATOR;
    }
    else
    {
        PRE_ITERATOR;
            *Actor = NULL;
            while (iActor < ActorList.Num())
            {
                AActor *TestActor = ActorList(iActor++);
                if (TestActor &&
                    (TestActor->Location - BaseLoc).SizeSquared() <
                        Square(Radius + TestActor->CollisionRadius))
                {
                    *Actor = TestActor;
                    break;
                }
            }
            if (*Actor == NULL)
            {
                Stack.Code = &Stack.Node->Script(wEndOffset + 1);
                break;
            }
        POST_ITERATOR;
    }
}

// Scaffolding for the link, not part of the unit.
void AActor::execRadiusActors(FFrame &Stack, RESULT_DECL)
{
    RadiusActorsHelper(XLevel->Actors, Stack, Result);
}
void AActor::execRadiusPawns(FFrame &Stack, RESULT_DECL)
{
    RadiusActorsHelper(XLevel->Pawns, Stack, Result);
}
void AActor::execRadiusAlarms(FFrame &Stack, RESULT_DECL)
{
    RadiusActorsHelper(XLevel->Alarms, Stack, Result);
}
void AActor::execRadiusGamePlayObjects(FFrame &Stack, RESULT_DECL)
{
    RadiusActorsHelper(XLevel->GamePlayObjects, Stack, Result);
}

void Escape(void *);
void Driver_127d80()
{
    void (AActor::*P1)(FFrame &, RESULT_DECL) = &AActor::execRadiusActors;
    void (AActor::*P2)(FFrame &, RESULT_DECL) = &AActor::execRadiusPawns;
    void (AActor::*P3)(FFrame &, RESULT_DECL) = &AActor::execRadiusAlarms;
    void (AActor::*P4)(FFrame &, RESULT_DECL) = &AActor::execRadiusGamePlayObjects;
    Escape(&P1);
    Escape(&P2);
    Escape(&P3);
    Escape(&P4);
}
