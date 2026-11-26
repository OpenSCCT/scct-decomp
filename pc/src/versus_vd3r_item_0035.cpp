// Work item 0035 (LTCG retry): Versus RVA 0x8930.
// A window helper that packs two values and a string into a parameter block
// and sends it as WM_COMMAND (0x111, id 0x8018) to the window at +0x1c.
// Class name unknown: UnnamedClass_8930 is a neutral name.
// Retail built this unit with /GL and linked with /LTCG; FString::operator=
// (0x4750) is reached with this in ESI and Other in EDI.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef struct HWND__ *HWND;
typedef long LONG, LPARAM, LRESULT;

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
void appMemcpy(void *Dest, const void *Src, INT Count);

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FString();
    FString &operator=(const TCHAR *Other);
};

FString &FString::operator=(const TCHAR *Other)
{
    if (Other != Data) {
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

// SendMessageW through the writable slot at 0x10c74c4c.
extern LRESULT (__stdcall *slot_SendMessageW)(HWND, DWORD, DWORD, long);

struct FCommandParams_8930
{
    INT A;
    INT B;
    FString Text;
};

class UnnamedClass_8930
{
public:
    char Pad[0x1c];
    HWND hWnd;
    void SendCommand(INT A, INT B, const TCHAR *Text);
};

void UnnamedClass_8930::SendCommand(INT A, INT B, const TCHAR *Text)
{
    FCommandParams_8930 Params;
    Params.A = A;
    Params.B = B;
    Params.Text = Text;
    slot_SendMessageW(hWnd, 0x111, 0x8018, (long)&Params);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_8930(UnnamedClass_8930 *C, INT A, INT B, const TCHAR *T, FString *S)
{
    Escape(&GMalloc);
    Escape(&slot_SendMessageW);
    // Retail callers outside the LTCG set keep SendCommand a plain thiscall.
    void (UnnamedClass_8930::*Fn)(INT, INT, const TCHAR *) = &UnnamedClass_8930::SendCommand;
    Escape(*(void **)&Fn);
    C->SendCommand(A, B, T);
    *S = T;
}
