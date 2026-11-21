// Work item w3 0284: Versus RVA 0xfea90-0xfef20 (UInput virtuals and a TMap).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};
template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
};

enum EName { NAME_None = 0 };
enum EFindName { FNAME_Find = 0, FNAME_Add = 1 };
class FName
{
public:
    INT Index;
    FName(const TCHAR *Name, EFindName FindType);   // 0x1091ff70 (this in EBX, Name in EAX)
    const TCHAR *operator*() const;
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
    UBOOL operator!=(EName Other) const { return Index != Other; }
};
struct FNameEntry
{
    INT Index;
    DWORD Flags;
    FNameEntry *HashNext;
    TCHAR Name[64];
};
inline INT appStrlen(const TCHAR *String) { return (INT)wcslen(String); }
extern TArray<FNameEntry *> FName_Names;         // 0x10cc9e5c, FName::Names
inline const TCHAR *FName::operator*() const { return FName_Names(Index)->Name; }

enum EInputKey { IK_None = 0, IK_MAX = 255 };

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;                 // 0x10c73bf0
extern TCHAR GEmptyTCHAR[];              // 0x10c10928, the empty string ""

class FString : public TArray<TCHAR>
{
public:
    FString() { Data = 0; ArrayNum = 0; ArrayMax = 0; }
    FString(const TCHAR *In);
    ~FString();                                  // 0x109048b0
    FString &operator=(const TCHAR *Other);      // 0x10904750 (this in ESI, Other in EDI)
    FString &operator=(const FString &Other);    // 0x10904800
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : GEmptyTCHAR; }
    TCHAR &operator[](INT i) { return ((TCHAR *)Data)[i]; }
    __declspec(noinline) FString Caps() const;   // 0x10940370 (this in ESI)
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
// 0x109128b0 (LangExt in EAX, Package in EBX, Key in EDI).
const TCHAR *Localize(const TCHAR *Section, const TCHAR *Key, const TCHAR *Package, const TCHAR *LangExt, UBOOL Optional);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *A, const TCHAR *B);
extern const TCHAR Text_KeyNames[];        // 0x10c48c4c, localization section
extern const TCHAR Text_KeyNamesPackage[]; // 0x10c48c3c, localization package
extern const TCHAR Text_UnknownKey[];      // 0x10c48c60, compared case-insensitively

// ---- Core field reflection (minimal layout) ----
class UClass;
class UStruct;
class UField
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26();
    virtual UStruct *GetInheritanceSuper();                   // +0x6c
    BYTE Pad04[0x24 - 0x04];
    UClass *Class;          // +0x24
    UField *SuperField;     // +0x28
    UField *Next;           // +0x2c
    UClass *GetClass() const { return Class; }
    UBOOL IsA(UClass *SomeBase) const;
};
class UStruct : public UField
{
public:
    UField *Children;       // +0x30
};
class UClass : public UStruct
{
};
inline UBOOL UField::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return 0;
}
enum { CPF_Input = 0x4 };
class UProperty : public UField
{
public:
    short ArrayDim;         // +0x30
    short ElementSize;      // +0x32
    DWORD PropertyFlags;    // +0x34
    FName Category;         // +0x38
    INT Offset;             // +0x3c
};
class UByteProperty : public UProperty
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};
class UFloatProperty : public UProperty
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};
template <class T> class TFieldIterator
{
public:
    UStruct *Struct;
    UField *Field;
    TFieldIterator(UStruct *InStruct) : Struct(InStruct), Field(InStruct ? InStruct->Children : 0) { IterateToNext(); }
    operator UBOOL() { return Field != 0; }
    void operator++() { Field = Field->Next; IterateToNext(); }
    T *operator->() { return (T *)Field; }
    // 0x109ff050 (UByteProperty) and 0x109ff0b0 (UFloatProperty): outside this
    // item; defined here only so the link passes the iterator in ESI.
    __declspec(noinline) void IterateToNext()
    {
        while (Struct) {
            while (Field) {
                if (Field->IsA(T::StaticClass()))
                    return;
                Field = Field->Next;
            }
            Struct = Struct->GetInheritanceSuper();
            if (Struct)
                Field = Struct->Children;
        }
    }
};

// UEnum: the EInputKey enumeration, its names at +0x30.
class UEnum : public UField
{
public:
    TArray<FName> Names;    // +0x30
};

class AActor : public UField
{
};
class UViewport : public UField
{
public:
    AActor *Actor;          // +0x30
    virtual void Slot28(); virtual void Slot29(); virtual void Slot30(); virtual void Slot31();
    virtual void Slot32(); virtual void Slot33(); virtual void Slot34(); virtual void Slot35();
    virtual void Slot36(); virtual void Slot37(); virtual void Slot38(); virtual void Slot39();
    virtual void Slot40(); virtual void Slot41(); virtual void Slot42(); virtual void Slot43();
    virtual void UpdateInput(UBOOL Reset, FLOAT DeltaSeconds);   // +0xb0
    virtual void Slot45(); virtual void Slot46(); virtual void Slot47(); virtual void Slot48();
    virtual void Slot49();
    // +0xc8: fills Result with the display text for Key (neutral name).
    virtual void GetKeyText_c8(EInputKey Key, FString &Result);
};
enum EInputAction { IST_None = 0 };

class UInput
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26(); virtual void Slot27();
    virtual void ResetInput();                                               // slot 28
    virtual const TCHAR *GetKeyName(EInputKey Key) const;                    // slot 29
    virtual void GetLocalizedKeyName(EInputKey Key, FString &Result);      // slot 30 (neutral name)
    virtual UBOOL FindKeyName(const TCHAR *KeyName, EInputKey &iKey) const;  // slot 31
    BYTE Pad[0xd60 - 4];
    UViewport *Viewport;       // 0xd60
    UEnum *InputKeys;          // 0xd64
    EInputAction Action;       // 0xd68
    FLOAT Delta;               // 0xd6c
    BYTE KeyDownTable[IK_MAX]; // 0xd70
    void SetInputAction(EInputAction NewAction) { Action = NewAction; }
    void SetInputDelta(FLOAT NewDelta) { Delta = NewDelta; }
};

// SCCT's appMemzero is a byte loop (as in item 0150); the compiler turns it into rep stos.
inline void appMemzero(void *Dest, INT Count)
{
    BYTE *D = (BYTE *)Dest;
    for (INT i = 0; i < Count; i++) D[i] = 0;
}

// RVA 0xfea90: UInput::ResetInput (UInput vtable slot 28).
void UInput::ResetInput()
{
    appMemzero(KeyDownTable, sizeof(KeyDownTable));

    // Reset all input bytes.
    for (TFieldIterator<UByteProperty> ItB(Viewport->Actor->GetClass()); ItB; ++ItB)
        if (ItB->PropertyFlags & CPF_Input)
            *(BYTE *)((BYTE *)Viewport->Actor + ItB->Offset) = 0;

    // Reset all input floats.
    for (TFieldIterator<UFloatProperty> ItF(Viewport->Actor->GetClass()); ItF; ++ItF)
        if (ItF->PropertyFlags & CPF_Input)
            *(FLOAT *)((BYTE *)Viewport->Actor + ItF->Offset) = 0;

    SetInputAction(IST_None);
    SetInputDelta(0.0);
    Viewport->UpdateInput(1, 0.0);
}

// RVA 0xfeba0: UInput::GetKeyName (UInput vtable slot 29).
const TCHAR *UInput::GetKeyName(EInputKey Key) const
{
    if (Key >= 0 && Key < IK_MAX)
        if (appStrlen(*InputKeys->Names(Key)) > 3)
            return *InputKeys->Names(Key) + 3;
    return L"";
}

// RVA 0xfec10: UInput vtable slot 30 (neutral name). Keys with a localized
// name are looked up in the localization files; the rest ask the viewport.
void UInput::GetLocalizedKeyName(EInputKey Key, FString &Result)
{
    if (Key >= 0 && Key < IK_MAX) {
        FString Name;
        if (Key == 1 || Key == 2 || Key == 4 || Key == 5 || Key == 6
            || Key == 0x13 || Key == 0x14 || Key == 9 || Key == 0xd || Key == 0x10
            || Key == 0x90 || Key == 0x1b
            || (Key >= 0xc8 && Key <= 0xd7) || (Key >= 0xe4 && Key <= 0xed)
            || (Key >= 0xf0 && Key <= 0xf3) || (Key >= 0x60 && Key <= 0x6f)
            || (Key >= 0x20 && Key <= 0x2f))
            Name = Localize(Text_KeyNames, GetKeyName(Key), Text_KeyNamesPackage, 0, 0);
        else
            Viewport->GetKeyText_c8(Key, Name);
        if (_wcsicmp(*Name, Text_UnknownKey) == 0)
            Name = GetKeyName(Key);
        Result = Name.Caps();
    } else {
        Result.Empty();
    }
}

extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscat(TCHAR *, const TCHAR *);
// 0x11960: strips a numeric marker out of Str and returns it (neutral name, see item 0069).
INT ExtractNumberMarker_11960(TCHAR *Str);
extern const TCHAR Text_IK_[];   // 0x10c48c70, L"IK_"

// RVA 0xfedf0: UInput::FindKeyName (UInput vtable slot 31).
UBOOL UInput::FindKeyName(const TCHAR *KeyName, EInputKey &iKey) const
{
    TCHAR Temp[256];
    wcscpy(Temp, Text_IK_);
    wcscat(Temp, KeyName);
    ExtractNumberMarker_11960(Temp);
    FName N(Temp, FNAME_Find);
    if (N != NAME_None) {
        TArray<FName> &Keys = InputKeys->Names;
        for (iKey = IK_None; iKey < Keys.Num(); iKey = (EInputKey)(iKey + 1))
            if (Keys(iKey) == N)
                return 1;
    }
    return 0;
}

// ---- 0xfee90 / 0xfeee0: a TMap with 4-byte keys and values ----
// The key and value types are unknown 4-byte values (GetTypeHash is the
// value itself); the map has a neutral name.
class FArrayM
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArrayM() : Data(0), ArrayNum(0), ArrayMax(0) {}
    void Remove(INT Index, INT Count, INT ElementSize);   // 0x109119c0
    INT Add(INT Count, INT ElementSize);                  // 0x109044e0
};
template <class T> class TArrayM : public FArrayM
{
public:
    TArrayM() {}
    ~TArrayM() { Remove(0, ArrayNum); }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArrayM::Remove(Index, Count, sizeof(T));
    }
};
inline void *operator new(unsigned int, void *Mem) { return Mem; }
template <class T> inline void *operator new(unsigned int Size, TArrayM<T> &Array)
{
    INT Index = Array.FArrayM::Add(1, Size);
    return &Array(Index);
}
inline DWORD GetTypeHash(DWORD A) { return A; }
extern const TCHAR Text_HashMapHash[];

template <class TK, class TI> class TMapBase
{
public:
    class TPair
    {
    public:
        INT HashNext;
        TK Key;
        TI Value;
        TPair(const TK &InKey, const TI &InValue) : Key(InKey), Value(InValue) {}
    };

    TArrayM<TPair> Pairs;
    INT *Hash;
    INT HashCount;

    // 0x109fef60 and 0x109fefe0: outside this item, defined here only so the
    // link gives them their retail conventions.
    __declspec(noinline) void Rehash()
    {
        INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), Text_HashMapHash);
        for (INT i = 0; i < HashCount; i++)
            NewHash[i] = -1;
        for (INT i = 0; i < Pairs.Num(); i++)
        {
            TPair &Pair = Pairs(i);
            INT iHash = GetTypeHash(Pair.Key) & (HashCount - 1);
            Pair.HashNext = NewHash[iHash];
            NewHash[iHash] = i;
        }
        if (Hash)
            GMalloc->Free(Hash);
        Hash = NewHash;
    }
    __declspec(noinline) TI &Add(const TK &InKey, const TI &InValue)
    {
        TPair &Pair = *new (Pairs) TPair(InKey, InValue);
        INT iHash = GetTypeHash(Pair.Key) & (HashCount - 1);
        Pair.HashNext = Hash[iHash];
        Hash[iHash] = Pairs.Num() - 1;
        if (HashCount * 2 + 8 < Pairs.Num())
        {
            HashCount *= 2;
            Rehash();
        }
        return Pair.Value;
    }

    // RVA 0xfee90 (this on the stack, ret 4).
    TMapBase() : Hash(0), HashCount(8) { Rehash(); }
    // RVA 0xfeee0 (this in EAX, Key in EDI, Value in EBX). Out of line in
    // retail; noinline stands in for the retail callers that kept it so.
    __declspec(noinline) TI &Set(const TK &InKey, const TI &InValue)
    {
        for (INT i = Hash[GetTypeHash(InKey) & (HashCount - 1)]; i != -1; )
        {
            TPair &Pair = Pairs(i);
            if (Pair.Key == InKey)
            {
                Pair.Value = InValue;
                return Pair.Value;
            }
            i = Pair.HashNext;
        }
        return Add(InKey, InValue);
    }
};
template <class TK, class TI> class TMap : public TMapBase<TK, TI>
{
};
typedef TMap<DWORD, DWORD> FUnnamedMap_fee90;

// ---- Scaffolding for the LTCG link, not part of the unit. ----
void Escape(void *);
const TCHAR *Driver_feba0(UInput *I, EInputKey K) { Escape(&FName_Names); return I->UInput::GetKeyName(K); }
UBOOL Driver_fedf0(UInput *I, const TCHAR *K, EInputKey *Out) { Escape(&FName_Names); return I->UInput::FindKeyName(K, *Out); }

// FName::FName (0x1ff70) and ExtractNumberMarker_11960 (0x11960) are separate
// retail functions; these /GL stand-ins (copied from item 0223) only let the
// linker pick the retail register conventions.
extern "C" __declspec(dllimport) TCHAR* __cdecl wcsstr( const TCHAR*, const TCHAR* );
extern "C" __declspec(dllimport) TCHAR* __cdecl wcschr( const TCHAR*, TCHAR );
extern "C" __declspec(dllimport) int __cdecl _wtoi( const TCHAR* S );
extern "C" void* __cdecl memmove( void*, const void*, unsigned int );
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
extern FMallocStandIn* GMallocStandIn;
extern const TCHAR Text_NameEntry[];
__declspec(noinline) FNameEntry* AllocateNameEntry( const TCHAR* Name, INT Index, DWORD Flags, FNameEntry* HashNext )
{
	FNameEntry* NameEntry = (FNameEntry*)GMallocStandIn->Malloc( sizeof(FNameEntry) + wcslen( Name ) * sizeof(TCHAR), Text_NameEntry );
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
FUnnamedMap_fee90 *Driver_fee90(void *Mem) { Escape(&GMalloc); return new (Mem) FUnnamedMap_fee90; }
void Driver_feee0(FUnnamedMap_fee90 *M, DWORD &K, DWORD &V) { Escape(&GMalloc); M->Set(K, V); }
void Driver_fea90(UInput *I) { I->UInput::ResetInput(); }
void Driver_fec10(UInput *I, EInputKey K, FString &R) { Escape(&GMalloc); Escape(&FName_Names); I->UInput::GetLocalizedKeyName(K, R); }

// FString::operator= (0x4750), FString::Caps (0x40370) and Localize (0x128b0)
// are separate retail functions; these /GL stand-ins only let the linker pick
// the retail register conventions.
extern "C" void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count);
__declspec(noinline) FString &FString::operator=(const TCHAR *Other)
{
    if (Other != (const TCHAR *)Data) {
        if (*Other == 0) {
            if (Data) { ArrayNum = 0; ArrayMax = 0; GMalloc->Free(Data); Data = 0; }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), L"FString::=");
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), L"FArray");
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}
inline TCHAR appToUpper(TCHAR c) { return (c < 'a' || c > 'z') ? c : c - ('a' - 'A'); }
FString FString::Caps() const
{
    FString New(**this);
    for (INT i = 0; i < ArrayNum; i++)
        New[i] = appToUpper(New[i]);
    return New;
}
class FConfigCache
{
public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual const TCHAR *GetStr(const TCHAR *Section, INT Unknown, const TCHAR *Key, const TCHAR *Filename);
};
extern UBOOL GIsStarted;
extern FConfigCache *GConfig;
extern TCHAR GLanguage[];
extern TCHAR GEmptyLocalized[];
extern const TCHAR Text_FilenameFmt[];
extern const TCHAR Text_Int[];
INT __cdecl appSprintf(TCHAR *Dest, const TCHAR *Fmt, ...);
__declspec(noinline) const TCHAR *Localize(const TCHAR *Section, const TCHAR *Key, const TCHAR *Package, const TCHAR *LangExt, UBOOL Optional)
{
    if (!GIsStarted || !GConfig)
        return Key;
    if (!LangExt)
        LangExt = GLanguage;
    TCHAR Filename[256];
    for (;;) {
        appSprintf(Filename, Text_FilenameFmt, Package, LangExt);
        if (const TCHAR *Result = GConfig->GetStr(Section, 0, Key, Filename))
            return Result;
        if (_wcsicmp(LangExt, Text_Int) == 0)
            break;
        LangExt = Text_Int;
    }
    return Optional ? GEmptyLocalized : Key;
}
