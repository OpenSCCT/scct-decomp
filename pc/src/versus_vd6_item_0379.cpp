typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned short TCHAR;
typedef unsigned char BYTE;

struct FMemStack;
struct FCheckResult;
class AActor;
class UPrimitive;
struct FOctreeNode;
struct FOctreeNodeBounds;
class FCollisionOctree;

struct FVector
{
    FLOAT X, Y, Z;

    inline FVector() {}
    inline FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    inline FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}

    inline FVector operator+(const FVector &V) const
    {
        return FVector(X + V.X, Y + V.Y, Z + V.Z);
    }

    inline FVector operator-(const FVector &V) const
    {
        return FVector(X - V.X, Y - V.Y, Z - V.Z);
    }
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

extern FVector *GBoxInitMin;
extern FVector *GBoxInitMax;

struct FBox
{
    FVector Min;
    FVector Max;

    FBox() {}
    FBox(const FVector &InMin, const FVector &InMax);

    FBox &operator+=(const FVector &Other);

    inline UBOOL IsValid() const
    {
        return (Min.X - Max.X) != 1.0f;
    }
};

template<class T> inline T MinVal(const T A, const T B) { return (A <= B) ? A : B; }
template<class T> inline T MaxVal(const T A, const T B) { return (A >= B) ? A : B; }

FBox &FBox::operator+=(const FVector &Other)
{
    if (IsValid())
    {
        Min.X = MinVal(Min.X, Other.X);
        Min.Y = MinVal(Min.Y, Other.Y);
        Min.Z = MinVal(Min.Z, Other.Z);
        Max.X = MaxVal(Max.X, Other.X);
        Max.Y = MaxVal(Max.Y, Other.Y);
        Max.Z = MaxVal(Max.Z, Other.Z);
    }
    else
    {
        Min = Max = Other;
    }
    return *this;
}

FBox::FBox(const FVector &InMin, const FVector &InMax)
{
    Min = InMin;
    Max = InMax;
    Min = *GBoxInitMin;
    Max = *GBoxInitMax;
    *this += InMin;
    *this += InMax;
}

class UPrimitive
{
public:
    virtual void Pad00(); virtual void Pad01(); virtual void Pad02(); virtual void Pad03();
    virtual void Pad04(); virtual void Pad05(); virtual void Pad06(); virtual void Pad07();
    virtual void Pad08(); virtual void Pad09(); virtual void Pad0A(); virtual void Pad0B();
    virtual void Pad0C(); virtual void Pad0D(); virtual void Pad0E(); virtual void Pad0F();
    virtual void Pad10(); virtual void Pad11(); virtual void Pad12(); virtual void Pad13();
    virtual void Pad14(); virtual void Pad15(); virtual void Pad16(); virtual void Pad17();
    virtual void Pad18(); virtual void Pad19();
    virtual FBox GetCollisionBoundingBox(const AActor *Owner) const; // 0x68
};

class AActor
{
public:
    virtual void Pad00(); virtual void Pad01(); virtual void Pad02(); virtual void Pad03();
    virtual void Pad04(); virtual void Pad05(); virtual void Pad06(); virtual void Pad07();
    virtual void Pad08(); virtual void Pad09(); virtual void Pad0A(); virtual void Pad0B();
    virtual void Pad0C(); virtual void Pad0D(); virtual void Pad0E(); virtual void Pad0F();
    virtual void Pad10(); virtual void Pad11(); virtual void Pad12(); virtual void Pad13();
    virtual void Pad14(); virtual void Pad15(); virtual void Pad16(); virtual void Pad17();
    virtual void Pad18(); virtual void Pad19(); virtual void Pad1A(); virtual void Pad1B();
    virtual void Pad1C(); virtual void Pad1D(); virtual void Pad1E(); virtual void Pad1F();
    virtual void Pad20(); virtual void Pad21(); virtual void Pad22(); virtual void Pad23();
    virtual void Pad24(); virtual void Pad25(); virtual void Pad26(); virtual void Pad27();
    virtual void Pad28(); virtual void Pad29(); virtual void Pad2A(); virtual void Pad2B();
    virtual UPrimitive *GetPrimitive(); // 0xB0

    BYTE Pad_04[0x7C];
    FVector Location;  // 0x80
    BYTE Pad_8C[0x54];
    FRotator Rotation; // 0xE0
};

struct FOctreeNodeBounds
{
    FVector Center;
    FLOAT HalfExtent;
};

extern FOctreeNodeBounds RootNodeBounds;

struct FOctreeNode
{
    void ActorPointCheck(FCollisionOctree *Octree, FOctreeNodeBounds *Bounds);
    void ActorRadiusCheck(FCollisionOctree *Octree, FOctreeNodeBounds *Bounds);
    void ActorEncroachmentCheck(FCollisionOctree *Octree, FOctreeNodeBounds *Bounds);
    void ActorOverlapCheck(FCollisionOctree *Octree, FOctreeNodeBounds *Bounds);
};

template<class T> inline void Exchange(T &A, T &B)
{
    const T Temp = A;
    A = B;
    B = Temp;
}

class FCollisionOctree
{
public:
    FOctreeNode *RootNode;   // 0x00
    INT CheckTag;            // 0x04
    FCheckResult *ChkResult; // 0x08
    FMemStack *ChkMem;       // 0x0C
    BYTE Pad_10[0x0C];       // 0x10
    FVector ChkStart;        // 0x1C
    BYTE Pad_28[0x24];       // 0x28
    FVector ChkExtent;       // 0x4C
    DWORD ChkTraceFlags;     // 0x58
    DWORD ChkExtraNodeFlags; // 0x5C
    AActor *ChkActor;        // 0x60
    FLOAT ChkRadiusSqr;      // 0x64
    FBox ChkBox;             // 0x68
    UBOOL ChkBlockOnly;      // 0x80

    FCheckResult *ActorPointCheck(FMemStack &Mem, const FVector &Location, const FVector &Extent, DWORD TraceFlags, DWORD ExtraNodeFlags, UBOOL bSingleResult);
    FCheckResult *ActorRadiusCheck(FMemStack &Mem, const FVector &Location, FLOAT Radius, DWORD ExtraNodeFlags);
    FCheckResult *ActorEncroachmentCheck(FMemStack &Mem, AActor *Actor, FVector Location, FRotator Rotation, DWORD TraceFlags, DWORD ExtraNodeFlags);
    FCheckResult *ActorOverlapCheck(FMemStack &Mem, AActor *Actor, FBox *Box, UBOOL bBlockOnly);
};

// RVA 0x11a0a0
FCheckResult *FCollisionOctree::ActorPointCheck(FMemStack &Mem, const FVector &Location, const FVector &Extent, DWORD TraceFlags, DWORD ExtraNodeFlags, UBOOL bSingleResult)
{
    CheckTag++;
    ChkMem = &Mem;
    ChkResult = 0;
    ChkStart = Location;
    ChkExtent = Extent;
    ChkExtraNodeFlags = ExtraNodeFlags;
    ChkTraceFlags = TraceFlags;
    if (bSingleResult)
        ChkTraceFlags |= 0x200;
    ChkBox = FBox(ChkStart - ChkExtent, ChkStart + ChkExtent);
    RootNode->ActorPointCheck(this, &RootNodeBounds);
    return ChkResult;
}

// RVA 0x11a170
FCheckResult *FCollisionOctree::ActorRadiusCheck(FMemStack &Mem, const FVector &Location, FLOAT Radius, DWORD ExtraNodeFlags)
{
    ChkMem = &Mem;
    ChkResult = 0;
    CheckTag++;
    ChkStart = Location;
    ChkRadiusSqr = Radius * Radius;
    ChkExtraNodeFlags = ExtraNodeFlags;
    ChkBox = FBox(Location - FVector(Radius, Radius, Radius), Location + FVector(Radius, Radius, Radius));
    RootNode->ActorRadiusCheck(this, &RootNodeBounds);
    return ChkResult;
}

// RVA 0x11a230
FCheckResult *FCollisionOctree::ActorEncroachmentCheck(FMemStack &Mem, AActor *Actor, FVector Location, FRotator Rotation, DWORD TraceFlags, DWORD ExtraNodeFlags)
{
    ChkMem = &Mem;
    ChkTraceFlags = TraceFlags;
    ChkExtraNodeFlags = ExtraNodeFlags;
    ChkResult = 0;
    ChkActor = Actor;
    CheckTag++;
    Exchange(Location, Actor->Location);
    Exchange(Rotation, Actor->Rotation);
    ChkBox = Actor->GetPrimitive()->GetCollisionBoundingBox(Actor);
    if (ChkBox.IsValid())
        RootNode->ActorEncroachmentCheck(this, &RootNodeBounds);
    Exchange(Location, Actor->Location);
    Exchange(Rotation, Actor->Rotation);
    return ChkResult;
}

// RVA 0x11a370
FCheckResult *FCollisionOctree::ActorOverlapCheck(FMemStack &Mem, AActor *Actor, FBox *Box, UBOOL bBlockOnly)
{
    CheckTag++;
    ChkResult = 0;
    ChkBox = *Box;
    ChkActor = Actor;
    ChkMem = &Mem;
    ChkBlockOnly = bBlockOnly;
    if (ChkBox.IsValid())
        RootNode->ActorOverlapCheck(this, &RootNodeBounds);
    return ChkResult;
}

// Scaffolding for the link, not part of the unit.
extern void Escape(void *);
extern FMemStack GMem;

FCheckResult *Driver_11a0a0(FCollisionOctree *O, FMemStack *Mem, const FVector *Loc, const FVector *Ext, DWORD TraceFlags, DWORD ExtraFlags, UBOOL bSingle)
{
    Escape(&RootNodeBounds);
    Escape(&GBoxInitMin);
    Escape(&GBoxInitMax);
    FCheckResult *R1 = O->ActorPointCheck(*Mem, *Loc, *Ext, TraceFlags, ExtraFlags, bSingle);
    FCheckResult *R2 = O->ActorPointCheck(GMem, *Loc, *Ext, 0x4000, 0, 1);
    return R1 ? R1 : R2;
}

FCheckResult *Driver_11a170(FCollisionOctree *O, FMemStack *Mem, const FVector *Loc, FLOAT Radius, DWORD ExtraFlags)
{
    Escape(&RootNodeBounds);
    Escape(&GBoxInitMin);
    Escape(&GBoxInitMax);
    FCheckResult *R1 = O->ActorRadiusCheck(*Mem, *Loc, Radius, ExtraFlags);
    FCheckResult *R2 = O->ActorRadiusCheck(GMem, *Loc, Radius, 0);
    return R1 ? R1 : R2;
}

FCheckResult *Driver_11a230(FCollisionOctree *O, FMemStack *Mem, AActor *Actor, FVector Loc, FRotator Rot, DWORD TraceFlags, DWORD ExtraFlags)
{
    Escape(&RootNodeBounds);
    FCheckResult *R1 = O->ActorEncroachmentCheck(*Mem, Actor, Loc, Rot, TraceFlags, ExtraFlags);
    FCheckResult *R2 = O->ActorEncroachmentCheck(GMem, Actor, Loc, Rot, 0x9F, 0);
    return R1 ? R1 : R2;
}

FCheckResult *Driver_11a370(FCollisionOctree *O, FMemStack *Mem, AActor *Actor, FBox *Box, UBOOL bBlockOnly, INT Mode)
{
    Escape(&RootNodeBounds);
    if (Mode == 1) return O->ActorOverlapCheck(*Mem, Actor, Box, bBlockOnly);
    if (Mode == 2) return O->ActorOverlapCheck(GMem, Actor, Box, 0);
    if (Mode == 3) return O->ActorOverlapCheck(GMem, Actor, Box, 1);
    if (Mode == 4) return O->ActorOverlapCheck(*Mem, Actor, Box, 0);
    return O->ActorOverlapCheck(*Mem, Actor, Box, 1);
}
