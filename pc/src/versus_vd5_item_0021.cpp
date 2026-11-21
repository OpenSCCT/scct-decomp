// Work item w3 0021: UObjectProperty::ImportText (RVA 0x55300), UnProp.cpp.
// vtable UObjectProperty@30c808 slot 33. Built /GL in retail: the callees it
// reaches (ReadToken, the number-marker helper, StaticFindObject,
// UStruct::IsChildOf, UObject::GetFullName and FOutputDevice::Logf) use
// link-time register conventions; their stand-in bodies sit at the end.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned short _WORD;

// Event names passed to Logf; the FName indices 0x237 / 0x246 are not
// identified, so the enumerator names are neutral.
enum EName { NAME_Error = 0x237, NAME_Warning = 0x246 };   // (names unconfirmed)
enum { PPF_CheckReferences = 4 };
enum { LOAD_NoWarn = 2 };

extern "C" __declspec(dllimport) int __cdecl _wcsicmp( const TCHAR* A, const TCHAR* B );

class FOutputDevice
{
public:
	virtual void Serialize( const TCHAR* V, EName Event ) = 0;
	virtual void Flush();
	void Logf( EName Event, const TCHAR* Fmt, ... );      // RVA 0x11850
};
extern FOutputDevice* GWarn;                              // VA 0x10c946bc

class UClass;
class UStruct;

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
	INT Name;
	UClass* Class;

	UClass* GetClass() const { return Class; }
	const TCHAR* GetFullName( TCHAR* Str = 0 ) const;    // RVA 0x15e10
	const TCHAR* GetPathName( UObject* StopOuter = 0, TCHAR* Str = 0 ) const;
	UBOOL IsA( UClass* SomeBase ) const;
	UBOOL IsIn( UObject* SomeOuter ) const;
	static UObject* StaticFindObject( UClass* Class, UObject* InOuter, const TCHAR* Name, UBOOL ExactClass = 0 ); // RVA 0x17630
	static UObject* StaticLoadObject( UClass* Class, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename, DWORD LoadFlags, void* Sandbox ); // RVA 0x1adb0
	static UBOOL ResolveName( UObject*& InPackage, const TCHAR* InName, TCHAR* OutName, UBOOL Create, UBOOL Throw );
	static UObject* GObjHash[4096];
};
#define ANY_PACKAGE ((UObject*)-1)

class UField : public UObject
{
public:
	UField* SuperField;
	UField* Next;
};

class UStruct : public UField
{
public:
	UBOOL IsChildOf( const UStruct* SomeBase ) const;     // RVA 0x158b0
};

class UClass : public UStruct
{
public:
	static UClass PrivateStaticClass;                     // VA 0x10cc9b18
};

class UProperty : public UField
{
public:
	short ArrayDim;
	_WORD ElementSize;
	DWORD PropertyFlags;
	INT Category;
	INT Offset;
	INT Pad40[6];
};

class UObjectProperty : public UProperty
{
public:
	UClass* PropertyClass;   // +0x58
	// Virtual (vtable slot 33) in retail; declared non-virtual here so the
	// driver can take its address and keep the standard thiscall convention.
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
};

const TCHAR* ReadToken( const TCHAR* Buffer, TCHAR* String, INT MaxLen, UBOOL DottedNames ); // RVA 0x53ec0
INT ExtractNumberMarker_11960( TCHAR* Str );               // RVA 0x11960

extern const TCHAR Text_None[];                  // 0x10c5183c "None"
extern const TCHAR Text_UnresolvedRef[];         // 0x10c51848 "%s: unresolved reference to '%s'"
extern const TCHAR Text_UnresolvedCast[];        // 0x10c5188c "%s: unresolved cast in '%s'"
extern const TCHAR Text_BadCast[];               // 0x10c518c4 "%s: bad cast in '%s'"
extern const TCHAR Text_UnresolvedRef2[];        // 0x10c518f0 "%s: unresolved reference to '%s'"

// RVA 0x55300
const TCHAR* UObjectProperty::ImportText( const TCHAR* InBuffer, BYTE* Data, INT PortFlags ) const
{
	TCHAR Temp[1024], Other[1024];
	const TCHAR* Buffer = ReadToken( InBuffer, Temp, 1024, 1 );
	if( !Buffer )
		return 0;
	ExtractNumberMarker_11960( Temp );
	if( _wcsicmp( Temp, Text_None ) == 0 )
	{
		*(UObject**)Data = 0;
	}
	else
	{
		while( *Buffer == ' ' )
			Buffer++;
		if( *Buffer++ != '\'' )
		{
			ExtractNumberMarker_11960( Temp );
			*(UObject**)Data = StaticFindObject( PropertyClass, ANY_PACKAGE, Temp );
			if( !*(UObject**)Data )
			{
				if( PortFlags & PPF_CheckReferences )
					GWarn->Logf( NAME_Error, Text_UnresolvedRef, GetFullName(), InBuffer );
				return 0;
			}
		}
		else
		{
			Buffer = ReadToken( Buffer, Other, 1024, 1 );
			if( !Buffer )
				return 0;
			if( *Buffer++ != '\'' )
				return 0;
			UClass* ObjectClass = (UClass*)StaticFindObject( &UClass::PrivateStaticClass, ANY_PACKAGE, Temp );
			if( !ObjectClass )
			{
				if( PortFlags & PPF_CheckReferences )
					GWarn->Logf( NAME_Warning, Text_UnresolvedCast, GetFullName(), InBuffer );
				return 0;
			}
			ExtractNumberMarker_11960( Other );
			ExtractNumberMarker_11960( Other );
			UObject* Obj = StaticFindObject( ObjectClass, ANY_PACKAGE, Other );
			if( !Obj )
				Obj = StaticLoadObject( ObjectClass, 0, Other, 0, LOAD_NoWarn, 0 );
			if( Obj && (PortFlags & PPF_CheckReferences) && !Obj->GetClass()->IsChildOf( PropertyClass ) )
				GWarn->Logf( NAME_Warning, Text_BadCast, GetFullName(), InBuffer );
			if( !Obj )
			{
				if( PortFlags & PPF_CheckReferences )
					GWarn->Logf( NAME_Error, Text_UnresolvedRef2, GetFullName(), InBuffer );
				*(UObject**)Data = Obj;
				return 0;
			}
			*(UObject**)Data = Obj;
		}
	}
	return Buffer;
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit. These /GL stand-ins for
// separate retail functions only let the linker pick the retail register
// conventions (ReadToken: Buffer EAX, MaxLen EDX, DottedNames ECX, String on
// the stack; ExtractNumberMarker: Str EAX; StaticFindObject: Name EDX;
// IsChildOf: this EAX, base ECX; GetFullName: this EDI, Str EAX; Logf: this
// EBX, Event EAX). Only ImportText's bytes are compared.
extern "C" __declspec(dllimport) TCHAR* __cdecl wcsstr( const TCHAR*, const TCHAR* );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcschr( const TCHAR*, TCHAR );
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen( const TCHAR* S );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcscpy( TCHAR* D, const TCHAR* S );
extern "C" void* __cdecl memmove( void*, const void*, unsigned int );
extern "C" __declspec(dllimport) int __cdecl _wtoi( const TCHAR* S );
__declspec(noinline) const TCHAR* CopyColorCode( const TCHAR* Buffer, TCHAR* String, INT& Count, INT MaxLength )
{
	TCHAR C = *Buffer;
	if( C == 0xa7 )
	{
		do
		{
			String[Count++] = C;
			C = *++Buffer;
		} while( C != ')' );
		String[Count++] = C;
		Buffer++;
	}
	return Buffer;
}
__declspec(noinline) const TCHAR* ReadToken( const TCHAR* Buffer, TCHAR* String, INT MaxLength, UBOOL DottedNames )
{
	INT Count = 0;
	if( *Buffer == '"' )
	{
		Buffer = CopyColorCode( Buffer+1, String, Count, MaxLength );
		while( *Buffer && *Buffer!='"' && *Buffer!=13 && *Buffer!=10 && Count<MaxLength-1 )
			String[Count++] = *Buffer++;
		if( Count==MaxLength-1 )
			return 0;
		if( *Buffer++ != '"' )
			return 0;
	}
	else
	{
		Buffer = CopyColorCode( Buffer, String, Count, MaxLength );
		while( *Buffer && *Buffer!=' ' && Count<MaxLength-1 && (DottedNames || *Buffer!='.') )
			String[Count++] = *Buffer++;
		if( Count==MaxLength-1 )
			return 0;
	}
	String[Count] = 0;
	return Buffer;
}
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
__declspec(noinline) UBOOL UStruct::IsChildOf( const UStruct* SomeBase ) const
{
	for( const UStruct* Struct = this; Struct; Struct = (const UStruct*)Struct->SuperField )
		if( Struct == SomeBase )
			return 1;
	return 0;
}
struct FNameEntry { INT Index; DWORD Flags; void* HashNext; TCHAR Name[64]; };
extern FNameEntry** FName_Names;
extern TCHAR appStaticString1024_Result[1024];   // local static of appStaticString1024
TCHAR* __cdecl appSprintf( TCHAR* Dest, const TCHAR* Fmt, ... );
extern const TCHAR Text_FullNameFmt[];
extern const TCHAR Text_FullNameNone[];
__declspec(noinline) const TCHAR* UObject::GetFullName( TCHAR* Str ) const
{
	TCHAR* Result = Str ? Str : appStaticString1024_Result;
	if( this )
	{
		appSprintf( Result, Text_FullNameFmt, FName_Names[((UObject*)Class)->Name]->Name );
		GetPathName( 0, Result + wcslen( Result ) );
	}
	else
		wcscpy( Result, Text_FullNameNone );
	return Result;
}
struct FMalloc
{
	virtual void* Malloc( DWORD Count, const TCHAR* Tag );
	virtual void* Realloc( void* Original, DWORD Count, const TCHAR* Tag );
	virtual void Free( void* Original );
};
extern FMalloc* GMalloc;
struct FArrayStandIn
{
	void* Data;
	INT ArrayNum;
	INT ArrayMax;
	INT Add( INT Count, INT ElementSize );
	void Remove( INT Index, INT Count, INT ElementSize );
};
extern FArrayStandIn FName_NamesArray;   // FName::Names
extern FArrayStandIn FName_Available;    // FName::Available
extern FNameEntry* FName_NameHash[4096];
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
struct FName
{
	INT Index;
	FName( const TCHAR* Name, INT FindType );   // RVA 0x1ff70
};
__declspec(noinline) FName::FName( const TCHAR* Name, INT FindType )
{
	if( !*Name )
	{
		Index = 0;
		return;
	}
	INT iHash = appStrihash( Name ) & 4095;
	for( FNameEntry* Hash = FName_NameHash[iHash]; Hash; Hash = (FNameEntry*)Hash->HashNext )
	{
		if( _wcsicmp( Name, Hash->Name ) == 0 )
		{
			Index = Hash->Index;
			if( FindType == 2 )
				((FNameEntry**)FName_NamesArray.Data)[Index]->Flags |= 0x4000000;
			return;
		}
	}
	if( FindType == 0 )
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
		Index = FName_NamesArray.Add( 1, 4 );
	((FNameEntry**)FName_NamesArray.Data)[Index] = FName_NameHash[iHash] = AllocateNameEntry( Name, Index, 0, FName_NameHash[iHash] );
	if( FindType == 2 )
		((FNameEntry**)FName_NamesArray.Data)[Index]->Flags |= 0x4000000;
}
__declspec(noinline) UBOOL UObject::IsIn( UObject* SomeOuter ) const
{
	for( UObject* It = Outer; It; It = It->Outer )
		if( It == SomeOuter )
			return 1;
	return SomeOuter == 0;
}
extern UClass PackageClass_ResolveName;
UObject* StaticFindObjectByFName_17720( UClass* ObjectClass, UObject* InObjectPackage, INT A, INT B, INT ObjectName, UBOOL ExactClass );
// Approximate body of UObject::ResolveName (RVA 0x1ab80); scaffolding only.
UBOOL UObject::ResolveName( UObject*& InPackage, const TCHAR* InName, TCHAR* OutName, UBOOL Create, UBOOL Throw )
{
	const TCHAR* Dot;
	while( (Dot = wcschr( InName, '.' )) != 0 )
	{
		TCHAR PartialName[256];
		INT i;
		for( i = 0; InName + i < Dot && i < 255; i++ )
			PartialName[i] = InName[i];
		PartialName[i] = 0;
		InPackage = StaticFindObjectByFName_17720( &PackageClass_ResolveName, InPackage, 0, 0, FName( PartialName, 0 ).Index, 0 );
		if( !InPackage )
			return 0;
		InName = Dot + 1;
	}
	wcscpy( OutName, InName );
	return 1;
}
__declspec(noinline) UObject* UObject::StaticFindObject( UClass* ObjectClass, UObject* InObjectPackage, const TCHAR* OrigInName, UBOOL ExactClass )
{
	UObject* ObjectPackage = InObjectPackage != ANY_PACKAGE ? InObjectPackage : 0;
	TCHAR InName[256];
	if( !ResolveName( ObjectPackage, OrigInName, InName, 0, 0 ) )
		return 0;
	FName ObjectName( InName, 0 );
	if( ObjectName.Index != 0 )
	{
		for( UObject* Hash = GObjHash[ObjectName.Index & 4095]; Hash; Hash = Hash->HashNext )
		{
			if
			(	Hash->Name == ObjectName.Index
			&&	(	(ObjectPackage == 0 && InObjectPackage == ANY_PACKAGE)
				||	Hash->Outer == ObjectPackage
				||	(InObjectPackage == ANY_PACKAGE && ObjectPackage && Hash->IsIn( ObjectPackage )) )
			&&	(	ObjectClass == 0
				||	(ExactClass ? Hash->Class == ObjectClass : Hash->IsA( ObjectClass )) ) )
				return Hash;
		}
	}
	return 0;
}
typedef char* va_list;
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf( TCHAR*, unsigned int, const TCHAR*, va_list );
extern "C" __declspec(dllimport) int __cdecl _wcsnicmp( const TCHAR*, const TCHAR*, unsigned int );
extern DWORD FName_Initialized;
extern const TCHAR Logf_Tag[];
extern TCHAR GCmdLine[];
extern const TCHAR Text_LogFlush_11850[];
__declspec(noinline) const TCHAR* appStrfind( const TCHAR* Str, const TCHAR* Find )
{
	UBOOL Alnum  = 0;
	TCHAR f      = (*Find < 'a' || *Find > 'z') ? (*Find) : (TCHAR)(*Find + 'A' - 'a');
	INT   Length = (INT)wcslen( Find++ ) - 1;
	TCHAR c      = *Str++;
	while( c )
	{
		if( c >= 'a' && c <= 'z' ) c += 'A' - 'a';
		if( !Alnum && c == f && !_wcsnicmp( Str, Find, Length ) )
			return Str - 1;
		Alnum = (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
		c = *Str++;
	}
	return 0;
}
__declspec(noinline) UBOOL ParseParam( const TCHAR* Stream, const TCHAR* Param )
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
__declspec(noinline) void FOutputDevice::Logf( EName Event, const TCHAR* Fmt, ... )
{
	if( !(FName_Initialized && (FName_Names[Event]->Flags & 0x1000)) )
	{
		TCHAR* Buffer = (TCHAR*)GMalloc->Malloc( 0x10000, Logf_Tag );
		_vsnwprintf( Buffer, 0x8000, Fmt, (va_list)&Fmt + sizeof(Fmt) );
		Serialize( Buffer, Event );
		GMalloc->Free( Buffer );
	}
	if( !ParseParam( GCmdLine, Text_LogFlush_11850 ) )
		Flush();
}
void Escape( void* );
extern UClass DriverClassB;
typedef const TCHAR* (UObjectProperty::*ImportTextFn)( const TCHAR*, BYTE*, INT ) const;
void Driver_55300( UObjectProperty* P, const TCHAR* Buffer, BYTE* Data, INT PortFlags, UObject* O, const TCHAR* M, UBOOL E )
{
	Escape( &GWarn );
	Escape( &UObject::GObjHash );
	UBOOL (*ResolveByString)( UObject*&, const TCHAR*, TCHAR*, UBOOL, UBOOL ) = &UObject::ResolveName;
	Escape( (void*)ResolveByString );
	Escape( UObject::StaticFindObject( &DriverClassB, O, M, E ) );
	ImportTextFn F = &UObjectProperty::ImportText;
	Escape( &F );
	(P->*F)( Buffer, Data, PortFlags );
}
