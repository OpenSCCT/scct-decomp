// Work item 0219 (LTCG part): UDelegateProperty::ImportText at RVA 0x54a00.
// The Core declarations and callee bodies (StaticFindObject, FName, IsIn,
// ResolveName, TFieldIterator) are copied from work item 0073_ltcg / 0099 so the
// link gives the callees the same register conventions retail has.
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
// UDelegateProperty (UnProp.cpp).

enum { CPF_OutParm = 0x100 };

inline const TCHAR* GetObjName( const UObject* Obj ) { return ((FNameEntry**)FName::Names.Data)[Obj->Name.Index]->Name; }

class UFunction : public UStruct
{
public:
	BYTE Pad68[0x79 - 0x68];
	BYTE NumParms;
};

class UObjectClassHolder
{
public:
	static UClass UObjectPrivateStaticClass;   // UObject::PrivateStaticClass
	static UClass UClassPrivateStaticClass;    // UClass::PrivateStaticClass
};

template<class T> inline T* FindObject( UObject* Package, const TCHAR* Name, UBOOL ExactClass = 0 )
{
	return (T*)UObject::StaticFindObject( &UObjectClassHolder::UObjectPrivateStaticClass, Package, Name, ExactClass );
}

// RVA 0x576f0 (out of line, owner in EAX, name in EBX). Approximate body.
template<class T> __declspec(noinline) T* FindField( UStruct* Owner, const TCHAR* FieldName )
{
	for( TFieldIterator<T> It( Owner ); It; ++It )
		if( appStricmp( GetObjName( *It ), FieldName ) == 0 )
			return *It;
	return 0;
}

struct FScriptDelegate
{
	UObject* Object;
	FName FunctionName;
};

class UDelegateProperty : public UProperty
{
public:
	// Virtual slot 33 in retail; declared non-virtual here so the driver can
	// take its address (the vtable is not emitted in this unit).
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* PropertyValue, INT PortFlags ) const;
};

const TCHAR* UDelegateProperty::ImportText( const TCHAR* Buffer, BYTE* PropertyValue, INT PortFlags ) const
{
	TCHAR ObjName[64];
	TCHAR FuncName[64];
	// Get object name.
	INT i;
	for( i=0; *Buffer && *Buffer != '.'; Buffer++ )
		ObjName[i++] = *Buffer;
	ObjName[i] = 0;
	// Get function name.
	if( *Buffer )
	{
		Buffer++;
		for( i=0; *Buffer; Buffer++ )
			FuncName[i++] = *Buffer;
		FuncName[i] = 0;
	}
	else
		FuncName[0] = 0;
	// Look up the object and the function.
	UObject* Obj = FindObject<UObject>( ANY_PACKAGE, ObjName );
	UFunction* Func = 0;
	if( Obj )
	{
		Func = FindField<UFunction>( IsAInline( Obj, &UObjectClassHolder::UClassPrivateStaticClass ) ? (UClass*)Obj : Obj->Class, FuncName );
		if( Func )
		{
			// Check the function's parameters against the delegate's signature
			// function: this property is named "__<Name>__Delegate".
			wcscpy( FuncName, GetObjName( this ) + 2 );
			FuncName[wcslen( FuncName ) - 10] = 0;
			UFunction* OtherFunc = FindField<UFunction>( (UStruct*)GetOuter(), FuncName );
			if( Func->NumParms == OtherFunc->NumParms )
			{
				INT Count = 0;
				for( TFieldIterator<UProperty> It1( Func ), It2( OtherFunc ); Count < OtherFunc->NumParms; ++It1, ++It2, ++Count )
				{
					if( It1->Class != It2->Class || (It1->PropertyFlags & CPF_OutParm) != (It2->PropertyFlags & CPF_OutParm) )
					{
						Func = 0;
						break;
					}
				}
			}
			else
				Func = 0;
		}
	}
	((FScriptDelegate*)PropertyValue)->Object = Func ? Obj : 0;
	((FScriptDelegate*)PropertyValue)->FunctionName = Func ? Func->GetFName() : FName( NAME_None );
	return Buffer;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
extern UClass DriverClassA, DriverClassB;
void Driver_54a00(UDelegateProperty *P, const TCHAR *B, BYTE *V, INT F, UObject *O, const TCHAR *N, const TCHAR *M, UBOOL E)
{
    UBOOL (*ResolveByString)( UObject*&, const TCHAR*, TCHAR*, UBOOL, UBOOL ) = &UObject::ResolveName;
    UBOOL (*ResolveByName)( UObject*&, FName, FName, UBOOL, UBOOL ) = &UObject::ResolveName;
    Escape( (void*)ResolveByString );
    Escape( (void*)ResolveByName );
    Escape( &UObject::GObjHash );
    Escape( &FName::Names );
    UObject* R = UObject::StaticFindObject( &DriverClassA, ANY_PACKAGE, N, 0 );
    if( !R )
        R = UObject::StaticFindObject( &DriverClassB, O, M, E );
    Escape( R );
    const TCHAR* (UDelegateProperty::*Import)( const TCHAR*, BYTE*, INT ) const = &UDelegateProperty::ImportText;
    Escape( *(void**)&Import );
    Escape( (void*)(P->*Import)( B, V, F ) );
}
