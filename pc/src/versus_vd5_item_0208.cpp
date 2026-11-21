// Work item 0208 (w3): Versus RVA 0xe6bf0-0xe7109.
// 0xe7030 is a script event thunk on a UObject-derived class (name not recovered):
//   one 4-byte parameter, event name FName index 0xa37, compiled with /GL (this in ESI,
//   the parameter in EAX).
// 0xe7060 reverses the winding of a polygon (FPoly::Reverse-style): negates the normal
//   and swaps the vertices end for end. The layout differs from stock UE2 FPoly
//   (vertex count is a WORD at 0xe0), so the class keeps a neutral name.
typedef unsigned short TCHAR;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;

enum EName { NAME_Unnamed_A37 = 0xa37 }; // event name index; real name not recovered

class FName {
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
};

class UFunction;

class UObject {
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    UFunction *FindFunctionChecked(FName InName, INT Global = 0);
};

// Name not recovered.
class UnnamedClass_e7030 : public UObject {
public:
    // __declspec(noinline) stands in for the retail call site (0xe6455, in a large
    // render routine) where the LTCG inliner declined this event.
    __declspec(noinline) void eventUnnamed_e7030(INT Value);
};

void UnnamedClass_e7030::eventUnnamed_e7030(INT Value)
{
    struct UnnamedClass_e7030_eventUnnamed_e7030_Parms {
        INT Value;
    } Parms;
    Parms.Value = Value;
    ProcessEvent(FindFunctionChecked(FName(NAME_Unnamed_A37)), &Parms);
}

class FVector {
public:
    FLOAT X, Y, Z;
    FVector &operator*=(FLOAT Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }
};

template <class T> inline void Exchange(T &A, T &B)
{
    const T Temp = A;
    A = B;
    B = Temp;
}

// Polygon class; name not recovered (FPoly-like).
class UnnamedPoly_e7060 {
public:
    FVector Base;          // 0x00
    FVector Normal;        // 0x0c
    FVector Vertex[16];    // 0x18
    _WORD Pad_d8[4];       // 0xd8
    _WORD NumVertices;     // 0xe0
    void Reverse();
};

void UnnamedPoly_e7060::Reverse()
{
    Normal *= -1;
    INT c = NumVertices / 2;
    for (INT i = 0; i < c; i++) {
        FVector Temp = Vertex[i];
        Vertex[i] = Vertex[(NumVertices - 1) - i];
        Vertex[(NumVertices - 1) - i] = Temp;
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_e7030(UnnamedClass_e7030 *A, INT V) { A->eventUnnamed_e7030(V); }
