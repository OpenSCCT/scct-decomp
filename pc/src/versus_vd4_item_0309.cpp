// Work item 0309: Versus RVA 0x81ca0 and 0x81d00.
// Neutral names: the owning class is a UObject subclass (Outer at 0x18,
// ObjectFlags at 0x1c) holding a TArray of 0x2c-byte records at 0x118.
typedef int INT;
typedef unsigned long DWORD;

class UObject;

// 0x2c-byte record; the first field is a key compared against.
struct FUnnamedRecord_81ca0
{
    INT Key;
    INT Pad[10];
    void Bind(UObject *InOuter); // retail 0x9df5e0
};

template <class T> struct TArray
{
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

class UnnamedClass_81ca0
{
public:
    virtual void Destroy();
    void *Pad04[5];
    UObject *Outer;          // 0x18
    DWORD ObjectFlags;       // 0x1c
    char Pad20[0x118 - 0x20];
    TArray<FUnnamedRecord_81ca0> Records; // 0x118

    void Refresh();          // retail 0x81ca0
    void ConditionalLoad();  // retail 0x16f70
};

void UnnamedClass_81ca0::Refresh()
{
    ObjectFlags |= 0x20000000;
    if (ObjectFlags & 0x100)
        ConditionalLoad();
    for (INT i = 0; i < Records.Num(); i++)
        Records(i).Bind(Outer);
}

// Class at 0x81d00: virtual slot 32 (vtable +0x80) yields the record owner.
class UnnamedClass_81d00
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void Slot04();
    virtual void Slot05();
    virtual void Slot06();
    virtual void Slot07();
    virtual void Slot08();
    virtual void Slot09();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual void Slot31();
    virtual UnnamedClass_81ca0 *GetRecordOwner(); // vtable +0x80

    FUnnamedRecord_81ca0 *FindRecord(INT Key); // retail 0x81d00
};

FUnnamedRecord_81ca0 *UnnamedClass_81d00::FindRecord(INT Key)
{
    UnnamedClass_81ca0 *Owner = GetRecordOwner();
    for (INT i = 0; i < Owner->Records.Num(); i++)
        if (Key == Owner->Records(i).Key)
            return &Owner->Records(i);
    return 0;
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit. Retail 0x16f70 and
// 0xdf5e0 are themselves LTCG functions taking `this` in ESI and EDI; these
// rough stand-ins give the linker callees with the same register needs.
// Only Refresh (0x81ca0) is compared.
struct FUnnamedEntry_df5e0 { INT A; INT B; INT C; };
void *ConstructHelper(void *Cls, INT Outer, INT Flags, INT Kind, INT, DWORD, INT, INT);
void RegisterHelper(void *Obj);
void LoadHelper(void *Cls, INT Outer, INT Name, UnnamedClass_81ca0 *Obj);
extern void *GHelperClass;
extern INT GDefaultOuter;
extern DWORD GHelperFlags;

__declspec(noinline) void FUnnamedRecord_81ca0::Bind(UObject *InOuter)
{
    TArray<FUnnamedEntry_df5e0> &E = *(TArray<FUnnamedEntry_df5e0> *)&Pad[6];
    for (INT i = 0; i < E.Num(); i++) {
        if (E(i).B) {
            INT O = (INT)InOuter;
            if (O == -1) O = GDefaultOuter;
            void *Obj = ConstructHelper(&GHelperClass, O, 0, 4, 0, GHelperFlags, 0, 0);
            if (Obj) RegisterHelper(Obj);
            ((INT *)Obj)[11] = E(i).B;
            E(i).C = (INT)Obj;
            E(i).B = 0;
        }
    }
}

__declspec(noinline) void UnnamedClass_81ca0::ConditionalLoad()
{
    INT *Cls = ((INT **)this)[9];
    if (Cls[0x22] & 0x20) {
        INT Idx = ((INT *)this)[1];
        if (Idx != -1 && (ObjectFlags & 0x100) && ((INT *)Outer)[6]) {
            RegisterHelper(((INT **)Outer)[6]);
            LoadHelper(Cls, ((INT *)Outer)[8], ((INT *)this)[8], this);
        } else {
            RegisterHelper(Idx == -1 ? (void *)Cls[6] : (void *)Outer);
            LoadHelper(Cls, Idx, Idx == -1 ? Cls[8] : ((INT *)this)[8], this);
        }
    }
}

void Escape(void *);
// Retail reaches Refresh through its address (standard thiscall), so the
// driver takes the address instead of calling it directly.
void Driver_81ca0()
{
    void (UnnamedClass_81ca0::*P)() = &UnnamedClass_81ca0::Refresh;
    Escape(&P);
}
