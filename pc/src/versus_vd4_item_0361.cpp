// Work item 0361: Versus RVA 0x9e5b0-0x9e864.
//   0x9e5b0 AActor::LocalToWorld (LTCG: this in EDI, result pointer in ESI)
//   0x9e800 TArray<FUnnamed_9e800>::~TArray, element size 0x48 (LTCG: this on
//           the stack, ret 4)
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
#define FORCEINLINE __forceinline

struct FVector { FLOAT X, Y, Z; };
struct FRotator { INT Pitch, Yaw, Roll; };

struct FGlobalMath
{
    void SinCos(INT Angle, FLOAT *S, FLOAT *C) const;   // RVA 0x40950
};
extern FGlobalMath GMath;

struct FMatrix
{
    FLOAT M[4][4];

    FMatrix() {}
    // Translate by -PrePivot, scale, rotate, translate by Location, built in
    // place (the retail code writes straight into the returned matrix).
    FORCEINLINE FMatrix(const FVector &Location, const FRotator &Rotation, const FVector &DrawScale3D,
            const FLOAT &DrawScale, const FVector &PrePivot)
    {
        FLOAT SY, CY, SP, CP, SR, CR;
        GMath.SinCos(Rotation.Yaw, &SY, &CY);
        GMath.SinCos(Rotation.Pitch, &SP, &CP);
        GMath.SinCos(Rotation.Roll, &SR, &CR);

        FLOAT LX = Location.X, LY = Location.Y, LZ = Location.Z;
        FLOAT PX = PrePivot.X, PY = PrePivot.Y, PZ = PrePivot.Z;
        FLOAT DX = DrawScale3D.X * DrawScale,
              DY = DrawScale3D.Y * DrawScale,
              DZ = DrawScale3D.Z * DrawScale;

        M[0][3] = 0.f;
        FLOAT CPSY = CP * SY, CPCY = CP * CY;
        M[0][0] = CPCY * DX;
        M[0][1] = CPSY * DX;
        M[0][2] = SP * DX;

        FLOAT CRSY = CR * SY, CRCY = CR * CY, SRCP = SR * CP;
        FLOAT SRCY = SR * CY, SRCYSP = SRCY * SP;
        FLOAT YY = SR * SP * SY + CRCY;
        M[1][0] = (SRCYSP - CRSY) * DY;
        M[1][1] = YY * DY;
        M[1][2] = -(SRCP * DY);
        M[1][3] = 0.f;

        FLOAT SRSY = SR * SY, CRCYSP = CRCY * SP, CRSYSP = CRSY * SP, CRCP = CR * CP;
        FLOAT ZX = CRCYSP + SRSY;
        FLOAT ZY = SRCY - CRSYSP;
        M[2][0] = -(ZX * DZ);
        M[2][1] = ZY * DZ;
        M[2][2] = CRCP * DZ;
        M[2][3] = 0.f;
        M[3][3] = 1.f;

        FLOAT TX = DX * PX, TY = DY * PY, TZ = DZ * PZ;
        M[3][0] = (LX - TX * CPCY) + (CRSY - SRCYSP) * TY + ZX * TZ;
        M[3][1] = LY - (ZY * TZ + YY * TY + TX * CPSY);
        M[3][2] = LZ - ((TX * SP - TY * SRCP) + TZ * CRCP);
    }
};

// Only the fields used here; offsets from the retail code.
class AActor
{
public:
    unsigned char Pad0[0x80];
    FVector Location;           // 0x80
    unsigned char Pad8c[0xb0 - 0x8c];
    FVector DrawScale3D;        // 0xb0
    FVector PrePivot;           // 0xbc
    unsigned char Padc8[0xe0 - 0xc8];
    FRotator Rotation;          // 0xe0
    unsigned char Padec[0x23c - 0xec];
    FLOAT DrawScale;            // 0x23c

    FMatrix LocalToWorld();
};

FMatrix AActor::LocalToWorld()
{
    return FMatrix(Location, Rotation, DrawScale3D, DrawScale, PrePivot);
}

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize); // RVA 0x119c0
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray() { Remove(0, ArrayNum); }
    void Remove(INT Index, INT Count = 1) { FArray::Remove(Index, Count, sizeof(T)); }
};

// Neutral name: a 0x48-byte element with a trivial destructor.
struct FUnnamed_9e800 { unsigned char Bytes[0x48]; };

template class TArray<FUnnamed_9e800>;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void MayThrow(void *);
void UseMatrix(const FMatrix &M);
void Driver_9e5b0(AActor *A)
{
    UseMatrix(A->LocalToWorld());
    UseMatrix(A->LocalToWorld());
}
void Driver_9e800()
{
    TArray<FUnnamed_9e800> A;
    MayThrow(&A);
}
