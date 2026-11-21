// Work item 0114: UObject::CollectGarbage (RVA 0x1db10).
// LTCG unit: FArchiveTagUsed's constructor (0x1d8d0) takes `this` in EAX.

typedef unsigned long DWORD;
typedef int INT;

class UObject;

class FArchive
{
public:
	virtual ~FArchive() {}
	virtual void Serialize( void* V, INT Length ) {}
	virtual void SerializeBits( void* V, INT LengthBits ) {}
	virtual void SerializeInt( DWORD& Value, DWORD Max ) {}
	virtual void Preload( UObject* Object ) {}
	virtual void CountBytes( INT InNum, INT InMax ) {}
	virtual FArchive& operator<<( UObject*& Res ) { return *this; }
	INT ArVer;
	INT ArNetVer;
	INT ArLicenseeVer;
	INT ArIsLoading;
	INT ArIsSaving;
	INT ArIsTrans;
	INT ArIsPersistent;
	INT ArForEdit;
	INT ArForClient;
	INT ArForServer;
	INT ArIsError;
	INT ArIsCriticalError;
	INT ArUnknown34;
	INT ArUnknown38;
	INT ArUnknown3C;
};

class UObject
{
public:
	void* VfTable;
	INT Index;
	UObject* HashNext;
	void* StateFrame;
	void* Linker;
	INT LinkerIndex;
	UObject* Outer;
	DWORD ObjectFlags;

	static void SerializeRootSet( FArchive& Ar, DWORD KeepFlags, DWORD RequiredFlags );
	static void PurgeGarbage();
	static void CollectGarbage( DWORD KeepFlags );
};

// GObjObjects (0x10cc9e80) and a second object list (0x10cc9e5c).
extern UObject** GObjObjects_Data;
extern INT GObjObjects_Num;
extern DWORD** GObjRoots_Data;
extern INT GObjRoots_Num;
extern UObject* GSerializedObject_10c925fc;
// Unnamed global at 0x10c97144: garbage collection is skipped while it is set.
extern DWORD GNoGarbageCollection_10c97144;

enum { RF_Unreachable = 0x02, RF_TagGarbage = 0x40 };

class FArchiveTagUsed : public FArchive
{
public:
	FArchiveTagUsed();
	FArchive& operator<<( UObject*& Object );
	UObject* Context;
};

__declspec(noinline) FArchiveTagUsed::FArchiveTagUsed()
: Context( 0 )
{
	ArVer = 0xaf; ArNetVer = 2000; ArLicenseeVer = 0;
	ArIsLoading = ArIsSaving = ArIsTrans = ArIsPersistent = 0;
	ArForEdit = ArForClient = ArForServer = 1;
	ArIsError = ArIsCriticalError = 0;
	ArUnknown34 = 3; ArUnknown38 = 0; ArUnknown3C = -1;
	GSerializedObject_10c925fc = 0;
	for( INT i = 0; i < GObjObjects_Num; i++ )
		if( GObjObjects_Data[i] )
			GObjObjects_Data[i]->ObjectFlags |= RF_Unreachable | RF_TagGarbage;
	for( INT j = 0; j < GObjRoots_Num; j++ )
		if( GObjRoots_Data[j] )
			GObjRoots_Data[j][1] |= 2;
}

// RVA 0x1db10.
void UObject::CollectGarbage( DWORD KeepFlags )
{
	if( !GNoGarbageCollection_10c97144 )
	{
		FArchiveTagUsed TagUsedAr;
		SerializeRootSet( TagUsedAr, KeepFlags, RF_TagGarbage );
		PurgeGarbage();
	}
}

// Scaffolding for the link, not part of the unit.
void Escape( void* );
void Driver_1db10( DWORD KeepFlags )
{
	Escape( &GNoGarbageCollection_10c97144 );
	UObject::CollectGarbage( KeepFlags );
}
