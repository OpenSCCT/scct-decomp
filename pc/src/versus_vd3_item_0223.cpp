// Work item 0223: Versus RVA 0x55560-0x5578d (Core UnProp.cpp).
// UClassProperty::Serialize/ImportText, UNameProperty::Identical/ExportTextItem/
// ImportText, UStrProperty::Link. Names follow Unreal Engine 2 (vtable labels).
typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum EName { NAME_None = 0 };
enum EFindName { FNAME_Find = 0, FNAME_Add = 1 };
enum { CPF_Native = 0x1000, CPF_NeedCtorLink = 0x400000 };
enum { RF_TagExp = 0x20000000 };  // neutral: retail sets name flag 0x20000000 on export/import
enum { PPF_Delimited = 2 };

struct FNameEntry
{
    INT Index;
    DWORD Flags;
    FNameEntry *HashNext;
    TCHAR Name[1];
};

extern FNameEntry **FName_Names; // 0x10cc9e5c: FName::Names.Data

class FName
{
public:
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    FName(const TCHAR *Name, EFindName FindType);
    const TCHAR *operator*() const { return FName_Names[Index]->Name; }
    FNameEntry *GetEntry() const { return FName_Names[Index]; }
    void SetFlags(DWORD F) const { FName_Names[Index]->Flags |= F; }
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
};

class UObject;
class FArchive
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05();
    virtual FArchive &operator<<(UObject *&Res);
};

extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscat(TCHAR *, const TCHAR *);
INT __cdecl appSprintf(TCHAR *Dest, const TCHAR *Fmt, ...);

class UClass;

class UObject
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09();
    virtual void Serialize(FArchive &Ar);
    virtual void Slot11(); virtual void Slot12(); virtual void Slot13(); virtual void Slot14();
    virtual void Slot15(); virtual void Slot16(); virtual void Slot17(); virtual void Slot18();
    virtual void Slot19(); virtual void Slot20(); virtual void Slot21(); virtual void Slot22();
    virtual void Slot23(); virtual void Slot24(); virtual void Slot25();
    virtual INT GetPropertiesSize();          // slot 26 (UStruct)

    INT Index;              // +0x04
    UObject *HashNext;      // +0x08
    void *StateFrame;       // +0x0c
    void *_Linker;          // +0x10
    INT _LinkerIndex;       // +0x14
    UObject *Outer;         // +0x18
    DWORD ObjectFlags;      // +0x1c
    FName Name;             // +0x20
    UClass *Class;          // +0x24
};

class UField : public UObject
{
public:
    UField *SuperField;     // +0x28
    UField *Next;           // +0x2c
};

class UStruct : public UField
{
public:
    UBOOL IsChildOf(const UStruct *SomeBase) const
    {
        for (const UStruct *Struct = this; Struct; Struct = (const UStruct *)Struct->SuperField)
            if (Struct == SomeBase)
                return 1;
        return 0;
    }
};

class UClass : public UStruct
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class UProperty : public UField
{
public:
    _WORD ArrayDim;         // +0x30
    _WORD ElementSize;      // +0x32
    DWORD PropertyFlags;    // +0x34
    FName Category;         // +0x38
    INT Offset;             // +0x3c
    BYTE Pad40[0x58 - 0x40];

    void Serialize(FArchive &Ar);
};

class UObjectProperty : public UProperty
{
public:
    UClass *PropertyClass;  // +0x58
    const TCHAR *ImportText(const TCHAR *Buffer, BYTE *Data, INT PortFlags) const;
};

class UClassProperty : public UObjectProperty
{
public:
    UClass *MetaClass;      // +0x5c
    void Serialize(FArchive &Ar);
    const TCHAR *ImportText(const TCHAR *Buffer, BYTE *Data, INT PortFlags) const;
};

class UNameProperty : public UProperty
{
public:
    UBOOL Identical(const void *A, const void *B) const;
    void ExportTextItem(TCHAR *ValueStr, BYTE *PropertyValue, BYTE *DefaultValue, INT PortFlags) const;
    const TCHAR *ImportText(const TCHAR *Buffer, BYTE *Data, INT PortFlags) const;
};

class UStrProperty : public UProperty
{
public:
    INT Link(FArchive &Ar, UProperty *Prev);
};

void UClassProperty::Serialize(FArchive &Ar)
{
    UProperty::Serialize(Ar);
    Ar << (UObject *&)PropertyClass;
    Ar << (UObject *&)MetaClass;
}

const TCHAR *UClassProperty::ImportText(const TCHAR *Buffer, BYTE *Data, INT PortFlags) const
{
    const TCHAR *Result = UObjectProperty::ImportText(Buffer, Data, PortFlags);
    if (Result) {
        // Validate metaclass.
        UClass *&C = *(UClass **)Data;
        if ((C && C->Class != UClass::StaticClass()) || !C->IsChildOf(MetaClass))
            C = 0;
    }
    return Result;
}

UBOOL UNameProperty::Identical(const void *A, const void *B) const
{
    return *(const FName *)A == (B ? *(const FName *)B : FName(NAME_None));
}

extern const TCHAR UNameProperty_QuotedFmt[];  // 0x10c51934
extern const TCHAR UNameProperty_NumberFmt[];  // 0x10c51940

void UNameProperty::ExportTextItem(TCHAR *ValueStr, BYTE *PropertyValue, BYTE *DefaultValue, INT PortFlags) const
{
    FName Temp = *(FName *)PropertyValue;
    Temp.SetFlags(RF_TagExp);
    if (!(PortFlags & PPF_Delimited))
        wcscpy(ValueStr, *Temp);
    else
        appSprintf(ValueStr, UNameProperty_QuotedFmt, *Temp);
    TCHAR Num[32];
    appSprintf(Num, UNameProperty_NumberFmt, Temp.Index);
    wcscat(ValueStr, Num);
}

// 0x53ec0: UnProp.cpp's static ReadToken helper (link-time register convention).
const TCHAR *ReadToken(const TCHAR *Buffer, TCHAR *String, INT MaxLen, UBOOL DottedNames);
// 0x11960: strips a numeric marker out of Str and returns it (neutral name, see item 0069).
INT ExtractNumberMarker_11960(TCHAR *Str);

const TCHAR *UNameProperty::ImportText(const TCHAR *Buffer, BYTE *Data, INT PortFlags) const
{
    TCHAR Temp[1024];
    Buffer = ReadToken(Buffer, Temp, 1024, 0);
    if (Temp[0] == '\'')
        Buffer = ReadToken(Buffer + 1, Temp, 1024, 0) + 1;
    if (!Buffer)
        return 0;
    ExtractNumberMarker_11960(Temp);
    FName Name(Temp, FNAME_Add);
    *(FName *)Data = Name;
    Name.SetFlags(RF_TagExp);
    return Buffer;
}

INT UStrProperty::Link(FArchive &Ar, UProperty *Prev)
{
    ElementSize = 12; // sizeof(FString)
    Offset = (((UStruct *)Outer)->GetPropertiesSize() + 3) & ~3;
    if (!(PropertyFlags & CPF_Native))
        PropertyFlags |= CPF_NeedCtorLink;
    return Offset - ((UStruct *)Outer)->GetPropertiesSize();
}

// Scaffolding for the LTCG link of UNameProperty::ImportText, not part of the unit.
// ReadToken (0x53ec0), ExtractNumberMarker_11960 and FName::FName (0x1ff70) are
// separate retail functions; these /GL stand-ins (copied from item 0217) only let
// the linker pick the retail register conventions.
extern "C" __declspec(dllimport) int __cdecl _wcsicmp( const TCHAR* A, const TCHAR* B );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcsstr( const TCHAR*, const TCHAR* );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcschr( const TCHAR*, TCHAR );
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen( const TCHAR* S );
extern "C" __declspec(dllimport) int __cdecl _wtoi( const TCHAR* S );
extern "C" void* __cdecl memmove( void*, const void*, unsigned int );
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
extern FNameEntry *FName_NameHash[4096]; // 0x10c7d4d8: FName::NameHash
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
		Index = NAME_None;
		return;
	}
	INT iHash = appStrihash( Name ) & 4095;
	for( FNameEntry* Hash = FName_NameHash[iHash]; Hash; Hash = Hash->HashNext )
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
		Index = NAME_None;
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
	((FNameEntry**)FName_NamesArray.Data)[Index] = FName_NameHash[iHash] = AllocateNameEntry( Name, Index, 0, FName_NameHash[iHash] );
	if( FindType == 2 )
		((FNameEntry**)FName_NamesArray.Data)[Index]->Flags |= 0x4000000;
}
void Escape( void* );
typedef const TCHAR* (UNameProperty::*ImportTextFn)( const TCHAR*, BYTE*, INT ) const;
void Driver_556b0( UNameProperty* P, const TCHAR* Buffer, BYTE* Data, INT PortFlags, TCHAR* S, INT N, UBOOL D )
{
	Escape( &FName_Names );
	ImportTextFn F = &UNameProperty::ImportText;
	Escape( &F );
	(P->*F)( Buffer, Data, PortFlags );
	Escape( (void*)ReadToken( Buffer, S, N, D ) );
}
