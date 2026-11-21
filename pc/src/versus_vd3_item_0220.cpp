// Work item 0220: UBoolProperty virtual methods (vtable UBoolProperty@30d4c0).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef unsigned char BYTE;
typedef unsigned short _WORD;

#define FIRST_BITFIELD 1
#define NEXT_BITFIELD(b) ((b)<<1)

extern TCHAR GTrue[];
extern TCHAR GFalse[];
TCHAR* __cdecl appSprintf( TCHAR* Dest, const TCHAR* Fmt, ... );
extern "C" __declspec(dllimport) int __cdecl _wcsicmp( const TCHAR* A, const TCHAR* B );
// RVA 0x53ec0. Built with /GL; the linker gave it a register convention
// (Buffer in EAX, MaxLen in EDX, DottedNames in ECX, String on the stack).
const TCHAR* ReadToken( const TCHAR* Buffer, TCHAR* String, INT MaxLen, UBOOL DottedNames );

// Retail VC7.0 keeps these literals in writable .data, one copy per function.
extern const TCHAR Text_ExportTrue[];   // L"True",  VA 0x10c51788
extern const TCHAR Text_ExportFalse[];  // L"False", VA 0x10c51794
extern const TCHAR Text_ExportFmt[];    // L"%s",    VA 0x10c517a0
extern const TCHAR Text_Import1[];      // L"1",     VA 0x10c517a8
extern const TCHAR Text_ImportTrue[];   // L"True",  VA 0x10c517ac
extern const TCHAR Text_Import0[];      // L"0",     VA 0x10c517b8
extern const TCHAR Text_ImportFalse[];  // L"False", VA 0x10c517bc

class FArchive
{
public:
	virtual ~FArchive();
	virtual void Serialize( void* V, INT Length );
	INT IsLoading() { return ArIsLoading; }
	INT IsSaving()  { return ArIsSaving; }
	INT ArVer;
	INT ArNetVer;
	INT ArLicenseeVer;
	UBOOL ArIsLoading;
	UBOOL ArIsSaving;
};

class UClass;

// Outer of a property: a UStruct. Only the two virtuals used here are named.
class UStruct
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22();
	virtual UBOOL MergeBools();
	virtual void v24(); virtual void v25();
	virtual INT GetPropertiesSize();
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
	UStruct* Outer;
	DWORD ObjectFlags;
	INT Name;
	UClass* Class;
	UStruct* GetOuterUField() const { return Outer; }
};

class UField : public UObject
{
public:
	UField* SuperField;
	UField* Next;
};

class UClass : public UField
{
};

class UProperty : public UField
{
public:
	_WORD ArrayDim;
	_WORD ElementSize;
	DWORD PropertyFlags;
	INT Category;
	INT Offset;
	INT Pad40[6];
	void Serialize( FArchive& Ar );
};

class UBoolProperty : public UProperty
{
public:
	BITFIELD BitMask;
	static UClass PrivateStaticClass;
	static UClass* StaticClass() { return &PrivateStaticClass; }

	INT Link( FArchive& Ar, UProperty* Prev );
	void Serialize( FArchive& Ar );
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	UBOOL Identical( const void* A, const void* B ) const;
	void SerializeItem( FArchive& Ar, void* Value, INT MaxReadBytes ) const;
};

inline UBoolProperty* CastBool( UObject* Src )
{
	if( Src )
		for( UClass* C = Src->Class; C; C = (UClass*)C->SuperField )
			if( C == UBoolProperty::StaticClass() )
				return (UBoolProperty*)Src;
	return 0;
}

INT UBoolProperty::Link( FArchive& Ar, UProperty* Prev )
{
	UBoolProperty* PrevBool = CastBool( Prev );
	if( GetOuterUField()->MergeBools() && PrevBool && NEXT_BITFIELD(PrevBool->BitMask) )
	{
		Offset  = Prev->Offset;
		BitMask = NEXT_BITFIELD(PrevBool->BitMask);
	}
	else
	{
		Offset  = (GetOuterUField()->GetPropertiesSize() + 3) & ~3;
		BitMask = FIRST_BITFIELD;
	}
	ElementSize = sizeof(BITFIELD);
	if( Prev && Offset == Prev->Offset )
		return -1;
	return Offset - GetOuterUField()->GetPropertiesSize();
}

void UBoolProperty::Serialize( FArchive& Ar )
{
	UProperty::Serialize( Ar );
	if( !Ar.IsLoading() && !Ar.IsSaving() )
		Ar.Serialize( &BitMask, sizeof(BitMask) );
}

void UBoolProperty::ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const
{
	const TCHAR* Temp;
	if( PortFlags & 1 )
		Temp = (*(BITFIELD*)PropertyValue & BitMask) ? GTrue : GFalse;
	else
		Temp = (*(BITFIELD*)PropertyValue & BitMask) ? Text_ExportTrue : Text_ExportFalse;
	appSprintf( ValueStr, Text_ExportFmt, Temp );
}

const TCHAR* UBoolProperty::ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const
{
	TCHAR Temp[1024];
	Buffer = ReadToken( Buffer, Temp, 1024, 0 );
	if( !Buffer )
		return 0;
	if( _wcsicmp(Temp,Text_Import1)==0 || _wcsicmp(Temp,Text_ImportTrue)==0 || _wcsicmp(Temp,GTrue)==0 )
		*(BITFIELD*)Data |= BitMask;
	else if( _wcsicmp(Temp,Text_Import0)==0 || _wcsicmp(Temp,Text_ImportFalse)==0 || _wcsicmp(Temp,GFalse)==0 )
		*(BITFIELD*)Data &= ~BitMask;
	else
		return 0;
	return Buffer;
}

UBOOL UBoolProperty::Identical( const void* A, const void* B ) const
{
	return ((*(BITFIELD*)A ^ (B ? *(BITFIELD*)B : 0)) & BitMask) == 0;
}

void UBoolProperty::SerializeItem( FArchive& Ar, void* Value, INT MaxReadBytes ) const
{
	BYTE B = (*(BITFIELD*)Value & BitMask) ? 1 : 0;
	Ar.Serialize( &B, 1 );
	if( B )
		*(BITFIELD*)Value |= BitMask;
	else
		*(BITFIELD*)Value &= ~BitMask;
}

// Scaffolding for the LTCG link of ImportText, not part of the unit.
// ReadToken (0x53ec0) and its colour-code helper (0x53e80, copies a
// U+00A7 ... ')' run) are separate functions; these simplified stand-ins
// follow their shape so the linker picks the retail register convention
// (Buffer in EAX, MaxLength in EDX, DottedNames in ECX, String on the stack).
// Only ImportText's bytes are compared.
void Escape( void* );
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
typedef const TCHAR* (UBoolProperty::*ImportTextFn)( const TCHAR*, BYTE*, INT ) const;
void Driver_54d80( UBoolProperty* P, const TCHAR* Buffer, BYTE* Data, INT PortFlags, TCHAR* S, INT N, UBOOL D )
{
	Escape( (void*)GTrue );
	Escape( (void*)GFalse );
	ImportTextFn F = &UBoolProperty::ImportText;
	Escape( &F );
	(P->*F)( Buffer, Data, PortFlags );
	Escape( (void*)ReadToken( Buffer, S, N, D ) );
}
