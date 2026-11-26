typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef struct HWND__ *HWND;
extern "C" __declspec(dllimport) size_t __cdecl wcslen(const TCHAR *);
extern "C" void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count);

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString &operator=(const TCHAR *Other);
};

FString &FString::operator=(const TCHAR *Other)
{
    if (Other != Data) {
        if (*Other == 0) {
            if (Data) {
                ArrayNum = 0;
                ArrayMax = 0;
                GMalloc->Free(Data);
                Data = 0;
            }
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

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_4750(FString *S, const TCHAR *T) { Escape(&GMalloc); *S = T; }
