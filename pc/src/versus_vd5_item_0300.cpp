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

// FVector / FPlane / FMatrix from Unreal Engine 2.
class FVector
{
public:
    FLOAT X, Y, Z;
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
};
class FPlane : public FVector
{
public:
    FLOAT W;
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
};
class FMatrix
{
public:
    FLOAT M[4][4];
    FMatrix() {}
    FMatrix(FPlane InX, FPlane InY, FPlane InZ, FPlane InW);  // retail 0x1094fbc0
    FMatrix operator*(const FMatrix& Other) const;             // retail 0x1097b110
    FMatrix Inverse() const;                                   // retail 0x10953af0
};
// Retail 0x10981910 and 0x109819b0 (out of line in this build).
class FScaleMatrix : public FMatrix
{
public:
    FScaleMatrix(const FVector& Scale);
};
class FTranslationMatrix : public FMatrix
{
public:
    FTranslationMatrix(const FVector& Delta);
};

class FRenderInterface;

// Canvas helper holding the canvas <-> screen transforms (cf. UE2's
// FCanvasUtil; the class name is neutral, layout from this function).
class UnnamedCanvasUtil_103f00
{
public:
    DWORD Pad[4];
    FRenderInterface* RI;           // 0x10
    FMatrix ScreenToCanvas;         // 0x14
    FMatrix CanvasToScreen;         // 0x54

    void SetTransforms(FRenderInterface* InRI, FLOAT SizeX, FLOAT SizeY);
};

// RVA 0x103f00.
__declspec(noinline) void UnnamedCanvasUtil_103f00::SetTransforms(FRenderInterface* InRI, FLOAT SizeX, FLOAT SizeY)
{
    RI = InRI;
    CanvasToScreen = FTranslationMatrix(FVector(-SizeX / 2.0f - 0.5f, -SizeY / 2.0f - 0.5f, 0.0f))
                   * FScaleMatrix(FVector(2.0f / SizeX, -2.0f / SizeY, 1.0f));
    ScreenToCanvas = CanvasToScreen.Inverse();
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

__declspec(noinline) FScaleMatrix::FScaleMatrix(const FVector& Scale)
    : FMatrix(FPlane(Scale.X, 0, 0, 0), FPlane(0, Scale.Y, 0, 0), FPlane(0, 0, Scale.Z, 0), FPlane(0, 0, 0, 1)) {}
__declspec(noinline) FTranslationMatrix::FTranslationMatrix(const FVector& Delta)
    : FMatrix(FPlane(1, 0, 0, 0), FPlane(0, 1, 0, 0), FPlane(0, 0, 1, 0), FPlane(Delta.X, Delta.Y, Delta.Z, 1)) {}
__declspec(noinline) FMatrix FMatrix::operator*(const FMatrix& Other) const
{
    FMatrix Result;
    Result.M[0][0] = M[0][0] * Other.M[0][0] + M[0][1] * Other.M[1][0] + M[0][2] * Other.M[2][0] + M[0][3] * Other.M[3][0];
    Result.M[0][1] = M[0][0] * Other.M[0][1] + M[0][1] * Other.M[1][1] + M[0][2] * Other.M[2][1] + M[0][3] * Other.M[3][1];
    Result.M[0][2] = M[0][0] * Other.M[0][2] + M[0][1] * Other.M[1][2] + M[0][2] * Other.M[2][2] + M[0][3] * Other.M[3][2];
    Result.M[0][3] = M[0][0] * Other.M[0][3] + M[0][1] * Other.M[1][3] + M[0][2] * Other.M[2][3] + M[0][3] * Other.M[3][3];
    Result.M[1][0] = M[1][0] * Other.M[0][0] + M[1][1] * Other.M[1][0] + M[1][2] * Other.M[2][0] + M[1][3] * Other.M[3][0];
    Result.M[1][1] = M[1][0] * Other.M[0][1] + M[1][1] * Other.M[1][1] + M[1][2] * Other.M[2][1] + M[1][3] * Other.M[3][1];
    Result.M[1][2] = M[1][0] * Other.M[0][2] + M[1][1] * Other.M[1][2] + M[1][2] * Other.M[2][2] + M[1][3] * Other.M[3][2];
    Result.M[1][3] = M[1][0] * Other.M[0][3] + M[1][1] * Other.M[1][3] + M[1][2] * Other.M[2][3] + M[1][3] * Other.M[3][3];
    Result.M[2][0] = M[2][0] * Other.M[0][0] + M[2][1] * Other.M[1][0] + M[2][2] * Other.M[2][0] + M[2][3] * Other.M[3][0];
    Result.M[2][1] = M[2][0] * Other.M[0][1] + M[2][1] * Other.M[1][1] + M[2][2] * Other.M[2][1] + M[2][3] * Other.M[3][1];
    Result.M[2][2] = M[2][0] * Other.M[0][2] + M[2][1] * Other.M[1][2] + M[2][2] * Other.M[2][2] + M[2][3] * Other.M[3][2];
    Result.M[2][3] = M[2][0] * Other.M[0][3] + M[2][1] * Other.M[1][3] + M[2][2] * Other.M[2][3] + M[2][3] * Other.M[3][3];
    Result.M[3][0] = M[3][0] * Other.M[0][0] + M[3][1] * Other.M[1][0] + M[3][2] * Other.M[2][0] + M[3][3] * Other.M[3][0];
    Result.M[3][1] = M[3][0] * Other.M[0][1] + M[3][1] * Other.M[1][1] + M[3][2] * Other.M[2][1] + M[3][3] * Other.M[3][1];
    Result.M[3][2] = M[3][0] * Other.M[0][2] + M[3][1] * Other.M[1][2] + M[3][2] * Other.M[2][2] + M[3][3] * Other.M[3][2];
    Result.M[3][3] = M[3][0] * Other.M[0][3] + M[3][1] * Other.M[1][3] + M[3][2] * Other.M[2][3] + M[3][3] * Other.M[3][3];
    return Result;
}
extern FMatrix GIdentityMatrix;
FLOAT Determinant(const FMatrix* M);
__declspec(noinline) FMatrix FMatrix::Inverse() const
{
    if (Determinant(this) == 0.0f)
        return GIdentityMatrix;
    FMatrix R;
    for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
            R.M[i][j] = M[j][i];
    return R;
}
void Driver_103f00(UnnamedCanvasUtil_103f00* U, FRenderInterface* RI, INT X, INT Y, UnnamedCanvasUtil_103f00* U2)
{
    U->SetTransforms(RI, (FLOAT)X, (FLOAT)Y);
    U2->SetTransforms(RI, (FLOAT)Y, (FLOAT)X);
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
