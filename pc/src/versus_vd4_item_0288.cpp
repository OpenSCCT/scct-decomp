// Work item 0288: Versus RVA 0x74bf0-0x74e8b (LTCG unit, custom calling conventions).
// Neutral names: no symbol evidence for this subsystem. Layouts follow item 0286
// (owner +0x108 renderer, +0x2af10 state; state +0x534 page of 0x7c-byte entries).
// The renderer holds an IDirect3DDevice8 at +0x46a4; slot 50 (+0xc8) is
// SetRenderState. 0x91/0x94 are D3DRS_DIFFUSEMATERIALSOURCE / EMISSIVEMATERIALSOURCE.
// The 0x68-byte record at state +0x1b8 is a D3DLIGHT8.
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;

class IDirect3DDevice8
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26(); virtual void Slot27();
    virtual void Slot28(); virtual void Slot29(); virtual void Slot30(); virtual void Slot31();
    virtual void Slot32(); virtual void Slot33(); virtual void Slot34(); virtual void Slot35();
    virtual void Slot36(); virtual void Slot37(); virtual void Slot38(); virtual void Slot39();
    virtual void Slot40(); virtual void Slot41(); virtual void Slot42(); virtual void Slot43();
    virtual void Slot44(); virtual void Slot45(); virtual void Slot46(); virtual void Slot47();
    virtual void Slot48(); virtual void Slot49();
    virtual INT __stdcall SetRenderState(DWORD State, DWORD Value);
};

enum
{
    D3DRS_DIFFUSEMATERIALSOURCE = 145,
    D3DRS_EMISSIVEMATERIALSOURCE = 148,
};

struct D3DCOLORVALUE { FLOAT r, g, b, a; };
struct D3DVECTOR { FLOAT x, y, z; };
struct D3DLIGHT8
{
    INT Type;
    D3DCOLORVALUE Diffuse;      // +0x04
    D3DCOLORVALUE Specular;     // +0x14
    D3DCOLORVALUE Ambient;      // +0x24
    D3DVECTOR Position;
    D3DVECTOR Direction;
    FLOAT Range, Falloff, Attenuation0, Attenuation1, Attenuation2, Theta, Phi;
};

struct UnnamedBlock_74bf0 { FLOAT D[16]; };

// 0x7c-byte entry stored in a page (array at page + 0x34).
struct UnnamedEntry_6d180
{
    INT Field00;
    INT Field04[11];
    INT Field30;                    // +0x30
    INT Field34;                    // +0x34
    INT Field38;                    // +0x38
    UnnamedBlock_74bf0 Block;       // +0x3c (+0x5c..+0x64 are floats)
};

struct UnnamedPage_71b00
{
    INT Pad0[0x30 / 4];
    INT Count;                          // +0x30
    UnnamedEntry_6d180 Entries[16];     // +0x34
};

struct UnnamedState_71b00
{
    char Pad0[0x1b8];
    D3DLIGHT8 Light;                    // +0x1b8
    char Pad220[0x4f8 - 0x220];
    INT LightDirty;                     // +0x4f8
    char Pad4FC[0x534 - 0x4fc];
    UnnamedPage_71b00 *Pages[8];        // +0x534
};

struct UnnamedRenderer_74ce0
{
    char Pad0[0x46a4];
    IDirect3DDevice8 *Device;           // +0x46a4
    char Pad46A8[0x2fbb4 - 0x46a8];
    INT LightEnabled;                   // +0x2fbb4
    char Pad2FBB8[0x300d4 - 0x2fbb8];
    D3DLIGHT8 Light;                    // +0x300d4
    char Pad3013C[0x30414 - 0x3013c];
    INT LightSet;                       // +0x30414
};

struct UnnamedOwner_71b00;

// Sub-object at owner + 0x2c (neutral name). Its own fields are not used here.
struct UnnamedSub_74d30
{
    void SetLight(UnnamedOwner_71b00 *Owner, INT Mode, INT Enable, FLOAT Level);
};

struct UnnamedOwner_71b00
{
    char Pad0[0x108];
    UnnamedRenderer_74ce0 *Renderer;    // +0x108
    char Pad10C[0x2af10 - 0x10c];
    UnnamedState_71b00 *State;          // +0x2af10

    void SetLightThunk_62180(INT Mode, INT Enable, FLOAT Level);
};

void __cdecl CopyLight_9040a0(D3DLIGHT8 *Dest, const D3DLIGHT8 *Src, INT Size);

// RVA 0x74bf0 (owner in EAX, one unused stack argument)
void __stdcall InitEntry2_74bf0(INT Unused, UnnamedOwner_71b00 *Owner)
{
    UnnamedPage_71b00 *Page = Owner->State->Pages[0];
    UnnamedBlock_74bf0 Zero;
    Zero.D[0] = 0.0f; Zero.D[1] = 0.0f; Zero.D[2] = 0.0f; Zero.D[3] = 0.0f;
    Zero.D[4] = 0.0f; Zero.D[5] = 0.0f; Zero.D[6] = 0.0f; Zero.D[7] = 0.0f;
    Zero.D[8] = 0.0f; Zero.D[9] = 0.0f; Zero.D[10] = 0.0f; Zero.D[11] = 0.0f;
    Zero.D[12] = 0.0f; Zero.D[13] = 0.0f; Zero.D[14] = 0.0f; Zero.D[15] = 0.0f;
    UnnamedEntry_6d180 &E = Page->Entries[2];
    E.Block = Zero;
    E.Block.D[10] = 0.0002f;
    E.Block.D[9] = 0.0002f;
    E.Block.D[8] = 0.0002f;
    E.Field38 = 1;
    E.Field30 = 0x20000;
    E.Field34 = 3;
    E.Field00 = 0;
    Page->Count = 3;
}

// RVA 0x74ce0 (owner on the stack)
__declspec(noinline) void __stdcall SetMaterialSources_74ce0(UnnamedOwner_71b00 *Owner)
{
    Owner->Renderer->Device->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, 1);
    Owner->Renderer->Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, 2);
}

// RVA 0x74d30 (owner in ESI, mode in ECX, three stack arguments)
// Retail passes this (owner + 0x2c) on the stack; it is unused.
void UnnamedSub_74d30::SetLight(UnnamedOwner_71b00 *Owner, INT Mode, INT Enable, FLOAT Level)
{
    Owner->State->Pages[0]->Entries[3].Field30 = (Mode == 2);
    D3DLIGHT8 *L = &Owner->State->Light;
    if (Enable && Mode != 3 && Mode != 2)
    {
        L->Diffuse.g = Level * 0.7f;
        L->Ambient.g = Level * 0.3f;
    }
    else if (Mode == 2)
    {
        Owner->Renderer->LightEnabled = 0;
        Owner->Renderer->Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, 2);
        return;
    }
    else if (Enable || Mode)
    {
        Owner->Renderer->LightSet = 0;
        Owner->Renderer->LightEnabled = 1;
        Owner->Renderer->Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, 0);
        return;
    }
    else
    {
        L->Diffuse.g = 0;
        L->Ambient.g = Level;
    }
    L->Diffuse.r = 0;
    L->Diffuse.b = 0;
    L->Ambient.r = 0;
    L->Ambient.b = 0;
    CopyLight_9040a0(&Owner->Renderer->Light, L, sizeof(D3DLIGHT8));
    Owner->Renderer->LightSet = 1;
    Owner->State->LightDirty = 1;
    Owner->Renderer->LightEnabled = 1;
    Owner->Renderer->Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, 0);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_74bf0(INT X, UnnamedOwner_71b00 *O) { InitEntry2_74bf0(X, O); InitEntry2_74bf0(X + 1, O + 1); }
void Driver_74ce0(UnnamedOwner_71b00 *O) { Escape((void *)&SetMaterialSources_74ce0); SetMaterialSources_74ce0(O); }
// RVA 0x62180 (retail caller, not part of this item)
void UnnamedOwner_71b00::SetLightThunk_62180(INT Mode, INT Enable, FLOAT Level)
{
    ((UnnamedSub_74d30 *)(Pad0 + 0x2c))->SetLight(this, Mode, Enable, Level);
}
typedef void (UnnamedOwner_71b00::*ThunkPtr)(INT, INT, FLOAT);
void Escape(ThunkPtr);
void Driver_74d30() { Escape(&UnnamedOwner_71b00::SetLightThunk_62180); }
