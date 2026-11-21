// w4_item_0192.cpp -- UGameServiceSubsystem::GetResultPlayerName (Versus RVA 0x16dbd0)

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

struct FGuid;

// The untyped storage of every dynamic array (from unreal_containers.h).
class FArray {
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
};

template<class T>
class TArray : public FArray {
public:
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class FString : public TArray<TCHAR> {
public:
    FString() {}
    FString(const FString &Other);
    FString(const TCHAR *In);
    ~FString();
};

// Core.Object hierarchy (from unreal_object.h, unreal_subsystem.h, versus_matchmaking.h).
class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();

    BYTE unk_4[0x24];
};

class USubsystem : public UObject {
public:
    virtual ~USubsystem();
};

class UMatchmakingSubsystem : public USubsystem {
public:
    virtual ~UMatchmakingSubsystem();
    virtual FString GetResultPlayerName(INT Index);

    BYTE unk_28[0x8];
};

// Entry in UGameServiceSubsystem's result-player array (stride 0x44, wide player name at offset 0;
// struct and field names invented, exact Name length and trailing fields unknown).
struct FResultPlayerRecord {
    TCHAR Name[34];
};

// GameService.GameServiceSubsystem (vtable slot 91 is GetResultPlayerName).
class UGameServiceSubsystem : public UMatchmakingSubsystem {
public:
    virtual ~UGameServiceSubsystem();
    virtual FString GetResultPlayerName(INT Index);

    BYTE                        unk_30[0x4c];
    TArray<FResultPlayerRecord> ResultPlayers;
};

// UGameServiceSubsystem::GetResultPlayerName -- returns the wide name of result player Index.
FString UGameServiceSubsystem::GetResultPlayerName(INT Index)
{
    return FString(ResultPlayers(Index).Name);
}
