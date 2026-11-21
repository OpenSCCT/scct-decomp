// Work item 0217: UByteProperty virtual methods (vtable UByteProperty@30c948),
// UnProp.cpp in UE2. Layout follows item 0220 (UBoolProperty).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned short _WORD;

#define CPF_Net 0x00000080

TCHAR* __cdecl appSprintf( TCHAR* Dest, const TCHAR* Fmt, ... );
extern "C" void* __cdecl appMemcpy_40a0( void* Dest, const void* Src, INT Count ); // RVA 0x40a0
extern "C" __declspec(dllimport) int __cdecl _wtoi( const TCHAR* S );

class FArchive
{
public:
	virtual ~FArchive();
	virtual void Serialize( void* V, INT Length );
	virtual void SerializeBits( void* V, INT LengthBits );
};
class UPackageMap;

struct FNameEntry
{
	INT Index;
	DWORD Flags;
	FNameEntry* HashNext;
	TCHAR Name[64];
};

enum EFindName { FNAME_Find, FNAME_Add, FNAME_Intrinsic };

class FName
{
public:
	INT Index;
	FName( const TCHAR* Name, EFindName FindType );   // RVA 0x1ff70
	static FNameEntry** Names;                        // FName::Names.Data, VA 0x10cc9e5c
	static FNameEntry* NameHash[4096];
	UBOOL operator==( const FName& Other ) const { return Index == Other.Index; }
	const TCHAR* operator*() const { return Names[Index]->Name; }
	INT GetIndex() const { return Index; }
	void SetFlags( DWORD F ) const { Names[Index]->Flags |= F; }
	UBOOL operator!=( INT Other ) const { return Index != Other; }
};

template<class T> class TArray
{
public:
	T* Data;
	INT ArrayNum;
	INT ArrayMax;
	INT Num() const { return ArrayNum; }
	T& operator()( INT i ) const { return Data[i]; }
	UBOOL FindItem( const T& Item, INT& Index ) const;  // RVA 0x57660 for FName
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
	virtual INT GetPropertiesSize();
};

class UClass;

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

class UEnum : public UField
{
public:
	TArray<FName> Names;   // +0x30
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

class UByteProperty : public UProperty
{
public:
	UEnum* Enum;   // +0x58

	INT Link( FArchive& Ar, UProperty* Prev );
	UBOOL Identical( const void* A, const void* B ) const;
	UBOOL NetSerializeItem( FArchive& Ar, UPackageMap* Map, void* Data ) const;
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	void CopyCompleteValue( void* Dest, void* Src, UObject* Obj ) const;
};

BYTE appCeilLogTwo( DWORD Arg );                       // RVA 0x12050
INT ExtractNumberMarker_11960( TCHAR* Str );           // RVA 0x11960
const TCHAR* ReadToken( const TCHAR* Buffer, TCHAR* String, INT MaxLen, UBOOL DottedNames ); // RVA 0x53ec0

extern const TCHAR Text_EnumExportFmt[];     // 0x10c51738
extern const TCHAR Text_EnumBadFmt[];        // 0x10c5175c
extern const TCHAR Text_EnumBadArg[];        // 0x10c51748
extern const TCHAR Text_ByteExportFmt[];     // 0x10c5176c

// RVA 0x543b0
INT UByteProperty::Link( FArchive& Ar, UProperty* Prev )
{
	ElementSize = sizeof(BYTE);
	Offset = GetOuterUField()->GetPropertiesSize();
	return Offset - GetOuterUField()->GetPropertiesSize();
}

// RVA 0x543f0
void UByteProperty::CopyCompleteValue( void* Dest, void* Src, UObject* Obj ) const
{
	if( ArrayDim == 1 )
		*(BYTE*)Dest = *(BYTE*)Src;
	else
		appMemcpy_40a0( Dest, Src, ArrayDim );
}

// RVA 0x54420
UBOOL UByteProperty::Identical( const void* A, const void* B ) const
{
	return *(BYTE*)A == (B ? *(BYTE*)B : 0);
}

// RVA 0x54470
UBOOL UByteProperty::NetSerializeItem( FArchive& Ar, UPackageMap* Map, void* Data ) const
{
	INT Bits;
	if( PropertyFlags & CPF_Net )
		Bits = Enum ? appCeilLogTwo( Enum->Names.Num() ) : ArrayDim * 8;
	else
		Bits = Enum ? appCeilLogTwo( Enum->Names.Num() ) : 8;
	Ar.SerializeBits( Data, Bits );
	return 1;
}

// RVA 0x544d0
void UByteProperty::ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const
{
	if( Enum )
	{
		if( *PropertyValue < Enum->Names.Num() )
		{
			FName N = Enum->Names( *PropertyValue );
			appSprintf( ValueStr, Text_EnumExportFmt, *N, N.GetIndex() );
			N.SetFlags( 0x20000000 );
		}
		else
			appSprintf( ValueStr, Text_EnumBadFmt, Text_EnumBadArg, 0 );
	}
	else
		appSprintf( ValueStr, Text_ByteExportFmt, *PropertyValue );
}

// RVA 0x54560
const TCHAR* UByteProperty::ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const
{
	if( Enum )
	{
		TCHAR Temp[1024];
		Buffer = ReadToken( Buffer, Temp, 1024, 0 );
		if( !Buffer )
			return 0;
		ExtractNumberMarker_11960( Temp );
		FName EnumName( Temp, FNAME_Find );
		if( EnumName != 0 )
		{
			INT EnumIndex = 0;
			if( Enum->Names.FindItem( EnumName, EnumIndex ) )
			{
				*Data = EnumIndex;
				return Buffer;
			}
		}
	}
	if( *Buffer >= '0' && *Buffer <= '9' )
	{
		*Data = _wtoi( Buffer );
		while( *Buffer >= '0' && *Buffer <= '9' )
			Buffer++;
		return Buffer;
	}
	return 0;
}

// Scaffolding for the LTCG link, not part of the unit: appCeilLogTwo is defined
// here only so the linker gives it the register convention retail uses (EDX).
extern const BYTE GLogs[256];   // VA 0x10c78bc8
__declspec(noinline) BYTE appCeilLogTwo( DWORD Arg )
{
	if( --Arg == (DWORD)-1 )
		return 0;
	BYTE Shift = Arg <= 0x10000 ? (Arg > 0x100 ? 8 : 0) : (Arg > 0x1000000 ? 24 : 16);
	return GLogs[Arg >> Shift] + Shift;
}
// Retail reaches these methods only through the vtable: taking their address
// keeps the standard thiscall convention.
void Escape( void* );
void Driver_54470()
{
	UBOOL (UByteProperty::*F)( FArchive&, UPackageMap*, void* ) const = &UByteProperty::NetSerializeItem;
	Escape( &F );
}

// Scaffolding for the LTCG link of ImportText, not part of the unit.
// ReadToken (0x53ec0), ExtractNumberMarker_11960, FName::FName (0x1ff70) and
// TArray<FName>::FindItem (0x57660) are separate retail functions; these /GL
// stand-ins (shared with item 0223) only let the linker pick the retail
// register conventions (ReadToken: Buffer EAX, MaxLen EDX, DottedNames ECX,
// String on the stack; FName::FName: this EBX, Name EAX). Only ImportText's
// bytes are compared.
extern "C" __declspec(dllimport) int __cdecl _wcsicmp( const TCHAR* A, const TCHAR* B );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcsstr( const TCHAR*, const TCHAR* );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcschr( const TCHAR*, TCHAR );
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen( const TCHAR* S );
extern "C" void* __cdecl memmove( void*, const void*, unsigned int );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcscpy( TCHAR* D, const TCHAR* S );
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
struct FArrayStandIn
{
	void* Data;
	INT ArrayNum;
	INT ArrayMax;
	INT Add( INT Count, INT ElementSize );
	void Remove( INT Index, INT Count, INT ElementSize );
};
extern FArrayStandIn FName_NamesArray;   // 0x10cc9e5c, FName::Names as an array
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
class FMallocStandIn
{
public:
	virtual void* Malloc( DWORD Count, const TCHAR* Tag ) = 0;
};
extern FMallocStandIn* GMalloc;
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
template<class T> __declspec(noinline) UBOOL TArray<T>::FindItem( const T& Item, INT& Index ) const
{
	for( Index=0; Index<ArrayNum; Index++ )
		if( (*this)(Index) == Item )
			return 1;
	return 0;
}
typedef const TCHAR* (UByteProperty::*ImportTextFn)( const TCHAR*, BYTE*, INT ) const;
void Driver_54560( UByteProperty* P, const TCHAR* Buffer, BYTE* Data, INT PortFlags, TCHAR* S, INT N, UBOOL D )
{
	Escape( &FName::Names );
	ImportTextFn F = &UByteProperty::ImportText;
	Escape( &F );
	(P->*F)( Buffer, Data, PortFlags );
	Escape( (void*)ReadToken( Buffer, S, N, D ) );
}
