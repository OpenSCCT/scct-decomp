/* Versus RVA 0xc0120-0xc03ba: USkeletalMeshInstance animation channel helpers.
   Channels (0x100) is the array of MeshAnimChannel (0x90-byte elements) also
   seen in items 0115-0124. Names of channel fields and of the non-virtual
   helpers are assumed from UE2 (CopyAnimation, SetAnimRate, SetBlendAlpha,
   UpdateBlendAlpha, SetAnimSequence); 0xc0250 is vtable slot 62. */
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

class FName {
public:
    INT Index;
};

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);          /* retail 0x109044e0 */
    INT AddZeroed(INT ElementSize, INT Count = 1); /* retail 0x10915400 */
    INT Num() const { return ArrayNum; }
};

typedef void *HMeshAnim;

struct MeshAnimChannel {                          /* 0x90 bytes */
    DWORD Pad00;
    INT MeshAnimIndex;                            /* 0x04 */
    FName AnimSequence;                           /* 0x08 */
    FLOAT AnimRate;                               /* 0x0c */
    FLOAT AnimFrame;                              /* 0x10 */
    DWORD AnimLast;                               /* 0x14 */
    DWORD Flags18;                                /* 0x18 */
    DWORD Flags1c;                                /* 0x1c */
    FLOAT OrigRate;                               /* 0x20 */
    DWORD Pad24[2];
    DWORD Field2c;                                /* 0x2c */
    DWORD Field30;                                /* 0x30 */
    UBOOL bNotifies;                              /* 0x34 */
    DWORD Field38;                                /* 0x38 */
    DWORD Pad3c[5];
    FLOAT CurrentAlpha;                             /* 0x50 */
    DWORD Pad54[2];
    DWORD Field5c;                                /* 0x5c */
    DWORD Field60;                                /* 0x60 */
    DWORD Pad64[11];
};

template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}
inline FLOAT Abs(FLOAT A) { return A >= 0.f ? A : -A; }

extern void InitChannels_c0d50();                 /* retail 0x109c0d50 */

class USkeletalMeshInstance {
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29(); virtual void V30(); virtual void V31();
    virtual void V32(); virtual void V33(); virtual void V34(); virtual void V35();
    virtual void V36(); virtual void V37(); virtual void V38(); virtual void V39();
    virtual void V40();
    virtual HMeshAnim GetAnimNamed(FName Name);                   /* 41, +0xa4 */
    virtual void V42(); virtual void V43(); virtual void V44();
    virtual FLOAT AnimGetFrameCount(HMeshAnim Anim);              /* 45, +0xb4 */
    virtual FLOAT AnimGetRate(HMeshAnim Anim);                    /* 46, +0xb8 */
    virtual INT AnimGetNotifyCount(HMeshAnim Anim);               /* 47, +0xbc */
    virtual void V48(); virtual void V49();
    virtual void V50(); virtual void V51(); virtual void V52(); virtual void V53();
    virtual void V54(); virtual void V55(); virtual void V56(); virtual void V57();
    virtual void V58(); virtual void V59(); virtual void V60(); virtual void V61();
    virtual void SetAnimFrame(INT Channel, FLOAT Frame, INT UnitFlag); /* 62, +0xf8 */

    __declspec(noinline) UBOOL ValidateAnimChannel(INT Channel); /* retail 0x109b5910 */
    __declspec(noinline) void CopyAnimation(INT SrcChannel, INT DestChannel);
    __declspec(noinline) void SetAnimRate(INT Channel, FLOAT Rate);
    __declspec(noinline) void SetBlendAlpha(INT Channel, FLOAT Alpha);
    __declspec(noinline) void UpdateBlendAlpha(INT Channel, FLOAT Target, FLOAT Rate);
    void SetAnimSequence(INT Channel, FName Sequence);

    MeshAnimChannel &Chan(INT i) { return ((MeshAnimChannel *)Channels.Data)[i]; }

    unsigned char Pad04[0xfc];
    FArray Channels;                                /* 0x100 */
};

/* retail 0x109b5910, defined so the linker sees its body (as in item 0124) */
UBOOL USkeletalMeshInstance::ValidateAnimChannel(INT Channel)
{
    if (Channel > 256 || Channel < 0)
        return 0;
    if (Channels.Num() <= Channel) {
        do {
            Channels.AddZeroed(sizeof(MeshAnimChannel));
        } while (Channels.Num() <= Channel);
        InitChannels_c0d50();
    }
    return 1;
}

/* 0xc0120 */
void USkeletalMeshInstance::CopyAnimation(INT SrcChannel, INT DestChannel)
{
    if (SrcChannel < 0 || SrcChannel >= Channels.Num() || DestChannel < 0)
        return;
    if (!ValidateAnimChannel(DestChannel))
        return;
    MeshAnimChannel &Src = Chan(SrcChannel);
    MeshAnimChannel &Dst = Chan(DestChannel);
    Dst.AnimSequence = Src.AnimSequence;
    Dst.MeshAnimIndex = Src.MeshAnimIndex;
    Dst.AnimRate = Src.AnimRate;
    Dst.OrigRate = Src.OrigRate;
    Dst.AnimFrame = Src.AnimFrame;
    Dst.CurrentAlpha = Src.CurrentAlpha;
    Dst.AnimLast = Src.AnimLast;
    Dst.bNotifies = Src.bNotifies;
    Dst.Field2c = Src.Field2c;
    Dst.Field30 = Src.Field30;
    Dst.Flags18 = Src.Flags18;
    Dst.Flags1c = Src.Flags1c;
    Dst.Field38 = Src.Field38;
    Dst.Field60 = Src.Field60;
    Dst.Field5c = Src.Field5c;
}

/* 0xc01c0 */
void USkeletalMeshInstance::SetAnimRate(INT Channel, FLOAT Rate)
{
    if (Channel >= 0 && Channel < Channels.Num())
    {
        MeshAnimChannel &C = Chan(Channel);
        C.AnimRate = Rate * C.OrigRate;
    }
}

/* 0xc01f0 */
void USkeletalMeshInstance::SetBlendAlpha(INT Channel, FLOAT Alpha)
{
    if (Channel >= 0 && Channel < Channels.Num()) {
        MeshAnimChannel &C = Chan(Channel);
        C.CurrentAlpha = Clamp(Alpha, 0.f, 1.f);
    }
}

/* 0xc0250, vtable slot 62 */
void USkeletalMeshInstance::SetAnimFrame(INT Channel, FLOAT Frame, INT UnitFlag)
{
    if (Channel >= 0 && Channel < Channels.Num()) {
        MeshAnimChannel &C = Chan(Channel);
        if (UnitFlag == 0) {
            C.AnimFrame = Frame;
            return;
        }
        FLOAT Count = AnimGetFrameCount(GetAnimNamed(C.AnimSequence));
        C.AnimFrame = Count >= 1.f ? Frame / (Count - 1.f) : Frame;
    }
}

/* 0xc02d0 */
#include "versus_skeletal_channel_alpha.inl"

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_c0120(USkeletalMeshInstance *M, INT A, INT B) { M->CopyAnimation(5, 10); M->CopyAnimation(8, 13); M->CopyAnimation(6, 11); }
void Driver_c01c0(USkeletalMeshInstance *M, INT A, FLOAT B) { M->SetAnimRate(A, B); }
void Driver_c01f0(USkeletalMeshInstance *M, INT A, FLOAT B) { M->SetBlendAlpha(A, B); }
void Driver_c0250() { USkeletalMeshInstance Obj; Escape(&Obj); }
void Driver_c02d0(USkeletalMeshInstance *M, INT A, FLOAT B, FLOAT C) { M->UpdateBlendAlpha(A, B, C); }
void Driver_c0340(USkeletalMeshInstance *M, INT A, FName B) { M->SetAnimSequence(A, B); }
