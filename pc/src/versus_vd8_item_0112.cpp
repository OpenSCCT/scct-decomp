// Work item 0112: Versus RVA 0x153050
// Virtual method (vtable 0x10c03268 slot 12) that looks up the key code (0..254)
// bound to a given action string by querying KEYNAME %i and KEYBINDING %s on
// PC->Player. Class name is neutral (no RTTI/export identifies vtable 0x10c03268).

typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum EName
{
    NAME_None = 0,
};

extern "C" __declspec(dllimport) int __cdecl wcscmp(const TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);

INT __cdecl appSprintf(TCHAR *Dest, const TCHAR *Fmt, ...);

inline INT appStrcmp(const TCHAR *String1, const TCHAR *String2) { return wcscmp(String1, String2); }
inline INT appStricmp(const TCHAR *String1, const TCHAR *String2) { return _wcsicmp(String1, String2); }

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

class FString : public FArray
{
public:
    FString(const TCHAR *In);
    ~FString();

    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
};

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *Data, EName Event) = 0;
};

class FStringOutputDevice : public FString, public FOutputDevice
{
public:
    FStringOutputDevice(const TCHAR *InStr = L"")
        : FString(InStr)
    {
    }
    void Serialize(const TCHAR *Data, EName Event);
};

class FExec
{
public:
    virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar) = 0;
};

class UObject
{
public:
    virtual ~UObject();
    BYTE unk_04[0x28];
};

class UPlayer : public UObject, public FExec
{
public:
};

class APlayerController
{
public:
    BYTE unk_00[0x4a4];
    UPlayer *Player;
};

class UnnamedClass_153050
{
public:
    virtual INT FindKeyForBinding(const TCHAR *Binding, APlayerController *PC);
};

// Retail keeps these literals in writable .data/.bss (unpooled VC7.0 literals).
extern const TCHAR KeyNameInitEmpty[];     // 0x10c92284, L""
extern const TCHAR KeyNameCmpEmpty[];      // 0x10c92288, L""
extern const TCHAR KeyBindingInitEmpty[];  // 0x10c9228c, L""
extern const TCHAR KeyNameFmt[];           // 0x10c46ddc, L"KEYNAME %i"
extern const TCHAR KeyBindingFmt[];        // 0x10c46df4, L"KEYBINDING %s"

// RVA 0x153050: UnnamedClass_153050::FindKeyForBinding
INT UnnamedClass_153050::FindKeyForBinding(const TCHAR *Binding, APlayerController *PC)
{
    INT Result = -1;
    TCHAR Command[256];

    for (INT i = 0; i < 255 && Result == -1; i++)
    {
        FStringOutputDevice KeyName(KeyNameInitEmpty);
        appSprintf(Command, KeyNameFmt, i);
        PC->Player->Exec(Command, KeyName);
        if (appStrcmp(*KeyName, KeyNameCmpEmpty) != 0)
        {
            FStringOutputDevice KeyBinding(KeyBindingInitEmpty);
            appSprintf(Command, KeyBindingFmt, *KeyName);
            PC->Player->Exec(Command, KeyBinding);
            if (appStricmp(*KeyBinding, Binding) == 0)
            {
                Result = i;
            }
        }
    }
    return Result;
}
