// Work item 0051: AActor::UpdateTimers, AActor::CacheNetRelevant, AActor::IsNetRelevantFor
// Versus RVA 0x130400-0x130721 (VC7.0 /GL /LTCG)

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef float FLOAT;

extern FLOAT GAudioMaxRadiusMultiplier;

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}

    FVector operator-(const FVector &V) const;
    FLOAT Size() const;
    FLOAT SizeSquared() const;
};

#pragma auto_inline(off)
FLOAT FVector::SizeSquared() const
{
    return X * X + Y * Y + Z * Z;
}
#pragma auto_inline(on)

class FSphere : public FVector
{
public:
    FLOAT W;
    FSphere() {}
};

class AActor;
class APawn;
class APlayerController;
class USound;
class UFunction;

class UPrimitive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual FSphere GetRenderBoundingSphere(const AActor *Owner);
};

class UModel
{
public:
    BYTE unk_0[0x54];
    void *unk_54;
    INT NodesNum;
    BYTE unk_5c[0xa8];
    BYTE RootOutside;

    __declspec(noinline) BYTE FastLineCheck(const FVector &End, const FVector &Start);
};

extern void *GModelFastLineCheckNodes;
BYTE FastLineCheckNode(INT iNode, FVector End, const FVector &Start, BYTE Outside);

__declspec(noinline) BYTE UModel::FastLineCheck(const FVector &End, const FVector &Start)
{
    GModelFastLineCheckNodes = unk_54;
    if (NodesNum)
        return FastLineCheckNode(0, End, Start, RootOutside);
    return RootOutside;
}

class ULevel
{
public:
    BYTE unk_0[0x13c];
    UModel *Model;
};

class ALevelInfo
{
public:
    BYTE unk_0[0x3b0];
    FLOAT TimeSeconds;
};

struct FStateFrame
{
    BYTE unk_0[0x1c];
    DWORD ProbeMask;
};

class AActor
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *UnusedResult = 0);
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual UPrimitive *GetPrimitive();
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual UBOOL IsNetRelevantFor(APlayerController *RealViewer, AActor *Viewer, const FVector &SrcLocation);

    BYTE unk_4[0x8];
    FStateFrame *StateFrame;             // 0x00c
    BYTE unk_10[0x70];
    FVector Location;                    // 0x080
    BYTE unk_8c[0x78];
    AActor *Owner;                       // 0x104
    BYTE unk_108[0x8c];
    APawn *Instigator;                   // 0x194
    USound *AmbientSound;                // 0x198
    BYTE unk_19c[0x4];
    ALevelInfo *Level;                   // 0x1a0
    ULevel *XLevel;                      // 0x1a4
    BYTE unk_1a8[0x10];
    FLOAT TimerRate;                     // 0x1b8
    BYTE unk_1bc[0x14];
    FLOAT TimerCounter;                  // 0x1d0
    BYTE unk_1d4[0x98];
    FLOAT CollisionHeight;               // 0x26c
    FLOAT SoundRadius;                   // 0x270
    BYTE unk_274[0x74];
    BITFIELD unk_2e8_0 : 12;             // 0x2e8
    BITFIELD bHidden : 1;                // 0x2e8 bit 12 (0x1000)
    BITFIELD unk_2e8_13 : 5;
    BITFIELD bTimerLoop : 1;             // 0x2e8 bit 18 (0x40000)
    BITFIELD bOnlyOwnerSee : 1;          // 0x2e8 bit 19 (0x80000)
    BITFIELD unk_2e8_20 : 12;
    BITFIELD unk_2ec_0 : 3;              // 0x2ec
    BITFIELD bAlwaysRelevant : 1;        // 0x2ec bit 3 (0x8)
    BITFIELD unk_2ec_4 : 28;
    BITFIELD unk_2f0_0 : 15;             // 0x2f0
    BITFIELD bBlockPlayers : 1;          // 0x2f0 bit 15 (0x8000)
    BITFIELD unk_2f0_16 : 16;
    BYTE unk_2f4[0x9c];
    FLOAT LastNetRelevantTime;           // 0x390
    APlayerController *LastNetRelevantRealViewer; // 0x394
    AActor *LastNetRelevantViewer;       // 0x398
    BYTE unk_39c[0x110];
    BITFIELD unk_4ac_0 : 10;             // 0x4ac
    BITFIELD bLastNetRelevant : 1;       // 0x4ac bit 10 (0x400)
    BITFIELD unk_4ac_11 : 21;

    UFunction *FindFunctionChecked(INT Name, INT Global);
    __declspec(noinline) void eventTimer();

    inline UBOOL IsOwnedBy(const AActor *TestOwner) const
    {
        for (const AActor *Arg = this; Arg; Arg = Arg->Owner)
            if (Arg == TestOwner)
                return 1;
        return 0;
    }

    inline FLOAT WorldSoundRadius() const
    {
        return GAudioMaxRadiusMultiplier * SoundRadius;
    }

    __declspec(noinline) void UpdateTimers(FLOAT DeltaSeconds);
    UBOOL CacheNetRelevant(UBOOL bRelevant, APlayerController *RealViewer, AActor *Viewer);
};

class APawn : public AActor
{
};

class APlayerController : public AActor
{
};

inline FLOAT Square(FLOAT F)
{
    return F * F;
}

__declspec(noinline) void AActor::eventTimer()
{
    if (!StateFrame || (StateFrame->ProbeMask & 0x100))
        ProcessEvent(FindFunctionChecked(0x134, 0), 0, 0);
}

// 0x130400: AActor::UpdateTimers
__declspec(noinline) void AActor::UpdateTimers(FLOAT DeltaSeconds)
{
    if (TimerRate > 0.0f)
    {
        TimerCounter += DeltaSeconds;
        if (TimerCounter >= TimerRate)
        {
            INT Count = (INT)(TimerCounter / TimerRate);
            TimerCounter -= Count * TimerRate;
            if (Count && !bTimerLoop)
                TimerRate = 0.0f;
            eventTimer();
        }
    }
}

// 0x1304a0: AActor::CacheNetRelevant (name is a guess)
UBOOL AActor::CacheNetRelevant(UBOOL bRelevant, APlayerController *RealViewer, AActor *Viewer)
{
    bLastNetRelevant = bRelevant;
    LastNetRelevantTime = Level->TimeSeconds;
    LastNetRelevantRealViewer = RealViewer;
    LastNetRelevantViewer = Viewer;
    return bRelevant;
}

// 0x1304f0: AActor::IsNetRelevantFor
UBOOL AActor::IsNetRelevantFor(APlayerController *RealViewer, AActor *Viewer, const FVector &SrcLocation)
{
    if (LastNetRelevantTime == Level->TimeSeconds
        && RealViewer == LastNetRelevantRealViewer
        && Viewer == LastNetRelevantViewer)
        return bLastNetRelevant;

    if (bAlwaysRelevant || IsOwnedBy(Viewer) || IsOwnedBy(RealViewer) || this == Viewer || Viewer == Instigator)
        return CacheNetRelevant(1, RealViewer, Viewer);

    USound *Sound = AmbientSound;
    if (Sound)
    {
        if ((Location - Viewer->Location).SizeSquared() < Square(WorldSoundRadius()))
            return CacheNetRelevant(1, RealViewer, Viewer);
    }

    if ((bHidden || bOnlyOwnerSee) && !bBlockPlayers && !Sound)
        return CacheNetRelevant(0, RealViewer, Viewer);

    UPrimitive *Prim = GetPrimitive();
    if (!((Location - SrcLocation).Size() - Prim->GetRenderBoundingSphere(this).W < 2500.0f))
    {
        FVector TopLoc = Location;
        TopLoc.Z += CollisionHeight;
        if (!XLevel->Model->FastLineCheck(TopLoc, SrcLocation)
            && !XLevel->Model->FastLineCheck(Location, SrcLocation))
            return CacheNetRelevant(0, RealViewer, Viewer);
    }

    return CacheNetRelevant(1, RealViewer, Viewer);
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);

void Driver_130400(AActor *A, FLOAT Delta)
{
    A->VirtualSlot6();
    A->UpdateTimers(Delta);
    Escape(A);
}

void Driver_1304f0(AActor *A, APlayerController *RV, AActor *V, const FVector &Src)
{
    Escape(&GAudioMaxRadiusMultiplier);
    Escape(&GModelFastLineCheckNodes);
    UBOOL (AActor::*Fn)(APlayerController *, AActor *, const FVector &) = &AActor::IsNetRelevantFor;
    Escape(&Fn);
    Escape((void *)A->AActor::IsNetRelevantFor(RV, V, Src));
}
