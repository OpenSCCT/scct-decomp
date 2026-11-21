// w4_item_0038.cpp -- Versus RVA 0x12a420-0x12a65d: AActor and ASLogManager script natives

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef DWORD BITFIELD;

enum { CPF_Config = 0x4000 };
enum EFileWrite { FILEWRITE_EvenIfReadOnly = 0x04, FILEWRITE_Append = 0x10 };

#define RESULT_DECL void *const Result

struct FVector {
    FLOAT X;
    FLOAT Y;
    FLOAT Z;
};

struct FName {
    INT Index;
};

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

class FString : public FArray {
public:
    FString()
    {
        Data = 0;
        ArrayNum = 0;
        ArrayMax = 0;
    }
    ~FString();
    FString &operator=(const FString &Other);
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
};

class FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
};

extern FOutputDevice *GNull;

class FArchive;

class FFileManager {
public:
    virtual ~FFileManager();
    virtual void Init(UBOOL Startup);
    virtual FArchive *CreateFileReader(const TCHAR *Filename, DWORD ReadFlags = 0,
                                       FOutputDevice *Error = GNull);
    virtual FArchive *CreateFileWriter(const TCHAR *Filename, DWORD WriteFlags = 0,
                                       FOutputDevice *Error = GNull, INT MaxFileSize = 0);
};

extern FFileManager *GFileManager;

struct FFrame;
class UClass;

class UObject {
public:
    virtual ~UObject();
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;
    UClass *Class;

    UClass *GetClass() const { return Class; }
    void LoadConfig(UBOOL Propagate = 0, UClass *InClass = 0, const TCHAR *Filename = 0);
    void __stdcall SaveConfig(DWORD Flags = CPF_Config, const TCHAR *Filename = 0, UBOOL Flush = 1);
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
    void *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_BYTE(Var) BYTE Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_STR(Var) FString Var; Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR(Var) FVector Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

// Retail global FString at 0x10cb785c (inferred name from execSetGlobalId / execGetGlobalId).
extern FString GGlobalId;

class AActor : public UObject {
public:
    BYTE unk_28[0x2f8 - 0x28];

    void execDrawDebugLine(FFrame &Stack, RESULT_DECL);
    void execSetGlobalId(FFrame &Stack, RESULT_DECL);
    void execGetGlobalId(FFrame &Stack, RESULT_DECL);
};

// Field names inferred from execSaveTagLog, execLoadTagLog, execOpenEventLog and execCloseEventLog.
class ASLogManager : public AActor {
public:
    FString TagLogFileName;     // +0x2f8
    FString EventLogFileName;   // +0x304
    FArchive *EventLogAr;       // +0x310
    BITFIELD bLogging : 1;      // +0x314

    void execSaveTagLog(FFrame &Stack, RESULT_DECL);
    void execLoadTagLog(FFrame &Stack, RESULT_DECL);
    void execOpenEventLog(FFrame &Stack, RESULT_DECL);
};

// AActor::execDrawDebugLine (RVA 0x12a420)
void AActor::execDrawDebugLine(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(LineStart);
    P_GET_VECTOR(LineEnd);
    P_GET_BYTE(R);
    P_GET_BYTE(G);
    P_GET_BYTE(B);
    P_FINISH;
}

// AActor::execSetGlobalId (RVA 0x12a4d0)
void AActor::execSetGlobalId(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Id);
    P_FINISH;
    GGlobalId = Id;
}

// AActor::execGetGlobalId (RVA 0x12a550)
void AActor::execGetGlobalId(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(FString *)Result = GGlobalId;
}

// ASLogManager::execSaveTagLog (RVA 0x12a570)
void ASLogManager::execSaveTagLog(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    if (bLogging)
        SaveConfig(CPF_Config, *TagLogFileName, 1);
}

// ASLogManager::execLoadTagLog (RVA 0x12a5c0)
void ASLogManager::execLoadTagLog(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    if (bLogging)
        LoadConfig(0, GetClass(), *TagLogFileName);
}

// ASLogManager::execOpenEventLog (RVA 0x12a610)
void ASLogManager::execOpenEventLog(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    if (bLogging)
        EventLogAr = GFileManager->CreateFileWriter(*EventLogFileName,
                                                    FILEWRITE_EvenIfReadOnly | FILEWRITE_Append,
                                                    GNull, 0);
}
