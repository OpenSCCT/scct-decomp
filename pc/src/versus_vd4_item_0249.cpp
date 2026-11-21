// Work item 0249: Versus RVA 0x5b7d0-0x5b8ff.
// Names are neutral: a hashed cache inside the D3D render device
// (UD3DRenderDevice vtable slot 31 uses it). Field layout from the retail code.

typedef unsigned long DWORD;
typedef int INT;
typedef DWORD UBOOL;
typedef unsigned __int64 QWORD;

#pragma pack(push, 4)  // Unreal builds packed to 4 bytes
struct FCachedResource_5b7d0 {
    virtual void Destroy(INT Flags);   // slot 0, called with 1 (deleting destructor)
    DWORD Pad04;
    QWORD CacheId;                     // +0x08
    DWORD Pad10[3];
    FCachedResource_5b7d0 *HashNext;   // +0x1c
};
#pragma pack(pop)

struct UnnamedDevice_5b7d0 {
    char Pad[0xb4];
    FCachedResource_5b7d0 *Hash[4096]; // +0xb4

    static FCachedResource_5b7d0 *__stdcall FindCached(UnnamedDevice_5b7d0 *Device, QWORD CacheId);
    void FlushCached(QWORD CacheId);
};

// RVA 0x5b7d0
FCachedResource_5b7d0 *__stdcall UnnamedDevice_5b7d0::FindCached(UnnamedDevice_5b7d0 *Device, QWORD CacheId)
{
    DWORD Low = (DWORD)CacheId;
    DWORD Index = (((Low >> 4) & 0xff0) + ((Low >> 16) & 0xf)) ^ (Low & 0xfff);
    for (FCachedResource_5b7d0 *Res = Device->Hash[Index]; Res; Res = Res->HashNext)
        if (Res->CacheId == CacheId)
            return Res;
    return 0;
}

// RVA 0x5b830 (UD3DRenderDevice vtable slot 31)
void UnnamedDevice_5b7d0::FlushCached(QWORD CacheId)
{
    FCachedResource_5b7d0 *Res = FindCached(this, CacheId);
    if (Res)
        Res->Destroy(1);
}

// ---------------------------------------------------------------------------
// RVA 0x5b850: find-or-create a vertex shader for a stream declaration in a
// linked list on the D3D render device (head at +0x40b4). Built with /GL;
// LTCG passes the shader type in EBX. 0x602e0 compares declarations, 0x6a700
// constructs the node (its IDirect3DDevice8 call is slot 75,
// CreateVertexShader). Names are neutral where the evidence is thin.

typedef unsigned short TCHAR;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
inline void operator delete(void *Ptr, const TCHAR *Tag) { GMalloc->Free(Ptr); }

extern const TCHAR VertexShaderTag_5b850[];   // allocation tag string at 0x10c109d8

struct FStreamComponent_5b850 { DWORD Type; DWORD Function; };
struct FStreamDecl_5b850 {
    FStreamComponent_5b850 Components[8];
    INT NumComponents;                 // +0x40
};
struct FShaderDeclaration_5b850 {
    FStreamDecl_5b850 Streams[16];
    INT NumStreams;                    // +0x440
    UBOOL operator==(const FShaderDeclaration_5b850 &Other) const;   // RVA 0x602e0
};

struct UnnamedDevice_5b850;

struct IDirect3DDevice8_5b850 {
    // Only slot 75 (CreateVertexShader) is used here.
    virtual void __stdcall Slot00(); virtual void __stdcall Slot01(); virtual void __stdcall Slot02();
    virtual void __stdcall Slot03(); virtual void __stdcall Slot04(); virtual void __stdcall Slot05();
    virtual void __stdcall Slot06(); virtual void __stdcall Slot07(); virtual void __stdcall Slot08();
    virtual void __stdcall Slot09(); virtual void __stdcall Slot10(); virtual void __stdcall Slot11();
    virtual void __stdcall Slot12(); virtual void __stdcall Slot13(); virtual void __stdcall Slot14();
    virtual void __stdcall Slot15(); virtual void __stdcall Slot16(); virtual void __stdcall Slot17();
    virtual void __stdcall Slot18(); virtual void __stdcall Slot19(); virtual void __stdcall Slot20();
    virtual void __stdcall Slot21(); virtual void __stdcall Slot22(); virtual void __stdcall Slot23();
    virtual void __stdcall Slot24(); virtual void __stdcall Slot25(); virtual void __stdcall Slot26();
    virtual void __stdcall Slot27(); virtual void __stdcall Slot28(); virtual void __stdcall Slot29();
    virtual void __stdcall Slot30(); virtual void __stdcall Slot31(); virtual void __stdcall Slot32();
    virtual void __stdcall Slot33(); virtual void __stdcall Slot34(); virtual void __stdcall Slot35();
    virtual void __stdcall Slot36(); virtual void __stdcall Slot37(); virtual void __stdcall Slot38();
    virtual void __stdcall Slot39(); virtual void __stdcall Slot40(); virtual void __stdcall Slot41();
    virtual void __stdcall Slot42(); virtual void __stdcall Slot43(); virtual void __stdcall Slot44();
    virtual void __stdcall Slot45(); virtual void __stdcall Slot46(); virtual void __stdcall Slot47();
    virtual void __stdcall Slot48(); virtual void __stdcall Slot49(); virtual void __stdcall Slot50();
    virtual void __stdcall Slot51(); virtual void __stdcall Slot52(); virtual void __stdcall Slot53();
    virtual void __stdcall Slot54(); virtual void __stdcall Slot55(); virtual void __stdcall Slot56();
    virtual void __stdcall Slot57(); virtual void __stdcall Slot58(); virtual void __stdcall Slot59();
    virtual void __stdcall Slot60(); virtual void __stdcall Slot61(); virtual void __stdcall Slot62();
    virtual void __stdcall Slot63(); virtual void __stdcall Slot64(); virtual void __stdcall Slot65();
    virtual void __stdcall Slot66(); virtual void __stdcall Slot67(); virtual void __stdcall Slot68();
    virtual void __stdcall Slot69(); virtual void __stdcall Slot70(); virtual void __stdcall Slot71();
    virtual void __stdcall Slot72(); virtual void __stdcall Slot73(); virtual void __stdcall Slot74();
    virtual long __stdcall CreateVertexShader(const DWORD *Declaration, const DWORD *Function, DWORD *Handle, DWORD Usage);
};

struct FVertexShaderBase_5b850 {
    DWORD Type;                        // +0x000
    FShaderDeclaration_5b850 Declaration;  // +0x004
    DWORD *DeclTokens;                 // +0x448
    INT NumTokens, MaxTokens;
    DWORD Handle;                      // +0x454
    UnnamedDevice_5b850 *RenDev;       // +0x458
    FVertexShaderBase_5b850 *NextShader;   // +0x45c
    FVertexShaderBase_5b850(UnnamedDevice_5b850 *InRenDev, const FShaderDeclaration_5b850 &InDecl);   // RVA 0x6a2f0
    ~FVertexShaderBase_5b850();
};

struct FVertexShader_5b850 : FVertexShaderBase_5b850 {
    FVertexShader_5b850(UnnamedDevice_5b850 *InRenDev, const FShaderDeclaration_5b850 &InDecl);   // RVA 0x6a700
};
#define FVertexShader_5b850_Next(S) ((FVertexShader_5b850 *)(S)->NextShader)

struct UnnamedDevice_5b850 {
    char Pad[0x40b4];
    FVertexShader_5b850 *VertexShaders;    // +0x40b4
    char Pad2[0x40d8 - 0x40b8];
    UBOOL UseHardwareTL;               // +0x40d8
    char Pad3[0x46a4 - 0x40dc];
    IDirect3DDevice8_5b850 *Direct3DDevice8;   // +0x46a4

    FVertexShader_5b850 *GetVertexShader(DWORD Type, const FShaderDeclaration_5b850 &Decl);
};

// RVA 0x602e0 (LTCG helper; not reported as matched)
UBOOL FShaderDeclaration_5b850::operator==(const FShaderDeclaration_5b850 &Other) const
{
    if (NumStreams != Other.NumStreams)
        return 0;
    for (INT i = 0; i < NumStreams; i++) {
        if (Streams[i].NumComponents != Other.Streams[i].NumComponents)
            return 0;
        for (INT j = 0; j < Streams[i].NumComponents; j++)
            if (Streams[i].Components[j].Type != Other.Streams[i].Components[j].Type ||
                Streams[i].Components[j].Function != Other.Streams[i].Components[j].Function)
                return 0;
    }
    return 1;
}

// RVA 0x6a700 (LTCG helper; not reported as matched)
FVertexShader_5b850::FVertexShader_5b850(UnnamedDevice_5b850 *InRenDev, const FShaderDeclaration_5b850 &InDecl)
    : FVertexShaderBase_5b850(InRenDev, InDecl)
{
    Type = 0;
    RenDev->Direct3DDevice8->CreateVertexShader(DeclTokens, 0, &Handle, InRenDev->UseHardwareTL ? 0 : 0x10);
}

FVertexShader_5b850 *UnnamedDevice_5b850::GetVertexShader(DWORD Type, const FShaderDeclaration_5b850 &Decl)
{
    for (FVertexShader_5b850 *Shader = VertexShaders; Shader; Shader = FVertexShader_5b850_Next(Shader))
        if (Shader->Type == Type && Decl == Shader->Declaration)
            return Shader;
    if (Type == 0)
        return new(VertexShaderTag_5b850) FVertexShader_5b850(this, Decl);
    return 0;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_5b850(UnnamedDevice_5b850 *Device, DWORD Type, const FShaderDeclaration_5b850 *Decl)
{
    Escape(&GMalloc);
    Escape(Device->GetVertexShader(Type, *Decl));
}
