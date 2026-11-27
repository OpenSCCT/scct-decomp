#include "versus_build.h"
#include "unreal_object.h"

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    ~FArray() {
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);
};

template<class T> class TArray : public FArray {
public:
    ~TArray() { Remove(0, ArrayNum); }
    void Remove(INT Index, INT Count);
};
template<class T> void TArray<T>::Remove(INT Index, INT Count) {
    for (INT i = Index; i < Index + Count; ++i)
        ((T *)Data)[i].~T();
    FArray::Remove(Index, Count, sizeof(T));
}

class FString : public TArray<TCHAR> {
public:
    ~FString();
};

// Member names and declaration order follow the shipped SBase.SMapSettings structs.
struct FGameModeInfo {
    INT TimeLimit, ScoreLimit, SpiesLives, RespawnTime, SentriesLives, Handicap, NumDisksMax;
    BYTE GameModeId;  // Reflected EGameMode.
};

struct FGameModeInfoStrings {
    FString ExplicationModeSpy;
    FString ExplicationModeSentry;
    FString ExpliModeInBriefSpy;
    FString LegendModeInBriefSpy;
    FString ExpliModeInBriefSentry;
    FString LegendModeInBriefSentry;
};

class USMapSettings : public UObject {
public:
    virtual ~USMapSettings();
    FString MapName, LegendMap, LegendMapInBrief, ExpliMapInBriefSpy, ExpliMapInBriefSentry;
    INT IsAmateur;
    TArray<FGameModeInfo> Modes;
    TArray<FGameModeInfoStrings> ModesStrings;
};

USMapSettings::~USMapSettings()
{
    ConditionalDestroy();
}

typedef char GameModeInfo_size[sizeof(FGameModeInfo) == 32 ? 1 : -1];
typedef char GameModeInfoStrings_size[sizeof(FGameModeInfoStrings) == 72 ? 1 : -1];
typedef char MapSettings_size[sizeof(USMapSettings) == 0x80 ? 1 : -1];
