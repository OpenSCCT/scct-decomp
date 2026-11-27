extern FNameEntry **GNames;
extern TCHAR GFullNameBuffer[1024];
static UBOOL IsChildOf(UClass *Type, UClass *Base)
{
    for (; Type; Type = static_cast<UClass *>(Type->SuperField))
        if (Type == Base)
            return 1;
    return 0;
}
INT appSprintf(TCHAR *Dest,const TCHAR *Fmt,...);
extern "C" __declspec(dllimport) unsigned int wcslen(const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *wcscpy(TCHAR *, const TCHAR *);
inline const TCHAR *UObject::GetFullName(TCHAR *Buffer) const
{
    TCHAR *Result = Buffer ? Buffer : GFullNameBuffer;
    if (this) {
        appSprintf(Result, L"%s ", GNames[Class->Name.Index]->Name);
        GetPathName(0, Result + wcslen(Result));
    } else {
        wcscpy(Result, L"None");
    }
    return Result;
}
enum { LOAD_Quiet = 8 };

void appThrowf(const TCHAR *Fmt,...);
void SafeLoadError(DWORD Flags,const TCHAR *Error,const TCHAR *Format,...);
UClass *UObject::StaticLoadClass(UClass *BaseClass, UObject *Outer, FName Package, FName Group, FName Name,
    const TCHAR *Filename, DWORD Flags, UPackageMap *Sandbox)
{
    try {
        UClass *Loaded = (UClass *)StaticLoadObject(&UClass::PrivateStaticClass, Outer, Package,
            Group, Name, Filename, Flags | LOAD_Quiet, Sandbox);
        if (Loaded && !IsChildOf(Loaded, BaseClass)) {
            // The retail format has three conversions and supplies these two full names.
            appThrowf(L"%s is not a child class of %s.%s", Loaded->GetFullName(), BaseClass->GetFullName());
        }
        return Loaded;
    } catch (const TCHAR *Error) {
        SafeLoadError(Flags, Error, Error);
        return 0;
    }
}

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
extern TArray<UObject *> GObjObjects;    // 0x10cc9e80
extern TCHAR GLanguage[];                // 0x10c6f868
extern TCHAR GTrue[];                    // 0x10c71ab8
extern TCHAR GFalse[];                   // 0x10c71ac8

// Iterator over every live object (no class filter in this build).
class FObjectIterator
{
public:
    FObjectIterator();
    ~FObjectIterator();                  // RVA 0x4a550 (folded empty `ret 4`)
    void operator++()
    {
        while (++Index < Objects->Num() && !(*Objects)(Index))
            ;
    }
    operator UBOOL() { return Index < Objects->Num(); }
    UObject *operator->() { return (*Objects)(Index); }
protected:
    TArray<UObject *> *Objects;
    INT Index;
};

// FObjectIterator begins on the first live object.
FObjectIterator::FObjectIterator()
    : Objects(&GObjObjects), Index(-1)
{
    ++*this;
}


__declspec(noinline) FObjectIterator::~FObjectIterator()
{
}

// RVA 0x1ee10: UObject::SetLanguage (LTCG: LangExt in EAX).
void UObject::SetLanguage(const TCHAR *LangExt)
{
    if (_wcsicmp(LangExt, GLanguage) != 0) {
        wcscpy(GLanguage, LangExt);
        wcscpy(GTrue, L"True");
        wcscpy(GFalse, L"False");
        for (FObjectIterator It; It; ++It)
            It->LanguageChange();
    }
}
