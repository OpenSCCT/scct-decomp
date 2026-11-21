// Work item 0279 (w3): Versus RVA 0xfd230-0xfd4f2.
// LTCG functions on one owner object holding two fixed tables of pointer
// arrays (255 at +0xe74, 20 at +0x1a68) and twenty name records at +0x2c.
// Class names are neutral: no vtable labels or strings identify these types.
typedef unsigned long DWORD;
typedef int INT;
typedef unsigned short TCHAR;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

extern const TCHAR EmptyString[];   // L"" at 0x10c10928
extern const TCHAR FArrayTag[];     // L"FArray" at 0x10c10974

// Element owned by the pointer arrays; slot 0 is the deleting destructor.
class UnnamedItem_fd230 {
public:
    virtual ~UnnamedItem_fd230();
};

// TArray<UnnamedItem_fd230*> with the owner's inline clean-up helpers.
struct UnnamedItemArray_fd230 {
    UnnamedItem_fd230 **Data;
    INT ArrayNum;
    INT ArrayMax;

    void Empty()
    {
        ArrayNum = 0;
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
    void Shrink()
    {
        if (ArrayMax != ArrayNum) {
            ArrayMax = ArrayNum;
            Data = (UnnamedItem_fd230 **)GMalloc->Realloc(Data, ArrayMax * sizeof(void *), FArrayTag);
        }
    }
    void DeleteAll()
    {
        INT i = ArrayNum - 1;
        if (i >= 0) {
            do {
                if (Data[i])
                    delete Data[i];
            } while (--i >= 0);
            Empty();
        }
    }
};

// FString-like storage.
struct UnnamedString_fd230 {
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    const TCHAR *operator*() const { return ArrayNum ? Data : EmptyString; }
    INT Len() const { return ArrayNum ? ArrayNum - 1 : 0; }
    void Empty()
    {
        ArrayNum = 0;
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};

struct UnnamedNameRecord_fd230 {      // 16 bytes, at +0x2c
    INT Used;
    UnnamedString_fd230 Name;
};



// ---- Types for 0xfd420 ----
typedef DWORD UBOOL;
enum EFindName { FNAME_Find, FNAME_Add, FNAME_Intrinsic };
class FName {
public:
    INT Index;
    FName(const TCHAR *Name, EFindName FindType);   // 0x1ff70 (this in EBX, Name in EAX)
    INT GetIndex() const { return Index; }
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
    static struct FNameEntry *NameHash[4096];
};
struct FNameEntry { INT Index; DWORD Flags; FNameEntry *HashNext; TCHAR Name[64]; };
typedef unsigned char BYTE;
enum { NAME_SIZE = 64 };

class UObject;
class UStruct;
struct FStateFrame {
    INT Reserved[6];
    UStruct *StateNode;         // +0x18
};
class UObject {
public:
    virtual ~UObject();
    INT Index;
    INT HashNext;
    FStateFrame *StateFrame;    // +0x0c
    INT Reserved[4];
    FName Name;                 // +0x20
    UStruct *Class;             // +0x24
};
struct FFieldHashEntry { UObject *Field; INT Next; };
struct FFieldHash { INT HashCount; FFieldHashEntry *Entries; };
class UStruct : public UObject {
public:
    UStruct *SuperField;            // +0x28
    unsigned char Pad2C[0x80 - 0x2c];
    FFieldHash FieldHash;           // +0x80
    DWORD Flags;                    // +0x88 (class flags when a UClass)
};
UObject *__stdcall FindFieldInHash(UStruct *Struct, FFieldHash *Hash, FName InName);  // 0x158d0
UBOOL ParseToken(const TCHAR *&Str, TCHAR *Result, INT MaxLen, UBOOL UseQuotes);     // 0x126c0
INT StripNameNumber_11960(TCHAR *Str);                                               // 0x11960

struct UnnamedContext_fd420 {
    INT Reserved[12];
    UObject *Object;                // +0x30
};

class UnnamedOwner_fd230;
void __stdcall LoadItems_fd500(UnnamedOwner_fd230 *Owner, const TCHAR *Key, UnnamedItemArray_fd230 *Out, INT Mode);

class UnnamedOwner_fd230 {
public:
    INT Header[11];
    UnnamedNameRecord_fd230 Names[20];      // +0x2c
    UnnamedString_fd230 Slots[255];        // +0x16c
    UnnamedContext_fd420 *Context;          // +0xd60
    INT Pad[68];
    UnnamedItemArray_fd230 SlotItems[255];  // +0xe74
    UnnamedItemArray_fd230 NameItems[20];   // +0x1a68
    INT Loaded;                             // +0x1b58

    void DeleteNameItems();
    void DeleteSlotItems();
    void LoadNames();
    void LoadSlots();
    UBOOL ParseFunctionName(const TCHAR *&Str, FName &OutName);
};

// 0xfd230
void UnnamedOwner_fd230::DeleteNameItems()
{
    for (INT i = 0; i < 20; i++)
        NameItems[i].DeleteAll();
}

// 0xfd290
void UnnamedOwner_fd230::DeleteSlotItems()
{
    for (INT i = 0; i < 255; i++)
        SlotItems[i].DeleteAll();
}

// 0xfd2f0
void UnnamedOwner_fd230::LoadNames()
{
    if (Loaded)
        return;
    for (INT i = 0; i < 20; i++) {
        if (Names[i].Used) {
            LoadItems_fd500(this, *Names[i].Name, &NameItems[i], 0);
            Names[i].Name.Empty();
            NameItems[i].Shrink();
        }
    }
    Loaded = 1;
}

// 0xfd3b0
void UnnamedOwner_fd230::LoadSlots()
{
    for (INT i = 0; i < 255; i++) {
        if (Slots[i].Len()) {
            LoadItems_fd500(this, *Slots[i], &SlotItems[i], 1);
            SlotItems[i].Shrink();
        }
    }
}

// 0xfd420 (near: retail tests Object in ECX and copies it to EDI after the
// prologue; this source loads EDI directly, 2 bytes shorter). Parses a name token and accept it when it names a field of the
// context object's current state or class whose class has flag 0x80000.
UBOOL UnnamedOwner_fd230::ParseFunctionName(const TCHAR *&Str, FName &OutName)
{
    const TCHAR *Original = Str;
    UObject *Object = Context->Object;
    if (Object) {
        TCHAR Token[NAME_SIZE];
        if (ParseToken(Str, Token, NAME_SIZE, 1)) {
            StripNameNumber_11960(Token);
            FName Name(Token, FNAME_Add);
            OutName = Name;
            if (Name.GetIndex()) {
                UObject *Field = 0;
                if (Object->StateFrame && Object->StateFrame->StateNode)
                    Field = FindFieldInHash(Object->StateFrame->StateNode, &Object->StateFrame->StateNode->FieldHash, Name);
                if (!Field)
                    Field = FindFieldInHash(Object->Class, &Object->Class->FieldHash, Name);
                if (Field && (Field->Class->Flags & 0x80000))
                    return 1;
            }
        }
    }
    Str = Original;
    return 0;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_fd230(UnnamedOwner_fd230 *O) { Escape(&GMalloc); O->DeleteNameItems(); }
void Driver_fd290(UnnamedOwner_fd230 *O) { Escape(&GMalloc); O->DeleteSlotItems(); }
void Driver_fd2f0(UnnamedOwner_fd230 *O) { Escape(&GMalloc); O->LoadNames(); }
void Driver_fd3b0(UnnamedOwner_fd230 *O) { Escape(&GMalloc); O->LoadSlots(); }


// Scaffolding for the LTCG link of 0xfd420, not part of the unit.
// ParseToken (0x126c0), StripNameNumber_11960, FName::FName (0x1ff70) and
// FindFieldInHash (0x158d0) are separate retail functions; these /GL
// stand-ins (FName and the strip helper adapted from published item 0217,
// FindFieldInHash from item 0091) only let the linker pick the retail register
// conventions (ParseToken: Str EAX, Result EBX; FName::FName: this EBX, Name
// EAX; FindFieldInHash: Struct EAX, Hash ECX). Only 0xfd420 is compared.
extern "C" __declspec(dllimport) int __cdecl _wtoi( const TCHAR* S );
// bytes are compared.
extern "C" __declspec(dllimport) int __cdecl _wcsicmp( const TCHAR* A, const TCHAR* B );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcsstr( const TCHAR*, const TCHAR* );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcschr( const TCHAR*, TCHAR );
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen( const TCHAR* S );
extern "C" void* __cdecl memmove( void*, const void*, unsigned int );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcscpy( TCHAR* D, const TCHAR* S );
extern const TCHAR Text_NumberMarker[];
__declspec(noinline) INT StripNameNumber_11960( TCHAR* Str )
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
__declspec(noinline) UBOOL ParseToken(const TCHAR *&Str, TCHAR *Result, INT MaxLen, UBOOL UseQuotes)
{
    INT Len = 0;
    while (*Str == ' ' || *Str == 9)
        Str++;
    if (UseQuotes && *Str == '"') {
        Str++;
        while (*Str && *Str != '"' && (Len + 1) < MaxLen) {
            TCHAR c = *Str++;
            if (c == '\\') {
                c = *Str++;
                if (!c)
                    break;
            }
            if ((Len + 1) < MaxLen)
                Result[Len++] = c;
        }
        if (*Str == '"')
            Str++;
    } else {
        for (; *Str && *Str != ' ' && *Str != 9; Str++)
            if ((Len + 1) < MaxLen)
                Result[Len++] = *Str;
    }
    Result[Len] = 0;
    return Len != 0;
}
__declspec(noinline) UObject *__stdcall FindFieldInHash(UStruct *Struct, FFieldHash *Hash, FName InName)
{
    for (;;) {
        if (Hash->HashCount) {
            FFieldHashEntry *Entry = &Hash->Entries[(Hash->HashCount - 1) & InName.GetIndex()];
            for (UObject *Field = Entry->Field; Field; Field = Entry->Field) {
                if (Field->Name == InName)
                    return Field;
                if (!Entry->Next)
                    break;
                Entry = &Hash->Entries[Entry->Next];
            }
        }
        UStruct *Super = Struct->SuperField;
        if (!Super)
            return 0;
        Struct = Super;
        Hash = &Struct->FieldHash;
    }
}
typedef UBOOL (UnnamedOwner_fd230::*ParseFn)(const TCHAR *&, FName &);
void Driver_fd420(UnnamedOwner_fd230 *O, const TCHAR *&S, FName &N, UStruct *T, FName M, TCHAR *B, INT L, UBOOL Q)
{
    ParseFn F = &UnnamedOwner_fd230::ParseFunctionName;
    Escape(&F);
    Escape(&FName::NameHash);
    Escape((void *)(O->*F)(S, N));
    Escape(FindFieldInHash(T, &T->FieldHash, M));
    Escape((void *)ParseToken(S, B, L, Q));
}
