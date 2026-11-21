// Work item 0086: Versus RVA 0x14a0b0-0x14a57d, 6 functions, 1186 bytes.
//
// 0x14a0b0: FCylinderPushOut (name not recovered; cylinder support projection along normal)
// 0x14a160: CompressBoundingBox (name not recovered; packs child FBox relative to parent FBox into 30 bits)
// 0x14a2f0: DecompressBoundingBox (name not recovered; unpacks 30-bit quantized box relative to parent FBox)
// 0x14a420: QuantizeCollisionTree (name not recovered; recursively quantizes UStaticMesh collision node boxes)
// 0x14a530: FInBunch::operator<<(UObject *&) (vtable 0x3047c0 slot 6)
// 0x14a560: FInBunch::operator<<(FName &) (vtable 0x3047c0 slot 7)

typedef unsigned char BYTE;
typedef short SWORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef double DOUBLE;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

inline FLOAT appSqrt(DOUBLE F)
{
    return (FLOAT)sqrt(F);
}

template<class T> inline T Abs(const T A)
{
    return (A >= (T)0) ? A : -A;
}

template<class T> inline T Square(const T A)
{
    return A * A;
}

template<class T> inline T Min(const T A, const T B)
{
    return (A <= B) ? A : B;
}

template<class T> inline T Max(const T A, const T B)
{
    return (A >= B) ? A : B;
}

template<class T> inline T Clamp(const T X, const T MinVal, const T MaxVal)
{
    return X < MinVal ? MinVal : X > MaxVal ? MaxVal : X;
}

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

// Constant vectors read through pointers (imported data, as in versus_vd3_item_0307.cpp).
__declspec(dllimport) extern const FVector GMath_Zero;   // 0x10ccacc0
__declspec(dllimport) extern const FVector GMath_UnitX;  // 0x10ccacc4

// SCCT's FBox has no IsValid flag: an invalid box has Min.X = 1.f, Max.X = 0.f.
struct FBox
{
    FVector Min, Max;
    FBox() { Min.X = 1.f; Max.X = 0.f; }
    FBox(const FVector &InMin, const FVector &InMax);
    FBox &operator+=(const FVector &Other);
};

// RVA 0x4f820 (versus_vd3_item_0307.cpp), copied so LTCG gives FBox::FBox its retail convention.
__declspec(noinline) FBox &FBox::operator+=(const FVector &Other)
{
    if (Min.X - Max.X != 1.f)
    {
        Min.X = ::Min(Min.X, Other.X); Min.Y = ::Min(Min.Y, Other.Y); Min.Z = ::Min(Min.Z, Other.Z);
        Max.X = ::Max(Max.X, Other.X); Max.Y = ::Max(Max.Y, Other.Y); Max.Z = ::Max(Max.Z, Other.Z);
    }
    else
    {
        Min = Max = Other;
    }
    return *this;
}

// RVA 0x81ad0 (versus_vd3_item_0307.cpp; LTCG: this in ESI, InMin in EDX, InMax in EDI).
__declspec(noinline) FBox::FBox(const FVector &InMin, const FVector &InMax)
    : Min(InMin), Max(InMax)
{
    Min = GMath_UnitX;
    Max = GMath_Zero;
    *this += InMin;
    *this += InMax;
}

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
};

struct FStaticMeshCollisionNode
{
    SWORD unk_0;
    SWORD Child1;
    SWORD Child2;
    SWORD Child3;
    DWORD QuantizedBox;
};

class UStaticMesh
{
public:
    BYTE unk_0[0xf8];
    TArray<FStaticMeshCollisionNode> CollisionNodes;        // +0xf8
    BYTE unk_104[0x134 - 0x104];
    TArray<FStaticMeshCollisionNode> SecondCollisionNodes;  // +0x134
};

// RVA 0x14a0b0 (LTCG: Normal in ECX, Radius and HalfHeight on stack).
__declspec(noinline) FLOAT FCylinderPushOut(const FVector &Normal, FLOAT Radius, FLOAT HalfHeight)
{
    FLOAT Z = Normal.Z;
    FLOAT Y2 = Square(Normal.Y);
    FLOAT X2 = Square(Normal.X);
    if (Square(Z) + X2 + Y2 < 0.001f)
        return 0.f;

    if (Abs(Normal.Z) <= 0.99999f)
    {
        DOUBLE RadialX2 = X2;
        DOUBLE RadialY2 = Y2;
        FLOAT Scale = (1.f / appSqrt(RadialX2 + RadialY2)) * Radius;
        return (FLOAT)((Scale * RadialY2) + (Scale * RadialX2) + Abs(Normal.Z) * HalfHeight);
    }
    return HalfHeight;
}

inline INT QuantizeMin(FLOAT Val, FLOAT Base, FLOAT Size)
{
    INT Q = (Size > 0.f) ? (INT)((Val - Base) / Size * 31.f) : 0;
    return Clamp(Q, 0, 31);
}

inline INT QuantizeMax(FLOAT Val, FLOAT Base, FLOAT Size)
{
    INT Q = (Size > 0.f) ? (INT)((Val - Base) / Size * 31.f + 0.9999f) : 0;
    return Clamp(Q, 0, 31);
}

// RVA 0x14a160 (LTCG: Parent in ESI, Child in EDI).
__declspec(noinline) DWORD CompressBoundingBox(const FBox &Parent, const FBox &Child)
{
    DWORD Result = 0;

    FLOAT SizeX = Parent.Max.X - Parent.Min.X;
    Result |= QuantizeMin(Child.Min.X, Parent.Min.X, SizeX) << 27;
    Result |= QuantizeMax(Child.Max.X, Parent.Min.X, SizeX) << 11;

    FLOAT SizeY = Parent.Max.Y - Parent.Min.Y;
    Result |= QuantizeMin(Child.Min.Y, Parent.Min.Y, SizeY) << 22;
    Result |= QuantizeMax(Child.Max.Y, Parent.Min.Y, SizeY) << 6;

    FLOAT SizeZ = Parent.Max.Z - Parent.Min.Z;
    Result |= QuantizeMin(Child.Min.Z, Parent.Min.Z, SizeZ) << 17;
    Result |= QuantizeMax(Child.Max.Z, Parent.Min.Z, SizeZ) << 1;

    return Result;
}

// RVA 0x14a2f0 (LTCG: Parent in ECX, Packed in EAX, OutBox on stack).
__declspec(noinline) void DecompressBoundingBox(const FBox &Parent, DWORD Packed, FBox &OutBox)
{
    FVector Min, Max;

    FLOAT BaseX = Parent.Min.X;
    FLOAT StepX = (Parent.Max.X - BaseX) * (1.f / 31.f);
    Min.X = BaseX + ((Packed >> 27) & 0x1f) * StepX;
    Max.X = BaseX + ((Packed >> 11) & 0x1f) * StepX;

    FLOAT BaseY = Parent.Min.Y;
    FLOAT StepY = (Parent.Max.Y - BaseY) * (1.f / 31.f);
    Min.Y = BaseY + ((Packed >> 22) & 0x1f) * StepY;
    Max.Y = BaseY + ((Packed >> 6) & 0x1f) * StepY;

    FLOAT BaseZ = Parent.Min.Z;
    FLOAT StepZ = (Parent.Max.Z - BaseZ) * (1.f / 31.f);
    Min.Z = BaseZ + ((Packed >> 17) & 0x1f) * StepZ;
    Max.Z = BaseZ + ((Packed >> 1) & 0x1f) * StepZ;

    OutBox = FBox(Min, Max);
}

// RVA 0x14a420 (cdecl LTCG caller of CompressBoundingBox and DecompressBoundingBox).
__declspec(noinline) void QuantizeCollisionTree(UStaticMesh *Mesh, INT NodeIndex, UBOOL bUseSecond, TArray<FBox> &Boxes, const FBox &ParentBox)
{
    INT NumNodes = bUseSecond ? Mesh->SecondCollisionNodes.Num() : Mesh->CollisionNodes.Num();
    if (NodeIndex >= NumNodes)
        return;

    FBox &NodeBox = Boxes(NodeIndex);
    INT Child1, Child2, Child3;
    DWORD *QuantizedBox;
    if (bUseSecond)
    {
        Child1 = Mesh->SecondCollisionNodes(NodeIndex).Child1;
        Child2 = Mesh->SecondCollisionNodes(NodeIndex).Child2;
        Child3 = Mesh->SecondCollisionNodes(NodeIndex).Child3;
        QuantizedBox = &Mesh->SecondCollisionNodes(NodeIndex).QuantizedBox;
    }
    else
    {
        Child1 = Mesh->CollisionNodes(NodeIndex).Child1;
        Child2 = Mesh->CollisionNodes(NodeIndex).Child2;
        Child3 = Mesh->CollisionNodes(NodeIndex).Child3;
        QuantizedBox = &Mesh->CollisionNodes(NodeIndex).QuantizedBox;
    }

    *QuantizedBox = CompressBoundingBox(ParentBox, NodeBox);
    FBox DecompressedBox;
    DecompressBoundingBox(ParentBox, *QuantizedBox, DecompressedBox);

    if (Child3 != -1)
        QuantizeCollisionTree(Mesh, Child3, bUseSecond, Boxes, DecompressedBox);
    if (Child1 != -1)
        QuantizeCollisionTree(Mesh, Child1, bUseSecond, Boxes, DecompressedBox);
    if (Child2 != -1)
        QuantizeCollisionTree(Mesh, Child2, bUseSecond, Boxes, DecompressedBox);
}

// --- FInBunch serialization overrides (0x14a530, 0x14a560) ---

struct FName
{
    INT Index;
};

class UClass;
class FArchive;

class UObject
{
public:
    static UClass PrivateStaticClass; // 0x10cc9ed8
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class UPackageMap
{
public:
    virtual void Slot0();  virtual void Slot1();  virtual void Slot2();  virtual void Slot3();
    virtual void Slot4();  virtual void Slot5();  virtual void Slot6();  virtual void Slot7();
    virtual void Slot8();  virtual void Slot9();  virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22();
    virtual UBOOL SerializeObject(FArchive &Ar, UClass *Class, UObject *&Obj); // +0x5c
    virtual UBOOL SerializeName(FArchive &Ar, FName &Name);                    // +0x60
};

class UNetConnection
{
public:
    BYTE unk_0[0xb4];
    UPackageMap *PackageMap; // +0xb4
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(UObject *Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive &operator<<(FName &Name);
    virtual FArchive &operator<<(UObject *&Object);
};

class FBitReader : public FArchive
{
public:
    BYTE unk_4[0x50 - 4];
};

class FInBunch : public FBitReader
{
public:
    FInBunch *Next;              // +0x50
    UNetConnection *Connection;  // +0x54

    virtual FArchive &operator<<(UObject *&Object);
    virtual FArchive &operator<<(FName &Name);
};

// RVA 0x14a530
FArchive &FInBunch::operator<<(UObject *&Object)
{
    Connection->PackageMap->SerializeObject(*this, UObject::StaticClass(), Object);
    return *this;
}

// RVA 0x14a560
FArchive &FInBunch::operator<<(FName &Name)
{
    Connection->PackageMap->SerializeName(*this, Name);
    return *this;
}

// Scaffolding for the LTCG link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);

FLOAT Driver_14a0b0(const FVector *N, FLOAT R, FLOAT H)
{
    return FCylinderPushOut(*N, R, H);
}

void Driver_14a420(UStaticMesh *Mesh, INT NodeIndex, UBOOL bUseSecond, TArray<FBox> *Boxes, const FBox *ParentBox, FBox *Out, const FVector *A, const FVector *B)
{
    Escape((void *)&GMath_Zero);
    Escape((void *)&GMath_UnitX);
    new (Out) FBox(*A, *B);
    QuantizeCollisionTree(Mesh, NodeIndex, bUseSecond, *Boxes, *ParentBox);
}
