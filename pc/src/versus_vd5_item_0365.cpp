// Work item 0365 (vwork3): Versus RVA 0x1164b0-0x116985.
// LTCG unit. Class names are neutral: no vtable labels or strings identify them.
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;

class UnnamedListener_116940 {
public:
    virtual void Begin();   // slot 0
    virtual void End();     // slot 1
};

class UnnamedRenderer_111c60 {
public:
    INT Pad[3];
    INT Count;              // +0x0c
    UnnamedListener_116940 *Target; // +0x10
};

struct UnnamedViewport_68 {
    char Pad[0x7c];
    UnnamedRenderer_111c60 *Renderer; // +0x7c
};

class UnnamedClient_116940 {
public:
    char Pad[0x68];
    UnnamedViewport_68 *Viewport;     // +0x68
    UnnamedListener_116940 *Sink;     // +0x70
};

void __stdcall UnnamedFlush_10b050(UnnamedClient_116940 *Client);   // retail 0x10b050

// Retail 0x146800 and 0x111c60 take their argument in EBX and ESI (LTCG).
// The bodies below are stand-ins so the linker picks those registers; they are
// scaffolding, not reconstructions.
struct UnnamedNode_146800 { virtual __int64 F(); INT Pad[5]; INT Busy; UnnamedNode_146800 *Next; INT Refs; };
struct UnnamedSinkTable_146800 { virtual void Use(__int64 A); };
struct FMallocLike { virtual void A(); virtual void B(); virtual void Free(void *P); };
extern FMallocLike *GMalloc;
extern UnnamedNode_146800 *GUnnamedList_146800;
__declspec(noinline) void UnnamedTick_146800(UnnamedClient_116940 *Client)
{
    UnnamedNode_146800 *Prev = 0;
    for (UnnamedNode_146800 *N = GUnnamedList_146800; N; N = Prev ? Prev->Next : GUnnamedList_146800) {
        N->Busy = 0;
        if (--N->Refs <= 0) {
            if (Prev) Prev->Next = N->Next; else GUnnamedList_146800 = N->Next;
            N->Next = 0;
            Client->Sink->End();
            N = Prev;
        }
        Prev = N;
    }
}
__declspec(noinline) void UnnamedDraw_111c60(UnnamedRenderer_111c60 *R)
{
    if (R->Count > 0) {
        R->Target->Begin();
        R->Target->End();
    }
}

class UnnamedHandler_116940 {
public:
    // vtable at +0x00
    UnnamedClient_116940 *Client;     // +0x04
    void Dispatch_115da0(UnnamedListener_116940 *L, INT Flag);  // retail 0x115da0
    virtual void Process(UnnamedListener_116940 *L, INT Unused);
};

void UnnamedHandler_116940::Process(UnnamedListener_116940 *L, INT Unused)
{
    L->Begin();
    Dispatch_115da0(L, 1);
    UnnamedFlush_10b050(Client);
    UnnamedTick_146800(Client);
    UnnamedDraw_111c60(Client->Viewport->Renderer);
    L->End();
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void *operator new(unsigned int Size);
void Driver_116940(UnnamedHandler_116940 *H, UnnamedListener_116940 *L, INT U)
{
    Escape(new UnnamedHandler_116940);
    Escape(&GUnnamedList_146800);
    Escape(&GMalloc);
    H->Process(L, U);
}
