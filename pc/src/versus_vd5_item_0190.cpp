// AESoftBodyActor::execSBExplosionHit (RVA 0xe2030).
// native function SBExplosionHit(vector HitLocation, vector Momentum);
typedef unsigned char BYTE;
typedef int INT;
typedef float FLOAT;

struct FFrame;
class UObject {
public:
    virtual ~UObject();
};
typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

struct FVector { FLOAT X, Y, Z; };

struct FOutputDevice {
    virtual void Serialize(const unsigned short *V, int Event);
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

// Soft-body simulation object held by the actor; slot 0xcc / 4 = 51 is the
// explosion-hit handler. Name is neutral (UnnamedSoftBody_e2030).
class UnnamedSoftBody_e2030 {
public:
#define SLOT(n) virtual void Slot##n();
    SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9)
    SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
    SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
    SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
    SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49)
    SLOT(50)
#undef SLOT
    virtual void ExplosionHit(FVector &HitLocation, FVector &Momentum);
};

class AESoftBodyActor : public UObject {
public:
    BYTE Pad[0x2f8 - 4];
    UnnamedSoftBody_e2030 *SoftBody;
    void execSBExplosionHit(FFrame &Stack, void *const Result);
};

void AESoftBodyActor::execSBExplosionHit(FFrame &Stack, void *const Result)
{
    FVector HitLocation;
    Stack.Step(Stack.Object, &HitLocation);
    FVector Momentum;
    Stack.Step(Stack.Object, &Momentum);
    Stack.Code++;
    if (SoftBody)
        SoftBody->ExplosionHit(HitLocation, Momentum);
}
