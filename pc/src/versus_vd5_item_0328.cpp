// Work item 0328: Versus RVA 0x10c520-0x10c760, UMagmaInteraction virtual methods.
// The object was compiled with /GL and linked with /LTCG (callees take
// arguments in registers), so this unit is checked with try_ltcg.py.
typedef unsigned long DWORD;
typedef int INT;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned short _WORD;

struct FColor {
    BYTE B, G, R, A;
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA) : B(InB), G(InG), R(InR), A(InA) {}
};

class FRenderInterface {
public:
    virtual void PushState();
    virtual void PopState();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void Clear(UBOOL UseColor, FColor Color, UBOOL UseDepth, FLOAT Depth, UBOOL UseStencil, DWORD Stencil);
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void SetViewport(INT X, INT Y, INT W, INT H);
};

// Neutral name: the object at canvas+0x7c holding a render interface at +0x10.
// Begin (0x112180) and End (0x112240) take this in ESI in retail. Their bodies
// here are short stand-ins (not matched) so LTCG gives them the same register
// convention; they belong to work item 0351.
class UnnamedRenderTarget_112180 {
public:
    BYTE Pad0[0x10];
    FRenderInterface *RI;
    __declspec(noinline) void Begin();
    __declspec(noinline) void End();
};
void UnnamedRenderTarget_112180::Begin() { RI->PushState(); RI->SetViewport(0, 0, 0, 0); }
void UnnamedRenderTarget_112180::End() { RI->SetViewport(0, 0, 0, 0); RI->PopState(); }

// Neutral name: the canvas-like object passed to slots 27 and 28.
struct UnnamedCanvas_10c520 {
    BYTE Pad0[0x3c];
    INT Field3C;
    INT Field40;
    INT Pad44;
    BYTE Field48;
    BYTE Pad49[0x7c - 0x49];
    UnnamedRenderTarget_112180 *Target;
};

// Queued key entry (8 bytes) and its std::vector-style container.
struct FQueuedKey {
    INT Key;
    _WORD Flag;
};
class FQueuedKeyVector {
public:
    BYTE Allocator;
    FQueuedKey *First;
    FQueuedKey *Last;
    FQueuedKey *End;
    INT Num() const { return First == 0 ? 0 : (INT)(Last - First); }
    void Clear();                        // 0x39f6a0
    void AddHeld(const FQueuedKey &K);   // 0x39f750
    void AddReleased(const FQueuedKey &K); // 0x39f780
};

// Neutral name: the global object at 0x10c75e94.
struct UnnamedMagmaManager {
    BYTE Pad0[0x10];
    FQueuedKeyVector Queue;
};
extern UnnamedMagmaManager *GMagmaManager;

// Neutral name: the object at 0x10c923c4 (+0x44) that sees input first.
class UnnamedInputHandler {
public:
    virtual void VirtualSlot0(); virtual void VirtualSlot1(); virtual void VirtualSlot2(); virtual void VirtualSlot3();
    virtual void VirtualSlot4(); virtual void VirtualSlot5(); virtual void VirtualSlot6(); virtual void VirtualSlot7();
    virtual void VirtualSlot8(); virtual void VirtualSlot9(); virtual void VirtualSlot10(); virtual void VirtualSlot11();
    virtual void VirtualSlot12(); virtual void VirtualSlot13(); virtual void VirtualSlot14(); virtual void VirtualSlot15();
    virtual void VirtualSlot16(); virtual void VirtualSlot17(); virtual void VirtualSlot18(); virtual void VirtualSlot19();
    virtual void VirtualSlot20(); virtual void VirtualSlot21(); virtual void VirtualSlot22(); virtual void VirtualSlot23();
    virtual void VirtualSlot24(); virtual void VirtualSlot25(); virtual void VirtualSlot26(); virtual void VirtualSlot27();
    virtual UBOOL InputEvent(INT Key, INT Action, FLOAT Delta);
};
struct UnnamedEngine_923c4 {
    BYTE Pad0[0x44];
    UnnamedInputHandler *Handler;
};
extern UnnamedEngine_923c4 *GEngine_923c4;

// Neutral name: the argument of slot 10, which registers the manager (0x24c350).
class UnnamedSlot10Arg {
public:
    void Register(UnnamedMagmaManager *Manager);
};

// Maps a key code to an internal code (0x10c310, published in w3_item_0327).
UBOOL MapKeyCode_10c310(INT Key, DWORD *Out)
{
    switch (Key) {
    case 0x08: case 0x1b: case 0x2e: case 0xc9: *Out = 0x81; return 1;
    case 0x11: *Out = 0x11; return 1;
    case 0x70: *Out = 0x54; return 1;
    case 0x21: case 0x26: case 0xd4: *Out = 0x26; return 1;
    case 0x27: case 0xd5: *Out = 0x27; return 1;
    case 0x22: case 0x28: case 0xd6: *Out = 0x28; return 1;
    case 0x25: case 0xd7: *Out = 0x25; return 1;
    case 0x24: case 0xc8: *Out = 0x83; return 1;
    case 0x0d: case 0x20: case 0xca: *Out = 0x80; return 1;
    case 0x23: case 0xcb: *Out = 0x82; return 1;
    case 0xd3: *Out = 0x84; return 1;
    case 0xff: *Out = 0x8a; return 1;
    }
    if ((Key >= 'A' && Key <= 'Z') || (Key >= '0' && Key <= '9')) {
        *Out = 0;
        return 1;
    }
    return 0;
}

// Base class: slot 10 (0x115f50) is shared with many UObject classes.
class UObjectBase {
public:
    UObjectBase();
    virtual void VirtualSlot0(); virtual void VirtualSlot1(); virtual void VirtualSlot2(); virtual void VirtualSlot3();
    virtual void VirtualSlot4(); virtual void VirtualSlot5(); virtual void VirtualSlot6(); virtual void VirtualSlot7();
    virtual void VirtualSlot8(); virtual void VirtualSlot9();
    virtual void VirtualSlot10(UnnamedSlot10Arg *Arg);
    virtual void VirtualSlot11(); virtual void VirtualSlot12(); virtual void VirtualSlot13(); virtual void VirtualSlot14();
    virtual void VirtualSlot15(); virtual void VirtualSlot16(); virtual void VirtualSlot17(); virtual void VirtualSlot18();
    virtual void VirtualSlot19(); virtual void VirtualSlot20(); virtual void VirtualSlot21(); virtual void VirtualSlot22();
    virtual void VirtualSlot23(); virtual void VirtualSlot24(); virtual void VirtualSlot25(); virtual void VirtualSlot26();
    virtual void PreRender(UnnamedCanvas_10c520 *Canvas);
    virtual void PostRender(UnnamedCanvas_10c520 *Canvas);
    virtual void VirtualSlot29();
    virtual UBOOL InputEvent(INT Key, INT Action, FLOAT Delta);
    virtual UBOOL KeyPressed(INT Key, FLOAT Delta);
    virtual UBOOL KeyHeld(INT Key, FLOAT Delta);
    virtual UBOOL KeyReleased(INT Key, FLOAT Delta);
    BYTE Pad4[0x30];
    DWORD Flags34;
};

class UMagmaInteraction : public UObjectBase {
public:
    UMagmaInteraction() {}
    virtual void VirtualSlot10(UnnamedSlot10Arg *Arg);
    virtual void PreRender(UnnamedCanvas_10c520 *Canvas);
    virtual void PostRender(UnnamedCanvas_10c520 *Canvas);
    virtual UBOOL InputEvent(INT Key, INT Action, FLOAT Delta);
    virtual UBOOL KeyHeld(INT Key, FLOAT Delta);
    virtual UBOOL KeyReleased(INT Key, FLOAT Delta);
};

// 0x10c520, slot 27.
void UMagmaInteraction::PreRender(UnnamedCanvas_10c520 *Canvas)
{
    Canvas->Field48 = 1;
    Canvas->Field3C = 0;
    Canvas->Field40 = 0;
    PostRender(Canvas);
}

// 0x10c570, slot 10.
void UMagmaInteraction::VirtualSlot10(UnnamedSlot10Arg *Arg)
{
    UObjectBase::VirtualSlot10(Arg);
    Arg->Register(GMagmaManager);
}

// 0x10c5a0, slot 28.
void UMagmaInteraction::PostRender(UnnamedCanvas_10c520 *Canvas)
{
    Canvas->Target->Begin();
    Canvas->Target->RI->Clear(0, FColor(0, 0, 0, 255), 1, 1.0f, 0, 0);
    GMagmaManager->Queue.Clear();
    UnnamedRenderTarget_112180 *Target = Canvas->Target;
    Target->End();
    Target->RI->PopState();
}

// 0x10c600, slot 30.
UBOOL UMagmaInteraction::InputEvent(INT Key, INT Action, FLOAT Delta)
{
    if (GEngine_923c4->Handler->InputEvent(Key, Action, Delta))
        return 1;
    if (Flags34 & 1)
        return 0;
    switch (Action) {
    case 1: return KeyPressed(Key, Delta);
    case 2: return KeyHeld(Key, Delta);
    case 3: return KeyReleased(Key, Delta);
    default: return 0;
    }
}

// 0x10c690, slot 32.
UBOOL UMagmaInteraction::KeyHeld(INT Key, FLOAT Delta)
{
    UnnamedMagmaManager *M = GMagmaManager;
    if (M->Queue.Num() && MapKeyCode_10c310(Key, (DWORD *)&Key) && Key >= 0x25 && Key <= 0x28) {
        FQueuedKey Entry;
        Entry.Key = Key;
        Entry.Flag = 0;
        M->Queue.AddHeld(Entry);
        return 1;
    }
    return 0;
}

// 0x10c700, slot 33.
UBOOL UMagmaInteraction::KeyReleased(INT Key, FLOAT Delta)
{
    UnnamedMagmaManager *M = GMagmaManager;
    if (M->Queue.Num() && MapKeyCode_10c310(Key, (DWORD *)&Key)) {
        FQueuedKey Entry;
        Entry.Key = Key;
        Entry.Flag = 0;
        M->Queue.AddReleased(Entry);
        return 1;
    }
    return 0;
}

// Scaffolding for the link, not part of the unit: building the object emits
// the vtable, which keeps the virtual methods on the standard convention.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
void Driver_10c520(void *Mem)
{
    Escape(&GEngine_923c4);
    new (Mem) UMagmaInteraction;
}
