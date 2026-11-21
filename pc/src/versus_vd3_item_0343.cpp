// Work item 0343: Versus RVA 0x96ec0-0x9719f.
//
// 0x97140 is the UGlobalTempObjects default constructor (vtable 0x10c0bb60,
// its deleting destructor follows at 0x971a0): a TArray member at 0x28 and an
// inlined UObject::AddToRoot() (GObjRoot.AddItem(this), with FArray::Add out
// of line). It is an LTCG function: "this" arrives on the stack (ret 4).
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef double DOUBLE;
typedef unsigned short TCHAR;

class FArray
{
public:
	void* Data;
	INT ArrayNum;
	INT ArrayMax;
	FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
	~FArray();
	INT Add(INT Count, INT ElementSize);
};

template<class T> class TArray : public FArray
{
public:
	TArray() {}
	~TArray();
	T& operator()(INT i) { return ((T*)Data)[i]; }
	INT AddItem(const T& Item)
	{
		INT Index = Add(1, sizeof(T));
		(*this)(Index) = Item;
		return Index;
	}
};

class UObject
{
public:
	DWORD UObjectData[9];
	UObject() {}
	virtual ~UObject();
	void AddToRoot();
};

extern TArray<UObject*> GObjRoot;

inline void UObject::AddToRoot()
{
	GObjRoot.AddItem(this);
}

class UGlobalTempObjects : public UObject
{
public:
	TArray<UObject**> GlobalObjectPtrs;   // 0x28
	UGlobalTempObjects();
	virtual ~UGlobalTempObjects();
};

// RVA 0x97140
UGlobalTempObjects::UGlobalTempObjects()
{
	AddToRoot();
}


// RVA 0x96ec0: UGameEngine::InputEvent (UGameEngine vtable slot 31).
// UInteractionMaster::MasterProcessKeyEvent at 0x10fb70 takes "this" in ESI
// (LTCG). The flag at InteractionMaster+0x40 bit 0 is unnamed.
enum EInputKey {};
enum EInputAction { IST_None = 0, IST_Press = 1, IST_Hold = 2, IST_Release = 3 };

class FOutputDevice;
extern FOutputDevice* GLog;
extern UBOOL GIsRunning;

class UInput : public UObject
{
public:
	virtual void Slot01();
	virtual void Slot02();
	virtual void Slot03();
	virtual void Slot04();
	virtual void Slot05();
	virtual void Slot06();
	virtual void Slot07();
	virtual void Slot08();
	virtual void Slot09();
	virtual void Slot10();
	virtual void Slot11();
	virtual void Slot12();
	virtual void Slot13();
	virtual void Slot14();
	virtual void Slot15();
	virtual void Slot16();
	virtual void Slot17();
	virtual void Slot18();
	virtual void Slot19();
	virtual void Slot20();
	virtual void Slot21();
	virtual void Slot22();
	virtual void Slot23();
	virtual UBOOL PreProcess(EInputKey iKey, EInputAction State, FLOAT Delta);           // 0x60
	virtual UBOOL Process(FOutputDevice& Ar, EInputKey iKey, EInputAction State, FLOAT Delta); // 0x64
};

class UViewport : public UObject
{
public:
	DWORD UViewportData[17];
	UInput* Input;     // 0x6c
};

class UInteractionMaster : public UObject
{
public:
	DWORD UInteractionMasterData[6];
	UBOOL bFlag40 : 1; // 0x40
	UBOOL MasterProcessKeyEvent(EInputKey iKey, EInputAction State, FLOAT Delta);
};

class UClient : public UObject
{
public:
	DWORD UClientData[31];
	UInteractionMaster* InteractionMaster;   // 0xa4
};

class UGameEngine : public UObject
{
public:
	DWORD Pad[2];
	UClient* Client;   // 0x30
	UBOOL InputEvent(UViewport* Viewport, EInputKey iKey, EInputAction State, FLOAT Delta);
};

UBOOL UGameEngine::InputEvent(UViewport* Viewport, EInputKey iKey, EInputAction State, FLOAT Delta)
{
	if (!GIsRunning)
		return 0;
	if (Client->InteractionMaster && Client->InteractionMaster->MasterProcessKeyEvent(iKey, State, Delta))
	{
		if (State == IST_Release || Client->InteractionMaster->bFlag40)
			Viewport->Input->PreProcess(iKey, State, Delta);
		return 1;
	}
	if (Viewport->Input->PreProcess(iKey, State, Delta) && Viewport->Input->Process(*GLog, iKey, State, Delta))
		return 1;
	return 0;
}

// RVA 0x96f90: UServerCommandlet::Main, the dedicated-server main loop
// (UE2 UCC "server" commandlet). Names follow Unreal Engine 2; the global at
// 0x10c96910 (set to 3) and the two FName indices 0x15 and 0xc4 passed to
// StaticLoadClass are not identified. UObject::SetLanguage, FStats::Clear and
// UObject::StaticLoadClass are LTCG callees with register arguments.
enum EName { NAME_None = 0 };
struct FName
{
	INT Index;
	FName(EName N) : Index(N) {}
};

class UClass;
class UPackageMap;
class FConfigCache
{
public:
	virtual void Slot00();
	virtual void Slot01();
	virtual void Slot02();
	virtual const TCHAR* GetStr(const TCHAR* Section, INT Unknown1, const TCHAR* Key, INT Unknown2);
};
class FStats
{
public:
	DWORD Data[32];
	void Clear();
};

extern FConfigCache* GConfig;
extern FOutputDevice* GError;
extern UObject* GObjTransientPkg;
extern UBOOL GIsRequestingExit;
extern DWORD GUnknown_96910;
extern FStats GStats;
extern UClass UEngine_PrivateStaticClass;
DOUBLE appSeconds();
extern "C" __declspec(dllimport) void __stdcall Sleep(DWORD dwMilliseconds);

inline void appSleep(FLOAT Seconds)
{
	Sleep((DWORD)(Seconds * 1000.0));
}
template<class T> inline T Max(const T A, const T B)
{
	return (A >= B) ? A : B;
}

class UClass
{
public:
	DWORD UClassData[65];
	void (*ClassConstructor)(void*);   // 0x104
};

void SetLanguage(const TCHAR* LanguageExt);
UClass* StaticLoadClass(UClass* BaseClass, UObject* InOuter, FName A, FName B, FName C, const TCHAR* Filename, DWORD LoadFlags, UPackageMap* Sandbox);
UObject* StaticConstructObject(UClass* Class, UObject* InOuter, FName Name, DWORD SetFlags, UObject* Template, FOutputDevice* Error, UObject* SubobjectRoot, void* InstanceGraph);

class UEngine : public UObject
{
public:
	virtual void ESlot01();
	virtual void ESlot02();
	virtual void ESlot03();
	virtual void ESlot04();
	virtual void ESlot05();
	virtual void ESlot06();
	virtual void ESlot07();
	virtual void ESlot08();
	virtual void ESlot09();
	virtual void ESlot10();
	virtual void ESlot11();
	virtual void ESlot12();
	virtual void ESlot13();
	virtual void ESlot14();
	virtual void ESlot15();
	virtual void ESlot16();
	virtual void ESlot17();
	virtual void ESlot18();
	virtual void ESlot19();
	virtual void ESlot20();
	virtual void ESlot21();
	virtual void Tick(FLOAT DeltaSeconds);   // 0x58
	virtual void Init();                     // 0x5c
	virtual void ESlot24();
	virtual void ESlot25();
	virtual void ESlot26();
	virtual void ESlot27();
	virtual void ESlot28();
	virtual void ESlot29();
	virtual void ESlot30();
	virtual void ESlot31();
	virtual void ESlot32();
	virtual void ESlot33();
	virtual void ESlot34();
	virtual void ESlot35();
	virtual void ESlot36();
	virtual void ESlot37();
	virtual void ESlot38();
	virtual void ESlot39();
	virtual FLOAT GetMaxTickRate();          // 0xa0
	DWORD UEngineData[32];
	FLOAT CurrentTickRate;                   // 0xa8
};

class UCommandlet : public UObject
{
public:
	INT Main(const TCHAR* Parms);
};

INT UCommandlet::Main(const TCHAR* Parms)
{
	GUnknown_96910 = 3;
	if (const TCHAR* Language = GConfig->GetStr(L"Engine.Engine", 0, L"Language", 0))
		SetLanguage(Language);

	UClass* EngineClass = StaticLoadClass(&UEngine_PrivateStaticClass, 0, FName((EName)0x15), FName(NAME_None), FName((EName)0xc4), 0, 1, 0);
	UEngine* Engine = (UEngine*)StaticConstructObject(EngineClass, GObjTransientPkg, NAME_None, 0, 0, GError, 0, 0);
	if (Engine)
		(*EngineClass->ClassConstructor)(Engine);
	Engine->Init();

	GIsRunning = 1;
	DOUBLE OldTime = appSeconds();
	DOUBLE SecondStartTime = OldTime;
	INT TickCount = 0;
	while (GIsRunning && !GIsRequestingExit)
	{
		GStats.Clear();

		DOUBLE NewTime = appSeconds();
		Engine->Tick(NewTime - OldTime);
		OldTime = NewTime;
		TickCount++;
		if (OldTime > SecondStartTime + 1)
		{
			Engine->CurrentTickRate = (FLOAT)TickCount / (OldTime - SecondStartTime);
			SecondStartTime = OldTime;
			TickCount = 0;
		}

		FLOAT MaxTickRate = Engine->GetMaxTickRate();
		if (MaxTickRate > 0.0)
		{
			FLOAT Delta = (1.0 / MaxTickRate) - (appSeconds() - OldTime);
			appSleep(Max(0.f, Delta));
		}
	}
	GIsRunning = 0;
	return 0;
}

// Scaffolding for the link, not part of the unit.
// Stand-in body for UInteractionMaster::MasterProcessKeyEvent (0x10fb70) so
// the linker gives it the retail ESI "this" convention.
UBOOL ProcessHelper(void* List, EInputKey* Key, EInputAction* Action, FLOAT* Delta);
UBOOL NotifyHelper(UInteractionMaster* M, void* List);
UBOOL UInteractionMaster::MasterProcessKeyEvent(EInputKey iKey, EInputAction State, FLOAT Delta)
{
	if (ProcessHelper(&UInteractionMasterData[1], &iKey, &State, &Delta))
		return NotifyHelper(this, &UInteractionMasterData[2]);
	if (ProcessHelper(&UInteractionMasterData[3], &iKey, &State, &Delta))
		return NotifyHelper(this, &UInteractionMasterData[4]);
	return 0;
}
void Escape(void*);
void* operator new(unsigned int Size, void* Where);
void Driver_96ec0(UGameEngine* E, UViewport* V, EInputKey K, EInputAction A, FLOAT D, UInteractionMaster* M)
{
	Escape(&GIsRunning);
	Escape(&GLog);
	UBOOL (UGameEngine::*P)(UViewport*, EInputKey, EInputAction, FLOAT) = &UGameEngine::InputEvent;
	Escape(&P);
	E->InputEvent(V, K, A, D);
}
// Stand-in bodies for LTCG callees, so the linker gives them retail-like
// register conventions.
void LanguageHelper(TCHAR* Dest, const TCHAR* Src);
INT LanguageCompare(const TCHAR* A, const TCHAR* B);
extern TCHAR GLanguage[];
void SetLanguage(const TCHAR* LanguageExt)
{
	if (LanguageCompare(LanguageExt, GLanguage))
	{
		LanguageHelper(GLanguage, LanguageExt);
		LanguageHelper(GLanguage + 32, LanguageExt);
		if (*LanguageExt == 1)
			SetLanguage(LanguageExt + 1);   // keeps the stand-in out of line
	}
}
void StatsHelper(void* A, void* B, INT N);
void FStats::Clear()
{
	if (Data[10]) StatsHelper((void*)Data[12], (void*)Data[9], Data[10] * 4);
	if (Data[22]) StatsHelper((void*)Data[24], (void*)Data[21], Data[22] * 4);
	if (Data[0] == 1) ((FStats*)Data[1])->Clear();   // keeps the stand-in out of line
}
UObject* StaticLoadObjectHelper(UClass* Class, UObject* InOuter, FName A, FName B, FName C, const TCHAR* Filename, DWORD LoadFlags, UPackageMap* Sandbox);
extern UClass UClass_PrivateStaticClass;
void LoadErrorHelper(TCHAR* Buffer, const TCHAR* Format, const TCHAR* Text);
extern TCHAR LoadErrorBuffer[];
UClass* StaticLoadClass(UClass* BaseClass, UObject* InOuter, FName A, FName B, FName C, const TCHAR* Filename, DWORD LoadFlags, UPackageMap* Sandbox)
{
	UClass* Class = (UClass*)StaticLoadObjectHelper(&UClass_PrivateStaticClass, InOuter, A, B, C, Filename, LoadFlags | 8, Sandbox);
	if (Class)
	{
		for (UClass* Test = Class; Test; Test = (UClass*)Test->UClassData[10])
			if (Test == BaseClass)
				return Class;
		if (BaseClass)
			LoadErrorHelper(LoadErrorBuffer, L"%s", (TCHAR*)BaseClass->UClassData[9]);
		else
			LoadErrorHelper(LoadErrorBuffer, L"None", 0);
		LoadErrorHelper(LoadErrorBuffer, L"Failed", LoadErrorBuffer);
	}
	return 0;
}
void Driver_96f90(UCommandlet* C, const TCHAR* P)
{
	Escape(&GIsRunning);
	Escape(&GIsRequestingExit);
	Escape(&GUnknown_96910);
	Escape(&GConfig);
	Escape(&GObjTransientPkg);
	Escape(&GError);
	INT (UCommandlet::*M)(const TCHAR*) = &UCommandlet::Main;
	Escape(&M);
	C->Main(P);
	StaticLoadClass(0, 0, NAME_None, NAME_None, NAME_None, 0, 0, 0);
	SetLanguage(P);
	GStats.Clear();
}
void Driver_97140(void* X)
{
	Escape(&GObjRoot);
	new(X) UGlobalTempObjects;
}
void Driver2_97140(void* X)
{
	new(X) UGlobalTempObjects;
}
