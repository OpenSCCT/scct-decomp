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
	static void InternalConstructor(void *Storage);
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
void Driver_97140(void* X)
{
	Escape(&GObjRoot);
	new(X) UGlobalTempObjects;
}
void Driver2_97140(void* X)
{
	new(X) UGlobalTempObjects;
}

enum EInternal { EC_Internal };
inline void *operator new(unsigned int, EInternal *Storage) { return Storage; }
inline void operator delete(void *, EInternal *) {}

// InternalConstructor constructs the registered class in storage supplied by the object system.
void UGlobalTempObjects::InternalConstructor(void *Storage)
{
    new((EInternal *)Storage) UGlobalTempObjects;
}
