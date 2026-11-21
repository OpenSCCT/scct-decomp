// Work item w3 0010: Versus RVA 0x17010, UObject::SaveConfig (Core UnObj.cpp).
// Link-time (LTCG) object: `this` on the stack, callee pops all four words.
// Versus additions over UE2: a third "flush" argument, per-property
// CPF_GlobalConfig sections, and config files whose name contains
// "UbiAccounts" redirected to "<base>\UbiAccounts".
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef short SWORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum { INDEX_NONE = -1 };
enum { CPF_Config = 0x4000, CPF_GlobalConfig = 0x40000 };
enum { CLASS_Config = 0x4, CLASS_PerObjectConfig = 0x400, CLASS_IsAUProperty = 0x8000 };

extern "C" __declspec(dllimport) TCHAR* __cdecl wcscpy( TCHAR* D, const TCHAR* S );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcsstr( const TCHAR* S, const TCHAR* Find );
INT appSprintf( TCHAR* Dest, const TCHAR* Fmt, ... );

class FMalloc
{
public:
	virtual void* Malloc( DWORD Count, const TCHAR* Tag ) = 0;
	virtual void* Realloc( void* Original, DWORD Count, const TCHAR* Tag ) = 0;
	virtual void Free( void* Original ) = 0;
};
extern FMalloc* GMalloc;

class FArray
{
public:
	void* Data;
	INT ArrayNum;
	INT ArrayMax;
	INT Add( INT Count, INT ElementSize );
	void Remove( INT Index, INT Count, INT ElementSize );
	INT Num() const { return ArrayNum; }
	void* GetData() { return Data; }
};
template<class T> class TArray : public FArray
{
public:
	T& operator()( INT i ) { return ((T*)Data)[i]; }
};

struct FNameEntry
{
	INT Index;
	DWORD Flags;
	FNameEntry* HashNext;
	TCHAR Name[1];
};
struct FName
{
	INT Index;
	const TCHAR* operator*() const { return Names( Index )->Name; }
	static TArray<FNameEntry*> Names;
};

class UClass;
class UStruct;

class UObject
{
public:
	virtual void S00(); virtual void S01(); virtual void S02(); virtual void S03();
	virtual void S04(); virtual void S05(); virtual void S06(); virtual void S07();
	virtual void S08(); virtual void S09(); virtual void S10(); virtual void S11();
	virtual void S12(); virtual void S13(); virtual void S14(); virtual void S15();
	virtual void S16(); virtual void S17(); virtual void S18(); virtual void S19();
	virtual void S20(); virtual void S21(); virtual void S22(); virtual void S23();
	virtual void S24();
	INT Index;
	UObject* HashNext;
	void* StateFrame;
	void* _Linker;
	INT _LinkerIndex;
	UObject* Outer;
	DWORD ObjectFlags;
	FName Name;
	UClass* Class;

	INT GetIndex() const { return Index; }
	UClass* GetClass() const { return Class; }
	UObject* GetOuter() const { return Outer; }
	const TCHAR* GetName() const { return *Name; }
	const FName GetFName() const { return Name; }
	UBOOL IsA( UClass* SomeBase ) const;
	// RVA 0x15d90
	const TCHAR* GetPathName( UObject* StopOuter = 0, TCHAR* Str = 0 ) const;
	// RVA 0x16890
	void LoadConfig( UBOOL Propagate = 0, UClass* Class = 0, const TCHAR* Filename = 0 );
	void __stdcall SaveConfig( DWORD Flags = CPF_Config, const TCHAR* Filename = 0, UBOOL Flush = 1 );

	static TArray<UObject*> GObjObjects;
	static UObject* GObjTransientPkg;      // 0x10c925b4
};

class UField : public UObject
{
public:
	UField* SuperField;
	UField* Next;
	virtual UClass* GetOwnerClass();      // +0x64
};
class UStruct : public UField
{
public:
	UField* Children;
	virtual UStruct* GetInheritanceSuper();
};
class UClass : public UStruct
{
public:
	BYTE Pad34[0x88 - 0x34];
	DWORD ClassFlags;                     // +0x88
	INT Pad8C;
	FName ClassConfigName;                // +0x90
	BYTE Pad94[0xac - 0x94];
	TArray<BYTE> Defaults;                // +0xac
	static UClass PrivateStaticClass;
	static UClass* StaticClass() { return &PrivateStaticClass; }
	UClass* GetSuperClass() const { return (UClass*)SuperField; }
	UObject* GetDefaultObject() { return (UObject*)&Defaults( 0 ); }
	UBOOL IsChildOf( const UClass* SomeBase ) const
	{
		for( const UClass* TempClass = this; TempClass; TempClass = (const UClass*)TempClass->SuperField )
			if( TempClass == SomeBase )
				return 1;
		return 0;
	}
};
class UProperty : public UField
{
public:
	SWORD ArrayDim;                       // +0x30
	SWORD ElementSize;                    // +0x32
	DWORD PropertyFlags;                  // +0x34
	INT Pad38;
	INT Offset;                           // +0x3c
	virtual void P26(); virtual void P27(); virtual void P28(); virtual void P29();
	virtual void P30(); virtual void P31();
	virtual void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ); // +0x80
	virtual void ImportText();                                                                           // +0x84
	virtual UBOOL ExportText( INT ArrayElement, TCHAR* ValueStr, BYTE* Data, BYTE* Delta, INT PortFlags ); // +0x88
};
class UArrayProperty : public UProperty
{
public:
	BYTE Pad40[0x58 - 0x40];
	UProperty* Inner;                     // +0x58
	static UClass PrivateStaticClass;
	static UClass* StaticClass() { return &PrivateStaticClass; }
};

inline UBOOL IsAInline( const UObject* Obj, UClass* SomeBase )
{
	for( UClass* TempClass = Obj->Class; TempClass; TempClass = (UClass*)TempClass->SuperField )
		if( TempClass == SomeBase )
			return 1;
	return 0;
}

// TMap<FString,FString> (published at 0x14900, item 0082).
DWORD appStrihash( const TCHAR* Data );
extern const TCHAR EmptyString[];   // L"" shared in retail
class FString : public FArray
{
public:
	FString( const TCHAR* In );
	~FString();
	const TCHAR* operator*() const { return ArrayNum ? (const TCHAR*)Data : EmptyString; }
};
inline DWORD GetTypeHash( const FString& S ) { return appStrihash( *S ); }
struct TPair
{
	INT HashNext;
	FString Key;
	FString Value;
	__stdcall TPair( const TCHAR* InKey, const TCHAR* InValue ); // RVA 0x14f90 (`this` on the stack)
	~TPair();
};
class TPairArray : public FArray
{
public:
	TPair& operator()( INT i ) { return ((TPair*)Data)[i]; }
};
class TMapFString
{
public:
	TPairArray Pairs;
	INT* Hash;
	INT HashCount;
	void Rehash();
	FString& Add( const TCHAR* InKey, const TCHAR* InValue );
};
class FConfigSection : public TMapFString
{
public:
	// RVA 0x1f330; the link gives it `this` on the stack, callee cleans.
	INT __stdcall Remove( const TCHAR* Key );
};

class FConfigCache
{
public:
	virtual void C00(); virtual void C01(); virtual void C02(); virtual void C03(); virtual void C04();
	virtual FConfigSection* GetSectionPrivate( const TCHAR* Section, INT Unknown, UBOOL Force, UBOOL Const, const TCHAR* Filename ); // +0x14
	virtual void C06(); virtual void C07(); virtual void C08(); virtual void C09();
	virtual void SetString( const TCHAR* Section, INT Unknown, const TCHAR* Key, const TCHAR* Value, const TCHAR* Filename ); // +0x28
	virtual void Flush( UBOOL Read, const TCHAR* Filename = 0 );                                                       // +0x2c
};
extern FConfigCache* GConfig;             // 0x10c946c0

// RVA 0x20080: maps a package name to its file name (published with item 0098).
const TCHAR* GetLocalizedPackageName( FName Name );

// Retail keeps these TEXT() literals in writable data.
extern const TCHAR UbiAccountsText[];     // 0x10c6fa9c L"UbiAccounts"
extern const TCHAR UbiAccountsPathFmt[];  // 0x10c6fab4 L"%s\\UbiAccounts"
extern const TCHAR ArrayKeyFmt[];         // 0x10c6fad4 L"%s[%i]"
extern TCHAR GUbiAccountsDir[];           // 0x10c91f98
// The two TEXT("") initialisers of the value buffers (separate literals in
// writable data, 0x10c92600 and 0x10c92604).
extern const TCHAR EmptyValueText[];
extern const TCHAR EmptyBufferText[];

class FObjectIterator
{
public:
	__stdcall ~FObjectIterator();         // RVA 0x4a550 (folded empty `ret 4`)
	operator UBOOL() { return Index < Array->Num(); }
	UObject* operator*() { return (*Array)( Index ); }
	UObject* operator->() { return (*Array)( Index ); }
	TArray<UObject*>* Array;
	INT Index;
};
// RVA 0x4a550: empty in retail (folded `ret 4`, `this` on the stack). The
// stand-in body (scaffolding) only keeps the link from discarding the call.
void DestroyIteratorStandIn( INT );
__declspec(noinline) __stdcall FObjectIterator::~FObjectIterator()
{
	DestroyIteratorStandIn( 0 );
	DestroyIteratorStandIn( Index );
}
template<class T> class TObjectIterator : public FObjectIterator
{
public:
	// RVA 0x1f410 for UClass (this in ESI).
	__declspec(noinline) TObjectIterator()
	{
		Array = &UObject::GObjObjects;
		Index = -1;
		++*this;
	}
	void operator++()
	{
		while( ++Index < Array->Num() && (!(*Array)( Index ) || !IsAInline( (*Array)( Index ), T::StaticClass() )) );
	}
	T* operator*() { return (T*)(*Array)( Index ); }
	T* operator->() { return (T*)(*Array)( Index ); }
};

template<class T> class TFieldIterator
{
public:
	TFieldIterator( UStruct* InStruct )
	:	Struct( InStruct )
	,	Field( InStruct ? InStruct->Children : 0 )
	{
		IterateToNext();
	}
	operator UBOOL() { return Field != 0; }
	void operator++()
	{
		Field = Field->Next;
		IterateToNext();
	}
	T* operator*() { return (T*)Field; }
	T* operator->() { return (T*)Field; }
	// RVA 0x1f850 (out of line, this in ESI).
	__declspec(noinline) void IterateToNext()
	{
		while( Struct )
		{
			while( Field )
			{
				if( Field->Class->ClassFlags & CLASS_IsAUProperty )
					return;
				Field = Field->Next;
			}
			Struct = Struct->GetInheritanceSuper();
			if( Struct )
				Field = Struct->Children;
		}
	}
	UStruct* Struct;
	UField* Field;
};

// RVA 0x17010
void __stdcall UObject::SaveConfig( DWORD Flags, const TCHAR* InFilename, UBOOL Flush )
{
	UBOOL PerObject = ((GetClass()->ClassFlags & CLASS_PerObjectConfig) && GetIndex() != INDEX_NONE);
	const TCHAR* Filename
	=	InFilename ? InFilename
	:	(PerObject && Outer != GObjTransientPkg) ? *GetOuter()->GetFName()
	:	GetLocalizedPackageName( GetClass()->ClassConfigName );

	TCHAR FilenameBuf[400];
	appSprintf( FilenameBuf, Filename );
	if( wcsstr( FilenameBuf, UbiAccountsText ) )
		appSprintf( FilenameBuf, UbiAccountsPathFmt, GUbiAccountsDir );

	for( TFieldIterator<UProperty> It( GetClass() ); It; ++It )
	{
		DWORD PropertyFlags = It->PropertyFlags;
		if( (PropertyFlags & Flags) == Flags && PropertyFlags )
		{
			const TCHAR* Section;
			if( PerObject )
				Section = *GetFName();
			else if( PropertyFlags & CPF_GlobalConfig )
				Section = It->GetOwnerClass()->GetPathName();
			else
				Section = GetClass()->GetPathName();
			const TCHAR* Key = It->GetName();
			TCHAR SectionBuf[256];
			wcscpy( SectionBuf, Section );
			TCHAR Value[1024] = { EmptyValueText[0] };   // TEXT("")
			if( IsAInline( *It, UArrayProperty::StaticClass() ) )
			{
				FConfigSection* Sec = GConfig->GetSectionPrivate( SectionBuf, 0, 1, 0, FilenameBuf );
				Sec->Remove( Key );
				FArray* Array = (FArray*)((BYTE*)this + It->Offset);
				INT ElementSize = ((UArrayProperty*)*It)->Inner->ElementSize;
				for( INT i = 0; i < Array->Num(); i++ )
				{
					TCHAR Buffer[1024] = { EmptyBufferText[0] };   // TEXT("")
					BYTE* Elem = (BYTE*)Array->GetData() + i * ElementSize;
					((UArrayProperty*)*It)->Inner->ExportTextItem( Buffer, Elem, Elem, 0 );
					Sec->Add( Key, Buffer );
				}
			}
			else
			{
				TCHAR TempKey[256];
				for( INT Index = 0; Index < It->ArrayDim; Index++ )
				{
					if( It->ArrayDim != 1 )
					{
						appSprintf( TempKey, ArrayKeyFmt, It->GetName(), Index );
						Key = TempKey;
					}
					It->ExportText( Index, Value, (BYTE*)this, (BYTE*)this, 0 );
					GConfig->SetString( SectionBuf, 0, Key, Value, FilenameBuf );
				}
			}
		}
	}
	if( Flush )
		GConfig->Flush( 0 );

	UClass* BaseClass;
	for( BaseClass = GetClass(); BaseClass->GetSuperClass(); BaseClass = BaseClass->GetSuperClass() )
		if( !(BaseClass->GetSuperClass()->ClassFlags & CLASS_Config) )
			break;
	for( TObjectIterator<UClass> It; It; ++It )
		if( It->IsChildOf( BaseClass ) )
			It->GetDefaultObject()->LoadConfig( 1 );
}

// ---- Scaffolding for the link, not part of the unit: callees given bodies so
// the link gives them their retail conventions (published separately). ----
extern DWORD GCRCTable[256];
TCHAR appToUpper( TCHAR c );
DWORD appStrihash( const TCHAR* Data )
{
	DWORD Hash = 0;
	while( *Data )
	{
		TCHAR Ch = appToUpper( *Data++ );
		BYTE B = (BYTE)Ch;
		Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
		B = (BYTE)(Ch >> 8);
		Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
	}
	return Hash;
}
inline void* operator new( unsigned int Size, void* Mem ) { return Mem; }
// RVA 0x14900
FString& TMapFString::Add( const TCHAR* InKey, const TCHAR* InValue )
{
	TPair& Pair = *new( &((TPair*)Pairs.Data)[Pairs.Add( 1, sizeof(TPair) )] ) TPair( InKey, InValue );
	INT iHash = GetTypeHash( Pair.Key ) & (HashCount - 1);
	Pair.HashNext = Hash[iHash];
	Hash[iHash] = Pairs.ArrayNum - 1;
	if( HashCount * 2 + 8 < Pairs.ArrayNum )
	{
		HashCount *= 2;
		Rehash();
	}
	return Pair.Value;
}
TPair::~TPair() {}
void TMapFString::Rehash()
{
	INT* NewHash = (INT*)GMalloc->Malloc( HashCount * sizeof(INT), 0 );
	INT i;
	for( i = 0; i < HashCount; i++ )
		NewHash[i] = -1;
	for( i = 0; i < Pairs.ArrayNum; i++ )
	{
		TPair& Pair = Pairs( i );
		INT iHash = GetTypeHash( Pair.Key ) & (HashCount - 1);
		Pair.HashNext = NewHash[iHash];
		NewHash[iHash] = i;
	}
	if( Hash )
		GMalloc->Free( Hash );
	Hash = NewHash;
}
// RVA 0x20080
const TCHAR* GetLocalizedPackageName( FName Name );
void Escape( void* );
void Driver_17010( UObject* A, UObject* B, const TCHAR* F, DWORD Flags, TMapFString* M )
{
	M->Add( F, F );
	Escape( &GMalloc );
	Escape( &GConfig );
	Escape( &FName::Names );
	Escape( &UObject::GObjObjects );
	Escape( &UObject::GObjTransientPkg );
	A->SaveConfig();
	B->SaveConfig( Flags, F, 0 );
	A->SaveConfig( Flags, 0, 1 );
}
