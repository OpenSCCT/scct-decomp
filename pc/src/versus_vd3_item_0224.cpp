// Work item 0224: UStrProperty virtual methods (vtable UStrProperty@30d420)
// and two methods of UFixedArrayProperty (Inner at +0x58, Count at +0x5c;
// name inferred from layout and the neighbouring item 0225).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef short SWORD;

#define PPF_Delimited 2
#define CPF_Native    0x00001000
#define CPF_InitOuter 0x00400000

extern "C" __declspec(dllimport) int __cdecl _wcsicmp( const TCHAR* A, const TCHAR* B );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcscpy( TCHAR* D, const TCHAR* S );
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen( const TCHAR* S );
TCHAR* __cdecl appSprintf( TCHAR* Dest, const TCHAR* Fmt, ... );
void* appMemcpy( void* Dest, const void* Src, INT Count );
// RVA 0x53ec0. Built with /GL; register convention (Buffer in EAX, MaxLen
// in EDX, DottedNames in ECX, String on the stack).
const TCHAR* ReadToken( const TCHAR* Buffer, TCHAR* String, INT MaxLen, UBOOL DottedNames );

// Retail VC7.0 keeps these literals in writable .data.
extern const TCHAR Text_FStringEmpty[];   // L"" used by FString::operator*, VA 0x10c10928
extern const TCHAR Text_IdenticalEmpty[]; // L"" in UStrProperty::Identical, VA 0x10c92578
extern const TCHAR Text_QuotedFmt[];      // L"\"%s\"", VA 0x10c5194c
extern const TCHAR Text_FStringAssign[];  // L"FString::="
extern const TCHAR Text_FArray[];         // L"FArray"

class FMalloc
{
public:
	virtual void* Malloc( DWORD Count, const TCHAR* Tag );
	virtual void* Realloc( void* Original, DWORD Count, const TCHAR* Tag );
	virtual void Free( void* Original );
};
extern FMalloc* GMalloc;

class FString
{
public:
	TCHAR* Data;
	INT ArrayNum;
	INT ArrayMax;
	~FString();
	FString& operator=( const TCHAR* Other );
	const TCHAR* operator*() const { return ArrayNum ? Data : Text_FStringEmpty; }
};

class UObject;
class FArchive
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void Preload( UObject* Object );   // 0x10
};

class UStruct
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25();
	virtual INT GetPropertiesSize();           // 0x68
};

class UObject
{
public:
	virtual ~UObject();
	INT Index;
	void* HashNext;
	void* StateFrame;
	void* _Linker;
	INT _LinkerIndex;
	UStruct* Outer;       // +0x18
	DWORD ObjectFlags;
	INT Name;
	void* Class;
	UStruct* GetOuterUField() const { return Outer; }
};

class UField : public UObject
{
public:
	UField* SuperField;
	UField* Next;
};

class UProperty : public UField
{
public:
	SWORD ArrayDim;       // +0x30
	SWORD ElementSize;    // +0x32
	DWORD PropertyFlags;  // +0x34
	INT Category;         // +0x38
	INT Offset;           // +0x3c
	INT Pad40[6];

	virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26();
	virtual void DestroyValue( void* Dest ) const;          // 0x6c
	virtual INT Link( FArchive& Ar, UProperty* Prev );      // 0x70
};

class UStrProperty : public UProperty
{
public:
	UBOOL Identical( const void* A, const void* B ) const;
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	void DestroyValue( void* Dest ) const;
};

class UFixedArrayProperty : public UProperty
{
public:
	UProperty* Inner;   // +0x58
	INT Count;          // +0x5c
	void DestroyValue( void* Dest ) const;
	INT Link( FArchive& Ar, UProperty* Prev );
};

UBOOL UStrProperty::Identical( const void* A, const void* B ) const
{
	return _wcsicmp( **(const FString*)A, B ? **(const FString*)B : Text_IdenticalEmpty ) == 0;
}

void UStrProperty::ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const
{
	if( !(PortFlags & PPF_Delimited) )
		wcscpy( ValueStr, **(FString*)PropertyValue );
	else
		appSprintf( ValueStr, Text_QuotedFmt, **(FString*)PropertyValue );
}

const TCHAR* UStrProperty::ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const
{
	if( !(PortFlags & PPF_Delimited) )
	{
		*(FString*)Data = Buffer;
	}
	else
	{
		TCHAR Temp[4096];
		Buffer = ReadToken( Buffer, Temp, 4096, 0 );
		if( !Buffer )
			return 0;
		*(FString*)Data = Temp;
	}
	return Buffer;
}

void UStrProperty::DestroyValue( void* Dest ) const
{
	for( INT i=0; i<ArrayDim; i++ )
		((FString*)((BYTE*)Dest + i*ElementSize))->~FString();
}

void UFixedArrayProperty::DestroyValue( void* Dest ) const
{
	for( INT i=0; i<Count; i++ )
		Inner->DestroyValue( (BYTE*)Dest + i*ElementSize*ArrayDim );
}

INT UFixedArrayProperty::Link( FArchive& Ar, UProperty* Prev )
{
	Ar.Preload( Inner );
	Inner->Link( Ar, 0 );
	ElementSize = Inner->ElementSize * Count;
	Offset = (GetOuterUField()->GetPropertiesSize() + 3) & ~3;
	if( !(PropertyFlags & CPF_Native) )
		PropertyFlags |= Inner->PropertyFlags & CPF_InitOuter;
	return Offset - GetOuterUField()->GetPropertiesSize();
}

// Scaffolding for the LTCG link of ImportText, not part of the unit.
// FString::operator= (0x4750) and ReadToken (0x53ec0) are separate retail
// functions; these /GL definitions only let the linker pick the retail
// register conventions. CopyMarker matches retail 0x53e80 (try_ltcg, root
// Driver_55880); ReadToken is an approximation of 0x53ec0 and does not match.
void Escape( void* );
FString& FString::operator=( const TCHAR* Other )
{
	if( Other != Data ) {
		if( *Other == 0 ) {
			if( Data ) { ArrayNum = 0; ArrayMax = 0; GMalloc->Free(Data); Data = 0; }
		} else {
			if( Data == 0 ) {
				ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
				Data = (TCHAR*)GMalloc->Malloc( ArrayMax*sizeof(TCHAR), Text_FStringAssign );
			} else {
				ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
				Data = (TCHAR*)GMalloc->Realloc( Data, ArrayMax*sizeof(TCHAR), Text_FArray );
			}
			appMemcpy( Data, Other, ArrayNum*sizeof(TCHAR) );
		}
	}
	return *this;
}
// Retail ReadToken (0x53ec0, approximation) and its helper CopyMarker (0x53e80, matches),
// which copies a section-sign ... ")" localisation marker through unchanged.
extern const TCHAR Text_ReadTokenErr[];   // L"ReadToken: Bad quoted string", VA 0x10c516fc
#define NAME_Warning 0x237
class FOutputDevice
{
public:
	virtual void Serialize( const TCHAR* V, INT Event );
};
extern FOutputDevice* GLog;
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf( TCHAR* B, unsigned int N, const TCHAR* F, char* Args );
extern const TCHAR Text_DebugfTag[];
extern DWORD GNoSuppress;
extern DWORD* GSuppressTable;
// Stand-in for debugf (0x11850, built /GL; Event arrives in EAX).
__declspec(noinline) void debugf( INT Event, const TCHAR* Fmt, ... )
{
	if( GNoSuppress == 0 || !(GSuppressTable[Event] & 0x1000) )
	{
		TCHAR* Temp = (TCHAR*)GMalloc->Malloc( 0x10000, Text_DebugfTag );
		_vsnwprintf( Temp, 0x8000, Fmt, (char*)(&Fmt + 1) );
		GLog->Serialize( Temp, Event );
		GMalloc->Free( Temp );
	}
}
__declspec(noinline) const TCHAR* CopyMarker( const TCHAR* Buffer, TCHAR* String, INT& Count, INT MaxLength )
{
	if( *Buffer == 0xa7 )
	{
		do String[Count++] = *Buffer++; while( *Buffer != ')' );
		String[Count++] = *Buffer++;
	}
	return Buffer;
}
inline INT HexDigit( TCHAR C )
{
	if( C>='0' && C<='9' ) return C-'0';
	if( C>='a' && C<='f' ) return C-'a'+10;
	if( C>='A' && C<='F' ) return C-'A'+10;
	return 0;
}
inline UBOOL IsAlnum( TCHAR C ) { return (C>='a'&&C<='z') || (C>='A'&&C<='Z') || (C>='0'&&C<='9'); }
__declspec(noinline) const TCHAR* ReadToken( const TCHAR* Buffer, TCHAR* String, INT MaxLength, UBOOL DottedNames )
{
	INT Count = 0;
	if( *Buffer == '"' )
	{
		Buffer = CopyMarker( Buffer+1, String, Count, MaxLength );
		while( *Buffer && *Buffer!='"' && *Buffer!=13 && *Buffer!=10 && Count<MaxLength-1 )
		{
			if( *Buffer != '\\' )
				String[Count++] = *Buffer++;
			else if( Buffer[1] == '\\' )
			{
				String[Count++] = '\\';
				Buffer += 2;
			}
			else
			{
				String[Count++] = (TCHAR)(HexDigit(Buffer[1])*16 + HexDigit(Buffer[2]));
				Buffer += 3;
			}
			if( *Buffer == 0xa7 )
			{
				do String[Count++] = *Buffer++; while( *Buffer != ')' );
				String[Count++] = *Buffer++;
			}
		}
		if( Count == MaxLength-1 )
			return 0;
		if( *Buffer++ != '"' )
		{
			debugf( NAME_Warning, Text_ReadTokenErr );
			return 0;
		}
	}
	else if( IsAlnum(*Buffer) || *Buffer == 0xa7 )
	{
		Buffer = CopyMarker( Buffer, String, Count, MaxLength );
		while( (IsAlnum(*Buffer) || *Buffer=='_' || *Buffer=='-' || (DottedNames && *Buffer=='.')) && Count<MaxLength-1 )
		{
			String[Count++] = *Buffer++;
			if( *Buffer == 0xa7 )
			{
				do String[Count++] = *Buffer++; while( *Buffer != ')' );
				String[Count++] = *Buffer++;
			}
		}
		if( Count == MaxLength-1 )
			return 0;
	}
	else
	{
		String[0] = *Buffer;
		Count = 1;
	}
	Buffer = CopyMarker( Buffer, String, Count, MaxLength );
	String[Count] = 0;
	return Buffer;
}
typedef const TCHAR* (UStrProperty::*ImportTextFn)( const TCHAR*, BYTE*, INT ) const;
void Driver_55880( UStrProperty* P, const TCHAR* Buffer, BYTE* Data, INT PortFlags, TCHAR* S, INT N, UBOOL D, FString* F2, const TCHAR* T2 )
{
	Escape( &GMalloc );
	Escape( &GLog );
	ImportTextFn F = &UStrProperty::ImportText;
	Escape( &F );
	(P->*F)( Buffer, Data, PortFlags );
	Escape( (void*)ReadToken( Buffer, S, N, D ) );
	*F2 = T2;
}
