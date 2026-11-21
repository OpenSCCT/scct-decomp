// UParticleEmitter::SpawnParticles (RVA 0xf9eb0), reached through the
// UMeshEmitter / USpriteEmitter vtables, slot 27.
typedef int INT;
typedef float FLOAT;
typedef unsigned long DWORD;

extern "C" __declspec(dllimport) double __cdecl floor(double);

inline INT appTrunc(FLOAT F) { return (INT)F; }
inline INT appFloor(FLOAT F) { return appTrunc((FLOAT)floor(F)); }

template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
template <class T> inline T Clamp(const T X, const T Min, const T Max) { return X < Min ? Min : X < Max ? X : Max; }

// Global passed by value as SpawnParticle's last argument (unidentified).
extern void *GParticleSpawnArg_ccacc0;

class UParticleEmitter
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26();
    virtual FLOAT SpawnParticles(FLOAT OldLeftover, FLOAT Rate, FLOAT DeltaTime);
    virtual void SpawnParticle(INT Index, FLOAT SpawnTime, INT Flags, INT SpawnFlags, void *Extra);

    char Pad004[0x398 - 4];
    void *ParticlesData;        // 0x398
    INT ParticlesNum;           // 0x39c
    char Pad3a0[0x3ac - 0x3a0];
    INT ParticleIndex;          // 0x3ac
    INT ActiveParticles;        // 0x3b0
    char Pad3b4[0x3c8 - 0x3b4];
    INT MaxParticles;           // 0x3c8
    char Pad3cc[0x3e4 - 0x3cc];
    INT ParticlesLeftToSpawn;   // 0x3e4 (name unconfirmed)
};

FLOAT UParticleEmitter::SpawnParticles(FLOAT OldLeftover, FLOAT Rate, FLOAT DeltaTime)
{
    if (Rate <= 0.f || !ParticlesNum)
        return 0.f;

    FLOAT NewLeftover = OldLeftover + DeltaTime * Rate;
    INT Number = appFloor(NewLeftover);
    NewLeftover -= Number;
    FLOAT Increment = 1.f / Rate;
    FLOAT StartTime = DeltaTime + OldLeftover * Increment - Increment;

    Number = Clamp(Number, 0, MaxParticles);
    if (ParticlesLeftToSpawn) {
        Number = Clamp(Number, 0, ParticlesLeftToSpawn);
        ParticlesLeftToSpawn -= Number;
    }

    for (INT i = 0; i < Number; i++) {
        SpawnParticle(ParticleIndex, StartTime - i * Increment, 4, 0, GParticleSpawnArg_ccacc0);
        ActiveParticles = Max(ActiveParticles, ParticleIndex + 1);
        ParticleIndex = (ParticleIndex + 1) % MaxParticles;
    }
    return NewLeftover;
}
