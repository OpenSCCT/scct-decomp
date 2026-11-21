// w4_item_0113.cpp -- Versus Magma interface factories, localization, and color helpers
// (RVA 0x154140-0x154472)

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef unsigned short TCHAR;

extern "C" __declspec(dllimport) const TCHAR *__cdecl wcsstr(const TCHAR *Str, const TCHAR *SubStr);
extern const TCHAR *__cdecl Localize(const TCHAR *Section, const TCHAR *Key, const TCHAR *Package);

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};

extern FMalloc *GMalloc;

// Writable .data string literals in Versus retail.
extern const TCHAR GMagmaAllocTag[];          // L"Magma"
extern const TCHAR GCommonTagPrefix[];        // L"CMN_"
extern const TCHAR GCommonTagsSection[];      // L"CommonTags"
extern const TCHAR GMagmaPackageNameCommon[]; // L"Magma"
extern const TCHAR GMagmaPackageName[];       // L"Magma"

// Magma allocation base (custom operator new/delete using GMalloc with tag L"Magma").
class FMagmaAllocBase {
public:
    static void *operator new(unsigned int Size)
    {
        return GMalloc->Malloc(Size, GMagmaAllocTag);
    }
    static void operator delete(void *Ptr);
};

// Base class for 0x10-byte Magma object constructed at 0x154140 (unnamed in retail).
class FMagmaResourceBase : public FMagmaAllocBase {
public:
    FMagmaResourceBase();
    virtual ~FMagmaResourceBase();

    BYTE unk_04[0x0c];
};

// Derived 0x10-byte Magma object created at 0x154140 (vtable 0x10c03218).
class FMagmaResource_154140 : public FMagmaResourceBase {
public:
    FMagmaResource_154140() {}
    virtual ~FMagmaResource_154140();
};

// Base class for 0x30-byte Magma object constructed at 0x1541a0 (unnamed in retail).
class FMagmaStreamBase : public FMagmaAllocBase {
public:
    FMagmaStreamBase();
    virtual ~FMagmaStreamBase();

    BYTE unk_04[0x28];
};

// Derived 0x30-byte Magma object created at 0x1541a0 (vtable 0x10c032dc).
class FMagmaStream_1541a0 : public FMagmaStreamBase {
public:
    FMagmaStream_1541a0() : unk_2c(0) {}
    virtual ~FMagmaStream_1541a0();

    void *unk_2c;
};

// Magma host interface whose vtable (0x10c03480+) holds 0x154140, 0x1541a0, and 0x154220.
class FMagmaInterface {
public:
    virtual FMagmaResourceBase *CreateResource_154140();
    virtual FMagmaStreamBase *CreateStream_1541a0();
    virtual const TCHAR *LocalizeText(const TCHAR *Section, const TCHAR *Key);
};

// Four-channel floating-point color (packed byte order: B, G, R, A).
class FMagmaColor {
public:
    FLOAT B;
    FLOAT G;
    FLOAT R;
    FLOAT A;

    FMagmaColor() {}
    FMagmaColor(FLOAT InB, FLOAT InG, FLOAT InR, FLOAT InA) : B(InB), G(InG), R(InR), A(InA) {}
    FMagmaColor(DWORD Color);
    operator DWORD() const;
    FMagmaColor operator*(const FMagmaColor &Other) const;
};

// RVA 0x154140
FMagmaResourceBase *FMagmaInterface::CreateResource_154140()
{
    return new FMagmaResource_154140();
}

// RVA 0x1541a0
FMagmaStreamBase *FMagmaInterface::CreateStream_1541a0()
{
    return new FMagmaStream_1541a0();
}

// RVA 0x154220
const TCHAR *FMagmaInterface::LocalizeText(const TCHAR *Section, const TCHAR *Key)
{
    if (wcsstr(Key, GCommonTagPrefix) == Key)
        return Localize(GCommonTagsSection, Key, GMagmaPackageNameCommon);
    return Localize(Section, Key, GMagmaPackageName);
}

// RVA 0x154290
FMagmaColor::FMagmaColor(DWORD Color)
{
    const FLOAT Scale = 1.0f / 255.0f;
    B = (FLOAT)(Color & 0xff) * Scale;
    G = (FLOAT)((Color >> 8) & 0xff) * Scale;
    R = (FLOAT)((Color >> 16) & 0xff) * Scale;
    A = (FLOAT)(Color >> 24) * Scale;
}

// RVA 0x154330
FMagmaColor::operator DWORD() const
{
    DWORD dwA = A >= 1.0f ? 0xff : A <= 0.0f ? 0x00 : (DWORD)(A * 255.0f + 0.5f);
    DWORD dwR = R >= 1.0f ? 0xff : R <= 0.0f ? 0x00 : (DWORD)(R * 255.0f + 0.5f);
    DWORD dwG = G >= 1.0f ? 0xff : G <= 0.0f ? 0x00 : (DWORD)(G * 255.0f + 0.5f);
    DWORD dwB = B >= 1.0f ? 0xff : B <= 0.0f ? 0x00 : (DWORD)(B * 255.0f + 0.5f);
    return (((dwA << 8) | dwR) << 8 | dwG) << 8 | dwB;
}

// RVA 0x154450
FMagmaColor FMagmaColor::operator*(const FMagmaColor &Other) const
{
    return FMagmaColor(B * Other.B, G * Other.G, R * Other.R, A * Other.A);
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_154450(FMagmaColor *Out, const FMagmaColor *A, const FMagmaColor *B, INT Mode)
{
    if (Mode == 0) {
        *Out = A[0] * B[0];
        Escape(Out);
    } else if (Mode == 1) {
        *Out = A[1] * B[1];
        Escape(Out);
    } else if (Mode == 2) {
        *Out = A[2] * B[2];
        Escape(Out);
    } else if (Mode == 3) {
        *Out = A[3] * B[3];
        Escape(Out);
    } else if (Mode == 4) {
        *Out = A[4] * B[4];
        Escape(Out);
    } else if (Mode == 5) {
        *Out = A[5] * B[5];
        Escape(Out);
    } else if (Mode == 6) {
        *Out = A[6] * B[6];
        Escape(Out);
    } else if (Mode == 7) {
        *Out = A[7] * B[7];
        Escape(Out);
    } else if (Mode == 8) {
        *Out = A[8] * B[8];
        Escape(Out);
    } else if (Mode == 9) {
        *Out = A[9] * B[9];
        Escape(Out);
    } else if (Mode == 10) {
        *Out = A[10] * B[10];
        Escape(Out);
    } else if (Mode == 11) {
        *Out = A[11] * B[11];
        Escape(Out);
    }
}
