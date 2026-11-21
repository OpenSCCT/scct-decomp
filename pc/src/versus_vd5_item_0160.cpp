// Work item w3_0160: Versus RVA 0xc9aa0-0xc9dac.
//   0xc9aa0 AProjector::Detach(UBOOL)       (vtable slot 79 of AProjector)
//   0xc9b60 AProjector::Abandon()           (vtable slot 80 of AProjector)
//   0xc9bb0 TArray<FProjectorRenderInfo*>::AddUniqueItem (LTCG: this in esi, item in ebx)
//   0xc9c30 FPlane::FPlane(A,B,C)            (LTCG: A esi, B edi, C ebx, this on stack)
//   0xc9d30 FPlane::FPlane(Base,Normal)      (LTCG: this eax, Normal ecx, Base edx)
//   0xc9d60 BoxPushOut(Normal,Size)          (LTCG: ecx, eax)
// The object was compiled with VC7.0 /GL and linked with /LTCG.
typedef unsigned long DWORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag) = 0;
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag) = 0;
    virtual void Free(void* Original) = 0;
};
extern FMalloc* GMalloc;
inline void operator delete(void* Ptr) { GMalloc->Free(Ptr); }
extern const TCHAR FArrayAddTag[];   // TEXT("FArray::Add")
extern const TCHAR FArrayTag[];      // TEXT("FArray")

// FArray from Unreal Engine 2; Add is the published add_array (0x44e0),
// Remove is 0x119c0.
class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);
    void Remove(INT Index, INT Count, INT ElementSize);
};

template<class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T& operator()(INT i) { return ((T*)Data)[i]; }
    INT AddItem(T Item)
    {
        INT Index = Add(1, sizeof(T));
        (*this)(Index) = Item;
        return Index;
    }
    void Remove(INT Index, INT Count = 1) { FArray::Remove(Index, Count, sizeof(T)); }
    INT RemoveItem(const T& Item);  // LTCG instance at 0x10bd60
    INT AddUniqueItem(const T& Item);
    // FArray::Add as an inline in this header version.
    INT GrowBy(INT Count)
    {
        INT Index = ArrayNum;
        if ((ArrayNum += Count) > ArrayMax)
        {
            ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
            if (Data == 0)
                Data = GMalloc->Malloc(ArrayMax * sizeof(T), FArrayAddTag);
            else
                Data = GMalloc->Realloc(Data, ArrayMax * sizeof(T), FArrayTag);
        }
        return Index;
    }
};

class ULevel;
class AProjector;

// Projector render info: projector back pointer at 0, reference count at 4.
class FProjectorRenderInfo
{
public:
    AProjector* Projector;
    INT ReferenceCount;
    DWORD Field08, Field0C;
    double LastRenderTime;                  // 0x10 (name is a guess)
    void AddReference() { ReferenceCount++; }
    void RemoveReference() { if (--ReferenceCount == 0) GMalloc->Free(this); }
    // Retail 0xc9830 (LTCG: this in ebx, Force in eax).
    void Detach(ULevel* Level, UBOOL bNoRemove, UBOOL Force);
};

// An entry of a primitive's projector list: render info pointer first.
struct FProjectorRef
{
    FProjectorRenderInfo* RenderInfo;
    ~FProjectorRef();                       // retail 0x8ffe0
};
struct FProjectorList
{
    TArray<FProjectorRef*> Projectors;
};
class ALevelInfo
{
public:
    char Pad0[0x3b0];
    FLOAT TimeSeconds;                      // 0x3b0
};

class ULevel
{
public:
    char Pad0[0x190];
    double TimeLimit;                       // 0x190 (name is a guess)
    char Pad1[0x4a98 - 0x198];
    TArray<FProjectorRenderInfo*> StaticProjectors;    // 0x4a98
    TArray<FProjectorRenderInfo*> DynamicProjectors;   // 0x4aa4
    TArray<FProjectorRenderInfo*> AbandonedProjectors; // 0x4ab0
    TArray<FProjectorList*> PrimitiveProjectors;       // 0x4abc
    TArray<TArray<FProjectorRenderInfo*>*> ZoneProjectors; // 0x4ac8
};

class AProjector
{
public:
    virtual void Slot0();
    char Pad0[0x1a0 - 4];
    ALevelInfo* Level;                      // 0x1a0
    ULevel* XLevel;                         // 0x1a4
    char Pad1[0x464 - 0x1a8];
    FProjectorRenderInfo* RenderInfo;       // 0x464
    char Pad2[0x478 - 0x468];
    DWORD Bit0 : 1, Bit1 : 1, Bit2 : 1, Bit3 : 1, Bit4 : 1;
    DWORD bProjectStatic : 1;               // bit 5 (name is a guess)
    DWORD Bit6 : 1, Bit7 : 1, Bit8 : 1, Bit9 : 1, Bit10 : 1, Bit11 : 1, Bit12 : 1;
    DWORD bStaticProjector : 1;             // bit 13 (name is a guess)
    void Detach(UBOOL Force);
    void Abandon();
};

void AProjector::Detach(UBOOL Force)
{
    if (RenderInfo)
    {
        RenderInfo->Detach(XLevel, bStaticProjector, Force);
        if (!bStaticProjector && !bProjectStatic)
        {
            for (INT i = 0; i < XLevel->DynamicProjectors.Num(); i++)
            {
                if (XLevel->DynamicProjectors(i) == RenderInfo)
                {
                    INT Last = XLevel->DynamicProjectors.Num() - 1;
                    XLevel->DynamicProjectors(i) = XLevel->DynamicProjectors(Last);
                    XLevel->DynamicProjectors.Remove(Last);
                    break;
                }
            }
        }
        RenderInfo = 0;
    }
}

void AProjector::Abandon()
{
    FProjectorRenderInfo* Info = RenderInfo;
    if (Info)
    {
        Info->AddReference();
        XLevel->AbandonedProjectors.AddItem(Info);
        RenderInfo->Projector = 0;
        RenderInfo = 0;
    }
}

// Retail 0xc9830, written here so the link gives it the retail register
// convention (this in ebx, Force in eax); it is not part of this item.
void FProjectorRenderInfo::Detach(ULevel* InLevel, UBOOL bNoRemove, UBOOL Force)
{
    if (Force)
    {
        Field08 = 0;
        Field0C = 0;
    }
    else
        LastRenderTime = InLevel->TimeLimit == 0.0 ? 0.f : Projector->Level->TimeSeconds;
    if (!bNoRemove)
    {
        for (INT i = 0; i < InLevel->PrimitiveProjectors.Num(); i++)
        {
            FProjectorList* List = InLevel->PrimitiveProjectors(i);
            UBOOL bAll = 1;
            INT j;
            for (j = 0; j < List->Projectors.Num(); j++)
            {
                if (List->Projectors(j)->RenderInfo == this)
                    break;
                bAll = 0;
            }
            if (j < List->Projectors.Num())
            {
                delete List->Projectors(j);
                List->Projectors.Remove(j);
                RemoveReference();
                UBOOL bMore = 0;
                while (j < List->Projectors.Num())
                {
                    FProjectorRef* Ref = List->Projectors(j);
                    if (Ref->RenderInfo != this) { bMore = 1; break; }
                    delete Ref;
                    List->Projectors.Remove(j);
                    RemoveReference();
                }
                if (bMore)
                    continue;
            }
            if (bAll)
            {
                InLevel->PrimitiveProjectors(i) = InLevel->PrimitiveProjectors(InLevel->PrimitiveProjectors.Num() - 1);
                InLevel->PrimitiveProjectors.Remove(InLevel->PrimitiveProjectors.Num() - 1);
                i--;
            }
        }
        for (INT k = 0; k < InLevel->ZoneProjectors.Num(); k++)
        {
            TArray<FProjectorRenderInfo*>* Zone = InLevel->ZoneProjectors(k);
            for (INT j = 0; j < Zone->Num(); j++)
            {
                if ((*Zone)(j) == this)
                {
                    Zone->Remove(j);
                    RemoveReference();
                    break;
                }
            }
            if (Zone->Num() == 0)
            {
                InLevel->ZoneProjectors(k) = InLevel->ZoneProjectors(InLevel->ZoneProjectors.Num() - 1);
                InLevel->ZoneProjectors.Remove(InLevel->ZoneProjectors.Num() - 1);
                k--;
            }
        }
    }
    else
    {
        RemoveReference();
        FProjectorRenderInfo* Self = this;
        Projector->XLevel->StaticProjectors.RemoveItem(Self);
    }
    Projector = 0;
    RemoveReference();
}

template<class T> __declspec(noinline) INT TArray<T>::AddUniqueItem(const T& Item)
{
    INT Index;
    for (Index = 0; Index < Num(); Index++)
        if ((*this)(Index) == Item)
            return Index;
    Index = GrowBy(1);
    (*this)(Index) = Item;
    return Index;
}

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator^(const FVector &V) const { return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector SafeNormal() const; // 0x50d30
};

// 0x10ccacc0: the zero vector SafeNormal returns (read through a pointer).
__declspec(dllimport) extern const FVector GZeroVector;

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(const FVector &InBase, const FVector &InNormal);
    FPlane(const FVector &A, const FVector &B, const FVector &C);
};

FPlane::FPlane(const FVector &A, const FVector &B, const FVector &C)
    : FVector(((B - A) ^ (C - A)).SafeNormal()),
      W(A | ((B - A) ^ (C - A)).SafeNormal())
{
}

__declspec(noinline) FPlane::FPlane(const FVector &InBase, const FVector &InNormal)
    : FVector(InNormal), W(InBase | InNormal)
{
}

__declspec(noinline) FLOAT BoxPushOut(const FVector &Normal, const FVector &Size)
{
    FLOAT PX = Normal.X * Size.X;
    FLOAT PY = Normal.Y * Size.Y;
    FLOAT PZ = Normal.Z * Size.Z;
    *(DWORD *)&PX &= 0x7fffffff;    // Abs() by clearing the sign bit
    *(DWORD *)&PY &= 0x7fffffff;
    *(DWORD *)&PZ &= 0x7fffffff;
    return PX + PY + PZ;
}

// FVector::SafeNormal (retail 0x50d30), reproduced here only so the link
// gives it the retail register convention (result in ecx, this in edx).
__declspec(noinline) FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return GZeroVector;
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }
typedef void (AProjector::*DetachFn)(UBOOL);
typedef void (AProjector::*AbandonFn)();
void Escape(DetachFn);
void Escape(AbandonFn);
void Driver_c9aa0(AProjector *P, UBOOL Force) { Escape(&AProjector::Detach); P->Detach(Force); }
void Driver_c9b60(AProjector *P) { Escape(&AProjector::Abandon); P->Abandon(); }
INT Driver_c9bb0(TArray<FProjectorRenderInfo*> *A, FProjectorRenderInfo **I) { Escape(&GMalloc); return A->AddUniqueItem(*I); }
void Driver_c9c30(FPlane *Out, const FVector *A, const FVector *B, const FVector *C) { new(Out) FPlane(*A, *B, *C); }
void Driver_c9d30(FPlane *Out, const FVector *A, const FVector *B) { new(Out) FPlane(*A, *B); }
FLOAT Driver_c9d60(const FVector *A, const FVector *B) { return BoxPushOut(*A, *B); }
