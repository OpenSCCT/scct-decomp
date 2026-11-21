/* Versus RVA 0xb6ac0: USkeletalMeshInstance vtable slot 38.
   Matches the shape of UE2 USkeletalMeshInstance::SetBlendParams: stores the
   blend parameters into a 144-byte animation channel and marks it blended.
   The unit was built with VC7.0 /GL and linked /LTCG: ValidateAnimChannel
   (0x109b5910) takes this in EBX and the stage in EDI, which is why this
   function keeps this in EBX. Field names follow UE2 MeshAnimChannel where
   the layout fits; the slot-30 virtual and 0x109c0d50 are unnamed. */
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

class FName {
public:
    INT Index;
};

typedef unsigned short TCHAR;
typedef unsigned char BYTE;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
};
extern FMalloc *GMalloc;
extern const TCHAR ShrinkingTag[];   /* text not recovered */

class FArray {
public:
    INT Add(INT Count, INT ElementSize);         /* 0x109044e0 */
    INT AddZeroed(INT ElementSize, INT Count);   /* 0x10915400 */
    void Shrink(INT ElementSize)
    {
        if (ArrayMax != ArrayNum) {
            ArrayMax = ArrayNum;
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, ShrinkingTag);
        }
    }
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T> class TArray : public FArray {
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
    INT AddZeroed(INT n = 1) { return FArray::AddZeroed(sizeof(T), n); }
    void Shrink();                               /* 0x109c0d50 for MeshAnimChannel */
};

struct MeshAnimChannel {             /* 0x90 bytes */
    unsigned char Pad0[0x78];
    FLOAT BlendAlpha;                /* 0x78 */
    FLOAT BlendInTime;               /* 0x7c */
    FLOAT BlendOutTime;              /* 0x80 */
    FName StartBone;                 /* 0x84 */
    UBOOL bGlobalPose;               /* 0x88 */
    UBOOL bBlendSet;                 /* 0x8c */
};

#define MAX_CHANNELS 256

class USkeletalMeshInstance {
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29();
    virtual UBOOL HasSkeleton();     /* slot 30, +0x78, name assumed */
    UBOOL ValidateAnimChannel(INT Stage);
    void SetBlendParams(INT Stage, FLOAT BlendAlpha, FLOAT InTime, FLOAT OutTime, FName BoneName, UBOOL bGlobalPose);

    unsigned char Pad[0xfc];
    TArray<MeshAnimChannel> Blends;  /* 0x100 */
};

/* 0x109c0d50, defined here so the link sees its register use (array in ESI); not part of the match. */
template <class T> __declspec(noinline) void TArray<T>::Shrink() { FArray::Shrink(sizeof(T)); }

/* 0x109b5910, defined here so the link sees its register use; not part of the match. */
UBOOL USkeletalMeshInstance::ValidateAnimChannel(INT Stage)
{
    if (Stage > MAX_CHANNELS || Stage < 0)
        return 0;
    if (Blends.Num() <= Stage) {
        while (Blends.Num() <= Stage)
            Blends.AddZeroed();
        Blends.Shrink();
    }
    return 1;
}

void USkeletalMeshInstance::SetBlendParams(INT Stage, FLOAT BlendAlpha, FLOAT InTime, FLOAT OutTime, FName BoneName, UBOOL bGlobalPose)
{
    if (Stage >= 0 && ValidateAnimChannel(Stage) && HasSkeleton()) {
        MeshAnimChannel &Channel = Blends(Stage);
        Channel.BlendAlpha = BlendAlpha;
        Channel.BlendInTime = InTime;
        Channel.BlendOutTime = OutTime;
        Channel.StartBone = BoneName;
        Channel.bGlobalPose = bGlobalPose;
        Channel.bBlendSet = 1;
    }
}


// Scaffolding for the link, not part of the unit: retail reaches this
// function only through the vtable, so the driver takes its address.
typedef void (USkeletalMeshInstance::*SetBlendParamsFn)(INT, FLOAT, FLOAT, FLOAT, FName, UBOOL);
void Escape(void *);
void Driver_b6ac0()
{
    SetBlendParamsFn Fn = &USkeletalMeshInstance::SetBlendParams;
    Escape(&Fn);
}
