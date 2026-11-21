// Work item 0000: Versus RVA 0x122ee0 (APlayerController::execClientHearSound).
// Compiled with VC7.0 /GL and linked with /LTCG: AActor::IsOwnedBy (0x92790,
// published in versus_vd4_item_0336.cpp) uses LTCG's custom register convention
// (this in EAX, TestOwner in ECX) and is proved read-only across the call.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;
#define NULL 0

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
};

class __single_inheritance UObject;
class AActor;
class APlayerController;
class USound;
class UViewport;
class ULevel;
class UEngine;
class UAudioSubsystem;

struct FFrame
{
    void *VfTable;
    void *Node;
    UObject *Object;
    BYTE *Code;
    inline void Step(UObject *Context, void *const Result);
};

typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];   // 0x10c819d8

inline void FFrame::Step(UObject *Context, void *const Result)
{
    INT B = *Code++;
    (Context->*GNatives[B])(*this, Result);
}

#define P_GET_OBJECT(cls, var) cls *var = NULL; Stack.Step(Stack.Object, &var);
#define P_GET_ACTOR(var)       P_GET_OBJECT(AActor, var)
#define P_GET_INT(var)         INT var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_INT_OPTX(var, def) INT var = def; Stack.Step(Stack.Object, &var);
#define P_GET_UBOOL(var)       DWORD var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_VECTOR(var)      FVector var; Stack.Step(Stack.Object, &var);
#define P_FINISH               Stack.Code++;

enum ESoundFlags
{
    SF_No3D = 0x10
};

#define VSLOT(n) virtual void VSlot##n();

class UAudioSubsystem
{
public:
    VSLOT(00) VSLOT(01) VSLOT(02) VSLOT(03) VSLOT(04) VSLOT(05) VSLOT(06) VSLOT(07)
    VSLOT(08) VSLOT(09) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15)
    VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
    VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27)
    virtual UBOOL PlaySound(AActor *Actor, INT Id, USound *Sound, const FVector &Location,
                            FLOAT Volume, FLOAT Radius, FLOAT Pitch, INT Flags,
                            INT Unk1, INT Unk2, INT Bone);                   // +0x70
    VSLOT(29) VSLOT(30) VSLOT(31) VSLOT(32) VSLOT(33) VSLOT(34) VSLOT(35) VSLOT(36)
    VSLOT(37) VSLOT(38) VSLOT(39) VSLOT(40) VSLOT(41) VSLOT(42) VSLOT(43) VSLOT(44)
    VSLOT(45) VSLOT(46) VSLOT(47) VSLOT(48)
    virtual UViewport *GetViewport();                                        // +0xc4
};

class UViewport
{
public:
    BYTE Pad00[0x30];
    APlayerController *Actor;                                                // +0x30
};

class UEngine
{
public:
    BYTE Pad00[0x34];
    UAudioSubsystem *Audio;                                                  // +0x34
};

class ULevel
{
public:
    BYTE Pad00[0xf0];
    UEngine *Engine;                                                         // +0xf0
};

class UObject
{
public:
    VSLOT(00) VSLOT(01) VSLOT(02) VSLOT(03) VSLOT(04) VSLOT(05) VSLOT(06) VSLOT(07)
    VSLOT(08) VSLOT(09) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15)
    VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
    VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31)
    VSLOT(32) VSLOT(33) VSLOT(34) VSLOT(35) VSLOT(36) VSLOT(37) VSLOT(38) VSLOT(39)
    VSLOT(40) VSLOT(41) VSLOT(42) VSLOT(43) VSLOT(44) VSLOT(45) VSLOT(46) VSLOT(47)
    VSLOT(48) VSLOT(49) VSLOT(50) VSLOT(51) VSLOT(52) VSLOT(53) VSLOT(54) VSLOT(55)
    VSLOT(56) VSLOT(57) VSLOT(58) VSLOT(59) VSLOT(60) VSLOT(61) VSLOT(62) VSLOT(63)
    VSLOT(64) VSLOT(65) VSLOT(66) VSLOT(67) VSLOT(68) VSLOT(69) VSLOT(70) VSLOT(71)
    VSLOT(72) VSLOT(73) VSLOT(74) VSLOT(75) VSLOT(76) VSLOT(77) VSLOT(78)

    BYTE Pad04[0x28 - 0x04];
};

class AActor : public UObject
{
public:
    BYTE Pad28[0x104 - 0x28];
    AActor *Owner;                                                           // +0x104
    BYTE Pad108[0x1a4 - 0x108];
    ULevel *XLevel;                                                          // +0x1a4
    BYTE Pad1a8[0x2e8 - 0x1a8];
    DWORD Bits2e8_0 : 15;                                                    // +0x2e8
    DWORD bDeleteMe : 1;                                                     // +0x2e8 bit 15
    DWORD Bits2e8_16 : 16;

    UBOOL IsOwnedBy(const AActor *TestOwner) const;
};

class APlayerController : public AActor
{
public:
    virtual AActor *GetViewTarget();                                         // +0x13c
    virtual UBOOL IsLocalPlayerController();                                 // +0x140
    void execClientHearSound(FFrame &Stack, void *const Result);
};

// Global default sound radius (0x10c71b00).
extern FLOAT GAudioDefaultRadius;

// RVA 0x122ee0
void APlayerController::execClientHearSound(FFrame &Stack, void *const Result)
{
    P_GET_ACTOR(Actor);
    P_GET_INT(Id);
    P_GET_OBJECT(USound, S);
    P_GET_VECTOR(SoundLocation);
    P_GET_VECTOR(Parameters);
    P_GET_UBOOL(Attenuate);
    P_GET_INT_OPTX(Bone, -1);
    P_FINISH;

    FLOAT Volume = Parameters.X * 0.001f;
    FLOAT Radius = Parameters.Y;
    FLOAT Pitch  = Parameters.Z * 0.001f;

    if (IsLocalPlayerController() && XLevel->Engine->Audio && S)
    {
        if (Actor && Actor->bDeleteMe)
            Actor = NULL;

        INT Flags = 0;
        if (!Attenuate && Actor && XLevel->Engine->Audio)
        {
            UViewport *Viewport = XLevel->Engine->Audio->GetViewport();
            if (Viewport && Actor->IsOwnedBy(Viewport->Actor->GetViewTarget()))
                Flags |= SF_No3D;
        }

        XLevel->Engine->Audio->PlaySound(
            Actor, Id, S, SoundLocation, Volume,
            Radius ? Radius : GAudioDefaultRadius,
            Pitch, Flags, 0, 0, Bone);
    }
}

// Scaffolding for the link, not part of the unit.
// AActor::IsOwnedBy lives in another unit (RVA 0x92790, published in
// versus_vd4_item_0336.cpp). In the retail whole-program link, execClientHearSound
// sees IsOwnedBy with custom convention (this in EAX, TestOwner in ECX), read-only
// (Actor is not reloaded after the call), and EDX clobbered (forcing Actor into
// ESI and Flags into EBP). This stand-in body gives the single-TU LTCG link the
// same call-site summary; only execClientHearSound's bytes are compared.
__declspec(noinline) UBOOL AActor::IsOwnedBy(const AActor *TestOwner) const
{
    const AActor *Arg = this;
    if (!Arg)
        return 0;
    ULevel *SavedLevel = Arg->XLevel;
    do
    {
        if (Arg == TestOwner)
            return 1;
        Arg = Arg->Owner;
    } while (Arg);
    return SavedLevel == (ULevel *)1;
}
void Escape(void *);
extern Native GExecTable[1];
void Driver_122ee0()
{
    Escape(GNatives);
    Escape(&GAudioDefaultRadius);
    GExecTable[0] = (Native)&APlayerController::execClientHearSound;
}
