// UTexture::PostLoad (0xf2b00) and UTexture::Destroy (0xf2cc0), UTexture vtable slots 8 and 9.
#pragma pack(push, 4)
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef double DOUBLE;

class UObject;
class UClass;
struct FOutputDevice;

extern FOutputDevice *GError;
DOUBLE appSeconds();

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);
};

struct FColor {
    BYTE R, G, B, A;
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA) : R(InR), G(InG), B(InB), A(InA) {}
};

inline void *operator new(unsigned int Size, FArray &Array)
{
    INT Index = Array.Add(1, sizeof(FColor));
    return (FColor *)Array.Data + Index;
}

enum EName { NAME_None = 0 };
struct FName {
    INT Index;
    FName(EName N) : Index(N) {}
};

UObject *UObject_StaticAllocateObject(UClass *Class, UObject *InOuter, FName Name = NAME_None, DWORD SetFlags = 0,
                                      UObject *Template = 0, FOutputDevice *Error = GError, UObject *Ptr = 0,
                                      UObject *SubobjectRoot = 0);

class UObject {
public:
    virtual ~UObject();
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *Linker;
    INT LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;
    UClass *Class;
    void ConditionalPostLoadSub(); // FUN_10916f70, unnamed
    virtual void Destroy();               // 0x15ce0
    inline void PostLoad()
    {
        ObjectFlags |= 0x20000000;
        if (ObjectFlags & 0x100)
            ConditionalPostLoadSub();
    }
};

class UPalette : public UObject {
public:
    FArray Colors; // 0x28
    UPalette();    // 0xf2ee0
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
    void *operator new(unsigned int Size, UObject *Outer, FName Name = NAME_None, DWORD SetFlags = 0)
    {
        return UObject_StaticAllocateObject(StaticClass(), Outer, Name, SetFlags);
    }
};

struct FMipmap {
    INT Pad0;
    INT USize;
    INT VSize;
    BYTE Pad[0x1c];
};

inline INT Clamp(INT X, INT Min, INT Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

class UTexture : public UObject {
public:
    BYTE Pad28[0x4c - 0x28];
    INT USize;          // 0x4c
    INT VSize;          // 0x50
    INT UClamp;         // 0x54
    INT VClamp;         // 0x58
    BYTE Format;        // 0x5c
    BYTE Pad5d[0x64 - 0x5d];
    DOUBLE LastUpdateTime; // 0x64
    void *RenderInterface; // 0x6c
    FMipmap *MipsData;  // 0x70
    INT MipsNum;        // 0x74
    INT MipsMax;        // 0x78
    BYTE Pad7c[0x8c - 0x7c];
    INT Field8c;        // 0x8c
    BYTE Pad90[0x98 - 0x90];
    INT FirstMip;       // 0x98
    UPalette *Palette;  // 0x9c

    UTexture();
    virtual void PostLoad();
    virtual void Destroy();
};

void UTexture::PostLoad()
{
    UObject::PostLoad();

    if (Format == 12 && !Palette) {
        Palette = new(Outer) UPalette;
        for (INT i = 0; i < 16; i++)
            new(Palette->Colors) FColor(i, i, i, 0);
    } else if (Format == 0 && !Palette) {
        Palette = new(Outer) UPalette;
        for (INT i = 0; i < 256; i++)
            new(Palette->Colors) FColor(i, i, i, 0);
    }
    if (Format != 0 && Format != 12 && Palette)
        Palette = 0;

    UClamp = Clamp(UClamp, 0, USize);
    VClamp = Clamp(VClamp, 0, VSize);

    FirstMip = MipsNum - 1;
    for (INT i = 0; i < MipsNum; i++) {
        if (MipsData[i].USize < 64 ||
            (MipsData[i].VSize < 64 && MipsData[i].USize < 256 && MipsData[i].VSize < 256)) {
            FirstMip = i;
            break;
        }
    }

    Field8c = 0;
    DOUBLE Now = appSeconds();
    LastUpdateTime = Now;
}

void UTexture::Destroy()
{
    GMalloc->Free(RenderInterface);
    RenderInterface = 0;
    UObject::Destroy();
}

// Stand-in for the UPalette constructor at 0xf2ee0 (scaffolding, not matched here):
// defined so the LTCG link gives it the same register convention as retail.
void PaletteInitHook(UPalette *);
__declspec(noinline) UPalette::UPalette()
{
    Colors.Data = 0;
    Colors.ArrayNum = 0;
    Colors.ArrayMax = 0;

}

// Scaffolding for the LTCG link, not part of the unit: PostLoad is reached
// through the UTexture vtable, so its address escapes.
void Escape(void *);
extern char Escape_Mem[];
inline void *operator new(unsigned int, char *P) { return P; }
void Driver_f2b00()
{
    Escape(new(Escape_Mem) UTexture);
    Escape(&GError);
}

UTexture::UTexture() {}
UObject::~UObject() {}
