// Work item 0241: Versus RVA 0xf1a50-0xf1f1b.
// AActor::CheckNoiseHearing, AController::CheckEnemyVisible, AController::ShowSelf
// (UnPawn.cpp in Unreal Engine 2) and ASPlayerController slot 42.
// Unreal Engine 2 builds with 4-byte structure packing (/Zp4).
#pragma pack(push, 4)
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef int INT;
typedef float FLOAT;
typedef double DOUBLE;
typedef unsigned __int64 QWORD;

enum { NAME_PROBEMIN = 300, NAME_PROBEMAX = 364 };
enum EName
{
	NAME_SeePlayer       = 0x154,
	NAME_EnemyNotVisible = 0x155,
	NAME_HearNoise       = 0x156,
	NAME_SeeMonster      = 0x158,
};

class FName
{
public:
	INT Index;
	FName(EName N) : Index(N) {}
	INT GetIndex() const { return Index; }
};

struct FVector
{
	FLOAT X, Y, Z;
	FVector operator-(const FVector& V) const { FVector R; R.X = X - V.X; R.Y = Y - V.Y; R.Z = Z - V.Z; return R; }
	FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
};

struct FStateFrame
{
	char Pad[0x1c];
	QWORD ProbeMask;
};

class UFunction;


class UObject
{
public:
	virtual ~UObject();
	virtual void Slot1();
	virtual void Slot2();
	virtual void Slot3();
	virtual void ProcessEvent(UFunction* Function, void* Parms, void* Result = 0);
	virtual void Slot5(); virtual void Slot6(); virtual void Slot7(); virtual void Slot8(); virtual void Slot9();
	virtual void Slot10(); virtual void Slot11(); virtual void Slot12(); virtual void Slot13(); virtual void Slot14();
	virtual void Slot15(); virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
	virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23(); virtual void Slot24();
	virtual UBOOL IsPlayer();           // vtable +0x64 (an AActor virtual in Engine)
	INT Index;
	UObject* HashNext;
	FStateFrame* StateFrame;
	UBOOL IsProbing(FName ProbeName);
	UFunction* FindFunctionChecked(FName InName, UBOOL Global = 0);
};

// RVA 0x40450 (published separately; defined here so the link sees its body).
UBOOL UObject::IsProbing(FName ProbeName)
{
	return ProbeName.GetIndex() < NAME_PROBEMIN
		|| ProbeName.GetIndex() >= NAME_PROBEMAX
		|| !StateFrame
		|| (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
}

class APawn;
class AController;

class ULevel : public UObject
{
public:
	char Pad10[0x190 - 0x10];
	DOUBLE TimeSeconds;                 // 0x190
};

class ALevelInfo;

class AActor : public UObject
{
public:
	char Pad10[0x80 - 0x10];
	FVector Location;                   // 0x80
	char Pad8C[0x194 - 0x8c];
	APawn* Instigator;                  // 0x194
	char Pad198[0x1a0 - 0x198];
	ALevelInfo* Level;                  // 0x1a0
	ULevel* XLevel;                     // 0x1a4
	char Pad1A8[0x2bc - 0x1a8];
	FName Tag;                          // 0x2bc
	ULevel* GetLevel() const { return XLevel; }
	void CheckNoiseHearing(FLOAT Loudness);
};

class ALevelInfo : public AActor
{
public:
	char Pad2C0[0x510 - 0x2c0];
	AController* ControllerList;        // 0x510
};

class AController : public AActor
{
public:
	char Pad2C0[0x2fc - 0x2c0];
	APawn* Pawn;                        // 0x2fc
	INT Pad300;
	FLOAT SightCounter;                 // 0x304
	INT Pad308[2];
	DWORD bIsPlayer : 1;                // 0x310
	char Pad314[0x324 - 0x314];
	AController* nextController;        // 0x324
	char Pad328[0x350 - 0x328];
	APawn* Enemy;                       // 0x350
	void ShowSelf();
	__declspec(noinline) void CheckEnemyVisible();
	__declspec(noinline) UBOOL LineOfSightTo(AActor* Other, INT bUseLOSFlag = 0);
	__declspec(noinline) INT SeePawn(APawn* Other, UBOOL bMaySkipChecks = 1);
	void eventSeePlayer(APawn* Seen);
	void eventSeeMonster(APawn* Seen);
	void eventEnemyNotVisible();
	void eventHearNoise(FLOAT Loudness, AActor* NoiseMaker);
};

class APawn : public AActor
{
public:
	char Pad2C0[0x310 - 0x2c0];
	FVector noise1spot;                 // 0x310
	FVector noise2spot;                 // 0x31c
	char Pad328[0x38c - 0x328];
	AController* Controller;            // 0x38c
	char Pad390[0x414 - 0x390];
	FLOAT noise1time;                   // 0x414
	FLOAT Pad418;
	FLOAT noise1loudness;               // 0x41c
	FLOAT noise2time;                   // 0x420
	FLOAT Pad424;
	FLOAT noise2loudness;               // 0x428
};

// RVA 0xf1a50
void AActor::CheckNoiseHearing(FLOAT Loudness)
{
	if (!Instigator || !Instigator->Controller)
		return;


	// allow only one noise per 0.2 seconds from a given instigator & area (within 50 units) unless much louder
	// check the two sound slots
	FLOAT CurrentTime = GetLevel()->TimeSeconds;

	if ((Instigator->noise1time > CurrentTime - 0.2f)
		&& ((Instigator->noise1spot - Location).SizeSquared() < 2500.f)
		&& (Instigator->noise1loudness >= 0.9f * Loudness))
	{
		return;
	}

	if ((Instigator->noise2time > CurrentTime - 0.2f)
		&& ((Instigator->noise2spot - Location).SizeSquared() < 2500.f)
		&& (Instigator->noise2loudness >= 0.9f * Loudness))
	{
		return;
	}

	// put this noise in a slot
	if (Instigator->noise1time < CurrentTime - 0.18f)
	{
		Instigator->noise1time = CurrentTime;
		Instigator->noise1spot = Location;
		Instigator->noise1loudness = Loudness;
	}
	else if (Instigator->noise2time < CurrentTime - 0.18f)
	{
		Instigator->noise2time = CurrentTime;
		Instigator->noise2spot = Location;
		Instigator->noise2loudness = Loudness;
	}
	else if (((Instigator->noise1spot - Location).SizeSquared() < 2500.f)
		&& (Instigator->noise1loudness <= Loudness))
	{
		Instigator->noise1time = CurrentTime;
		Instigator->noise1spot = Location;
		Instigator->noise1loudness = Loudness;
	}
	else if (Instigator->noise2loudness <= Loudness)
	{
		Instigator->noise1time = CurrentTime;
		Instigator->noise1spot = Location;
		Instigator->noise1loudness = Loudness;
	}

	// if the noise is not made by a player or an AI with a player as an enemy, then only send it to
	// other AIs with the same tag
	if (!Instigator->IsPlayer()
		&& (!Instigator->Controller->Enemy || !Instigator->Controller->Enemy->IsPlayer()))
	{
		for (AController* next = Level->ControllerList; next != 0; next = next->nextController)
			if ((next->Pawn != Instigator) && next->IsProbing(NAME_HearNoise)
				&& (next->Tag.Index == Tag.Index))
				next->eventHearNoise(Loudness, this);
		return;
	}

	// all pawns can hear this noise
	for (AController* P = Level->ControllerList; P != 0; P = P->nextController)
		if ((P->Pawn != Instigator) && P->IsProbing(NAME_HearNoise))
			P->eventHearNoise(Loudness, this);
}

// Script event thunks (Engine class headers); IsProbing is inlined into them.
// RVA 0xf2150
void AController::eventHearNoise(FLOAT Loudness, AActor* NoiseMaker)
{
	struct { FLOAT Loudness; AActor* NoiseMaker; } Parms;
	if (!IsProbing(NAME_HearNoise))
		return;
	Parms.Loudness = Loudness;
	Parms.NoiseMaker = NoiseMaker;
	ProcessEvent(FindFunctionChecked(NAME_HearNoise), &Parms);
}

// RVA 0xf2110
void AController::eventEnemyNotVisible()
{
	if (!IsProbing(NAME_EnemyNotVisible))
		return;
	ProcessEvent(FindFunctionChecked(NAME_EnemyNotVisible), 0);
}

// RVA 0xf20c0
void AController::eventSeePlayer(APawn* Seen)
{
	struct { APawn* Seen; } Parms;
	if (!IsProbing(NAME_SeePlayer))
		return;
	Parms.Seen = Seen;
	ProcessEvent(FindFunctionChecked(NAME_SeePlayer), &Parms);
}

// RVA 0xf2070
void AController::eventSeeMonster(APawn* Seen)
{
	struct { APawn* Seen; } Parms;
	if (!IsProbing(NAME_SeeMonster))
		return;
	Parms.Seen = Seen;
	ProcessEvent(FindFunctionChecked(NAME_SeeMonster), &Parms);
}

// RVA 0xf1de0
void AController::CheckEnemyVisible()
{
	if (Enemy)
	{
		if (!LineOfSightTo(Enemy))
			eventEnemyNotVisible();
	}
}

// RVA 0xf1e10
void AController::ShowSelf()
{
	if (!Pawn)
		return;
	for (AController* C = Level->ControllerList; C != 0; C = C->nextController)
	{
		if (C != this && (bIsPlayer || C->bIsPlayer) && C->SightCounter < 0.f)
		{
			// check visibility
			if ((bIsPlayer ? C->IsProbing(NAME_SeePlayer) : C->IsProbing(NAME_SeeMonster))
				&& C->SeePawn(Pawn))
			{
				if (bIsPlayer)
					C->eventSeePlayer(Pawn);
				else
					C->eventSeeMonster(Pawn);
			}
		}
	}
}

// RVA 0xf14a0 and 0xf1170 are large (AController::LineOfSightTo and SeePawn);
// these stand-in bodies only give the link callees to choose conventions for.
// External helpers the real bodies call (line checks, trace tests).
INT SightTrace(AController* Viewer, AActor* Other, INT Flags);
INT SightRange(AController* Viewer, APawn* Other);
struct FCheckResult { INT Data[0x28]; };
INT SightTraceHit(FCheckResult& Hit, AController* Viewer, AActor* Other, INT Flags);
UBOOL AController::LineOfSightTo(AActor* Other, INT bUseLOSFlag)
{
	if (!Other)
		return 0;
	FCheckResult Hit;
	INT A = SightTraceHit(Hit, this, Other, 0);
	if (Other == Enemy)
		return SightTraceHit(Hit, this, Other, A + bUseLOSFlag);
	if (!Hit.Data[1])
		return SightTraceHit(Hit, this, Other, bUseLOSFlag + A);
	return 0;
}
INT AController::SeePawn(APawn* Other, UBOOL bMaySkipChecks)
{
	if (!Other || !Pawn)
		return 0;
	if (Other == Enemy)
		return LineOfSightTo(Other, 0);
	if (bMaySkipChecks && SightRange(this, Other))
		return 0;
	if (SightRange(this, Other) > 2)
		return 0;
	return LineOfSightTo(Other, bMaySkipChecks);
}

// Objects released through their virtual slot 3 with flag 1.
class FReleasable
{
public:
	virtual void Slot0();
	virtual void Slot1();
	virtual void Slot2();
	virtual void Release(INT Flags);
};

// ASPlayerController (reflected vtable 0x2fa678 slot 42); field and method names are neutral.
class ASPlayerController
{
public:
	unsigned char Pad[0x5b0];
	FReleasable* Resource5B0;           // 0x5b0
	INT Pad5B4;
	FReleasable* Resource5B8;           // 0x5b8
	void ReleaseResources();
};

// RVA 0xf1ee0
void ASPlayerController::ReleaseResources()
{
	if (Resource5B8)
		Resource5B8->Release(1);
	Resource5B8 = 0;
	if (Resource5B0)
		Resource5B0->Release(1);
	Resource5B0 = 0;
}

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void*);
void Driver_f1a50(AActor* A, FLOAT L) { A->CheckNoiseHearing(L); }
void Driver_f1de0(AController* C) { if (C->IsProbing(NAME_EnemyNotVisible)) C->CheckEnemyVisible(); }
void Driver_f1e10(AController* A, AController* B, INT F) { A->ShowSelf(); B->SightCounter = 1.f; B->ShowSelf(); Escape((void*)A->SeePawn(B->Pawn, F)); }
