// Work item 0129: Versus RVA 0x158550-0x158b47, 6 functions.
// XInterface GUI natives and UGUIStyles::Draw:
//   0x158550: UGUIController::execGetDedicatedServerLobby (LTCG)
//   0x158570: UGUIController::execUpdateDedicatedServerTitle
//   0x1585f0: UGUIFont::execGetFont (LTCG)
//   0x158740: UGUIStyles::execDraw (LTCG)
//   0x158850: UGUIStyles::execDrawText (LTCG)
//   0x1589e0: UGUIStyles::Draw (LTCG)

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef unsigned char BYTE;
typedef float FLOAT;
typedef char *va_list;

enum EName { NAME_None = 0, GUI_OnDraw = 0xce74 };
enum { LOAD_NoWarn = 0x0002 };

enum EImgStyle
{
    ISTY_Normal    = 0,
    ISTY_Stretched = 1,
    ISTY_Scaled    = 2,
};

extern "C" __declspec(dllimport) UINT __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" __declspec(dllimport) INT __cdecl _vsnwprintf(TCHAR *, UINT, const TCHAR *, va_list);
extern "C" void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count);

inline INT appFloor(FLOAT F) { return (INT)floor(F); }
template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
    virtual void Flush() {}
    void Logf(const TCHAR *Fmt, ...);
};
extern FOutputDevice *GLog;

struct FColor
{
    union
    {
        struct { BYTE B, G, R, A; };
        DWORD AlignmentDummy;
    };
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255)
        : R(InR), G(InG), B(InB), A(InA) {}
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Num() const { return ArrayNum; }
    INT Add(INT Count, INT ElementSize);
    INT __stdcall AddZeroed(INT ElementSize, INT n = 1);
};

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
    INT AddZeroed(INT n = 1) { return FArray::AddZeroed(sizeof(T), n); }
};

class FString : public FArray
{
public:
    FString() {}
    FString(const TCHAR *In);
    ~FString();
    FString &operator=(const TCHAR *Other);
    FString &operator=(const FString &Other);
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
};

struct FNameEntry
{
    INT Index;
    DWORD Flags;
    FNameEntry *HashNext;
    TCHAR Name[1];
};

extern FArray FName_Names;

class FName
{
public:
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    const TCHAR *operator*() const { return ((FNameEntry **)FName_Names.Data)[Index]->Name; }
};

class UClass;
class UPackageMap;
struct FFrame;

struct FScriptDelegate
{
    class UObject *Object;
    FName FunctionName;
};

class UObject
{
public:
    virtual void Vf00();
    virtual void Vf04();
    virtual void Vf08();
    virtual ~UObject();
    virtual void Vf10();
    virtual void ProcessDelegate(FName DelegateName, FScriptDelegate *Delegate, void *Parms, void *Result);

    INT Index;          // +0x04
    UObject *HashNext;  // +0x08
    void *StateFrame;   // +0x0c
    void *_Linker;      // +0x10
    INT _LinkerIndex;   // +0x14
    UObject *Outer;     // +0x18
    DWORD ObjectFlags;  // +0x1c
    FName Name;         // +0x20
    UClass *Class;      // +0x24

    UClass *GetClass() const { return Class; }
    FName GetFName() const { return Name; }
    const TCHAR *GetName() const { return *Name; }
    inline UBOOL IsA(UClass *SomeBase) const;

    static UObject *__cdecl StaticLoadObject(UClass *ObjectClass, UObject *InOuter,
                                             FName PackageName, FName GroupName, FName ObjectName,
                                             const TCHAR *Filename, DWORD LoadFlags, UPackageMap *Sandbox);
};

typedef void (UObject::*Native)(FFrame &TheStack, void *const Result);
extern Native GNatives[];

struct FFrame
{
    virtual void Serialize(const TCHAR *V, INT Event);
    class UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    void Step(UObject *Context, void *const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define RESULT_DECL void *const Result
#define P_GET_INT(var) INT var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_BYTE(var) BYTE var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_FLOAT(var) FLOAT var = 0.f; Stack.Step(Stack.Object, &var);
#define P_GET_STR(var) FString var; Stack.Step(Stack.Object, &var);
#define P_GET_OBJECT(cls, var) cls *var = 0; Stack.Step(Stack.Object, &var);
#define P_FINISH Stack.Code++;

class UField : public UObject
{
public:
    UField *SuperField; // +0x28
    UField *Next;       // +0x2c
};

class UStruct : public UField
{
public:
    UField *Children;   // +0x30
};

class UClass : public UStruct
{
public:
    UClass *GetSuperClass() const { return (UClass *)SuperField; }
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->GetSuperClass())
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

template<class T> T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}

class UFont : public UObject
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class UMaterial : public UObject
{
public:
    virtual void Vf18(); virtual void Vf1c();
    virtual void Vf20(); virtual void Vf24(); virtual void Vf28(); virtual void Vf2c();
    virtual void Vf30(); virtual void Vf34(); virtual void Vf38(); virtual void Vf3c();
    virtual void Vf40(); virtual void Vf44(); virtual void Vf48(); virtual void Vf4c();
    virtual void Vf50(); virtual void Vf54(); virtual void Vf58(); virtual void Vf5c();
    virtual void Vf60(); virtual void Vf64();
    virtual INT MaterialUSize(); // +0x68
    virtual INT MaterialVSize(); // +0x6c
};

class UCanvas : public UObject
{
public:
    UFont *Font;        // +0x28
    FLOAT OrgX;         // +0x2c
    FLOAT OrgY;         // +0x30
    FLOAT ClipX;        // +0x34
    FLOAT ClipY;        // +0x38
    FLOAT CurX;         // +0x3c
    FLOAT CurY;         // +0x40
    FLOAT Z;            // +0x44
    BYTE Style;         // +0x48
    FLOAT CurYL;        // +0x4c
    FColor DrawColor;   // +0x50
    INT SizeY;          // +0x54
    INT SizeX;          // +0x58

    void DrawTile(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                  FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, FColor Color);
    void DrawTileStretched(UMaterial *Mat, FLOAT Left, FLOAT Top, FLOAT AWidth, FLOAT AHeight);
    void DrawTileScaled(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL);
    void DrawTextJustified(BYTE Just, FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, const TCHAR *Fmt, ...);
};

class UGUI : public UObject
{
public:
    class UGUIController *Controller; // +0x28
};

class UGUIController : public UGUI
{
public:
    void execGetDedicatedServerLobby(FFrame &Stack, RESULT_DECL);
    void execUpdateDedicatedServerTitle(FFrame &Stack, RESULT_DECL);
};

class UGUIFont : public UGUI
{
public:
    FString KeyName;                 // +0x2c
    BITFIELD bFixedSize : 1;         // +0x38
    TArray<FName> FontArrayNames;    // +0x3c
    TArray<UFont *> FontArrayFonts;  // +0x48
    FName FontPackageName;           // +0x54

    UFont *GetFont(INT XRes);
    void execGetFont(FFrame &Stack, RESULT_DECL);
};

struct UGUIStyles_eventOnDraw_Parms
{
    UCanvas *Canvas;
    BYTE MenuState;
    FLOAT Left;
    FLOAT Top;
    FLOAT Width;
    FLOAT Height;
    BITFIELD ReturnValue;
};

struct UGUIStyles_eventOnDrawText_Parms
{
    UCanvas *Canvas;
    BYTE MenuState;
    FLOAT Left;
    FLOAT Top;
    FLOAT Width;
    FLOAT Height;
    BYTE Align;
    FString Text;
    BITFIELD ReturnValue;
};

class UGUIStyles : public UGUI
{
public:
    FString KeyName;             // +0x2c
    BYTE RStyles[5];             // +0x38
    UMaterial *Images[5];        // +0x40
    BYTE ImgStyle[5];            // +0x54
    FColor FontColors[5];        // +0x5c
    FColor ImgColors[5];         // +0x70
    UGUIFont *Fonts[5];          // +0x84
    BYTE unk_98[0xe4 - 0x98];
    DWORD unk_e4;                // +0xe4
    FScriptDelegate OnDraw;      // +0xe8
    FScriptDelegate OnDrawText;  // +0xf0

    UBOOL delegateOnDraw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height);
    UBOOL delegateOnDrawText(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height, BYTE Align, const FString &Text);
    void Draw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height);
    void DrawText(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height, BYTE Just, const TCHAR *Text);

    void execDraw(FFrame &Stack, RESULT_DECL);
    void execDrawText(FFrame &Stack, RESULT_DECL);
};

// Retail keeps L"Warning: %s could not load font %s" at 0x10c46730 in writable .data.
extern const TCHAR WarnFontLoadFmt[];

// RVA 0x158550: UGUIController::execGetDedicatedServerLobby
void UGUIController::execGetDedicatedServerLobby(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(FString *)Result = (const TCHAR *)0;
}

// RVA 0x158570: UGUIController::execUpdateDedicatedServerTitle
void UGUIController::execUpdateDedicatedServerTitle(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Title);
    P_FINISH;
}

// RVA 0x1585f0: UGUIFont::execGetFont
void UGUIFont::execGetFont(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(XRes);
    P_FINISH;

    INT Index;
    if (XRes < 800 || bFixedSize)
        Index = 0;
    else if (XRes < 1024)
        Index = 1;
    else if (XRes < 1280)
        Index = 2;
    else if (XRes < 1600)
        Index = 3;
    else
        Index = 4;

    Index = Min(Index, FontArrayNames.Num() - 1);

    if (Index < 0)
        *(UFont **)Result = 0;

    if (Index >= FontArrayFonts.Num())
        FontArrayFonts.AddZeroed(Index - FontArrayFonts.Num() + 1);

    if (!FontArrayFonts(Index))
    {
        FontArrayFonts(Index) = Cast<UFont>(
            UObject::StaticLoadObject(UFont::StaticClass(), 0, FontPackageName, NAME_None,
                                      FontArrayNames(Index), 0, LOAD_NoWarn, 0));
        if (!FontArrayFonts(Index))
            GLog->Logf(WarnFontLoadFmt, GetName(), *FontArrayNames(Index));
    }

    *(UFont **)Result = FontArrayFonts(Index);
}

// RVA 0x158740: UGUIStyles::execDraw
void UGUIStyles::execDraw(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UCanvas, Canvas);
    P_GET_BYTE(MenuState);
    P_GET_FLOAT(Left);
    P_GET_FLOAT(Top);
    P_GET_FLOAT(Width);
    P_GET_FLOAT(Height);
    P_FINISH;
    Draw(Canvas, MenuState, Left, Top, Width, Height);
}

// RVA 0x158850: UGUIStyles::execDrawText
void UGUIStyles::execDrawText(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UCanvas, Canvas);
    P_GET_BYTE(MenuState);
    P_GET_FLOAT(Left);
    P_GET_FLOAT(Top);
    P_GET_FLOAT(Width);
    P_GET_FLOAT(Height);
    P_GET_BYTE(Just);
    P_GET_STR(Text);
    P_FINISH;
    DrawText(Canvas, MenuState, Left, Top, Width, Height, Just, *Text);
}

// RVA 0x1589e0: UGUIStyles::Draw
void UGUIStyles::Draw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height)
{
    if (MenuState > 5)
        return;

    if (delegateOnDraw(Canvas, MenuState, Left, Top, Width, Height))
        return;

    if (!Images[MenuState])
        return;

    if (MenuState == 4)
        Canvas->DrawColor = FColor(64, 64, 64, 255);
    else
        Canvas->DrawColor = FColor(128, 128, 128, 255);

    UMaterial *M = Images[MenuState];
    if (!M)
        return;

    FLOAT mW = (FLOAT)M->MaterialUSize();
    FLOAT mH = (FLOAT)M->MaterialVSize();

    Canvas->Style = RStyles[MenuState];
    Canvas->DrawColor = ImgColors[MenuState];

    switch (ImgStyle[MenuState])
    {
        case ISTY_Normal:
            Canvas->DrawTile(M, Left, Top, mW, mH, 0, 0, mW, mH, 0, FColor(128, 128, 128, 255));
            break;
        case ISTY_Stretched:
            Canvas->DrawTileStretched(M, Left, Top, Width, Height);
            break;
        case ISTY_Scaled:
            Canvas->DrawTileScaled(M, Left, Top, Width, Height);
            break;
    }
}

// ---------------------------------------------------------------------------
// Scaffolding for LTCG links, not part of the units.
void Escape(void *);
void SinkTile(void *, void *, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FColor);
void SinkJustified(UCanvas *, BYTE, FLOAT, FLOAT, FLOAT, FLOAT, const TCHAR *);
UFont *SinkGetFont(UGUIFont *, INT);
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find);
extern TCHAR GCmdLine[];
extern const TCHAR Logf_LogFlushParam[];

#pragma auto_inline(off)
FString &FString::operator=(const TCHAR *Other)
{
    if (Other != (const TCHAR *)Data)
    {
        if (*Other == 0)
        {
            if (Data)
            {
                ArrayNum = 0;
                ArrayMax = 0;
                GMalloc->Free(Data);
                Data = 0;
            }
        }
        else
        {
            if (Data == 0)
            {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), L"FString::=");
            }
            else
            {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), L"FArray");
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}

static UBOOL ParseParam(const TCHAR *Stream, const TCHAR *Param)
{
    const TCHAR *Start = Stream;
    if (*Stream)
    {
        while ((Start = appStrfind(Start + 1, Param)) != 0)
        {
            if (Start > Stream && (Start[-1] == '-' || Start[-1] == '/'))
                return 1;
        }
    }
    return 0;
}

void FOutputDevice::Logf(const TCHAR *Fmt, ...)
{
    TCHAR *Buffer = (TCHAR *)GMalloc->Malloc(0x10000, L"Logf");
    va_list ArgPtr = (va_list)&Fmt + sizeof(Fmt);
    _vsnwprintf(Buffer, 0x8000, Fmt, ArgPtr);
    Serialize(Buffer, 0x24c);
    GMalloc->Free(Buffer);
    if (!ParseParam(GCmdLine, Logf_LogFlushParam))
        Flush();
}

UBOOL UGUIStyles::delegateOnDraw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height)
{
    UGUIStyles_eventOnDraw_Parms Parms;
    Parms.Canvas = Canvas;
    Parms.MenuState = MenuState;
    Parms.Left = Left;
    Parms.Top = Top;
    Parms.Width = Width;
    Parms.Height = Height;
    Parms.ReturnValue = 0;
    ProcessDelegate(GUI_OnDraw, &OnDraw, &Parms, 0);
    return Parms.ReturnValue;
}

UBOOL UGUIStyles::delegateOnDrawText(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height, BYTE Align, const FString &Text)
{
    UGUIStyles_eventOnDrawText_Parms Parms;
    Parms.Canvas = Canvas;
    Parms.MenuState = MenuState;
    Parms.Left = Left;
    Parms.Top = Top;
    Parms.Width = Width;
    Parms.Height = Height;
    Parms.Align = Align;
    Parms.Text = Text;
    Parms.ReturnValue = 0;
    ProcessDelegate(FName((EName)0xce75), &OnDrawText, &Parms, 0);
    return Parms.ReturnValue;
}

UFont *UGUIFont::GetFont(INT XRes)
{
    Escape(this);
    return SinkGetFont(this, XRes);
}

void UCanvas::DrawTextJustified(BYTE Just, FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, const TCHAR *Fmt, ...)
{
    TCHAR Buffer[4096];
    va_list ArgPtr = (va_list)&Fmt + sizeof(Fmt);
    _vsnwprintf(Buffer, 4096, Fmt, ArgPtr);
    SinkJustified(this, Just, X1, Y1, X2, Y2, Buffer);
}

void UGUIStyles::DrawText(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height, BYTE Just, const TCHAR *Text)
{
    Left = (FLOAT)appFloor(Left + 0.5f);
    Top = (FLOAT)appFloor(Top + 0.5f);
    Width = (FLOAT)appFloor(Width + 0.5f);
    Height = (FLOAT)appFloor(Height + 0.5f);

    BYTE SavedStyle = Canvas->Style;
    FColor SavedColor = Canvas->DrawColor;
    UFont *SavedFont = Canvas->Font;

    if (MenuState > 5)
        return;

    if (!Fonts[MenuState])
        return;

    if (delegateOnDrawText(Canvas, MenuState, Left, Top, Width, Height, Just, FString(Text)))
        return;

    Canvas->Style = RStyles[MenuState];
    Canvas->DrawColor = FontColors[MenuState];
    Canvas->Font = Fonts[MenuState]->GetFont(Canvas->SizeX);
    if (unk_e4 & 2)
        Just += 10;
    if (Canvas->Font)
        Canvas->DrawTextJustified(Just, Left, Top, Left + Width, Top + Height, Text);

    Canvas->Style = SavedStyle;
    Canvas->DrawColor = SavedColor;
    Canvas->Font = SavedFont;
}

void UCanvas::DrawTile(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                       FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT ZVal, FColor Color)
{
    Escape(Mat);
    Escape(this);
    FLOAT SX = ClipX, SY = ClipY;
    SinkTile(this, &CurX, X * SX + CurX, Y * SY + CurY, XL * SX, YL * SY, U + SX, V + SY, UL * SX, VL * SY, ZVal, Color);
    SinkTile(this, &CurY, X * SY, Y * SX, XL + CurX, YL + CurY, U * SY, V * SX, UL + SY, VL + SX, ZVal, Color);
    Escape(this);
}

void UCanvas::DrawTileStretched(UMaterial *Mat, FLOAT Left, FLOAT Top, FLOAT AWidth, FLOAT AHeight)
{
    CurX = Left;
    CurY = Top;
    if (!Mat || !Style)
        return;
    FLOAT mW = (FLOAT)Mat->MaterialUSize();
    FLOAT mH = (FLOAT)Mat->MaterialVSize();
    FLOAT MidX = (FLOAT)appFloor(mW * 0.5f);
    FLOAT MidY = (FLOAT)appFloor(mH * 0.5f);
    FLOAT SmallTileW = AWidth - mW;
    FLOAT SmallTileH = AHeight - mH;
    FLOAT fX, fY;
    if (mW < AWidth) {
        fX = MidX;
        fY = (mH > AHeight) ? AHeight * 0.5f : MidY;
        DrawTile(Mat, CurX + fX, CurY, SmallTileW, fY, fX, 0, 1.f, fY, 0, DrawColor);
        DrawTile(Mat, CurX + fX, CurY + AHeight - fY, SmallTileW, fY, fX, mH - fY, 1.f, fY, 0, DrawColor);
    } else
        fX = AWidth * 0.5f;
    if (mH < AHeight) {
        fY = MidY;
        DrawTile(Mat, CurX, CurY + fY, fX, SmallTileH, 0, fY, fX, 1.f, 0, DrawColor);
        DrawTile(Mat, CurX + AWidth - fX, CurY + fY, fX, SmallTileH, mW - fX, fY, fX, 1.f, 0, DrawColor);
    } else
        fY = AHeight * 0.5f;
    if (mH < AHeight && mW < AWidth)
        DrawTile(Mat, CurX + fX, CurY + fY, SmallTileW, SmallTileH, fX, fY, 1.f, 1.f, 0, DrawColor);
    DrawTile(Mat, CurX, CurY, fX, fY, 0, 0, fX, fY, 0, DrawColor);
    DrawTile(Mat, CurX + AWidth - fX, CurY, fX, fY, mW - fX, 0, fX, fY, 0, DrawColor);
    DrawTile(Mat, CurX, CurY + AHeight - fY, fX, fY, 0, mH - fY, fX, fY, 0, DrawColor);
    DrawTile(Mat, CurX + AWidth - fX, CurY + AHeight - fY, fX, fY, mW - fX, mH - fY, fX, fY, 0, DrawColor);
}

void UCanvas::DrawTileScaled(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL)
{
    if (Style)
    {
        FLOAT USize = (FLOAT)Mat->MaterialUSize();
        FLOAT VSize = (FLOAT)Mat->MaterialVSize();
        DrawTile(Mat, X, Y, XL, YL, 0, 0, USize, VSize, 0, DrawColor);
    }
}
#pragma auto_inline(on)

void Driver_158550(UGUIController *C, FFrame *S, void *R, FString *Str, const TCHAR *T)
{
    Escape(&GMalloc);
    void (UGUIController::*Fn)(FFrame &, void *const) = &UGUIController::execGetDedicatedServerLobby;
    Escape(&Fn);
    (C->*Fn)(*S, R);
    *Str = T;
}

void Driver_1585f0(UGUIFont *F, FFrame *S, void *R, FOutputDevice *Log, const TCHAR *Fmt)
{
    Escape(&GMalloc);
    Escape(&GLog);
    Escape(&FName_Names);
    Escape(GNatives);
    void (UGUIFont::*Fn)(FFrame &, void *const) = &UGUIFont::execGetFont;
    Escape(&Fn);
    (F->*Fn)(*S, R);
    Log->Logf(Fmt, 0);
}

void Driver_158740(UGUIStyles *St, FFrame *S, void *R, UCanvas *C, BYTE M, FLOAT X, FLOAT Y, FLOAT W, FLOAT H)
{
    Escape(GNatives);
    void (UGUIStyles::*Fn)(FFrame &, void *const) = &UGUIStyles::execDraw;
    Escape(&Fn);
    (St->*Fn)(*S, R);
    St->Draw(C, M, X, Y, W, H);
    C->DrawTileStretched(0, X, Y, W, H);
    C->DrawTileScaled(0, X, Y, W, H);
}

void UseDrawTextA(UGUIStyles *St, UCanvas *C, BYTE M, FLOAT *P, BYTE J, const TCHAR *T)
{
    St->DrawText(C, M, P[0], P[1], P[2], P[3], J, T);
    Escape(C);
}
void Driver_158850(UGUIStyles *St, FFrame *S, void *R, UCanvas *C, BYTE M, FLOAT X, FLOAT Y, FLOAT W, FLOAT H, BYTE J, const TCHAR *T)
{
    Escape(GNatives);
    void (UGUIStyles::*Fn)(FFrame &, void *const) = &UGUIStyles::execDrawText;
    Escape(&Fn);
    (St->*Fn)(*S, R);
    St->DrawText(C, M, X, Y, W, H, J, T);
    UseDrawTextA(St, C, M, &X, J, T);
}
