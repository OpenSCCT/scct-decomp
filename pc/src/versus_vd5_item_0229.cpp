// Work item 0229: Versus RVA 0xef740 (destructor of an unnamed UObject class
// with a secondary interface) and 0xef7d0 (AFileLog::execOpenLog).
#include "versus_build.h"
#include "unreal_object.h"

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;

enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };
enum EFileWrite { FILEWRITE_EvenIfReadOnly = 0x04, FILEWRITE_Append = 0x10 };

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
inline TCHAR *appStrcpy(TCHAR *D, const TCHAR *S) { return wcscpy(D, S); }

struct FFrame;

// ---------------------------------------------------------------------------
// RVA 0xef740. No vtable label names this class (primary vtable 0x10c04168,
// secondary 0x10c041e0), so it is named after its vtable:
// UnnamedClass304168. Parent destructor is retail 0x0cac0.
class UnnamedClass30D7D8 : public UObject { public: virtual ~UnnamedClass30D7D8(); };

// Interface-like secondary base at +0x28 (vtable only, trivial destructor).
class UnnamedInterface304168 { public: virtual void InterfaceSlot0(); };

struct UnnamedArray304168;
// Retail 0x10a7bf30: releases a TArray-like member, `this` on the stack.
void __stdcall UnnamedArray_Release(UnnamedArray304168 *Array);

struct UnnamedArray304168 {
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    ~UnnamedArray304168() { UnnamedArray_Release(this); }
};

class UnnamedClass304168 : public UnnamedClass30D7D8, public UnnamedInterface304168 {
public:
    UnnamedArray304168 Array;   // 0x2c
    virtual ~UnnamedClass304168();
};

UnnamedClass304168::~UnnamedClass304168() { ConditionalDestroy(); }

// ---------------------------------------------------------------------------
// RVA 0xef7d0: AFileLog::execOpenLog.
class FOutputDevice { public: virtual void Serialize(const TCHAR *V, INT Event); };
class FArchive;

class FFileManager {
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual FArchive *CreateFileWriter(const TCHAR *Filename, DWORD WriteFlags, FOutputDevice *Error, INT MaxFileSize);
};
extern FOutputDevice *GNull;
extern FFileManager *GFileManager;

class FArray {
public:
    ~FArray();
    INT Add(INT Count, INT ElementSize);
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T> class TArray : public FArray {
public:
    INT Add(INT n) { return FArray::Add(n, sizeof(T)); }
};

class FString : public TArray<TCHAR> {
public:
    FString() { Data = 0; ArrayNum = 0; ArrayMax = 0; }
    ~FString();
    FString &operator=(const FString &Other);
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
    TCHAR &operator()(INT i) { return ((TCHAR *)Data)[i]; }
    INT Len() const { return appStrlen(**this); }
    FString &operator+=(const TCHAR *Str)
    {
        if (*Str) {
            if (ArrayNum) {
                INT Index = ArrayNum - 1;
                Add(appStrlen(Str));
                appStrcpy(&(*this)(Index), Str);
            } else if (*Str) {
                Add(appStrlen(Str) + 1);
                appStrcpy(&(*this)(0), Str);
            }
        }
        return *this;
    }
};

typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
    void *Node;
    UObject *Object;
    BYTE *Code;
    void Step(UObject *Context, void *const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

// File extension appended to log names (retail 0x10c49558, L".txt").
extern TCHAR FileLog_Extension[];

class AFileLog : public UObject {
public:
    BYTE Pad[0x2f8 - 0x28];
    FArchive *LogAr;          // 0x2f8
    FString LogFileName;      // 0x2fc
    void execOpenLog(FFrame &Stack, void *const Result);
};

void AFileLog::execOpenLog(FFrame &Stack, void *const Result)
{
    FString FName;
    Stack.Step(Stack.Object, &FName);
    Stack.Code++;
    for (INT i = 0; i < FName.Len(); i++)
        if ((*FName)[i] == '\\' || (*FName)[i] == '.')
            ((TCHAR *)*FName)[i] = '_';
    FName += FileLog_Extension;
    LogFileName = FName;
    LogAr = GFileManager->CreateFileWriter(*LogFileName, FILEWRITE_EvenIfReadOnly | FILEWRITE_Append, GNull, 0);
}
