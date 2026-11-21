// Work item 0073 (LTCG retry): Versus RVA 0x121c0-0x123f8.
// The Parse() family from Core's UnMisc.cpp (UE2): ParseParam and the
// Parse(Stream, Match, X) overloads for FString, UObject*, FName, DWORD and
// BYTE. These objects were built with /GL and linked with /LTCG, which gave
// them custom register conventions. The Core object-system declarations and
// callee bodies below are copied from work item 0099 (UnObj.cpp) so the link
// sees the same callees retail did.
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef short SWORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum EName { NAME_None = 0 };
enum EFindName { FNAME_Find = 0, FNAME_Add = 1, FNAME_Intrinsic = 2 };
enum { INDEX_NONE = -1 };
enum { CPF_Transient = 0x2000, CPF_Config = 0x4000 };
enum { CLASS_IsAUProperty = 0x8000 };
enum { RF_Native = 0x4000000 };

class UObject;
class UClass;
class UStruct;
class UField;
class UProperty;
class UObjectProperty;

class FArray
{
public:
	void* Data;
	INT ArrayNum;
	INT ArrayMax;
	INT Add( INT Count, INT ElementSize );
	void Remove( INT Index, INT Count, INT ElementSize );
	INT Num() const { return ArrayNum; }
};
template<class T> class TArray : public FArray
{
public:
	T& operator()( INT i ) { return ((T*)Data)[i]; }
	INT Add( INT Count = 1 ) { return FArray::Add( Count, sizeof(T) ); }
	void Remove( INT Index, INT Count = 1 ) { FArray::Remove( Index, Count, sizeof(T) ); }
	T Pop()
	{
		T Result = ((T*)Data)[ArrayNum - 1];
		Remove( ArrayNum - 1 );
		return Result;
	}
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
	FName( EName N ) : Index( N ) {}
	FName( const TCHAR* Name, EFindName FindType );
	INT GetIndex() const { return Index; }
	UBOOL operator==( const FName& Other ) const { return Index == Other.Index; }
	UBOOL operator!=( const FName& Other ) const { return Index != Other.Index; }
	static FNameEntry* NameHash[4096];
	static TArray<FNameEntry*> Names;
	static TArray<INT> Available;
};


extern DWORD GCRCTable[256];
extern "C" __declspec(dllimport) int __cdecl _wcsicmp( const TCHAR* A, const TCHAR* B );
inline TCHAR appToUpper( TCHAR c ) { return (c < 'a' || c > 'z') ? c : (TCHAR)(c + 'A' - 'a'); }
inline INT appStricmp( const TCHAR* A, const TCHAR* B ) { return _wcsicmp( A, B ); }
// RVA 0xf6b0 (out of line, string in EAX).
__declspec(noinline) DWORD appStrihash( const TCHAR* Data )
{
	DWORD Hash = 0;
	while( *Data )
	{
		TCHAR Ch = appToUpper( *Data++ );
		BYTE  B  = (BYTE)Ch;
		Hash     = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
		B        = (BYTE)(Ch >> 8);
		Hash     = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
	}
	return Hash;
}
class FMalloc
{
public:
	virtual void* Malloc( DWORD Count, const TCHAR* Tag ) = 0;
	virtual void* Realloc( void* Original, DWORD Count, const TCHAR* Tag ) = 0;
	virtual void Free( void* Original ) = 0;
};
extern FMalloc* GMalloc;
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen( const TCHAR* S );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcscpy( TCHAR* D, const TCHAR* S );
// RVA 0x3b590 (out of line, name in EDI).
__declspec(noinline) FNameEntry* AllocateNameEntry( const TCHAR* Name, DWORD Index, DWORD Flags, FNameEntry* HashNext )
{
	FNameEntry* NameEntry = (FNameEntry*)GMalloc->Malloc( sizeof(FNameEntry) + wcslen( Name ) * sizeof(TCHAR), (const TCHAR*)L"NameEntry" );
	NameEntry->Index    = Index;
	NameEntry->Flags    = Flags;
	NameEntry->HashNext = HashNext;
	wcscpy( NameEntry->Name, Name );
	return NameEntry;
}
void* appMemcpy( void* Dest, const void* Src, INT Count );
inline void appMemzero( void* Dest, INT Count )
{
	BYTE* D = (BYTE*)Dest;
	for( INT i = 0; i < Count; i++ ) D[i] = 0;
}

class UObject
{
public:
	virtual ~UObject();
	virtual void Virtual01();
	virtual void Virtual02();
	virtual void Virtual03();
	virtual void Virtual04();
	virtual void Virtual05();
	virtual void Virtual06();
	virtual void Virtual07();
	virtual void Virtual08();
	virtual void Virtual09();
	virtual void Virtual10();
	virtual void Virtual11();
	virtual void Virtual12();
	virtual void Virtual13();
	virtual void Virtual14();
	virtual void Virtual15();
	virtual void PostEditChange();
	virtual void Virtual17();
	virtual void Virtual18();
	virtual void Register();
	virtual void Virtual20();
	virtual void Virtual21();
	virtual void Virtual22();
	virtual void Virtual23();
	virtual void Virtual24();
	virtual void Virtual25();
	virtual void Virtual26();
	INT Index;
	UObject* HashNext;
	void* StateFrame;
	void* _Linker;
	INT _LinkerIndex;
	UObject* Outer;
	DWORD ObjectFlags;
	FName Name;
	UClass* Class;

	void AddObject( INT InIndex );
	void HashObject();
	UObject* GetOuter() const { return Outer; }
	const FName GetFName() const { return Name; }
	UBOOL IsA( UClass* SomeBase ) const;
	UBOOL IsIn( UObject* SomeOuter ) const;
	// RVA 0x17010. Its link-time convention takes `this` on the stack and pops
	// all four words (ret 0x10); declared __stdcall because the body is not
	// part of this unit.
	void __stdcall SaveConfig( DWORD Flags, const TCHAR* Filename, UBOOL Unknown );

	static UObject* StaticFindObject( UClass* ObjectClass, UObject* InObjectPackage, const TCHAR* OrigInName, UBOOL ExactClass );
	static UObject* StaticFindObject( UClass* ObjectClass, UObject* InObjectPackage, FName A, FName B, FName ObjectName, UBOOL ExactClass );
	static UBOOL ResolveName( UObject*& InPackage, const TCHAR* InName, TCHAR* OutName, UBOOL Create, UBOOL Throw );
	static UBOOL ResolveName( UObject*& InPackage, FName A, FName B, UBOOL Create, UBOOL Throw );
	static UObject* CreatePackage( UObject* InOuter, FName A, FName B, const TCHAR* PackageName );
	static void InitProperties( BYTE* Data, INT DataCount, UClass* DefaultsClass, BYTE* Defaults, INT DefaultsCount, UObject* DestObject, UObject* SuperObject );
	static void ExitProperties( BYTE* Data, UClass* Class );

	static TArray<UObject*> GObjObjects;
	static TArray<INT> GObjAvailable;
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
	UField* Children;
	INT Pad34[12];
	UProperty* ConstructorLink;
	virtual UStruct* GetInheritanceSuper();

};
class UClass : public UStruct
{
public:
	INT Pad68[8];
	DWORD ClassFlags;
	INT Pad8C[8];
	TArray<BYTE> Defaults;
};
class UProperty : public UField
{
public:
	SWORD ArrayDim;
	SWORD ElementSize;
	DWORD PropertyFlags;
	INT Pad38;
	INT Offset;
	INT Pad40[2];
	UProperty* ConstructorLinkNext;
	INT GetSize() const { return ArrayDim * ElementSize; }
	virtual void UPropertyVirtual27();
	virtual void UPropertyVirtual28();
	virtual void UPropertyVirtual29();
	virtual void UPropertyVirtual30();
	virtual void UPropertyVirtual31();
	virtual void UPropertyVirtual32();
	virtual void ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags );
	virtual void UPropertyVirtual34();
	virtual void CopySingleValue( void* Dest, void* Src, UObject* SuperObject );
	virtual void CopyCompleteValue( void* Dest, void* Src, UObject* SuperObject );
	virtual void DestroyValue( void* Dest );
};
class UObjectProperty : public UProperty
{
public:
	static UClass PrivateStaticClass;
	static UClass* StaticClass() { return &PrivateStaticClass; }
};

// UObject::IsA (out of line at 0x4bc0), inlined where retail inlines it.
inline UBOOL IsAInline( const UObject* Obj, UClass* SomeBase )
{
	if( !SomeBase )
		return 1;
	for( UClass* TempClass = Obj->Class; TempClass; TempClass = (UClass*)TempClass->SuperField )
		if( TempClass == SomeBase )
			return 1;
	return 0;
}

// RVA 0x159d0 (out of line, this in EAX, outer in ECX).
__declspec(noinline) UBOOL UObject::IsIn( UObject* SomeOuter ) const
{
	for( UObject* It = Outer; It; It = It->Outer )
		if( It == SomeOuter )
			return 1;
	return SomeOuter == 0;
}

// RVA 0x1ff70 (out of line, this in EBX, name in EAX).
__declspec(noinline) FName::FName( const TCHAR* Name, EFindName FindType )
{
	// If empty or invalid name was specified, return NAME_None.
	if( !Name[0] )
	{
		Index = NAME_None;
		return;
	}

	// Try to find the name in the hash.
	INT iHash = appStrihash( Name ) & 4095;
	for( FNameEntry* Hash = NameHash[iHash]; Hash; Hash = Hash->HashNext )
	{
		if( appStricmp( Name, Hash->Name ) == 0 )
		{
			Index = Hash->Index;
			if( FindType == FNAME_Intrinsic )
				Names( Index )->Flags |= RF_Native;
			return;
		}
	}

	// Didn't find name.
	if( FindType == FNAME_Find )
	{
		Index = NAME_None;
		return;
	}

	// Find an available entry in the name table.
	if( Available.Num() )
	{
		Index = Available( Available.Num() - 1 );
		Available.Remove( Available.Num() - 1 );
	}
	else
	{
		Index = Names.Add();
	}

	// Allocate and set the name.
	Names( Index ) = NameHash[iHash] = AllocateNameEntry( Name, Index, 0, NameHash[iHash] );
	if( FindType == FNAME_Intrinsic )
		Names( Index )->Flags |= RF_Native;
}

class FObjectIterator
{
public:
	FObjectIterator();
	// Empty out-of-line destructor, folded into the `ret 4` at 0x4a550; retail
	// calls it with `this` on the stack (link-time convention).
	~FObjectIterator();
	void operator++()
	{
		while( ++Index < Array->Num() && !(*Array)( Index ) );
	}
	UObject* operator*() { return (*Array)( Index ); }
	UObject* operator->() { return (*Array)( Index ); }
	operator UBOOL() { return Index < Array->Num(); }
	TArray<UObject*>* Array;
	INT Index;
};
// RVA 0x1f470 (out of line, this in EAX).
__declspec(noinline) FObjectIterator::FObjectIterator()
:	Array( &UObject::GObjObjects )
,	Index( -1 )
{
	++*this;
}

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
				if( ((UClass*)Field->Class)->ClassFlags & CLASS_IsAUProperty )
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

// The two ResolveName overloads live in the same link-time-generated program
// in retail; the optimiser sees that neither keeps the package reference,
// which lets StaticFindObject hold the resolved package in a register.
// Approximate bodies (scaffolding for that analysis, not matched here).
extern "C" __declspec(dllimport) TCHAR* __cdecl wcschr( const TCHAR* S, TCHAR C );
extern UClass PackageClass_ResolveName;
UBOOL FindPackageByName_1fcf0( UObject* InOuter, FName A, FName B, FName Name );
// RVA 0x1ab80 (approximation)
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
		if( Create )
			InPackage = CreatePackage( InPackage, NAME_None, NAME_None, PartialName );
		else
		{
			InPackage = StaticFindObject( &PackageClass_ResolveName, InPackage, NAME_None, NAME_None, FName( PartialName, FNAME_Find ), 0 );
			if( !InPackage )
				return 0;
		}
		InName = Dot + 1;
	}
	wcscpy( OutName, InName );
	return 1;
}
// RVA 0x1aaa0 (approximation)
UBOOL UObject::ResolveName( UObject*& InPackage, FName A, FName B, UBOOL Create, UBOOL Throw )
{
	if( A == NAME_None )
		return 1;
	if( Create )
	{
		InPackage = CreatePackage( InPackage, NAME_None, NAME_None, (const TCHAR*)A.Index );
		if( B != NAME_None )
			InPackage = CreatePackage( InPackage, NAME_None, NAME_None, (const TCHAR*)B.Index );
		return 1;
	}
	UObject* Found = StaticFindObject( &PackageClass_ResolveName, InPackage, NAME_None, NAME_None, A, 0 );
	if( !Found )
		return 0;
	InPackage = Found;
	if( B != NAME_None )
	{
		Found = StaticFindObject( &PackageClass_ResolveName, Found, NAME_None, NAME_None, B, 0 );
		if( !Found && !FindPackageByName_1fcf0( InPackage, NAME_None, NAME_None, B ) )
			return 0;
		InPackage = Found;
	}
	return 1;
}

// RVA 0x17630
__declspec(noinline) UObject* UObject::StaticFindObject( UClass* ObjectClass, UObject* InObjectPackage, const TCHAR* OrigInName, UBOOL ExactClass )
{
	UObject* ObjectPackage = InObjectPackage != ANY_PACKAGE ? InObjectPackage : 0;
	TCHAR InName[256];
	if( !ResolveName( ObjectPackage, OrigInName, InName, 0, 0 ) )
		return 0;

	FName ObjectName( InName, FNAME_Find );
	if( ObjectName != NAME_None )
	{
		INT iHash = ObjectName.GetIndex() & 4095;
		for( UObject* Hash = GObjHash[iHash]; Hash; Hash = Hash->HashNext )
		{
			if
			(	Hash->Name == ObjectName
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

// RVA 0x17720
__declspec(noinline) UObject* UObject::StaticFindObject( UClass* ObjectClass, UObject* InObjectPackage, FName A, FName B, FName ObjectName, UBOOL ExactClass )
{
	UObject* ObjectPackage = InObjectPackage != ANY_PACKAGE ? InObjectPackage : 0;
	if( !ResolveName( ObjectPackage, A, B, 0, 0 ) )
		return 0;

	INT iHash = ObjectName.GetIndex() & 4095;
	for( UObject* Hash = GObjHash[iHash]; Hash; Hash = Hash->HashNext )
	{
		if
		(	Hash->Name == ObjectName
		&&	(	(ObjectPackage == 0 && InObjectPackage == ANY_PACKAGE)
			||	Hash->Outer == ObjectPackage
			||	(InObjectPackage == ANY_PACKAGE && ObjectPackage && Hash->IsIn( ObjectPackage )) )
		&&	(	ObjectClass == 0
			||	(ExactClass ? Hash->Class == ObjectClass : Hash->IsA( ObjectClass )) ) )
			return Hash;
	}
	return 0;
}

// ---------------------------------------------------------------------------
// Callees from other Core units, defined here so the link gives them the
// retail conventions (they were /GL objects too). The FName constructor,
// appStrihash, AllocateNameEntry, IsIn, ResolveName and StaticFindObject
// above come from work item 0099 (0x1ff70 and 0x17630 match there).

extern "C" __declspec(dllimport) int __cdecl _wcsnicmp(const TCHAR *, const TCHAR *, unsigned int);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcsncpy(TCHAR *, const TCHAR *, unsigned int);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcsstr(const TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) unsigned long __cdecl wcstoul(const TCHAR *, TCHAR **, int);
extern "C" __declspec(dllimport) int __cdecl _wtoi(const TCHAR *);
extern "C" __declspec(dllimport) void *__cdecl memmove(void *, const void *, unsigned int);

inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
inline INT appStrnicmp(const TCHAR *A, const TCHAR *B, INT Count) { return _wcsnicmp(A, B, Count); }
inline TCHAR *appStrncpy(TCHAR *Dest, const TCHAR *Src, INT Max) { wcsncpy(Dest, Src, Max); Dest[Max - 1] = 0; return Dest; }
inline INT appAtoi(const TCHAR *S) { return _wtoi(S); }
inline DWORD appStrtoi(const TCHAR *S, TCHAR **End, INT Base) { return wcstoul(S, End, Base); }
inline UBOOL appIsDigit(TCHAR c) { return c >= '0' && c <= '9'; }

enum { NAME_SIZE = 64 };

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString &operator=(const TCHAR *Other);
};

extern const TCHAR Text_None[];        // L"NONE"
extern const TCHAR Text_FStringTag[];  // L"FString::="
extern const TCHAR Text_FArrayTag[];   // L"FArray"
extern const TCHAR Text_Quote[];       // double quote
extern const TCHAR Text_Space[];       // L" "
extern const TCHAR Text_CR[];          // carriage return
extern const TCHAR Text_LF[];          // line feed
extern const TCHAR Text_Tab[];         // tab
extern const TCHAR Text_Comma[];       // L","
extern const TCHAR Text_Empty[];       // L""
extern const TCHAR Text_NameNumber[];  // marker searched by 0x11960

#pragma auto_inline(off)

// 0x11f90: UE2 appStrfind (Str in EAX).
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find)
{
    UBOOL Alnum = 0;
    TCHAR f = (*Find < 'a' || *Find > 'z') ? (*Find) : (*Find + 'A' - 'a');
    INT Length = appStrlen(Find++) - 1;
    TCHAR c = *Str++;
    while (c)
    {
        if (c >= 'a' && c <= 'z')
            c += 'A' - 'a';
        if (!Alnum && c == f && !appStrnicmp(Str, Find, Length))
            return Str - 1;
        Alnum = (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
        c = *Str++;
    }
    return 0;
}

// 0x120e0: UE2 Parse(Stream, Match, Value, MaxLen) (Stream in EAX, Value in
// ESI, MaxLen in ECX).
UBOOL Parse(const TCHAR *Stream, const TCHAR *Match, TCHAR *Value, INT MaxLen)
{
    const TCHAR *Found = appStrfind(Stream, Match);
    if (!Found)
        return 0;
    const TCHAR *Start = Found + appStrlen(Match);
    if (*Start == 0x22)
    {
        appStrncpy(Value, Start + 1, MaxLen);
        TCHAR *Temp = wcsstr(Value, Text_Quote);
        if (Temp) *Temp = 0;
    }
    else
    {
        appStrncpy(Value, Start, MaxLen);
        TCHAR *Temp;
        Temp = wcsstr(Value, Text_Space);   if (Temp) *Temp = 0;
        Temp = wcsstr(Value, Text_CR);      if (Temp) *Temp = 0;
        Temp = wcsstr(Value, Text_LF);      if (Temp) *Temp = 0;
        Temp = wcsstr(Value, Text_Tab);     if (Temp) *Temp = 0;
        Temp = wcsstr(Value, Text_Comma);   if (Temp) *Temp = 0;
    }
    return 1;
}

// 0x4750: FString::operator= (this in ESI, Other in EDI).
FString &FString::operator=(const TCHAR *Other)
{
    if (Other != Data) {
        if (*Other == 0) {
            if (Data) { ArrayNum = 0; ArrayMax = 0; GMalloc->Free(Data); Data = 0; }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), Text_FStringTag);
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), Text_FArrayTag);
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}

// 0x11960: SCCT helper that strips a numbered suffix from a name in place
// (string in EAX). Neutral name; approximate body.
INT StripNameNumber_11960(TCHAR *Str)
{
    TCHAR *P = wcsstr(Str, Text_NameNumber);
    if (!P)
        return 0;
    *P = 0;
    P += 2;
    TCHAR *E = wcschr(P, ')');
    *E = 0;
    INT N = _wtoi(P);
    E++;
    memmove(P - 2, E, appStrlen(E) * 2 + 2);
    return N;
}

// ---- The unit: retail 0x121c0-0x123f8 (Core UnMisc.cpp) ----

// 0x121c0: UE2 ParseParam (Stream in EDI, Param in ESI).
UBOOL ParseParam(const TCHAR *Stream, const TCHAR *Param)
{
    const TCHAR *Start = Stream;
    if (*Stream)
    {
        while ((Start = appStrfind(Start + 1, Param)) != 0)
        {
            if (Start > Stream && (Start[-1] == '-' || Start[-1] == '/'))
                return 1;
        }
    }
    return 0;
}

// 0x12210: Parse into an FString.
UBOOL Parse(const TCHAR *Stream, const TCHAR *Match, FString &Value)
{
    TCHAR Temp[4096] = { Text_Empty[0] }; // TEXT(""), kept in writable data
    if (Parse(Stream, Match, Temp, 4096))
    {
        Value = Temp;
        return 1;
    }
    return 0;
}

// 0x12280: UE2 ParseObject (Match in EAX, DestRes in EDI).
UBOOL ParseObject(const TCHAR *Stream, const TCHAR *Match, UClass *Class, UObject *&DestRes, UObject *InParent)
{
    TCHAR TempStr[512];
    if (!Parse(Stream, Match, TempStr, NAME_SIZE))
        return 0;
    else if (appStricmp(TempStr, Text_None) == 0)
    {
        DestRes = 0;
        return 1;
    }
    else
    {
        UObject *Res = UObject::StaticFindObject(Class, InParent, TempStr, 0);
        if (!Res)
            return 0;
        DestRes = Res;
        return 1;
    }
}

// 0x12310: Parse into an FName (Match in EAX).
UBOOL Parse(const TCHAR *Stream, const TCHAR *Match, FName &Name)
{
    TCHAR TempStr[NAME_SIZE];
    if (!Parse(Stream, Match, TempStr, NAME_SIZE))
        return 0;
    StripNameNumber_11960(TempStr);
    Name = FName(TempStr, FNAME_Add);
    return 1;
}

// 0x12370: Parse a DWORD (Stream in EAX, Match in EDI).
UBOOL Parse(const TCHAR *Stream, const TCHAR *Match, DWORD &Value)
{
    const TCHAR *Temp = appStrfind(Stream, Match);
    TCHAR *End;
    if (Temp == 0)
        return 0;
    Value = appStrtoi(Temp + appStrlen(Match), &End, 10);
    return 1;
}

// 0x123b0: Parse a BYTE (Stream in EAX, Match in EDI).
UBOOL Parse(const TCHAR *Stream, const TCHAR *Match, BYTE &Value)
{
    const TCHAR *Temp = appStrfind(Stream, Match);
    if (Temp == 0)
        return 0;
    Temp += appStrlen(Match);
    Value = (BYTE)appAtoi(Temp);
    return Value != 0 || appIsDigit(Temp[0]);
}
#pragma auto_inline(on)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Escape(UBOOL);
extern UClass DriverClassA, DriverClassB;
// StaticFindObject and FName's constructor have many callers in retail
// (adapted from item 0099's Driver_17630).
void EscapeObjectHelpers(UObject *O, const TCHAR *N, const TCHAR *M, UBOOL E)
{
    UBOOL (*ResolveByString)( UObject*&, const TCHAR*, TCHAR*, UBOOL, UBOOL ) = &UObject::ResolveName;
    UBOOL (*ResolveByName)( UObject*&, FName, FName, UBOOL, UBOOL ) = &UObject::ResolveName;
    Escape( (void*)ResolveByString );
    Escape( (void*)ResolveByName );
    Escape( &UObject::GObjHash );
    UObject* R = UObject::StaticFindObject( &DriverClassA, ANY_PACKAGE, N, 0 );
    if( !R )
        R = UObject::StaticFindObject( &DriverClassB, O, M, E );
    if( !R )
        R = UObject::StaticFindObject( &DriverClassA, O, N, 1 );
    Escape( R );
}
void Driver_121c0(const TCHAR *Stream, const TCHAR *Param) { Escape(ParseParam(Stream, Param)); }
void Driver_12210(const TCHAR *Stream, const TCHAR *Match, FString *Value) { Escape(&GMalloc); Escape(Parse(Stream, Match, *Value)); }
void Driver_12280(const TCHAR *Stream, const TCHAR *Match, UClass *Class, UObject **Dest, UObject *Parent, const TCHAR *M, UBOOL E)
{
    EscapeObjectHelpers(Parent, Stream, M, E);
    Escape(ParseObject(Stream, Match, Class, *Dest, Parent));
}
void Driver_12310(const TCHAR *Stream, const TCHAR *Match, FName *Name, UObject *Parent, const TCHAR *M, UBOOL E)
{
    EscapeObjectHelpers(Parent, Stream, M, E);
    Escape(Parse(Stream, Match, *Name));
}
void Driver_12370(const TCHAR *Stream, const TCHAR *Match, DWORD *Value) { Escape(Parse(Stream, Match, *Value)); }
void Driver_123b0(const TCHAR *Stream, const TCHAR *Match, BYTE *Value) { Escape(Parse(Stream, Match, *Value)); }
