// Work item 0287: Versus RVA 0xff300 and 0xff3a0 (LTCG, custom conventions).
// Names are neutral where evidence is thin. The 0x78/0x7c canvas members and
// the material size virtuals at vtable 0x68/0x6c follow UE2 UCanvas/UMaterial.
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef unsigned char BYTE;
struct FColor { BYTE B, G, R, A; };

struct FCanvasUtil;
struct UViewport_Partial { char Pad[0xa0]; INT SizeX; INT SizeY; };

struct UCanvas;
struct UMaterial
{
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0c();
    virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1c();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2c();
    virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3c();
    virtual void V40(); virtual void V44(); virtual void V48(); virtual void V4c();
    virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5c();
    virtual void V60(); virtual void V64();
    virtual INT MaterialUSize();   // 0x68
    virtual INT MaterialVSize();   // 0x6c
    DWORD RenderMaterial_104010(UCanvas *C);   // RVA 0x104010, unnamed
    void DrawTileFull_ff3a0(UCanvas *C, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                            FLOAT Unused, FColor Color);
};

struct FCanvasUtil
{
    void Flush_111c60();
    // RVA 0x111f50, unnamed draw call.
    void DrawTile_111f50(FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2,
                         FLOAT U1, FLOAT V1, FLOAT U2, FLOAT V2,
                         FLOAT Z, DWORD Material, FColor Color);
};

struct UCanvas
{
    char Pad[0x78];
    UViewport_Partial *Viewport;   // 0x78
    FCanvasUtil *pCanvasUtil;      // 0x7c
    void DrawTileScaled_ff300(UMaterial *M, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                              FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Unused, FColor Color);
};

extern FLOAT ScaleX_ff300;   // 0x10c10d80
extern FLOAT ScaleY_ff300;   // 0x10c10b58

void UCanvas::DrawTileScaled_ff300(UMaterial *M, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                          FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Unused, FColor Color)
{
    UCanvas *C = this;
    DWORD R = M->RenderMaterial_104010(C);
    FLOAT SY = (FLOAT)C->Viewport->SizeY;
    FLOAT SX = (FLOAT)C->Viewport->SizeX;
    FLOAT X1 = SX * X;
    FLOAT Y1 = SY * Y;
    FLOAT X2 = (X + XL) * SX;
    FLOAT Y2 = (Y + YL) * SY;
    C->pCanvasUtil->DrawTile_111f50(X1 * ScaleX_ff300, Y1 * ScaleY_ff300,
                                    X2 * ScaleX_ff300, Y2 * ScaleY_ff300,
                                    U, V, U + UL, V + VL, 0, R, Color);
}

__declspec(noinline) void UMaterial::DrawTileFull_ff3a0(UCanvas *C, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                        FLOAT Unused, FColor Color)
{
    UMaterial *M = this;
    C->DrawTileScaled_ff300(M, X, Y, XL, YL, 0, 0,
                         (FLOAT)M->MaterialUSize(), (FLOAT)M->MaterialVSize(), Unused, Color);
}

// 0xff3a0 is near: retail passes the material to 0xff300 in EAX (because the
// cached lookup at 0x104010 takes `this` in EAX); here that lookup is a plain
// external stub, so the material travels in ECX and the tail differs by 7 bytes.
// noinline mirrors retail, which kept 0xff3a0 out of line.

// Scaffolding for the link, not part of the unit. The callee at 0x111f50 is
// defined here only so the LTCG linker sees it and passes `this` in EAX as
// retail does; its body is a placeholder.
void Escape(void *);
void Sink_111f50(INT *, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, DWORD, FColor);
void FCanvasUtil::DrawTile_111f50(FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2,
                                  FLOAT U1, FLOAT V1, FLOAT U2, FLOAT V2,
                                  FLOAT Z, DWORD Material, FColor Color)
{
    INT *F = (INT *)this;
    if (F[1] != 0 || F[2] != (INT)Material || F[0x98 / 4] + 6 > 0x552) {
        Flush_111c60();
        F[1] = 0;
        F[2] = (INT)Material;
    }
    Sink_111f50(F + 0x94 / 4, X1, Y1, X2, Y2, U1, V1, U2, V2, Z, Material, Color);
    Sink_111f50(F + 0x94 / 4, X2, Y2, X1, Y1, U1, V1, U2, V2, Z, Material, Color);
}
void Driver_ff3a0(UMaterial *M, UCanvas *C, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL, FLOAT A, FColor B)
{
    M->DrawTileFull_ff3a0(C, X, Y, XL, YL, A, B);
    M->DrawTileFull_ff3a0(C, Y, X, YL, XL, A, B);
    M->DrawTileFull_ff3a0(C, X, X, YL, YL, A, B);
    M->DrawTileFull_ff3a0(C, Y, Y, XL, XL, A, B);
    M->DrawTileFull_ff3a0(C, XL, Y, X, YL, A, B);
    M->DrawTileFull_ff3a0(C, X, YL, XL, Y, A, B);
    C->DrawTileScaled_ff300(M, X, Y, XL, YL, X, Y, XL, YL, A, B);
    C->pCanvasUtil->DrawTile_111f50(X, Y, XL, YL, X, Y, XL, YL, 0, 0, B);
}
