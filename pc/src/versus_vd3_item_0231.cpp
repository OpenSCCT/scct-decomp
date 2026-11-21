// Work item 0231: Versus RVA 0x56f20-0x570b1.
// UStructProperty::Serialize (identical-code-folded with the UByteProperty,
// UObjectProperty, UArrayProperty and UDelegateProperty versions, vtable
// slot 10) and UStructProperty::ExportTextItem (vtable slot 32), from Core's
// UnProp.cpp (UE2). ExportTextItem writes each member name as an FName
// reference ("%s\xa7(%i)=") and tags the name entry, a Versus change.
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef short SWORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum { CLASS_IsAUProperty = 0x8000 };
enum { PPF_Delimited = 2 };
enum { NAME_TagExport = 0x20000000 }; // FNameEntry flag set by Versus export.

class UObject;
class UClass;
class UStruct;
class UField;
class UProperty;

class FArray
{
public:
	void* Data;
	INT ArrayNum;
	INT ArrayMax;
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
	static TArray<FNameEntry*> Names;
	void SetFlags( DWORD F ) const { Names( Index )->Flags |= F; }
	INT GetIndex() const { return Index; }
	const TCHAR* operator*() const { return Names( Index )->Name; }
};

class FArchive
{
public:
	virtual ~FArchive();
	virtual void Virtual01();
	virtual void Virtual02();
	virtual void Virtual03();
	virtual void Virtual04();
	virtual void Virtual05();
	virtual FArchive& operator<<( UObject*& Res );
};

extern "C" __declspec(dllimport) TCHAR* __cdecl wcscat( TCHAR* D, const TCHAR* S );
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen( const TCHAR* S );
INT appSprintf( TCHAR* Dest, const TCHAR* Fmt, ... );
extern const TCHAR ExportTextItem_NameFmt[];      // L"%s\xa7(%i)="
extern const TCHAR ExportTextItem_NameIndexFmt[]; // L"\xa7(%i)[%i]="

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
	virtual void Serialize( FArchive& Ar );
	virtual void Virtual11();
	virtual void Virtual12();
	virtual void Virtual13();
	virtual void Virtual14();
	virtual void Virtual15();
	virtual void Virtual16();
	virtual void Virtual17();
	virtual void Virtual18();
	virtual void Virtual19();
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
	const FName GetFName() const { return Name; }
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
};
class UProperty : public UField
{
public:
	SWORD ArrayDim;
	SWORD ElementSize;
	DWORD PropertyFlags;
	INT Pad38;
	INT Offset;
	INT Pad40[6];
	void Serialize( FArchive& Ar );
	virtual void UPropertyVirtual27();
	virtual void UPropertyVirtual28();
	virtual void UPropertyVirtual29();
	virtual void UPropertyVirtual30();
	virtual void UPropertyVirtual31();
	virtual void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags );
	virtual void UPropertyVirtual33();
	virtual UBOOL ExportText( INT Index, TCHAR* ValueStr, BYTE* Data, BYTE* Delta, INT PortFlags );
	virtual void UPropertyVirtual35();
	virtual void UPropertyVirtual36();
	virtual void UPropertyVirtual37();
	virtual UBOOL Port();
};
class UStructProperty : public UProperty
{
public:
	UStruct* Struct;
	void Serialize( FArchive& Ar );
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags );
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

// RVA 0x56f20
void UStructProperty::Serialize( FArchive& Ar )
{
	UProperty::Serialize( Ar );
	Ar << *(UObject**)&Struct;
}

// RVA 0x56f40
void UStructProperty::ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags )
{
	INT Count = 0;
	for( TFieldIterator<UProperty> It( Struct ); It; ++It )
	{
		if( It->Port() )
		{
			for( INT Index = 0; Index < It->ArrayDim; Index++ )
			{
				TCHAR Value[65536];
				if( It->ExportText( Index, Value, PropertyValue, DefaultValue, PPF_Delimited ) )
				{
					Count++;
					if( Count == 1 )
						*ValueStr++ = '(';
					else
						*ValueStr++ = ',';
					// Versus writes the member as an FName reference and tags the name.
					if( It->ArrayDim == 1 )
					{
						ValueStr += appSprintf( ValueStr, ExportTextItem_NameFmt, *It->GetFName(), It->GetFName().GetIndex() );
						It->GetFName().SetFlags( NAME_TagExport );
					}
					else
					{
						ValueStr += appSprintf( ValueStr, ExportTextItem_NameIndexFmt, It->GetFName().GetIndex(), Index );
						It->GetFName().SetFlags( NAME_TagExport );
					}
					wcscat( ValueStr, Value );
					ValueStr += wcslen( Value );
				}
			}
		}
	}
	if( Count > 0 )
	{
		*ValueStr++ = ')';
		*ValueStr = 0;
	}
}

// Scaffolding for the link, not part of the unit. The local object makes the
// compiler emit the vtable, so the virtual keeps its thiscall convention.
void Escape( void* );
void Driver_56f40( UStructProperty* P, TCHAR* S, BYTE* A, BYTE* B, INT F, FArchive* Ar )
{
	Escape( &FName::Names );
	UStructProperty Local;
	Escape( &Local );
	P->ExportTextItem( S, A, B, F );
	P->Serialize( *Ar );
}
