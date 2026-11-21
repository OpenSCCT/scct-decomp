// Work item 0365: Versus RVA 0xa2e20, the UERainPrimitive constructor
// (class size 0x80, derived from UPrimitive; vtable 0x10c0b368, UPrimitive's
// vtable 0x10c0bae8). Compiled with /GL and linked with /LTCG: this arrives in
// EDI and the member constructors take their this in ESI.
// The UPrimitive part is inlined: two vectors initialised from the global
// constant vectors and four zeroed dwords. Member types are not identified;
// their constructors are named after their RVAs.

typedef float FLOAT;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

// Pointers to the global constant vectors (zero and unit X).
extern FVector *GMath_Zero;   // 0x10ccacc0
extern FVector *GMath_UnitX;  // 0x10ccacc4

class UObject
{
public:
    UObject() {}
    virtual ~UObject();
    unsigned char ObjectData[0x28 - 4];
};

class UPrimitive : public UObject
{
public:
    UPrimitive()
        : VectorA(*GMath_UnitX), VectorB(*GMath_Zero), Field40()
    {}
    virtual ~UPrimitive();
    FVector VectorA;      // 0x28
    FVector VectorB;      // 0x34
    struct FZero4 { void *A, *B, *C, *D; FZero4() : A(0), B(0), C(0), D(0) {} } Field40;
    int Field50;
};

struct Member_a2f40 { Member_a2f40(); unsigned char Bytes[0x1c]; };  // ctor RVA 0xa2f40
struct Member_1126e0 { Member_1126e0(); unsigned char Bytes[0x10]; }; // ctor RVA 0x1126e0

class UERainPrimitive : public UPrimitive
{
public:
    UERainPrimitive();
    virtual ~UERainPrimitive();
    Member_a2f40 Field54;
    Member_1126e0 Field70;
};

// RVA 0xa2e20
UERainPrimitive::UERainPrimitive()
{
}

// Scaffolding for the link, not part of the unit: stand-in member
// constructors so the linker gives them the retail register convention.
void Escape(void *);
__declspec(noinline) Member_a2f40::Member_a2f40() { Escape(this); Bytes[0] = 0; }
__declspec(noinline) Member_1126e0::Member_1126e0() { Escape(this); Bytes[1] = 1; }
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_a2e20(void *Mem)
{
    Escape(&GMath_Zero);
    Escape(&GMath_UnitX);
    new (Mem) UERainPrimitive;
}
