// Work item 0294 (Versus RVA 0x101ce0-0x1021b1): UCanvas::DrawTileStretched and
// UCanvas::execDrawTileStretchedScreenPercentUV.
// Engine was built with /GL and linked with /LTCG: DrawTileStretched (0x101ce0)
// and DrawTileStretchedScreenPercentUV (0x1021c0) take `this` in EAX and the
// material in EBX; DrawTile (0xff300) takes `this` in ESI and the material in EAX.
// UCanvas layout: CurX at 0x3c, CurY at 0x40 (as in UE2); the byte at 0x48 and
// the dword at 0x50 are unnamed (Unk48 gates drawing, Unk50 is passed through
// to DrawTile as its last argument).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

extern "C" __declspec(dllimport) double __cdecl floor(double);

inline INT appFloor(FLOAT F) { return (INT)floor(F); }

class UObject
{
public:
    virtual ~UObject();
};

struct FFrame;
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
#define P_GET_FLOAT(var) FLOAT var = 0.f; Stack.Step(Stack.Object, &var);
#define P_GET_OBJECT(cls, var) cls *var = 0; Stack.Step(Stack.Object, &var);
#define P_FINISH Stack.Code++;

class UMaterial : public UObject
{
public:
    virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04();
    virtual void V05(); virtual void V06(); virtual void V07(); virtual void V08();
    virtual void V09(); virtual void V10(); virtual void V11(); virtual void V12();
    virtual void V13(); virtual void V14(); virtual void V15(); virtual void V16();
    virtual void V17(); virtual void V18(); virtual void V19(); virtual void V20();
    virtual void V21(); virtual void V22(); virtual void V23(); virtual void V24();
    virtual void V25();
    virtual INT MaterialUSize();    // +0x68
    virtual INT MaterialVSize();    // +0x6c
};

class UCanvas : public UObject
{
public:
    BYTE Pad04[0x34 - 0x04];
    FLOAT ClipX;    // 0x34 (scaled by the ScreenPercent variant)
    FLOAT ClipY;    // 0x38
    FLOAT CurX;     // 0x3c
    FLOAT CurY;     // 0x40
    BYTE Pad44[4];
    BYTE Unk48;     // 0x48
    BYTE Pad49[7];
    DWORD Unk50;    // 0x50

    void DrawTile(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL, FLOAT U, FLOAT V,
                  FLOAT UL, FLOAT VL, FLOAT Z, DWORD Extra);
    void DrawTileStretched(UMaterial *Mat, FLOAT Left, FLOAT Top, FLOAT AWidth, FLOAT AHeight);
    void DrawTileStretchedScreenPercentUV(UMaterial *Mat, FLOAT A, FLOAT B, FLOAT C, FLOAT D,
                                          FLOAT E, FLOAT F, FLOAT G, FLOAT H);
    void execDrawTileStretchedScreenPercentUV(FFrame &Stack, RESULT_DECL);
    void execDrawTileStretched(FFrame &Stack, RESULT_DECL);    // scaffolding
};

// RVA 0x101ce0.
void UCanvas::DrawTileStretched(UMaterial *Mat, FLOAT Left, FLOAT Top, FLOAT AWidth, FLOAT AHeight)
{
    CurX = Left;
    CurY = Top;
    if (!Mat || !Unk48)
        return;

    FLOAT mW = Mat->MaterialUSize();
    FLOAT mH = Mat->MaterialVSize();
    FLOAT MidX = appFloor(mW * 0.5f);
    FLOAT MidY = appFloor(mH * 0.5f);
    FLOAT SmallTileW = AWidth - mW;
    FLOAT SmallTileH = AHeight - mH;
    FLOAT fX, fY;

    // Top and bottom spans.
    if (mW < AWidth) {
        fX = MidX;
        if (mH > AHeight)
            fY = AHeight * 0.5f;
        else
            fY = MidY;
        DrawTile(Mat, CurX + fX, CurY, SmallTileW, fY, fX, 0, 1.f, fY, 0, Unk50);
        DrawTile(Mat, CurX + fX, CurY + AHeight - fY, SmallTileW, fY, fX, mH - fY, 1.f, fY, 0, Unk50);
    } else
        fX = AWidth * 0.5f;

    // Left and right spans.
    if (mH < AHeight) {
        fY = MidY;
        DrawTile(Mat, CurX, CurY + fY, fX, SmallTileH, 0, fY, fX, 1.f, 0, Unk50);
        DrawTile(Mat, CurX + AWidth - fX, CurY + fY, fX, SmallTileH, mW - fX, fY, fX, 1.f, 0, Unk50);
    } else
        fY = AHeight * 0.5f;

    // The centre.
    if (mH < AHeight && mW < AWidth)
        DrawTile(Mat, CurX + fX, CurY + fY, SmallTileW, SmallTileH, fX, fY, 1.f, 1.f, 0, Unk50);

    // Corners.
    DrawTile(Mat, CurX, CurY, fX, fY, 0, 0, fX, fY, 0, Unk50);
    DrawTile(Mat, CurX + AWidth - fX, CurY, fX, fY, mW - fX, 0, fX, fY, 0, Unk50);
    DrawTile(Mat, CurX, CurY + AHeight - fY, fX, fY, 0, mH - fY, fX, fY, 0, Unk50);
    DrawTile(Mat, CurX + AWidth - fX, CurY + AHeight - fY, fX, fY, mW - fX, mH - fY, fX, fY, 0, Unk50);
}

// RVA 0x102030.
void UCanvas::execDrawTileStretchedScreenPercentUV(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UMaterial, Mat);
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_GET_FLOAT(C);
    P_GET_FLOAT(D);
    P_GET_FLOAT(E);
    P_GET_FLOAT(F);
    P_GET_FLOAT(G);
    P_GET_FLOAT(H);
    P_FINISH;
    DrawTileStretchedScreenPercentUV(Mat, A, B, C, D, E, F, G, H);
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit: stand-in bodies for the
// callees whose custom LTCG conventions must be reproduced, and drivers that
// call the functions the way retail does. The DrawTile and
// DrawTileStretchedScreenPercentUV bodies below are approximations whose only
// job is to give the linker the retail register conventions (DrawTile: this in
// ESI, material in EAX; ScreenPercentUV: this in EAX, material in EBX).
void Escape(void *);
void Sink(void *, void *, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, DWORD);

void UCanvas::DrawTile(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                       FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, DWORD Extra)
{
    Escape(Mat);
    Escape(this);
    FLOAT SX = ClipX, SY = ClipY;
    Sink(this, &CurX, X * SX + CurX, Y * SY + CurY, XL * SX, YL * SY, U + SX, V + SY, UL * SX, VL * SY, Z, Extra);
    Sink(this, &CurY, X * SY, Y * SX, XL + CurX, YL + CurY, U * SY, V * SX, UL + SY, VL + SX, Z, Extra);
    Escape(this);
}

void UCanvas::DrawTileStretchedScreenPercentUV(UMaterial *Mat, FLOAT X, FLOAT Y,
                                               FLOAT XL, FLOAT YL, FLOAT U,
                                               FLOAT V, FLOAT UL, FLOAT VL)
{
    FLOAT AWidth = XL * ClipX;
    FLOAT AHeight = YL * ClipY;
    CurX = X * ClipX;
    CurY = Y * ClipY;
    if (!Mat || !Unk48)
        return;
    FLOAT mW = Mat->MaterialUSize() * UL;
    FLOAT mH = Mat->MaterialVSize() * VL;
    FLOAT MidX = appFloor(mW * 0.5f);
    FLOAT MidY = appFloor(mH * 0.5f);
    FLOAT SmallTileW = AWidth - mW;
    FLOAT SmallTileH = AHeight - mH;
    FLOAT fX, fY;

    // Top and bottom spans.
    if (mW < AWidth) {
        fX = MidX;
        if (mH > AHeight)
            fY = AHeight * 0.5f;
        else
            fY = MidY;
        DrawTile(Mat, CurX + fX, CurY, SmallTileW, fY, fX, 0, 1.f, fY, 0, Unk50);
        DrawTile(Mat, CurX + fX, CurY + AHeight - fY, SmallTileW, fY, fX, mH - fY, 1.f, fY, 0, Unk50);
    } else
        fX = AWidth * 0.5f;

    // Left and right spans.
    if (mH < AHeight) {
        fY = MidY;
        DrawTile(Mat, CurX, CurY + fY, fX, SmallTileH, 0, fY, fX, 1.f, 0, Unk50);
        DrawTile(Mat, CurX + AWidth - fX, CurY + fY, fX, SmallTileH, mW - fX, fY, fX, 1.f, 0, Unk50);
    } else
        fY = AHeight * 0.5f;

    // The centre.
    if (mH < AHeight && mW < AWidth)
        DrawTile(Mat, CurX + fX, CurY + fY, SmallTileW, SmallTileH, fX, fY, 1.f, 1.f, 0, Unk50);

    // Corners.
    DrawTile(Mat, CurX, CurY, fX, fY, 0, 0, fX, fY, 0, Unk50);
    DrawTile(Mat, CurX + AWidth - fX, CurY, fX, fY, mW - fX, 0, fX, fY, 0, Unk50);
    DrawTile(Mat, CurX, CurY + AHeight - fY, fX, fY, 0, mH - fY, fX, fY, 0, Unk50);
    DrawTile(Mat, CurX + AWidth - fX, CurY + AHeight - fY, fX, fY, mW - fX, mH - fY, fX, fY, 0, Unk50);
}

// Stand-ins for the many retail callers of DrawTileStretched (GUI code),
// each holding the canvas in a callee-saved register.
void UseCanvasA(UCanvas *C, UMaterial *M, FLOAT *P)
{
    C->DrawTileStretched(M, P[0], P[1], P[2], P[3]);
    Escape(C);
}
void UseCanvasB(UCanvas *C, UMaterial *M, FLOAT *P)
{
    Escape(M);
    C->DrawTileStretched(M, P[1], P[0], P[3], P[2]);
    Escape(C);
}
void UseCanvasC(UCanvas *C, UMaterial **M, FLOAT *P)
{
    C->DrawTileStretched(M[0], P[0], P[1], P[2], P[3]);
    C->DrawTileStretched(M[1], P[4], P[5], P[6], P[7]);
    Escape(C);
}

// Stand-in for the retail exec that calls DrawTileStretched.
void UCanvas::execDrawTileStretched(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UMaterial, Mat);
    P_GET_FLOAT(XL);
    P_GET_FLOAT(YL);
    P_FINISH;
    DrawTileStretched(Mat, CurX, CurY, XL, YL);
}

void Driver_101ce0(UCanvas *C, FFrame *Stack, void *Result)
{
    Escape(GNatives);
    void (UCanvas::*Exec)(FFrame &, void *const) = &UCanvas::execDrawTileStretchedScreenPercentUV;
    Escape(&Exec);
    void (UCanvas::*Exec2)(FFrame &, void *const) = &UCanvas::execDrawTileStretched;
    Escape(&Exec2);
    (C->*Exec)(*Stack, Result);
    (C->*Exec2)(*Stack, Result);
    UseCanvasA(C, 0, 0);
    UseCanvasB(C, 0, 0);
    UseCanvasC(C, 0, 0);
}
