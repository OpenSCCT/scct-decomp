// Work item 0115: Versus RVA 0x1e810-0x1e987, Core UnObj.cpp driver cache.
// 0x1e810 FRegistryObjectInfo copy constructor (five FStrings, 0x3c bytes),
// 0x1e8a0 UObject::GetPreferences and 0x1e930 UTextBuffer::UTextBuffer.
// GObjPreferences is the TArray at 0x10cc9eb0 (FPreferencesInfo, 0x2c bytes;
// its copy constructor is 0x6260), GObjDrivers the one at 0x10cc9ebc.
// All three come from the LTCG link (this on the stack, arguments in
// registers), so they are checked with try_ltcg.py.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class FString
{
public:
	FString( const TCHAR* In );               // 0x46c0
	FString( const FString& Other );          // 0x4640
	~FString();                               // 0x48b0
	const TCHAR* operator*() const { return ArrayNum ? Data : L""; }
protected:
	TCHAR* Data;
	INT ArrayNum;
	INT ArrayMax;
};

class FArray
{
public:
	void* Data;
	INT ArrayNum;
	INT ArrayMax;
	INT Num() const { return ArrayNum; }
	INT Add( INT Count, INT ElementSize );    // 0x44e0
	void Empty( INT ElementSize, INT Slack ); // 0x4550
};
template<class T> class TArray : public FArray
{
public:
	T& operator()( INT i ) { return ((T*)Data)[i]; }
	void Empty( INT Slack = 0 );
};
// RVA 0x1f0b0 for FPreferencesInfo (LTCG: this in ESI).
template<class T> void TArray<T>::Empty( INT Slack )
{
	for( INT i=0; i<ArrayNum; i++ )
		(&(*this)(i))->~T();
	FArray::Empty( sizeof(T), Slack );
}
template<class T> inline void* operator new( unsigned int Size, TArray<T>& Array )
{
	INT Index = Array.FArray::Add( 1, sizeof(T) );
	return &Array(Index);
}

class FName { public: INT Index; };

struct FRegistryObjectInfo
{
	FString Object;
	FString Class;
	FString MetaClass;
	FString Description;
	FString Autodetect;
	FRegistryObjectInfo( const FRegistryObjectInfo& Other );
};

struct FPreferencesInfo
{
	FString Caption;
	FString ParentCaption;
	FString Class;
	FName Category;
	UBOOL Immediate;
	FPreferencesInfo( const FPreferencesInfo& Other );
	~FPreferencesInfo();
};

// RVA 0x1e810: compiler-style member-wise copy (this on the stack, Other in ECX).
FRegistryObjectInfo::FRegistryObjectInfo( const FRegistryObjectInfo& Other )
:	Object( Other.Object )
,	Class( Other.Class )
,	MetaClass( Other.MetaClass )
,	Description( Other.Description )
,	Autodetect( Other.Autodetect )
{
}

// RVA 0x6260 (published elsewhere); defined so the link gives it the retail
// convention (this on the stack, Other in EDI).
FPreferencesInfo::FPreferencesInfo( const FPreferencesInfo& Other )
:	Caption( Other.Caption )
,	ParentCaption( Other.ParentCaption )
,	Class( Other.Class )
,	Category( Other.Category )
,	Immediate( Other.Immediate )
{
}

// RVA 0x6200 (published elsewhere); defined for its LTCG convention
// (this on the stack).
FPreferencesInfo::~FPreferencesInfo()
{
}

extern "C" __declspec(dllimport) INT __cdecl _wcsicmp( const TCHAR*, const TCHAR* );
inline INT appStricmp( const TCHAR* A, const TCHAR* B ) { return _wcsicmp( A, B ); }

class UObject
{
public:
	virtual ~UObject();
	INT Index;
	UObject* HashNext;
	void* StateFrame;
	void* _Linker;
	INT _LinkerIndex;
	UObject* Outer;
	DWORD ObjectFlags;
	FName Name;
	void* Class;

	UObject() {}
	static void CacheDrivers( UBOOL ForceRefresh );   // 0x1dcd0
	static void GetPreferences( TArray<FPreferencesInfo>& Results, const TCHAR* ParentCaption, UBOOL ForceRefresh );
	static TArray<FPreferencesInfo> GObjPreferences;
};

// RVA 0x1e8a0 (LTCG: Results in ECX, ForceRefresh in EAX).
void UObject::GetPreferences( TArray<FPreferencesInfo>& Results, const TCHAR* ParentCaption, UBOOL ForceRefresh )
{
	CacheDrivers( ForceRefresh );
	Results.Empty();
	for( INT i=0; i<GObjPreferences.Num(); i++ )
	{
		if( appStricmp( *GObjPreferences(i).ParentCaption, ParentCaption )==0 )
			new(Results)FPreferencesInfo( GObjPreferences(i) );
	}
}

class FOutputDevice
{
public:
	virtual void Serialize( const TCHAR* V, INT Event )=0;
	virtual void Flush() {}
};

class UTextBuffer : public UObject, public FOutputDevice
{
public:
	INT Pos, Top;
	FString Text;
	UTextBuffer( const TCHAR* Str );
	void Serialize( const TCHAR* Data, INT Event );
};

// RVA 0x1e930 (LTCG: this on the stack).
UTextBuffer::UTextBuffer( const TCHAR* Str )
:	Text( Str )
{
}

// Scaffolding for the link, not part of the unit.
void Escape( void* );
inline void* operator new( unsigned int, void* Mem ) { return Mem; }
void Driver_1e810( FRegistryObjectInfo* Mem, FRegistryObjectInfo* Src )
{
	if( Mem ) new(Mem) FRegistryObjectInfo( *Src );
}
// The tool gives each stub one byte, so GObjPreferences+4 would land on the
// next stub (__imp___wcsicmp); this extra stub moves that collision away.
void Scaffold_Spacer();
void Driver_1e8a0( TArray<FPreferencesInfo>* Results, const TCHAR* Caption )
{
	Scaffold_Spacer();
	Escape( &UObject::GObjPreferences );
	UObject::GetPreferences( *Results, Caption, 0 );
	// CacheDrivers and others also call Empty, which keeps it out of line.
	UObject::GObjPreferences.Empty();
	Escape( Results );
	Results[1].Empty();
	Escape( Results );
	Results[2].Empty();
}
void Driver_1e930( void* Mem, const TCHAR* Str )
{
	if( Mem ) Escape( new(Mem) UTextBuffer( Str ) );
}
