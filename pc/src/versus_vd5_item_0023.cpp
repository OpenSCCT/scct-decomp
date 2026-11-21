// Work item w3 0023: RVA 0x570c0 UStructProperty::ImportText (UnProp.cpp, UE2).
// vtable UStructProperty@30c628 slot 33. LTCG object (callees take registers).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

#define NAME_SIZE 64
#define PPF_Delimited 2

enum EName { NAME_None = 0, NAME_Error_237 = 0x237, NAME_Warning_246 = 0x246 };
enum EFindName { FNAME_Find, FNAME_Add, FNAME_Intrinsic };

extern "C" __declspec(dllimport) int __cdecl _wtoi( const TCHAR* S );

struct FNameEntry
{
	INT Index;
	DWORD Flags;
	FNameEntry* HashNext;
	TCHAR Name[64];
};

class FName
{
public:
	INT Index;
	FName() {}
	FName( const TCHAR* Name, EFindName FindType );   // RVA 0x1ff70
	static FNameEntry** Names;                        // FName::Names.Data, VA 0x10cc9e5c
	static FNameEntry* NameHash[4096];
	UBOOL operator==( const FName& Other ) const { return Index == Other.Index; }
	UBOOL operator!=( EName Other ) const { return Index != Other; }
	const TCHAR* operator*() const { return Names[Index]->Name; }
};

class FOutputDevice
{
public:
	virtual void Serialize( const TCHAR* V, EName Event );
	virtual void Flush();
	void Logf( EName Event, const TCHAR* Fmt, ... );   // RVA 0x11850
};
extern FOutputDevice* GWarn;   // VA 0x10c946bc

class UClass;
class UStruct;

class UObject
{
public:
	virtual ~UObject();
	INT Index;
	void* HashNext;
	void* StateFrame;
	void* _Linker;
	INT _LinkerIndex;
	UObject* Outer;
	DWORD ObjectFlags;
	FName Name;
	UClass* Class;
	const TCHAR* GetName() const { return *Name; }
};

class UField : public UObject
{
public:
	UField* SuperField;
	UField* Next;
};

class UStruct : public UField
{
public:
	UField* Children;   // +0x30
	virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08();
	virtual void s09(); virtual void s10(); virtual void s11(); virtual void s12();
	virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
	virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
	virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26();
	virtual UStruct* GetInheritanceSuper();   // slot 27, +0x6c
};

class UClass : public UStruct
{
public:
	INT Pad34[21];
	DWORD ClassCastFlags;   // +0x88
};

class UProperty : public UField
{
public:
	short ArrayDim;       // +0x30
	short ElementSize;    // +0x32
	DWORD PropertyFlags;
	INT Category;
	INT Offset;           // +0x3c
	INT GetSize() const { return ArrayDim * ElementSize; }

	virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
	virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12();
	virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
	virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
	virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
	virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32();
	virtual const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;  // slot 33, +0x84
	virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
	virtual UBOOL Port() const;   // slot 38, +0x98
};

class UStructProperty : public UProperty
{
public:
	INT Pad40[6];
	UStruct* Struct;   // +0x58
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
};

#define CLASS_IsAUProperty 0x8000
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
	// RVA 0x1f850 (out of line, this in ESI); scaffolding body, not compared.
	__declspec(noinline) void IterateToNext()
	{
		while( Struct )
		{
			while( Field )
			{
				if( Field->Class->ClassCastFlags & CLASS_IsAUProperty )
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

INT ExtractNumberMarker_11960( TCHAR* Str );   // RVA 0x11960 (Str in EAX)

extern const TCHAR Text_StructNoOpenParen[];     // 0x10c51c90
extern const TCHAR Text_StructBadIndex[];        // 0x10c51988
extern const TCHAR Text_StructNoEquals[];        // 0x10c519e0
extern const TCHAR Text_StructNegIndex[];        // 0x10c51a28
extern const TCHAR Text_StructIndexRange[];      // 0x10c51a78
extern const TCHAR Text_StructImportFailed[];    // 0x10c51ad4
extern const TCHAR Text_StructUnknownMember[];   // 0x10c51b08
extern const TCHAR Text_StructBadQuote[];        // 0x10c51b38
extern const TCHAR Text_StructBadParen[];        // 0x10c51b88
extern const TCHAR Text_StructUnclosedParen[];   // 0x10c51be0
extern const TCHAR Text_StructMissingClose[];    // 0x10c51c48

// RVA 0x570c0
const TCHAR* UStructProperty::ImportText( const TCHAR* InBuffer, BYTE* Data, INT PortFlags ) const
{
	const TCHAR* Buffer = InBuffer;
	if( *Buffer++ == '(' )
	{
		while( *Buffer != ')' )
		{
			// Member name.
			TCHAR Name[NAME_SIZE];
			INT Count = 0;
			while( Count < NAME_SIZE-1 && *Buffer && *Buffer != '=' && *Buffer != '[' )
				Name[Count++] = *Buffer++;
			Name[Count] = 0;

			// Optional array index.
			INT Index = 0;
			if( *Buffer == '[' )
			{
				const TCHAR* Start = ++Buffer;
				while( *Buffer >= '0' && *Buffer <= '9' )
					Buffer++;
				if( *Buffer++ != ']' )
				{
					GWarn->Logf( NAME_Warning_246, Text_StructBadIndex, InBuffer );
					return 0;
				}
				Index = _wtoi( Start );
			}
			if( *Buffer++ != '=' )
			{
				GWarn->Logf( NAME_Warning_246, Text_StructNoEquals, InBuffer );
				return 0;
			}
			if( Index < 0 )
			{
				GWarn->Logf( NAME_Warning_246, Text_StructNegIndex, InBuffer );
				return 0;
			}

			// Find the member.
			ExtractNumberMarker_11960( Name );
			FName ItemName( Name, FNAME_Find );
			if( ItemName != NAME_None )
			{
				for( TFieldIterator<UProperty> It(Struct); It; ++It )
				{
					UProperty* Property = *It;
					if( Property->Name == ItemName && Property->GetSize() && Property->Port() )
					{
						if( Index >= Property->ArrayDim )
						{
							GWarn->Logf( NAME_Warning_246, Text_StructIndexRange, InBuffer );
							return 0;
						}
						Buffer = Property->ImportText( Buffer, Data + Property->Offset + Index*Property->ElementSize, PortFlags | PPF_Delimited );
						if( !Buffer )
						{
							GWarn->Logf( NAME_Warning_246, Text_StructImportFailed, InBuffer );
							return 0;
						}
						goto Imported;
					}
				}
			}

			// Unknown member: skip its value.
			{
				GWarn->Logf( NAME_Warning_246, Text_StructUnknownMember, Name, GetName() );
				INT SubCount = 0;
				while( *Buffer && *Buffer != 10 && *Buffer != 13 && (SubCount > 0 || (*Buffer != ')' && *Buffer != ',')) )
				{
					if( *Buffer == '"' )
					{
						while( *Buffer && *Buffer != '"' && *Buffer != 10 && *Buffer != 13 )
							Buffer++;
						if( *Buffer != '"' )
						{
							GWarn->Logf( NAME_Warning_246, Text_StructBadQuote, InBuffer );
							return 0;
						}
					}
					else if( *Buffer == '(' )
						SubCount++;
					else if( *Buffer == ')' )
					{
						if( --SubCount < 0 )
						{
							GWarn->Logf( NAME_Warning_246, Text_StructBadParen, InBuffer );
							return 0;
						}
					}
					Buffer++;
				}
				if( SubCount > 0 )
				{
					GWarn->Logf( NAME_Warning_246, Text_StructUnclosedParen, InBuffer );
					return 0;
				}
			}
		Imported:
			if( *Buffer == ',' )
				Buffer++;
			else if( *Buffer != ')' )
			{
				GWarn->Logf( NAME_Warning_246, Text_StructMissingClose, InBuffer );
				return 0;
			}
		}
		return Buffer + 1;
	}
	GWarn->Logf( NAME_Error_237, Text_StructNoOpenParen, InBuffer );
	return 0;
}

// ---- Scaffolding for the LTCG link, not part of the unit. ----
// /GL stand-ins (from items 0157 and 0217) so the linker gives the retail
// callees their register conventions: Logf (this EBX, Event EAX),
// FName::FName (this EBX, Name EAX), 0x11960 (Str EAX), IterateToNext (ESI).
typedef char* va_list;
extern "C" int _vsnwprintf( TCHAR*, unsigned int, const TCHAR*, va_list );
class FMallocStandIn
{
public:
	virtual void* Malloc( DWORD Count, const TCHAR* Tag ) = 0;
	virtual void* Realloc( void* Original, DWORD Count, const TCHAR* Tag ) = 0;
	virtual void Free( void* Original ) = 0;
};
extern FMallocStandIn* GMalloc;
extern const TCHAR Logf_Tag[];
extern UBOOL GNamesInitialized;
extern TCHAR GCmdLine[];
extern const TCHAR Logf_FlushParam[];
const TCHAR* appStrfind( const TCHAR* Str, const TCHAR* Find );
UBOOL ParseParam( const TCHAR* Stream, const TCHAR* Param )
{
	const TCHAR* Start = Stream;
	if( *Stream )
	{
		while( (Start = appStrfind( Start + 1, Param )) != 0 )
		{
			if( Start > Stream && (Start[-1] == '-' || Start[-1] == '/') )
				return 1;
		}
	}
	return 0;
}
void FOutputDevice::Logf( EName Event, const TCHAR* Fmt, ... )
{
	if( !GNamesInitialized || !(FName::Names[Event]->Flags & 0x1000) )
	{
		TCHAR* TempStr = (TCHAR*)GMalloc->Malloc( 0x10000, Logf_Tag );
		_vsnwprintf( TempStr, 0x8000, Fmt, (va_list)(&Fmt + 1) );
		Serialize( TempStr, Event );
		GMalloc->Free( TempStr );
	}
	if( !ParseParam( GCmdLine, Logf_FlushParam ) )
		Flush();
}
extern "C" __declspec(dllimport) int __cdecl _wcsicmp( const TCHAR* A, const TCHAR* B );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcsstr( const TCHAR*, const TCHAR* );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcschr( const TCHAR*, TCHAR );
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen( const TCHAR* S );
extern "C" void* __cdecl memmove( void*, const void*, unsigned int );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcscpy( TCHAR* D, const TCHAR* S );
extern const TCHAR Text_NumberMarker[];
__declspec(noinline) INT ExtractNumberMarker_11960( TCHAR* Str )
{
	TCHAR* Marker = wcsstr( Str, Text_NumberMarker );
	INT Result = 0;
	if( Marker )
	{
		*Marker = 0;
		Marker += 2;
		TCHAR* Close = wcschr( Marker, ')' );
		*Close = 0;
		Result = _wtoi( Marker );
		Close++;
		memmove( Marker - 2, Close, (wcslen( Close ) + 1) * sizeof(TCHAR) );
	}
	return Result;
}
struct FArrayStandIn
{
	void* Data;
	INT ArrayNum;
	INT ArrayMax;
	INT Add( INT Count, INT ElementSize );
	void Remove( INT Index, INT Count, INT ElementSize );
};
extern FArrayStandIn FName_NamesArray;   // 0x10cc9e5c
extern FArrayStandIn FName_Available;    // 0x10cc9e68
extern DWORD GCRCTable[256];
__declspec(noinline) DWORD appStrihash( const TCHAR* Data )
{
	DWORD Hash = 0;
	while( *Data )
	{
		TCHAR Ch = *Data++;
		if( Ch >= 'a' && Ch <= 'z' )
			Ch -= 'a' - 'A';
		BYTE B = (BYTE)Ch;
		Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
		B = (BYTE)(Ch >> 8);
		Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
	}
	return Hash;
}
extern const TCHAR Text_NameEntry[];
__declspec(noinline) FNameEntry* AllocateNameEntry( const TCHAR* Name, INT Index, DWORD Flags, FNameEntry* HashNext )
{
	FNameEntry* NameEntry = (FNameEntry*)GMalloc->Malloc( sizeof(FNameEntry) + wcslen( Name ) * sizeof(TCHAR), Text_NameEntry );
	NameEntry->Index = Index;
	NameEntry->Flags = Flags;
	NameEntry->HashNext = HashNext;
	wcscpy( NameEntry->Name, Name );
	return NameEntry;
}
__declspec(noinline) FName::FName( const TCHAR* Name, EFindName FindType )
{
	if( !*Name )
	{
		Index = 0;
		return;
	}
	INT iHash = appStrihash( Name ) & 4095;
	for( FNameEntry* Hash = NameHash[iHash]; Hash; Hash = Hash->HashNext )
	{
		if( _wcsicmp( Name, Hash->Name ) == 0 )
		{
			Index = Hash->Index;
			if( FindType == 2 )
				((FNameEntry**)FName_NamesArray.Data)[Index]->Flags |= 0x4000000;
			return;
		}
	}
	if( FindType == FNAME_Find )
	{
		Index = 0;
		return;
	}
	if( FName_Available.ArrayNum )
	{
		Index = ((INT*)FName_Available.Data)[FName_Available.ArrayNum - 1];
		FName_Available.Remove( FName_Available.ArrayNum - 1, 1, 4 );
	}
	else
	{
		Index = FName_NamesArray.Add( 1, 4 );
	}
	((FNameEntry**)FName_NamesArray.Data)[Index] = NameHash[iHash] = AllocateNameEntry( Name, Index, 0, NameHash[iHash] );
	if( FindType == 2 )
		((FNameEntry**)FName_NamesArray.Data)[Index]->Flags |= 0x4000000;
}
void Escape( void* );
inline void* operator new( unsigned int, void* Mem ) { return Mem; }
void Driver_570c0( UStructProperty* P, const TCHAR* Buffer, BYTE* Data, INT PortFlags )
{
	Escape( &FName::Names );
	Escape( &GWarn );
	// Retail reaches ImportText only through the vtable: constructing the
	// object here emits the vtable, which keeps the thiscall convention.
	Escape( new( P ) UStructProperty );
	Escape( (void*)P->ImportText( Buffer, Data, PortFlags ) );
}
