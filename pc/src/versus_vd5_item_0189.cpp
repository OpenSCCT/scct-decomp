// Work item 0189: AESBPatchActor / AESoftBodyActor methods, RVA 0xe1ee0-0xe2027.
// The object held at +0x2f8 is the soft-body simulation object; its class is
// not recovered, so it is named USoftBodyObject_e1ee0 (neutral name).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

#define SLOT(n) virtual void Slot##n();

struct FFrame;
struct FVector { FLOAT X, Y, Z; };

class UObject {
public:
    SLOT(0)
};
typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

struct FOutputDevice {
    void *vtbl;
    // This build has no bSuppressEventTag: FFrame::Object sits at +8.
};

struct FFrame : public FOutputDevice {
    void *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;
    void Step(UObject *Context, void *const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

// Neutral name: class of the object at AESBPatchActor+0x2f8.
class USoftBodyObject_e1ee0 {
public:
    SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9)
    SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
    SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
    SLOT(30) SLOT(31) SLOT(32)
    virtual void Update();                         // +0x84
    SLOT(34)
    virtual void Notify(INT A, INT B);             // +0x8c
    SLOT(36) SLOT(37) SLOT(38) SLOT(39) SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45)
    SLOT(46) SLOT(47) SLOT(48) SLOT(49)
    virtual void BulletHit(const FVector &Location); // +0xc8
};

struct FLevelInfoPart_e1f10 {
    BYTE Pad[0xf0];
    struct { BYTE Pad[0x2c]; void *Result; } *Info;
};

class AActor : public UObject {
public:
    SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9)
    SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
    virtual void PostLoad();                       // slot 16
    SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25)
    SLOT(26) SLOT(27) SLOT(28)
    virtual void Slot29(INT A, INT B);             // slot 29
    virtual void Slot30();
    SLOT(31) SLOT(32) SLOT(33)
    virtual void Slot34();
    SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39) SLOT(40) SLOT(41) SLOT(42) SLOT(43)
    virtual void *Slot44();
    SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53)
    SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62)
    SLOT(63) SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71)
    SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77)
    virtual void Build(const TCHAR *Reason);       // slot 78, +0x138

    BYTE Pad[0x1a4 - 4];
    FLevelInfoPart_e1f10 *Level;                   // +0x1a4
    BYTE Pad2[0x2f8 - 0x1a8];
};

class AESBPatchActor : public AActor {
public:
    USoftBodyObject_e1ee0 *SoftBody;               // +0x2f8

    virtual void Slot29(INT A, INT B);
    virtual void *Slot44();
    virtual void PostLoad();
    virtual void Slot30();
    virtual void Slot34();
};

class AESoftBodyActor : public AESBPatchActor {
public:
    void execSBBulletHit(FFrame &Stack, void *const Result);
};

// Literals passed to Build; retail keeps them in data next to each other.
extern const TCHAR SBBuildReason_e1f60[];
extern const TCHAR SBBuildReason_e1f90[];
extern const TCHAR SBBuildReason_e1fc0[];

// 0xe1ee0
void AESBPatchActor::Slot29(INT A, INT B)
{
    if (SoftBody)
        SoftBody->Notify(B, A);
    AActor::Slot29(A, B);
}

// 0xe1f10
void *AESBPatchActor::Slot44()
{
    if (SoftBody)
        return SoftBody;
    if (Level->Info)
        return Level->Info->Result;
    return 0;
}

// 0xe1f60
void AESBPatchActor::PostLoad()
{
    AActor::PostLoad();
    if (!SoftBody)
        Build(SBBuildReason_e1f60);
    SoftBody->Update();
}

// 0xe1f90
void AESBPatchActor::Slot30()
{
    if (!SoftBody)
        Build(SBBuildReason_e1f90);
    SoftBody->Update();
}

// 0xe1fc0
void AESBPatchActor::Slot34()
{
    Build(SBBuildReason_e1fc0);
    SoftBody->Update();
}

// 0xe1fe0
void AESoftBodyActor::execSBBulletHit(FFrame &Stack, void *const Result)
{
    FVector HitLocation;
    Stack.Step(Stack.Object, &HitLocation);
    Stack.Code++;
    if (SoftBody)
        SoftBody->BulletHit(HitLocation);
}
