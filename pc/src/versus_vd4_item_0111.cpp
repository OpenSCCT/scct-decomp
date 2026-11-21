// Work item 0111: Versus RVA 0x1d2d0-0x1d372, Core UnObj.cpp object hash.
// 0x1d2d0 UObject::UnhashObject(INT OuterIndex) and 0x1d310
// UObject::AddObject(INT InIndex) with HashObject() inlined. GObjHash is the
// 4096-bin table at 0x10c790d8; GObjObjects/GObjAvailable are the TArrays at
// 0x10cc9e80/0x10cc9e8c. Retail passes `this` in EDX/ESI and InIndex in EAX:
// whole-program (LTCG) conventions, so these are checked with try_ltcg.py.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class FArray
{
public:
	void* Data;
	INT ArrayNum;
	INT ArrayMax;
	INT Num() const { return ArrayNum; }
	INT Add( INT Count, INT ElementSize );                    // 0x44e0
	void Remove( INT Index, INT Count, INT ElementSize );     // 0x119c0
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

class UClass;
class FStateFrame;
class ULinkerLoad;

enum { INDEX_NONE = -1 };
enum { OBJECT_HASH_BINS = 4096 };

class UObject
{
public:
	virtual ~UObject();
	INT Index;
	UObject* HashNext;
	FStateFrame* StateFrame;
	ULinkerLoad* _Linker;
	INT _LinkerIndex;
	UObject* Outer;
	DWORD ObjectFlags;
	INT Name;
	UClass* Class;

	void AddObject( INT InIndex );
	void HashObject();
	void UnhashObject( INT OuterIndex );

	static TArray<UObject*> GObjObjects;
	static TArray<INT> GObjAvailable;
	static UObject* GObjHash[OBJECT_HASH_BINS];
};

// The Versus hash ignores the outer and uses only the name index.
inline INT GetObjectHash( INT ObjName, INT Outer )
{
	return ObjName & (OBJECT_HASH_BINS - 1);
}

inline void UObject::HashObject()
{
	INT iHash = GetObjectHash( Name, Outer ? Outer->Index : 0 );
	HashNext = GObjHash[iHash];
	GObjHash[iHash] = this;
}

// RVA 0x1d2d0.
__declspec(noinline) void UObject::UnhashObject( INT OuterIndex )
{
	UObject** Hash = &GObjHash[GetObjectHash( Name, OuterIndex )];
	while( *Hash != 0 )
	{
		if( *Hash != this )
			Hash = &(*Hash)->HashNext;
		else
			*Hash = (*Hash)->HashNext;
	}
}

// RVA 0x1d310.
void UObject::AddObject( INT InIndex )
{
	if( InIndex == INDEX_NONE )
	{
		if( GObjAvailable.Num() )
			InIndex = GObjAvailable.Pop();
		else
			InIndex = GObjObjects.Add();
	}
	GObjObjects( InIndex ) = this;
	Index = InIndex;
	HashObject();
}

// Scaffolding for the link, not part of the unit.
void Escape( void* );
void Driver_1d2d0( UObject* Obj, INT OuterIndex )
{
	Escape( UObject::GObjHash );
	// Several call sites keep it out of line, as in retail.
	Obj->UnhashObject( OuterIndex );
	Escape( Obj );
	Obj->UnhashObject( OuterIndex + 1 );
	Escape( Obj );
	Obj->UnhashObject( OuterIndex + 2 );
}
void Driver_1d310( UObject* Obj, INT InIndex )
{
	Escape( UObject::GObjHash ); Escape( &UObject::GObjObjects ); Escape( &UObject::GObjAvailable );
	Obj->AddObject( InIndex );
}
