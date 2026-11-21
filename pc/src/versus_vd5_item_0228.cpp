// Work item 0228: Versus RVA 0xef430-0xef70c. All three are LTCG (VC7.0 /GL) code.
// They are members of one unnamed class (neutral name UnnamedNetOwner) that a holder
// object keeps at +0xec (retail wrappers at 0xf8330 and 0xf8370 reach it that way).
// 0xef430: finds a pawn-like actor whose controller-like member (+0x4a4) is of a given
//          class, fires a script event (FName index 0xf27) on it, then notifies every
//          player whose actor sits in one of eight slots. Class names not recovered.
// 0xef580 / 0xef650: 1000-byte ring buffer read / write.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

template <class T> class TArray {
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

enum EName { NAME_Unnamed_F27 = 0xf27 }; // event name index; real name not recovered

class FName {
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
};

class UFunction;
class UClass;

class UObject {
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;
    UClass *Class;
    UFunction *FindFunctionChecked(FName InName, INT Global = 0);
    inline UBOOL IsA(UClass *SomeBase) const;
};

class UField : public UObject {
public:
    UField *SuperField;
};

class UClass : public UField {
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *C = Class; C; C = (UClass *)C->SuperField)
        if (C == SomeBase)
            return 1;
    return 0;
}

// Neutral names: classes at 0x10cc6ce8 and 0x10cbc930.
extern UClass UnnamedClass_cc6ce8_Static;
extern UClass UnnamedClass_cbc930_Static;

template <class T> T *Cast(UObject *Src, UClass *Cls)
{
    return Src && Src->IsA(Cls) ? (T *)Src : 0;
}

class UnnamedActor_cbc930 : public UObject {
};

class UnnamedPawn_cc6ce8 : public UObject {
public:
    BYTE Pad[0x4a4 - 0x28];
    UObject *Controller; // +0x4a4
};

class UnnamedLevel : public UObject {
public:
    BYTE Pad[0x6c - 0x28];
    TArray<UObject *> Actors; // +0x6c
};

class UnnamedPlayerActor : public UObject {
public:
    BYTE Pad[0x1a4 - 0x28];
    UnnamedLevel *XLevel; // +0x1a4
};

class UnnamedPlayer : public UObject {
public:
    BYTE Pad[0x30 - 0x28];
    UnnamedPlayerActor *Actor; // +0x30
    INT Notify(INT A, INT B);  // FUN_10a0ea50 (LTCG, this in ESI)
};

class UnnamedSource : public UObject {
public:
    BYTE Pad0[0x30 - 0x28];
    UnnamedPawn_cc6ce8 *Pawn; // +0x30
    BYTE Pad1[0x49c0 - 0x34];
    UnnamedPlayerActor *Slots[8]; // +0x49c0
};

void appMemcpy(void *Dest, const void *Src, INT Count); // FUN_109040a0
double appSeconds();                                     // FUN_10904030
extern double RingBuffer_Timeout;                        // double at 0x10c10ad8

#pragma pack(push, 4)
class UnnamedNetOwner : public UObject {
public:
    INT Unknown28;                   // +0x28
    TArray<UnnamedPlayer *> Players; // +0x2c
    UnnamedPlayer *LocalPlayer;      // +0x38 (guess)
    BYTE Pad[0x104 - 0x3c];
    INT Count;                       // +0x104
    INT Head;                        // +0x108
    BYTE Buffer[1000];               // +0x10c
    double LastTime;                 // +0x4f4
    UnnamedPlayerActor *Slots[8];    // +0x4fc

    INT NotifySlots(INT A, INT B, UnnamedSource *Source);
    UBOOL Read(BYTE *Dest, INT Size);
    void Write(const BYTE *Src, DWORD Size);
};
#pragma pack(pop)

INT UnnamedNetOwner::NotifySlots(INT A, INT B, UnnamedSource *Source)
{
    UnnamedPawn_cc6ce8 *P = 0;
    if (Source) {
        P = Source->Pawn;
    } else if (Players.Num() > 0 && Players(0)->Actor) {
        UnnamedLevel *Level = Players(0)->Actor->XLevel;
        for (INT i = 0; i < Level->Actors.Num(); i++) {
            P = Cast<UnnamedPawn_cc6ce8>(Level->Actors(i), &UnnamedClass_cc6ce8_Static);
            if (Cast<UnnamedActor_cbc930>(P->Controller, &UnnamedClass_cbc930_Static))
                break;
        }
    }
    if (P)
        P->ProcessEvent(P->FindFunctionChecked(FName(NAME_Unnamed_F27)), 0);

    INT Result = 0;
    for (INT j = 0; j < 8; j++) {
        UnnamedPlayerActor *S = Source ? Source->Slots[j] : Slots[j];
        for (INT i = 0; i < Players.Num(); i++) {
            UnnamedPlayer *Player = Players(i);
            if (Player->Actor && S == Player->Actor)
                Result = Player->Notify(A, B);
        }
    }
    return Result;
}

UBOOL UnnamedNetOwner::Read(BYTE *Dest, INT Size)
{
    if (Dest) {
        if (Count >= Size) {
            if (1000 - Head >= Size) {
                appMemcpy(Dest, &Buffer[Head], Size);
                Head = (DWORD)(Head + Size) % 1000;
                Count -= Size;
            } else {
                INT Avail = 1000 - Head;
                appMemcpy(Dest, &Buffer[Head], Avail);
                appMemcpy(Dest + Avail, Buffer, Size - Avail);
                Head = Size - Avail;
                Count -= Size;
            }
            if (Count == 0)
                Head = 0;
            return 1;
        }
    } else {
        Count = 0;
        Head = 0;
    }
    return 0;
}

void UnnamedNetOwner::Write(const BYTE *Src, DWORD Size)
{
    double Now = appSeconds();
    if (Now - LastTime > RingBuffer_Timeout) {
        Count = 0;
        Head = 0;
    }
    LastTime = Now;
    if (1000 - Count < Size)
        return;
    DWORD Pos = (DWORD)(Head + Count) % 1000;
    INT Space = 1000 - Pos;
    if (Space >= (INT)Size) {
        appMemcpy(&Buffer[Pos], Src, Size);
    } else {
        appMemcpy(&Buffer[Pos], Src, Space);
        appMemcpy(Buffer, Src + Space, Size - Space);
    }
    Count += Size;
}

// Scaffolding for the link, not part of the unit: the holder wrappers retail has at
// 0xf8330 / 0xf8370, and drivers that call them the way retail does.
void Escape(void *);

class UnnamedHolder {
public:
    BYTE Pad[0xec];
    UnnamedNetOwner *Net; // +0xec
    INT NotifyNet(INT A, INT B)
    {
        UnnamedNetOwner *N = Net;
        if (!N)
            return 0;
        if (!N->LocalPlayer)
            return N->NotifySlots(A, B, 0);
        if (N->LocalPlayer)
            return N->LocalPlayer->Notify(A, B);
        return 0;
    }
    UBOOL ReadNet(BYTE *Dest, INT Size)
    {
        if (Net)
            return Net->Read(Dest, Size);
        return 0;
    }
};

INT Driver_ef430(UnnamedHolder *H, INT A, INT B)
{
    Escape(&UnnamedClass_cc6ce8_Static);
    Escape(&UnnamedClass_cbc930_Static);
    return H->NotifyNet(A, B);
}
INT Driver_ef580(UnnamedHolder *H, BYTE *D, INT N) { return H->ReadNet(D, N); }
void Driver_ef650(UnnamedNetOwner *R, const BYTE *S, DWORD N) { Escape(&RingBuffer_Timeout); R->Write(S, N); }
