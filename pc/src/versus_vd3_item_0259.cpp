// Work item 0259: Versus RVA 0x608c0-0x60b80.
// A large render state-machine object (0x2b370 bytes) owned by the D3D render
// device. No class names survive, so neutral names keyed to the constructor
// RVA are used.

typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef long HRESULT;

struct IDirect3DSurface8;

// Direct3D 8 device interface, up to the two methods used here
// (vtable slots 32 and 33).
struct IDirect3DDevice8
{
    virtual HRESULT __stdcall QueryInterface(const void *Iid, void **Out) = 0;
    virtual DWORD __stdcall AddRef() = 0;
    virtual DWORD __stdcall Release() = 0;
    virtual HRESULT __stdcall TestCooperativeLevel() = 0;
    virtual DWORD __stdcall GetAvailableTextureMem() = 0;
    virtual HRESULT __stdcall ResourceManagerDiscardBytes(DWORD Bytes) = 0;
    virtual HRESULT __stdcall GetDirect3D(void **Out) = 0;
    virtual HRESULT __stdcall GetDeviceCaps(void *Caps) = 0;
    virtual HRESULT __stdcall GetDisplayMode(void *Mode) = 0;
    virtual HRESULT __stdcall GetCreationParameters(void *Params) = 0;
    virtual HRESULT __stdcall SetCursorProperties(DWORD X, DWORD Y, IDirect3DSurface8 *Bitmap) = 0;
    virtual void __stdcall SetCursorPosition(INT X, INT Y, DWORD Flags) = 0;
    virtual INT __stdcall ShowCursor(INT Show) = 0;
    virtual HRESULT __stdcall CreateAdditionalSwapChain(void *Params, void **Out) = 0;
    virtual HRESULT __stdcall Reset(void *Params) = 0;
    virtual HRESULT __stdcall Present(const void *Src, const void *Dst, void *Wnd, const void *Dirty) = 0;
    virtual HRESULT __stdcall GetBackBuffer(DWORD Index, DWORD Type, IDirect3DSurface8 **Out) = 0;
    virtual HRESULT __stdcall GetRasterStatus(void *Status) = 0;
    virtual void __stdcall SetGammaRamp(DWORD Flags, const void *Ramp) = 0;
    virtual void __stdcall GetGammaRamp(void *Ramp) = 0;
    virtual HRESULT __stdcall CreateTexture(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, void **) = 0;
    virtual HRESULT __stdcall CreateVolumeTexture(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, void **) = 0;
    virtual HRESULT __stdcall CreateCubeTexture(DWORD, DWORD, DWORD, DWORD, DWORD, void **) = 0;
    virtual HRESULT __stdcall CreateVertexBuffer(DWORD, DWORD, DWORD, DWORD, void **) = 0;
    virtual HRESULT __stdcall CreateIndexBuffer(DWORD, DWORD, DWORD, DWORD, void **) = 0;
    virtual HRESULT __stdcall CreateRenderTarget(DWORD, DWORD, DWORD, DWORD, INT, IDirect3DSurface8 **) = 0;
    virtual HRESULT __stdcall CreateDepthStencilSurface(DWORD, DWORD, DWORD, DWORD, IDirect3DSurface8 **) = 0;
    virtual HRESULT __stdcall CreateImageSurface(DWORD, DWORD, DWORD, IDirect3DSurface8 **) = 0;
    virtual HRESULT __stdcall CopyRects(IDirect3DSurface8 *, const void *, DWORD, IDirect3DSurface8 *, const void *) = 0;
    virtual HRESULT __stdcall UpdateTexture(void *Src, void *Dst) = 0;
    virtual HRESULT __stdcall GetFrontBuffer(IDirect3DSurface8 *Dest) = 0;
    virtual HRESULT __stdcall SetRenderTarget(IDirect3DSurface8 *Target, IDirect3DSurface8 *Depth) = 0;
    virtual HRESULT __stdcall GetRenderTarget(IDirect3DSurface8 **Out) = 0;
    virtual HRESULT __stdcall GetDepthStencilSurface(IDirect3DSurface8 **Out) = 0;
};

// The owning render device; only the Direct3D device pointer is used here.
class UD3DRenderDevice
{
public:
    BYTE Pad0[0x46a4];
    IDirect3DDevice8 *Direct3DDevice8;
};

// The viewport being rendered; only its size is used here.
class UViewport
{
public:
    BYTE Pad0[0xa0];
    INT SizeX;
    INT SizeY;
};

// Unreal dynamic array (layout as in Core's FArray/TArray).
template<class T> class TArray
{
public:
    TArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
};

class UnnamedMachine_608c0;

// Embedded state objects: each is only a vtable. Slot 0 is entered when the
// machine switches to the state, slot 1 when it leaves (see 0x60a90).
class UnnamedState_608c0
{
public:
    virtual void Enter(UnnamedMachine_608c0 *Machine) = 0;
    virtual void Exit(UnnamedMachine_608c0 *Machine) = 0;
};

#define DECLARE_STATE(N) \
    class UnnamedState_608c0_##N : public UnnamedState_608c0 \
    { \
    public: \
        virtual void Enter(UnnamedMachine_608c0 *Machine); \
        virtual void Exit(UnnamedMachine_608c0 *Machine); \
    };

DECLARE_STATE(28)
DECLARE_STATE(2c)
DECLARE_STATE(30)
DECLARE_STATE(34)
DECLARE_STATE(3c)
DECLARE_STATE(40)
DECLARE_STATE(44)
DECLARE_STATE(48)
DECLARE_STATE(4c)
DECLARE_STATE(50)
DECLARE_STATE(54)
DECLARE_STATE(58)
DECLARE_STATE(64)
DECLARE_STATE(68)
DECLARE_STATE(70)
DECLARE_STATE(7c)

// 0x55c-byte render pass record, constructed by 0x60660. Its first fields are
// filled in by 0x60ac0.
class UnnamedPass_60660
{
public:
    UnnamedPass_60660();
    IDirect3DSurface8 *RenderTarget;
    IDirect3DSurface8 *DepthStencil;
    INT X;
    INT Y;
    INT SizeX;
    INT SizeY;
    BYTE Pad18[0x55c - 0x18];
};

// Sub-object at 0x2af14, constructed by 0x6ce90 (item 0282).
struct UnnamedEntry_6ce90
{
    INT A0;
    INT A1, A2, A3;
    float A4;
    INT A5, A6;
    INT B0, B1, B2, B3, B4;
    INT C0, C1, C2;
    BYTE Matrix[0x40];
};
void appMemcpy(void *Dest, const void *Src, INT Count);
extern BYTE UnnamedEntry_6ce90_DefaultMatrix[0x40];

class UnnamedObject_6ce90
{
public:
    UnnamedObject_6ce90();
    INT H0, H1;
    BYTE H2;
    INT H3, H4, H5, H6, H7, H8, H9, H10, H11, H12;
    UnnamedEntry_6ce90 Entries[8];
    INT T0, T1;
    BYTE Pad[0x2b344 - 0x2af14 - 0x41c];
};

class UnnamedMachine_608c0
{
public:
    UnnamedMachine_608c0(UD3DRenderDevice *InRenDev);
    virtual void Flush();
    void SetState(INT NewState);
    void Begin(UViewport *InViewport, INT InA, INT InB);

    INT Field04;
    INT Field08;
    INT Field0C;
    INT StateIndex;                     // 0x10
    UnnamedState_608c0 *CurrentState;   // 0x14
    INT Field18;
    INT Field1C;
    INT Field20;
    INT Field24;
    UnnamedState_608c0_28 State28;
    UnnamedState_608c0_2c State2c;
    UnnamedState_608c0_30 State30;
    UnnamedState_608c0_34 State34;
    INT Field38;
    UnnamedState_608c0_3c State3c;
    UnnamedState_608c0_40 State40;
    UnnamedState_608c0_44 State44;
    UnnamedState_608c0_48 State48;
    UnnamedState_608c0_4c State4c;
    UnnamedState_608c0_50 State50;
    UnnamedState_608c0_54 State54;
    UnnamedState_608c0_58 State58;
    INT Field5C;
    INT Field60;
    UnnamedState_608c0_64 State64;
    UnnamedState_608c0_68 State68;
    INT Field6C;
    UnnamedState_608c0_70 State70;
    INT Field74;
    INT Field78;
    UnnamedState_608c0_7c State7c;
    BYTE Pad80[0xc4 - 0x80];
    UnnamedState_608c0 *States[16];     // 0xc4
    BYTE Field104;
    UD3DRenderDevice *RenDev;           // 0x108
    UViewport *Viewport;                // 0x10c
    UnnamedPass_60660 Passes[128];      // 0x110
    UnnamedPass_60660 *CurrentPass;     // 0x2af10
    UnnamedObject_6ce90 Object2af14;
    INT Field2b344;
    TArray<INT> Array2b348;
    INT Field2b354;
    TArray<INT> Array2b358;
    INT Field2b364;
    INT Field2b368;
    INT Field2b36c;
};

// RVA 0x608c0 (LTCG: this in ESI, argument on the stack).
UnnamedMachine_608c0::UnnamedMachine_608c0(UD3DRenderDevice *InRenDev)
    : Field04(0), Field08(0), Field1C(0), Field104(0xff)
{
    RenDev = InRenDev;
    CurrentPass = &Passes[0];
    States[0] = &State28;
    States[1] = &State2c;
    States[2] = &State30;
    States[3] = &State34;
    States[4] = &State3c;
    States[5] = &State44;
    States[6] = &State48;
    States[7] = &State4c;
    States[8] = &State50;
    States[9] = &State54;
    States[10] = &State58;
    States[11] = &State64;
    States[13] = &State68;
    Viewport = 0;
    Field2b36c = 0;
    Field2b364 = 0;
    Field2b368 = 0;
    Field2b344 = 0;
    States[14] = &State70;
    States[15] = &State7c;
    Field2b354 = 1;
    StateIndex = 0;
    CurrentState = States[StateIndex];
}

// RVA 0x60a90.
void UnnamedMachine_608c0::SetState(INT NewState)
{
    if (StateIndex != NewState)
    {
        CurrentState->Exit(this);
        CurrentState = States[NewState];
        CurrentState->Enter(this);
        StateIndex = NewState;
    }
}

// RVA 0x60ac0 (LTCG: this in ESI, arguments in EAX, ECX and EDX).
void UnnamedMachine_608c0::Begin(UViewport *InViewport, INT InA, INT InB)
{
    Viewport = InViewport;
    Field2b36c = 0;
    Field2b364 = InB;
    Field2b368 = InA;
    IDirect3DSurface8 *RenderTarget = 0;
    IDirect3DSurface8 *DepthStencil = 0;
    RenDev->Direct3DDevice8->GetRenderTarget(&RenderTarget);
    RenDev->Direct3DDevice8->GetDepthStencilSurface(&DepthStencil);
    CurrentPass->X = 0;
    CurrentPass->Y = 0;
    CurrentPass->SizeX = Viewport->SizeX;
    CurrentPass->SizeY = Viewport->SizeY;
    CurrentPass->DepthStencil = DepthStencil;
    CurrentPass->RenderTarget = RenderTarget;
    Field2b344 = 0;
    Flush();
}

// Scaffolding for the link, not part of the unit: a stand-in body for
// 0x6ce90 so the linker gives it retail's this-on-the-stack convention.
UnnamedObject_6ce90::UnnamedObject_6ce90()
{
    for (INT i = 0; i < 8; i++)
    {
        UnnamedEntry_6ce90 &E = Entries[i];
        appMemcpy(E.Matrix, UnnamedEntry_6ce90_DefaultMatrix, 0x40);
        E.A1 = E.A2 = E.A3 = 3;
        E.A5 = E.A6 = 2;
        E.C2 = E.C0 = E.C1 = 0;
        E.A4 = -1000.f;
        E.A0 = 0;
        E.B0 = E.B1 = E.B2 = E.B3 = E.B4 = 1;
    }
    H3 = H4 = H9 = 1;
    H6 = H8 = 2;
    H0 = H1 = 0; H2 = 0; H5 = H7 = H12 = H10 = 0;
    T0 = T1 = 0;
}
inline void *operator new(unsigned int, void *Where) { return Where; }
void Driver_608c0(void *Mem, UD3DRenderDevice *RenDev)
{
    new (Mem) UnnamedMachine_608c0(RenDev);
}
void Driver_60ac0(UnnamedMachine_608c0 *Machine, UViewport *Viewport, INT A, INT B)
{
    Machine->Begin(Viewport, A, B);
}
