// Work item 0198: Versus RVA 0xe4b20 (USound::Serialize).
// Compiled without optimisation (#pragma optimize("", off)) inside the LTCG link,
// so USound::Serialize keeps an unoptimised frame while calling LTCG-linked helpers
// with custom register calling conventions.

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

enum EName { NAME_None = 0 };
enum EFindName { FNAME_Find = 0, FNAME_Add = 1, FNAME_Intrinsic = 2 };
enum { LOAD_NoWarn = 0x0002, LOAD_Quiet = 0x2000 };
enum { RF_Native = 0x4000000 };

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;
extern DWORD GCRCTable[256];

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcschr(const TCHAR *, TCHAR);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
void __cdecl appMemcpy(void *Dest, const void *Src, INT Count);

inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
inline TCHAR appToUpper(TCHAR c) { return (c < 'a' || c > 'z') ? c : (TCHAR)(c + 'A' - 'a'); }
inline INT appStricmp(const TCHAR *A, const TCHAR *B) { return _wcsicmp(A, B); }

class UObject;
class UClass;
class UPackageMap;
class USound;
class FArchive;

struct FNameEntry
{
    INT Index;
    DWORD Flags;
    FNameEntry *HashNext;
    TCHAR Name[1];
};

class FCompactIndex
{
public:
    INT Value;
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize)
        : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (!ArrayMax)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, L"Farray::protectedcstor");
    }
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    INT Add(INT Count, INT ElementSize);
    void Remove(INT Index, INT Count, INT ElementSize);
    void Realloc(INT ElementSize);
    void Empty(INT ElementSize, INT Slack = 0);
    __forceinline INT Num() const { return ArrayNum; }
};

class FString : public FArray
{
public:
    FString();
    FString(const TCHAR *In);
    ~FString();
    const TCHAR *operator*() const;
};

class FLazyLoader;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(UObject *Object);
    virtual void CountBytes(INT InNum, INT InMax);
    virtual FArchive &operator<<(struct FName &N);
    virtual FArchive &operator<<(UObject *&Res);
    virtual INT MapName(struct FName *Name);
    virtual INT MapObject(UObject *Object);
    virtual INT Tell();
    virtual INT TotalSize();
    virtual UBOOL AtEnd();
    virtual UBOOL AtStopper();
    virtual void SetStopper(INT InStopper);
    virtual void Seek(INT InPos);
    virtual void AttachLazyLoader(FLazyLoader *LazyLoader);

    INT ArVer;          // +0x04
    INT ArNetVer;       // +0x08
    INT ArLicenseeVer;  // +0x0c
    UBOOL ArIsLoading;  // +0x10
    UBOOL ArIsSaving;   // +0x14
    INT Pad18[5];       // +0x18..+0x2b
    UBOOL ArIsError;    // +0x2c
    UBOOL ArIsCriticalError; // +0x30
    INT Pad34;          // +0x34
    INT ArMaxSerializeSize; // +0x38

    UBOOL IsLoading() const { return ArIsLoading; }
    UBOOL IsSaving() const { return ArIsSaving; }
    INT Ver() const { return ArVer; }
};

inline FArchive &operator<<(FArchive &Ar, BYTE &B)
{
    Ar.Serialize(&B, 1);
    return Ar;
}

inline FArchive &operator<<(FArchive &Ar, INT &I)
{
    Ar.Serialize(&I, sizeof(I));
    return Ar;
}

inline FArchive &operator<<(FArchive &Ar, DWORD &D)
{
    Ar.Serialize(&D, sizeof(D));
    return Ar;
}

inline FArchive &operator<<(FArchive &Ar, FLOAT &F)
{
    Ar.Serialize(&F, sizeof(F));
    return Ar;
}

// RVA 0x1ea40: FCompactIndex serializer (Ar in ESI, &I in EDI).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving())
    {
        Ar.Serialize(&I.Value, sizeof(I.Value));
        return Ar;
    }
    INT Original = I.Value;
    DWORD V = Original >= 0 ? Original : -Original;
    BYTE B0 = (BYTE)((Original >= 0 ? 0 : 0x80) + (V < 0x40 ? V : ((V & 0x3f) + 0x40)));
    I.Value = 0;
    Ar.Serialize(&B0, 1);
    if (B0 & 0x40)
    {
        V >>= 6;
        BYTE B1 = (BYTE)(V < 0x80 ? V : ((V & 0x7f) + 0x80));
        Ar.Serialize(&B1, 1);
        if (B1 & 0x80)
        {
            V >>= 7;
            BYTE B2 = (BYTE)(V < 0x80 ? V : ((V & 0x7f) + 0x80));
            Ar.Serialize(&B2, 1);
            if (B2 & 0x80)
            {
                V >>= 7;
                BYTE B3 = (BYTE)(V < 0x80 ? V : ((V & 0x7f) + 0x80));
                Ar.Serialize(&B3, 1);
                if (B3 & 0x80)
                {
                    V >>= 7;
                    BYTE B4 = (BYTE)V;
                    Ar.Serialize(&B4, 1);
                    I.Value = B4;
                }
                I.Value = (I.Value << 7) + (B3 & 0x7f);
            }
            I.Value = (I.Value << 7) + (B2 & 0x7f);
        }
        I.Value = (I.Value << 7) + (B1 & 0x7f);
    }
    I.Value = (I.Value << 6) + (B0 & 0x3f);
    if (B0 & 0x80)
        I.Value = -I.Value;
    return Ar;
}

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Add(INT Count = 1) { return FArray::Add(Count, sizeof(T)); }
    void Remove(INT Index, INT Count = 1) { FArray::Remove(Index, Count, sizeof(T)); }
    void Empty(INT Slack = 0) { FArray::Empty(sizeof(T), Slack); }

    friend FArchive &operator<<(FArchive &Ar, TArray<T> &A)
    {
        Ar.CountBytes(A.ArrayNum * sizeof(T), A.ArrayMax * sizeof(T));
        if (sizeof(T) == 1)
        {
            Ar << AR_INDEX(A.ArrayNum);
            if (Ar.IsLoading())
            {
                A.ArrayMax = A.ArrayNum;
                if (!A.Data)
                {
                    if (A.ArrayNum)
                        A.Data = GMalloc->Malloc(A.ArrayNum, L"FArray");
                }
                else if (A.ArrayNum)
                {
                    A.Realloc(1);
                }
                else
                {
                    A.ArrayNum = A.ArrayMax = 0;
                    GMalloc->Free(A.Data);
                    A.Data = 0;
                    return Ar;
                }
            }
            Ar.Serialize(A.Data, A.ArrayNum);
        }
        else if (Ar.IsLoading())
        {
            INT NewNum;
            Ar << AR_INDEX(NewNum);
            A.Empty(NewNum);
            for (INT i = 0; i < NewNum; i++)
            {
                A.Add(1);
                Ar << A(i);
            }
        }
        else
        {
            Ar << AR_INDEX(A.ArrayNum);
            for (INT i = 0; i < A.ArrayNum; i++)
                Ar << A(i);
        }
        return Ar;
    }
};

template<> __forceinline INT TArray<USound *>::Add(INT Count)
{
    return FArray::Add(Count, sizeof(USound *));
}

struct FName
{
    INT Index;
    FName();
    FName(EName N);
    FName(const TCHAR *Name, EFindName FindType);
    INT GetIndex() const { return Index; }
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
    UBOOL operator!=(const FName &Other) const { return Index != Other.Index; }
    static FNameEntry *NameHash[4096];
    static TArray<FNameEntry *> Names;
    static TArray<INT> Available;
};

__declspec(noinline) DWORD appStrihash(const TCHAR *Data)
{
    DWORD Hash = 0;
    while (*Data)
    {
        TCHAR Ch = appToUpper(*Data++);
        BYTE B = (BYTE)Ch;
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
        B = (BYTE)(Ch >> 8);
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
    }
    return Hash;
}

__declspec(noinline) FNameEntry *AllocateNameEntry(const TCHAR *Name, DWORD Index, DWORD Flags, FNameEntry *HashNext)
{
    FNameEntry *NameEntry = (FNameEntry *)GMalloc->Malloc(sizeof(FNameEntry) + wcslen(Name) * sizeof(TCHAR), (const TCHAR *)L"NameEntry");
    NameEntry->Index = Index;
    NameEntry->Flags = Flags;
    NameEntry->HashNext = HashNext;
    wcscpy(NameEntry->Name, Name);
    return NameEntry;
}

__declspec(noinline) FName::FName(const TCHAR *Name, EFindName FindType)
{
    if (!Name[0])
    {
        Index = NAME_None;
        return;
    }
    INT iHash = appStrihash(Name) & 4095;
    for (FNameEntry *Hash = NameHash[iHash]; Hash; Hash = Hash->HashNext)
    {
        if (appStricmp(Name, Hash->Name) == 0)
        {
            Index = Hash->Index;
            if (FindType == FNAME_Intrinsic)
                Names(Index)->Flags |= RF_Native;
            return;
        }
    }
    if (FindType == FNAME_Find)
    {
        Index = NAME_None;
        return;
    }
    if (Available.Num())
    {
        Index = Available(Available.Num() - 1);
        Available.Remove(Available.Num() - 1);
    }
    else
    {
        Index = Names.Add();
    }
    Names(Index) = NameHash[iHash] = AllocateNameEntry(Name, Index, 0, NameHash[iHash]);
    if (FindType == FNAME_Intrinsic)
        Names(Index)->Flags |= RF_Native;
}

// Out of line in Core (RVA 0x11b80); defined here for its LTCG convention (Ar in EAX, A in EBX).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FString &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(TCHAR), A.ArrayMax * sizeof(TCHAR));
    INT SaveNum = A.ArrayNum;
    if (SaveNum)
    {
        for (const TCHAR *P = (const TCHAR *)A.Data; *P; P++)
        {
            if (*P > 0xff)
            {
                SaveNum = -SaveNum;
                break;
            }
        }
    }
    Ar << AR_INDEX(SaveNum);
    if (Ar.IsLoading())
    {
        if (Ar.ArMaxSerializeSize && (SaveNum < 0 ? -SaveNum : SaveNum) > Ar.ArMaxSerializeSize)
        {
            Ar.ArIsError = 1;
            Ar.ArIsCriticalError = 1;
            return Ar;
        }
        if (SaveNum < 0)
            Ar.Serialize(A.Data, -SaveNum * sizeof(TCHAR));
        else if (SaveNum > 0)
            Ar.Serialize(A.Data, SaveNum);
    }
    else
    {
        if (SaveNum < 0)
            Ar.Serialize(A.Data, -SaveNum * sizeof(TCHAR));
        else if (SaveNum > 0)
            Ar.Serialize(A.Data, SaveNum);
    }
    return Ar;
}

class FLazyLoader
{
public:
    virtual void Load();
    void *SavedAr;
    INT SavedPos;
};

extern DWORD GLazyLoadFlags;
extern UBOOL GLazyLoadEnabled;

template<class T> class TLazyArray : public FLazyLoader, public TArray<T>
{
public:
    INT Pad18;

    friend FArchive &operator<<(FArchive &Ar, TLazyArray<T> &This)
    {
        if (Ar.IsLoading())
        {
            INT SeekPos = 0;
            if (Ar.Ver() <= 61)
            {
                INT SkipCount = 0;
                Ar.AttachLazyLoader(&This);
                Ar << AR_INDEX(SkipCount);
                Ar.Tell();
            }
            else if (Ar.Ver() >= 0xaf)
            {
                INT Dummy;
                Ar << Dummy;
                Ar << (TArray<T> &)This;
            }
            else
            {
                Ar << SeekPos;
                if (GLazyLoadFlags & 8)
                    Ar << (TArray<T> &)This;
                else
                    Ar.AttachLazyLoader(&This);
                if (!GLazyLoadEnabled)
                    This.Load();
                Ar.Seek(SeekPos);
            }
        }
        else if (Ar.IsSaving() && Ar.Ver() > 61)
        {
            if (Ar.Ver() >= 0xaf)
            {
                INT Dummy = 0;
                Ar << Dummy;
                Ar << (TArray<T> &)This;
            }
            else
            {
                INT SkipPos = Ar.Tell();
                Ar << SkipPos;
                Ar << (TArray<T> &)This;
                INT EndPos = Ar.Tell();
                Ar.Seek(SkipPos);
                Ar << EndPos;
                Ar.Seek(EndPos);
            }
        }
        else
        {
            Ar << (TArray<T> &)This;
        }
        return Ar;
    }
};

class UClass;

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
    virtual void Serialize(FArchive &Ar);

    INT Index;          // +0x04
    UObject *HashNext;  // +0x08
    void *StateFrame;   // +0x0c
    void *_Linker;      // +0x10
    INT _LinkerIndex;   // +0x14
    UObject *Outer;     // +0x18
    DWORD ObjectFlags;  // +0x1c
    FName Name;         // +0x20
    UClass *Class;      // +0x24

    FName GetFName() const;
    const TCHAR *GetName() const { return FName::Names(Name.Index)->Name; }
    UObject *GetOuter() const { return Outer; }
    UBOOL IsA(UClass *SomeBase) const;
    UBOOL IsIn(UObject *SomeOuter) const;

    static UObject *StaticFindObject(UClass *ObjectClass, UObject *InObjectPackage, const TCHAR *OrigInName, UBOOL ExactClass);
    static UObject *StaticFindObject(UClass *ObjectClass, UObject *InObjectPackage, FName A, FName B, FName ObjectName, UBOOL ExactClass);
    static UObject *StaticLoadObject(UClass *ObjectClass, UObject *InOuter, const TCHAR *InName, const TCHAR *Filename, DWORD LoadFlags, UPackageMap *Sandbox);
    static UObject *StaticLoadObject(UClass *ObjectClass, UObject *InOuter, FName A, FName B, FName ObjectName, const TCHAR *Filename, DWORD LoadFlags, UPackageMap *Sandbox);
    static UBOOL ResolveName(UObject *&InPackage, const TCHAR *InName, TCHAR *OutName, UBOOL Create, UBOOL Throw);
    static UObject *CreatePackage(UObject *InOuter, FName A, FName B, const TCHAR *PackageName);

    static UObject *GObjHash[4096];
};

class UField : public UObject
{
public:
    UField *SuperField;
    UField *Next;
};
class UStruct : public UField {};
class UClass : public UStruct {};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    if (!SomeBase)
        return 1;
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

__declspec(noinline) UBOOL UObject::IsIn(UObject *SomeOuter) const
{
    for (UObject *It = Outer; It; It = It->Outer)
        if (It == SomeOuter)
            return 1;
    return SomeOuter == 0;
}

#define ANY_PACKAGE ((UObject *)-1)

extern UClass PackageClass_ResolveName;
// RVA 0x1ab80 (approximation for LTCG analysis, as in versus_vd2_item_0099.cpp).
UBOOL UObject::ResolveName(UObject *&InPackage, const TCHAR *InName, TCHAR *OutName, UBOOL Create, UBOOL Throw)
{
    const TCHAR *Dot;
    while ((Dot = wcschr(InName, '.')) != 0)
    {
        TCHAR PartialName[256];
        INT i;
        for (i = 0; InName + i < Dot && i < 255; i++)
            PartialName[i] = InName[i];
        PartialName[i] = 0;
        if (Create)
            InPackage = CreatePackage(InPackage, NAME_None, NAME_None, PartialName);
        else
        {
            InPackage = StaticFindObject(&PackageClass_ResolveName, InPackage, NAME_None, NAME_None, FName(PartialName, FNAME_Find), 0);
            if (!InPackage)
                return 0;
        }
        InName = Dot + 1;
    }
    wcscpy(OutName, InName);
    return 1;
}

// RVA 0x17630 (defined here for its LTCG convention: OrigInName in EDX).
__declspec(noinline) UObject *UObject::StaticFindObject(UClass *ObjectClass, UObject *InObjectPackage, const TCHAR *OrigInName, UBOOL ExactClass)
{
    UObject *ObjectPackage = InObjectPackage != ANY_PACKAGE ? InObjectPackage : 0;
    TCHAR InName[256];
    if (!ResolveName(ObjectPackage, OrigInName, InName, 0, 0))
        return 0;

    FName ObjectName(InName, FNAME_Find);
    if (ObjectName != NAME_None)
    {
        INT iHash = ObjectName.GetIndex() & 4095;
        for (UObject *Hash = GObjHash[iHash]; Hash; Hash = Hash->HashNext)
        {
            if (Hash->Name == ObjectName
                && ((ObjectPackage == 0 && InObjectPackage == ANY_PACKAGE)
                    || Hash->Outer == ObjectPackage
                    || (InObjectPackage == ANY_PACKAGE && ObjectPackage && Hash->IsIn(ObjectPackage)))
                && (ObjectClass == 0
                    || (ExactClass ? Hash->Class == ObjectClass : Hash->IsA(ObjectClass))))
                return Hash;
        }
    }
    return 0;
}

template<class T> inline T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}

void __stdcall UnnamedListAdd_1d1a0(USound *Sound);

class USound : public UObject
{
public:
    typedef UObject Super;

    TLazyArray<BYTE> Data;          // +0x28 (0x1c bytes)
    FName FileType;                 // +0x44
    FString FileName;               // +0x48 (0x0c bytes)
    INT OriginalSize;               // +0x54
    FLOAT Duration;                 // +0x58
    void *Handle;                   // +0x5c
    DWORD Flags;                    // +0x60
    DWORD Field64;                  // +0x64
    DWORD Field68;                  // +0x68
    TArray<USound *> SubSounds;     // +0x6c (0x0c bytes)
    TArray<FLOAT> Field78;          // +0x78 (0x0c bytes)

    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
    virtual void Serialize(FArchive &Ar);
};

// RVA 0xe4b20
#pragma optimize("", off)
void USound::Serialize(FArchive &Ar)
{
    Super::Serialize(Ar);
    if (!(Flags & 0x1000))
        Ar << FileType;
    if (Ar.IsLoading() || Ar.IsSaving())
    {
        Ar << FileName;
        Ar << Flags;
        if (Flags & 0x400)
            Ar << Field64;
        if (Ar.Ver() >= 0xad)
            Ar << Field68;
        else
            Field68 = 0;

        if ((Flags & 0x100) || (Flags & 0x80) || (Flags & 0x800))
        {
            INT Count;
            if (Ar.IsSaving())
                Count = SubSounds.Num();
            Ar << Count;
            if (Ar.IsLoading())
            {
                SubSounds.Add(Count);
                Field78.Add(Count);
            }
            for (INT i = 0; i < Count; i++)
            {
                if (Ar.IsSaving())
                {
                    if (Ar.Ver() >= 0xa7)
                    {
                        FName Name = SubSounds(i)->GetFName();
                        Ar << Name;
                    }
                    else
                    {
                        FString Name(SubSounds(i)->GetName());
                        Ar << Name;
                    }
                }
                if (Ar.IsLoading())
                {
                    USound *S = 0;
                    if (Ar.Ver() >= 0xa7)
                    {
                        FName Name;
                        Ar << Name;
                        S = Cast<USound>(StaticFindObject(USound::StaticClass(), ANY_PACKAGE, NAME_None, NAME_None, Name, 0));
                        if (!S)
                            S = Cast<USound>(StaticLoadObject(USound::StaticClass(), GetOuter(), NAME_None, NAME_None, Name, 0, LOAD_Quiet | LOAD_NoWarn, 0));
                    }
                    else
                    {
                        FString Name;
                        Ar << Name;
                        S = Cast<USound>(StaticFindObject(USound::StaticClass(), ANY_PACKAGE, *Name, 0));
                        if (!S)
                            S = Cast<USound>(StaticLoadObject(USound::StaticClass(), GetOuter(), *Name, 0, LOAD_Quiet | LOAD_NoWarn, 0));
                    }
                    UnnamedListAdd_1d1a0(S);
                    SubSounds(i) = S;
                }
                Ar << Field78(i);
            }
        }
        else if (Flags & 0x2000)
        {
            if (Ar.IsLoading())
                Field78.Add(1);
            Ar << Field78(0);
        }
        else if (!(Flags & 0x4))
        {
            Ar << Data;
        }
    }
    else
    {
        Ar.CountBytes(OriginalSize, OriginalSize);
    }
}
#pragma optimize("", on)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
extern UClass DriverClassA, DriverClassB;
void Driver_e4b20(USound *S, FArchive *Ar, UObject *O, const TCHAR *N, const TCHAR *M, UBOOL E, FString *Strs)
{
    Escape(&GMalloc);
    Escape(&FName::Names);
    Escape(&FName::NameHash);
    Escape(&FName::Available);
    Escape(&UObject::GObjHash);
    Escape(&USound::PrivateStaticClass);
    Escape(&GLazyLoadFlags);
    Escape(&GLazyLoadEnabled);
    UBOOL (*ResolveByString)(UObject *&, const TCHAR *, TCHAR *, UBOOL, UBOOL) = &UObject::ResolveName;
    Escape((void *)ResolveByString);
    USound *(*CastSound)(UObject *) = &Cast<USound>;
    Escape((void *)CastSound);
    UBOOL (UObject::*IsAFn)(UClass *) const = &UObject::IsA;
    Escape(&IsAFn);
    UObject::StaticFindObject(&DriverClassA, ANY_PACKAGE, N, 0);
    UObject::StaticFindObject(&DriverClassB, O, M, E);
    UObject::StaticFindObject(&DriverClassA, O, N, 1);
    UObject::StaticFindObject(0, O, M, 0);
    for (INT i = 0; i < 4; i++)
    {
        *Ar << S[i].Data;
        *Ar << Strs[i];
    }
    S->USound::Serialize(*Ar);
}
