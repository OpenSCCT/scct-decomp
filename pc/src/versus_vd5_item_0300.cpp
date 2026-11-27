// Work item 0300 (wave 3): Versus RVA 0x103ed0, 0x103f00, 0x104010.
// All three were compiled with VC7.0 /GL and linked with /LTCG.
typedef unsigned long DWORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef DWORD UBOOL;
typedef float FLOAT;

class UFont;

// UCanvas (UE2 layout from 0x2c: OrgX, OrgY, ClipX, ClipY, CurX, CurY).
class UCanvas
{
public:
    char Pad[0x2c];
    FLOAT OrgX, OrgY;       // 0x2c
    FLOAT ClipX, ClipY;     // 0x34
    FLOAT CurX, CurY;       // 0x3c

    // Retail 0x109ff400: draws a string clipped to ClipX/ClipY, offset by
    // OrgX/OrgY (the name is neutral; LTCG passes Text in EAX).
    void DrawClippedString(UFont* Font, FLOAT ScaleX, FLOAT ScaleY, INT X, INT Y, UBOOL Clip, const TCHAR* Text);

    // RVA 0x103ed0. Signature of UE2's UCanvas::ClippedPrint (callers pass
    // 1.0, 1.0, a 0/1 flag and the text); this build ignores Center.
    void ClippedPrint(UFont* Font, FLOAT ScaleX, FLOAT ScaleY, UBOOL Center, const TCHAR* Text);
};

__declspec(noinline) void UCanvas::ClippedPrint(UFont* Font, FLOAT ScaleX, FLOAT ScaleY, UBOOL Center, const TCHAR* Text)
{
    DrawClippedString(Font, ScaleX, ScaleY, (INT)CurX, (INT)CurY, 1, Text);
}

typedef unsigned char BYTE;

// UObject / UClass from Unreal Engine 2 (Class at 0x24, SuperField at 0x28).
class UClass;
class UObject
{
public:
    char Pad00[0x24];
    UClass* Class;                  // 0x24
    UObject* SuperField;            // 0x28 (UField)
    UBOOL IsA(UClass* SomeBase);    // retail 0x10904bc0
};
class UClass : public UObject {};

// Inline class test (no null-base case), as retail expands it.
inline UBOOL IsAInline(UObject* Obj, UClass* Base)
{
    for (UObject* C = (UObject*)Obj->Class; C; C = C->SuperField)
        if (C == (UObject*)Base)
            return 1;
    return 0;
}

class UMaterial : public UObject {};
// UFinalBlend from UE2.
class UFinalBlend : public UMaterial
{
public:
    char Pad2C[0x4c - 0x2c];
    UMaterial* Material;            // 0x4c
    BYTE FrameBufferBlending;       // 0x50
    DWORD ZWrite : 1;               // 0x54
    DWORD ZTest : 1;
    DWORD AlphaTest : 1;
    DWORD TwoSided : 1;
    BYTE AlphaRef;                  // 0x58
};
enum EFrameBufferBlending
{
    FB_Overwrite, FB_Modulate, FB_AlphaBlend, FB_AlphaModulate_MightNotFogCorrectly,
    FB_Translucent, FB_Darken, FB_Brighten, FB_Invisible
};
enum ERenderStyle
{
    STY_None, STY_Normal, STY_Masked, STY_Translucent, STY_Modulated,
    STY_Alpha, STY_Additive, STY_Subtractive, STY_Particle, STY_AlphaZ
};

// Class objects (StaticClass() results). Only UBitmapMaterial and
// UFinalBlend are identified; the other three names are neutral.
extern UClass UBitmapMaterial_PrivateStaticClass;   // 0x10cbd8c8
extern UClass UnnamedMaterialClass_31d8;            // 0x10cc31d8
extern UClass UnnamedMaterialClass_2fa8;            // 0x10cc2fa8
extern UClass UnnamedMaterialClass_30c0;            // 0x10cc30c0
extern UClass UFinalBlend_PrivateStaticClass;       // 0x10cc4470

class FOutputDevice;
extern FOutputDevice* GError;                       // 0x10c71aa8
extern UObject* GTransientPackage;                  // 0x10c925b4 (neutral name)
enum EName { NAME_None = 0 };
class FName
{
public:
    INT Index;
    FName(EName N) : Index(N) {}
};
UObject* StaticConstructObject(UClass* Class, UObject* InOuter, FName Name, DWORD SetFlags,
                               UObject* Template, FOutputDevice* Error, UObject* SubobjectRoot, UObject* Extra);
// UE2's ConstructObject template (this build's StaticConstructObject takes
// one more trailing pointer).
template<class T> __forceinline T* ConstructObject(UClass* Class, UObject* Outer, FName Name = NAME_None, DWORD SetFlags = 0,
                                            UObject* Template = 0, FOutputDevice* Error = GError, UObject* SubobjectRoot = 0)
{
    return (T*)StaticConstructObject(Class, Outer, Name, SetFlags, Template, Error, SubobjectRoot, 0);
}
extern void (*GUnnamedObjectHook_4574)(UObject* Obj);   // 0x10cc4574, a function pointer

// FArray from UE2 (Add is retail 0x109044e0).
class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);
};
// Holder of a list of object references kept alive (retail 0x10981a50
// adds one; the object is the global at 0x10c92540). Names neutral.
class UnnamedRefHolder_1a50
{
public:
    char Pad[0x28];
    FArray Refs;                    // 0x28
    void AddRef(void* Ref);
};
extern UnnamedRefHolder_1a50* GUnnamedRefHolder_1a50;

// Canvas renderer whose Flush is retail 0x10a11c60 (FCanvasUtil-like).
class UnnamedCanvasUtil_1c60
{
public:
    void Flush();
};

// Local statics of the function at 0x104010.
extern BYTE CanvasStyleMaterial_LastStyle;          // 0x10c923d4
extern UMaterial* CanvasStyleMaterial_LastMaterial; // 0x10c923d8
extern UMaterial* CanvasStyleMaterial_LastResult;   // 0x10c923dc
extern UFinalBlend* CanvasStyleMaterial_FinalBlend; // 0x10c923d0

// The canvas again (Style at 0x48, its renderer at 0x7c); separate class
// name because the layout above stops at 0x44.
class UCanvasStyle
{
public:
    char Pad[0x48];
    BYTE Style;                                 // 0x48
    char Pad49[0x7c - 0x49];
    UnnamedCanvasUtil_1c60* Util;               // 0x7c
    UMaterial* GetStyleMaterial(UMaterial* Material);
};

// RVA 0x104010: wrap a bitmap material in a shared UFinalBlend that applies
// the canvas Style, caching the last answer.
__declspec(noinline) UMaterial* UCanvasStyle::GetStyleMaterial(UMaterial* Material)
{
    UMaterial* Result = Material;
    if (Style == CanvasStyleMaterial_LastStyle && Material == CanvasStyleMaterial_LastMaterial)
    {
        Result = CanvasStyleMaterial_LastResult;
    }
    else
    {
        Util->Flush();
        CanvasStyleMaterial_LastStyle = Style;
        CanvasStyleMaterial_LastMaterial = Material;
        if (Material && IsAInline(Material, &UBitmapMaterial_PrivateStaticClass)
            && Style != 0xFF
            && !Material->IsA(&UnnamedMaterialClass_31d8)
            && !Material->IsA(&UnnamedMaterialClass_2fa8)
            && !Material->IsA(&UnnamedMaterialClass_30c0)
            && !Material->IsA(&UFinalBlend_PrivateStaticClass))
        {
            if (!CanvasStyleMaterial_FinalBlend)
            {
                UFinalBlend* Blend = ConstructObject<UFinalBlend>(&UFinalBlend_PrivateStaticClass, GTransientPackage);
                if (Blend)
                    GUnnamedObjectHook_4574(Blend);
                CanvasStyleMaterial_FinalBlend = Blend;
                GUnnamedRefHolder_1a50->AddRef(&CanvasStyleMaterial_FinalBlend);
                GUnnamedRefHolder_1a50->AddRef(&CanvasStyleMaterial_LastMaterial);
                GUnnamedRefHolder_1a50->AddRef(&CanvasStyleMaterial_LastResult);
            }
            CanvasStyleMaterial_FinalBlend->Material = Material;
            CanvasStyleMaterial_FinalBlend->TwoSided = 0;
            CanvasStyleMaterial_FinalBlend->ZWrite = 0;
            CanvasStyleMaterial_FinalBlend->ZTest = 0;
            switch (Style)
            {
            case STY_Masked:
                CanvasStyleMaterial_FinalBlend->FrameBufferBlending = FB_Overwrite;
                CanvasStyleMaterial_FinalBlend->AlphaTest = 1;
                CanvasStyleMaterial_FinalBlend->AlphaRef = 127;
                Result = CanvasStyleMaterial_FinalBlend;
                break;
            case STY_Translucent:
                CanvasStyleMaterial_FinalBlend->FrameBufferBlending = FB_Translucent;
                CanvasStyleMaterial_FinalBlend->AlphaTest = 0;
                Result = CanvasStyleMaterial_FinalBlend;
                break;
            case STY_Modulated:
                CanvasStyleMaterial_FinalBlend->FrameBufferBlending = FB_Modulate;
                CanvasStyleMaterial_FinalBlend->AlphaTest = 0;
                Result = CanvasStyleMaterial_FinalBlend;
                break;
            case STY_Alpha:
                CanvasStyleMaterial_FinalBlend->FrameBufferBlending = FB_AlphaBlend;
                CanvasStyleMaterial_FinalBlend->AlphaTest = 1;
                CanvasStyleMaterial_FinalBlend->AlphaRef = 0;
                Result = CanvasStyleMaterial_FinalBlend;
                break;
            case STY_Additive:
                CanvasStyleMaterial_FinalBlend->FrameBufferBlending = FB_Brighten;
                CanvasStyleMaterial_FinalBlend->AlphaTest = 1;
                CanvasStyleMaterial_FinalBlend->AlphaRef = 0;
                Result = CanvasStyleMaterial_FinalBlend;
                break;
            case STY_Subtractive:
                CanvasStyleMaterial_FinalBlend->FrameBufferBlending = FB_Darken;
                CanvasStyleMaterial_FinalBlend->AlphaTest = 0;
                Result = CanvasStyleMaterial_FinalBlend;
                break;
            }
        }
    }
    CanvasStyleMaterial_LastResult = Result;
    return Result;
}

// Scaffolding for the link, not part of the unit: a stand-in body for
// 0x109ff400 so the linker gives it the retail convention, and a driver.
void Escape(void *);
__declspec(noinline) void UCanvas::DrawClippedString(UFont* Font, FLOAT ScaleX, FLOAT ScaleY, INT X, INT Y, UBOOL Clip, const TCHAR* Text)
{
    if (*Text == 0) return;
    Escape((void*)Text);
    UCanvas* Self = this;
    Escape(&Self); Escape(&Font); Escape(&ScaleX); Escape(&ScaleY);
    Escape(&X); Escape(&Y); Escape(&Clip);
}
void Driver_103ed0(UCanvas* C, UFont* F, const TCHAR* T, const TCHAR* T2)
{
    C->ClippedPrint(F, 1.f, 1.f, 0, T);
    C->ClippedPrint(F, 1.f, 1.f, 1, T2);
}

__declspec(noinline) void UnnamedRefHolder_1a50::AddRef(void* Ref)
{
    INT Index = Refs.Add(1, sizeof(void*));
    ((void**)Refs.Data)[Index] = Ref;
}
struct UnnamedCanvasUtilData_1c60 { DWORD A, B, C; INT NumVertices; };
__declspec(noinline) void UnnamedCanvasUtil_1c60::Flush()
{
    if (((UnnamedCanvasUtilData_1c60*)this)->NumVertices > 0)
    {
        Escape(this);
        Escape(this);
    }
}
void Driver_104010(UCanvasStyle* C, UMaterial* M, UMaterial* M2)
{
    Escape(&CanvasStyleMaterial_LastStyle); Escape(&CanvasStyleMaterial_LastMaterial);
    Escape(&CanvasStyleMaterial_LastResult); Escape(&CanvasStyleMaterial_FinalBlend);
    Escape(&GUnnamedRefHolder_1a50); Escape(&GTransientPackage); Escape(&GError);
    Escape(C->GetStyleMaterial(M));
    Escape(C->GetStyleMaterial(M2));
}
