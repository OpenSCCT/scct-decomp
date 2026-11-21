// Work item 0196: Versus RVA 0x4a570-0x4a7a8, Core UnrealScript natives
// (SCCT additions in UnScript.cpp / UnObj.cpp).
//   0x4a570 UObject::execListClass    (LTCG: FObjectIterator ctor takes this in EAX)
//   0x4a610 UObject::execPackLW
//   0x4a680 UObject::execPackHW
//   0x4a6f0 UObject::execGetPackedLW
//   0x4a750 UObject::execGetPackedHW
// Evidence: GNatives table at 0x10c819d8 indexed by the script byte code,
// FFrame layout {vtable, Node, Object, Code}, FObjectIterator over GObjObjects
// (0x1f470 constructor, 0x4a550 folded empty destructor), UObject::Name at
// 0x20, Class at 0x24, UField::SuperField at 0x28.
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class UObject;
class UClass;
struct FFrame;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
};
template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

struct FName
{
    INT Index;
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
};

#define RESULT_DECL void *const Result

class UObject
{
public:
    virtual ~UObject();
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;
    UClass *Class;

    UClass *GetClass() const { return Class; }
    const FName GetFName() const { return Name; }

    void execListClass(FFrame &Stack, RESULT_DECL);
    void execPackLW(FFrame &Stack, RESULT_DECL);
    void execPackHW(FFrame &Stack, RESULT_DECL);
    void execGetPackedLW(FFrame &Stack, RESULT_DECL);
    void execGetPackedHW(FFrame &Stack, RESULT_DECL);

    static TArray<UObject *> GObjObjects;
};

class UField : public UObject
{
public:
    UField *SuperField;
    UField *Next;
};
class UClass : public UField
{
public:
    UClass *GetSuperClass() const { return (UClass *)SuperField; }
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame
{
    void *VTable;
    void *Node;
    UObject *Object;
    BYTE *Code;
    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_INT(var) INT var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_NAME(var) FName var; var.Index = 0; Stack.Step(Stack.Object, &var);
#define P_FINISH Stack.Code++;

class FObjectIterator
{
public:
    FObjectIterator();
    __stdcall ~FObjectIterator();      // RVA 0x4a550 (folded empty `ret 4`, `this` on the stack)
    void operator++()
    {
        while (++Index < Objects->Num() && !(*Objects)(Index))
            ;
    }
    operator UBOOL() { return Index < Objects->Num(); }
    UObject *operator*() { return (*Objects)(Index); }
    UObject *operator->() { return (*Objects)(Index); }
protected:
    TArray<UObject *> *Objects;
    INT Index;
};

// RVA 0x1f470 (published elsewhere; defined so the link gives it its convention).
__declspec(noinline) FObjectIterator::FObjectIterator()
    : Objects(&UObject::GObjObjects), Index(-1)
{
    ++*this;
}

// RVA 0x4a550 (empty in retail, published elsewhere). Stand-in body, link
// scaffolding only: it keeps the call, `this` on the stack, and the Index store.
void DestroyIteratorStandIn(INT);
__declspec(noinline) __stdcall FObjectIterator::~FObjectIterator()
{
    DestroyIteratorStandIn(0);
    DestroyIteratorStandIn(Index);
}

// RVA 0x4a570. Lists the objects of a named class; the log output is compiled
// out of this build, leaving only the walk.
void UObject::execListClass(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(ClassName);
    P_FINISH;
    for (FObjectIterator It; It; ++It) {
        for (UClass *C = It->GetClass(); C; C = C->GetSuperClass()) {
            if (C->GetFName() == ClassName)
                break;
        }
    }
}

// RVA 0x4a610
void UObject::execPackLW(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Packed);
    P_GET_INT(LW);
    P_FINISH;
    *(INT *)Result = (Packed & 0xffff0000) | (LW & 0xffff);
}

// RVA 0x4a680
void UObject::execPackHW(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(LW);
    P_GET_INT(HW);
    P_FINISH;
    *(INT *)Result = (HW << 16) | (LW & 0xffff);
}

// RVA 0x4a6f0
void UObject::execGetPackedLW(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Packed);
    P_FINISH;
    INT LW = Packed & 0xffff;
    if (LW > 32767)
        LW -= 65536;
    *(INT *)Result = LW;
}

// RVA 0x4a750
void UObject::execGetPackedHW(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Packed);
    P_FINISH;
    INT HW = (Packed >> 16) & 0xffff;
    if (HW > 32767)
        HW -= 65536;
    *(INT *)Result = HW;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_4a570(UObject *O, FFrame *S, void *R)
{
    Escape(&UObject::GObjObjects);
    Escape(&GNatives);
    // Retail reaches it only through the native table, which fixes its convention.
    Native N = &UObject::execListClass;
    Escape(&N);
    (O->*N)(*S, R);
}
