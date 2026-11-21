// Work item w3 0155: AProjector natives and FProjectorRenderInfo (Versus RVA 0xc63c0-0xc6787).
// 0xc63c0 FProjectorRenderInfo::FProjectorRenderInfo (LTCG: this on the stack, ret 0xc)
// 0xc65b0 AProjector virtual slot 44: lazily constructed singleton (neutral name)
// 0xc6600 AProjector virtual slot 82: fills one 0x4c-byte projector slot (neutral name)
// 0xc6670 AProjector::execForceAttachProjectorOnActor
// 0xc66b0 AProjector::AttachActor (LTCG: actor in EAX, this in ESI)
// 0xc6740 AProjector::execDetachProjector
// Field names are guesses from UE2's AProjector where the offsets agree.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;
typedef double DOUBLE;

#define NULL 0

enum EName { NAME_None = 0 };
enum ENetMode { NM_Standalone = 0, NM_DedicatedServer = 1 };

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    friend FVector operator*(FLOAT Scale, const FVector &V) { return FVector(V.X * Scale, V.Y * Scale, V.Z * Scale); }
};

class FPlane : public FVector
{
public:
    FLOAT W;
};

class FBox
{
public:
    FVector Min;
    FVector Max;
    UBOOL IsValid;
    FVector GetCenter() const { return FVector((Min + Max) * 0.5f); }
    FVector GetExtent() const { return 0.5f * (Max - Min); }
};

class FMatrix
{
public:
    FLOAT M[4][4];
    static FMatrix Identity;

    FLOAT Determinant() const;
    FMatrix Inverse() const;
};

class FOutputDevice;
class UClass;
class UObject;

class UField
{
public:
    void *VfTable;
    BYTE Pad04[0x28 - 0x04];
    UField *SuperField;
};

class UObject
{
public:
    virtual void Slot00();
    BYTE Pad04[0x24 - 0x04];
    UClass *Class;
    UClass *GetClass() const { return Class; }
    inline UBOOL IsA(UClass *SomeBase) const;
};

class UClass : public UField
{
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = GetClass(); TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == NULL;
}

// UBitmapMaterial-like class tested by the slot-82 cast; neutral name.
class UProjectedTexture : public UObject
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

template <class T> inline T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : NULL;
}

class UMaterial : public UObject
{
};

struct FFrame;
typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

struct FFrame
{
    void *VfTable;
    void *Node;
    UObject *Object;
    BYTE *Code;
    void Step(UObject *Context, void *const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_OBJECT(cls, var) cls *var = NULL; Stack.Step(Stack.Object, &var);
#define P_GET_UBOOL(var) DWORD var = 0; Stack.Step(Stack.Object, &var);
#define P_FINISH Stack.Code++;

class ALevelInfo
{
public:
    BYTE Pad000[0x4a8];
    BYTE NetMode;
};

class AProjector;
class FProjectorRenderInfo;

class AActor : public UObject
{
public:
    BYTE Pad028[0x1a0 - 0x28];
    ALevelInfo *Level;
    void AttachProjector(AProjector *Projector);
};

class AProjector : public AActor
{
public:
    BYTE Pad1a4[0x2f8 - 0x1a4];
    FPlane FrustumPlanes[6];          // 0x2f8
    BYTE Pad358[0x3b8 - 0x358];
    FMatrix WorldToTexture;           // 0x3b8
    FMatrix Matrix;                   // 0x3f8
    BYTE Pad438[0x444 - 0x438];
    FBox Box;                         // 0x444
    BYTE Pad460[0x464 - 0x460];
    FProjectorRenderInfo *RenderInfo; // 0x464
    UMaterial *GradientTexture;       // 0x468
    UMaterial *ProjTexture;           // 0x46c
    BYTE Pad470[0x474 - 0x470];
    BYTE FrameBufferBlendingOp;       // 0x474
    BYTE MaterialBlendingOp;          // 0x475
    BYTE Pad476[0x478 - 0x476];
    DWORD ProjectorFlags;             // 0x478 (UBOOL bitfield word)

    // vtable slots: 0x13c Detach, 0x144 CalcMatrix (names from UE2).
    virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26(); virtual void Slot27();
    virtual void Slot28(); virtual void Slot29(); virtual void Slot30(); virtual void Slot31();
    virtual void Slot32(); virtual void Slot33(); virtual void Slot34(); virtual void Slot35();
    virtual void Slot36(); virtual void Slot37(); virtual void Slot38(); virtual void Slot39();
    virtual void Slot40(); virtual void Slot41(); virtual void Slot42(); virtual void Slot43();
    virtual UObject *GetSingleton_c65b0();                                       // 44
    virtual void Slot45(); virtual void Slot46(); virtual void Slot47();
    virtual void Slot48(); virtual void Slot49(); virtual void Slot50(); virtual void Slot51();
    virtual void Slot52(); virtual void Slot53(); virtual void Slot54(); virtual void Slot55();
    virtual void Slot56(); virtual void Slot57(); virtual void Slot58(); virtual void Slot59();
    virtual void Slot60(); virtual void Slot61(); virtual void Slot62(); virtual void Slot63();
    virtual void Slot64(); virtual void Slot65(); virtual void Slot66(); virtual void Slot67();
    virtual void Slot68(); virtual void Slot69(); virtual void Slot70(); virtual void Slot71();
    virtual void Slot72(); virtual void Slot73(); virtual void Slot74(); virtual void Slot75();
    virtual void Slot76(); virtual void Slot77(); virtual void Attach();          // 0x138
    virtual void Detach(UBOOL Force);                                            // 0x13c
    virtual void Slot80();
    virtual void CalcMatrix();                                                   // 0x144
    virtual void FillSlot_c6600(struct FProjectorSlotTable *Out, INT Index);                           // 82

    AProjector() {}
    void AttachActor(AActor *A);
    void execForceAttachProjectorOnActor(FFrame &Stack, void *const Result);
    void execDetachProjector(FFrame &Stack, void *const Result);
};

class FProjectorRenderInfo
{
public:
    AProjector *Projector;   // 0x00
    INT ReferenceCount;      // 0x04
    INT Unknown08;           // 0x08
    INT Unknown0C;           // 0x0c
    DOUBLE Expires;          // 0x10
    UMaterial *Material;     // 0x18
    UMaterial *GradientTexture; // 0x1c
    BYTE FrameBufferBlendingOp; // 0x20
    BYTE MaterialBlendingOp;    // 0x21
    FMatrix Matrix;          // 0x24
    FMatrix InvMatrix;       // 0x64
    FVector BoxCenter;       // 0xa4
    FVector BoxExtent;       // 0xb0
    FPlane FrustumPlanes[6]; // 0xbc
    FMatrix WorldToTexture;  // 0x11c
    DWORD RenderFlags;       // 0x15c

    FProjectorRenderInfo(AProjector *InProjector, FLOAT InExpires);
};

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
};
extern FMalloc *GMalloc;
inline void *operator new(unsigned int Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
extern const TCHAR FProjectorRenderInfo_Tag[]; // L"FProjectorRenderInfo"

void appMemcpy(void *Dest, const void *Src, INT Count);

// Global at 0x10c9245c; checked before attaching (neutral name).
class FUnknownGlobal_c9245c
{
public:
    BYTE Pad00[0x28];
    struct Inner28 { BYTE Pad[0x38]; struct Inner38 { BYTE Pad[0x58]; INT Value; } *P; } *P28;
    BYTE Pad2c[0x54 - 0x2c];
    INT Value54;
};
extern FUnknownGlobal_c9245c *GUnknown_c9245c;

FProjectorRenderInfo::FProjectorRenderInfo(AProjector *InProjector, FLOAT InExpires)
    : Projector(InProjector), ReferenceCount(0), Unknown08(0), Unknown0C(0), Expires(InExpires),
      Material(InProjector->ProjTexture),
      FrameBufferBlendingOp(InProjector->FrameBufferBlendingOp),
      MaterialBlendingOp(InProjector->MaterialBlendingOp),
      Matrix(InProjector->Matrix)
{
    InvMatrix = Matrix.Inverse();
    BoxCenter = InProjector->Box.GetCenter();
    BoxExtent = InProjector->Box.GetExtent();
    appMemcpy(FrustumPlanes, InProjector->FrustumPlanes, sizeof(FrustumPlanes));
    GradientTexture = InProjector->GradientTexture;
    WorldToTexture = InProjector->WorldToTexture;
    DWORD F = InProjector->ProjectorFlags;
    RenderFlags = ((((F >> 1 & 0x2000) | (F & 0x800)) >> 1 | (F & 0x100)) >> 1 | (F & 0x400)) >> 6
                | (InProjector->Box.IsValid != 0)
                | ((F & 0x200) && InProjector->GradientTexture ? 4 : 0);
}

// Local static of the slot-44 function.
extern UObject *GetSingleton_c65b0_Result;
extern UClass Singleton_c65b0_Class;
extern UObject *GSingletonOuter_c925b4;
extern FOutputDevice *GError;
extern void (*GSingletonInit_cc03d4)(UObject *Obj);
UObject *StaticConstructObject(UClass *Class, UObject *InOuter, INT Name, DWORD SetFlags,
                               UObject *Template, FOutputDevice *Error, UObject *Extra1, UObject *Extra2);

// UObject::GetTransientPackage() returns GObjTransientPkg.
inline UObject *GetTransientPackage() { return GSingletonOuter_c925b4; }

template <class T> inline T *ConstructObject(UClass *Class, UObject *Outer = (UObject *)-1, INT Name = NAME_None,
                                             DWORD SetFlags = 0, UObject *Template = NULL, FOutputDevice *Error = GError,
                                             UObject *SubobjectRoot = NULL, UObject *Extra = NULL)
{
    if (Outer == (UObject *)-1)
        Outer = GetTransientPackage();
    return (T *)StaticConstructObject(Class, Outer, Name, SetFlags, Template, Error, SubobjectRoot, Extra);
}

// Near miss: same instructions as retail except register allocation of the
// zero arguments (retail keeps 0 in EAX and loads GError/Outer into ECX/EDX) and
// where `push esi` is scheduled.
UObject *AProjector::GetSingleton_c65b0()
{
    if (GetSingleton_c65b0_Result)
        return GetSingleton_c65b0_Result;
    UObject *Obj = ConstructObject<UObject>(&Singleton_c65b0_Class);
    if (Obj)
        GSingletonInit_cc03d4(Obj);
    return GetSingleton_c65b0_Result = Obj;
}

struct FProjectorSlot
{
    UProjectedTexture *Texture;
    FMatrix Matrix;
    UBOOL bBoxValid;
    INT MaterialBlendingOp;
};

// Owner of the slot array passed to slot 82 (neutral name; layout before 0x7c unknown).
struct FProjectorSlotTable
{
    BYTE Pad00[0x7c];
    FProjectorSlot Slots[1];
};

void AProjector::FillSlot_c6600(FProjectorSlotTable *Out, INT Index)
{
    Out->Slots[Index].Texture = Cast<UProjectedTexture>(ProjTexture);
    Out->Slots[Index].Matrix = Matrix;
    Out->Slots[Index].bBoxValid = Box.IsValid != 0;
    Out->Slots[Index].MaterialBlendingOp = MaterialBlendingOp;
}

void AProjector::execForceAttachProjectorOnActor(FFrame &Stack, void *const Result)
{
    P_GET_OBJECT(AActor, A);
    P_FINISH;
    AttachActor(A);
}

// Near miss (LTCG): retail passes A in EAX and copies it to a saved EDI for
// AActor::AttachProjector (this in EDI); this link passes A straight in EDI, so
// only the prologue differs (and one register in execForceAttachProjectorOnActor).
void AProjector::AttachActor(AActor *A)
{
    if (A
        && (!GUnknown_c9245c || (GUnknown_c9245c->Value54 && GUnknown_c9245c->P28->P->Value))
        && ProjTexture
        && Level->NetMode != NM_DedicatedServer) {
        CalcMatrix();
        RenderInfo = new(FProjectorRenderInfo_Tag) FProjectorRenderInfo(this, 0);
        if (RenderInfo) {
            RenderInfo->ReferenceCount++;
            A->AttachProjector(this);
        }
    }
}

void AProjector::execDetachProjector(FFrame &Stack, void *const Result)
{
    P_GET_UBOOL(Force);
    P_FINISH;
    Detach(Force);
}

// ---- Stand-ins defined so the LTCG link gives retail's register conventions. ----
FMatrix FMatrix::Inverse() const
{
    FMatrix Result;
    FLOAT Det = Determinant();
    if (Det == 0.0f)
        return FMatrix::Identity;
    FLOAT RDet = 1.0f / Det;
    for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
            Result.M[i][j] = RDet * M[j][i];
    return Result;
}

extern INT GAttachCount;
void AActor::AttachProjector(AProjector *Projector)
{
    if (Projector->RenderInfo && Level)
        GAttachCount++;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_c66b0(AProjector *P, FFrame &Stack, void *R)
{
    Escape(GNatives);
    Escape(&GMalloc);
    Escape(&GUnknown_c9245c);
    Native N = (Native)&AProjector::execForceAttachProjectorOnActor;
    Escape(&N);
    (P->*N)(Stack, R);
    Native D = (Native)&AProjector::execDetachProjector;
    Escape(&D);
    (P->*D)(Stack, R);
}
UObject *Driver_c65b0(AProjector *P)
{
    Escape(&GetSingleton_c65b0_Result);
    Escape(&GSingletonOuter_c925b4);
    Escape(&GError);
    AProjector *Q = new(FProjectorRenderInfo_Tag) AProjector;
    Escape(Q);
    return P->GetSingleton_c65b0();
}
// Scaffolding: the other retail caller (0x1b8241) of AttachActor, which keeps
// several values live in callee-saved registers across the call.
struct FProjectorOwner_Driver { BYTE Pad[0x3a4]; AProjector *Projector; INT Count; AActor **Actors; };
INT Driver_1b8241(FProjectorOwner_Driver *O, INT Mode)
{
    INT Total = 0;
    for (INT i = 0; i < O->Count; i++) {
        AActor *A = O->Actors[i];
        if (Mode) {
            O->Projector->ProjectorFlags &= ~0x400;
            O->Projector->AttachActor(A);
        }
        Total += O->Count + i + Mode;
    }
    return Total;
}
