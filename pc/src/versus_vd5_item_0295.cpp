// Work item 0295: UCanvas tile helpers, Versus RVA 0x1021c0-0x1027ab.
// Retail compiled these with VC7.0 /GL and linked with /LTCG. UCanvas::DrawTile
// (retail 0xff300) takes `this` in ESI and the material in EAX. The UCanvas
// field layout follows item 0291 (UCanvas::execDrawTile). Function names are
// neutral (suffix = RVA): no strings or symbols name them.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

extern "C" __declspec(dllimport) double __cdecl floor(double);
inline INT appFloor(FLOAT F) { return (INT)floor(F); }

struct FColor
{
    BYTE B, G, R, A;
};

class UMaterial
{
public:
    virtual void Vf00(); virtual void Vf04(); virtual void Vf08(); virtual void Vf0c();
    virtual void Vf10(); virtual void Vf14(); virtual void Vf18(); virtual void Vf1c();
    virtual void Vf20(); virtual void Vf24(); virtual void Vf28(); virtual void Vf2c();
    virtual void Vf30(); virtual void Vf34(); virtual void Vf38(); virtual void Vf3c();
    virtual void Vf40(); virtual void Vf44(); virtual void Vf48(); virtual void Vf4c();
    virtual void Vf50(); virtual void Vf54(); virtual void Vf58(); virtual void Vf5c();
    virtual void Vf60(); virtual void Vf64();
    virtual INT MaterialUSize();   // 0x68
    virtual INT MaterialVSize();   // 0x6c
};

class UCanvas
{
public:
    void *VfTable_Dummy;
    BYTE Pad04[0x2c - 0x04];
    FLOAT OrgX;      // 0x2c
    FLOAT OrgY;      // 0x30
    FLOAT ClipX;     // 0x34
    FLOAT ClipY;     // 0x38
    FLOAT CurX;      // 0x3c
    FLOAT CurY;      // 0x40
    FLOAT Z;         // 0x44
    BYTE Style;      // 0x48
    FLOAT CurYL;     // 0x4c
    FColor DrawColor; // 0x50

    void DrawTile(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                  FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, FColor Color);

    void DrawTileStretched_1021c0(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT W, FLOAT H,
                                  FLOAT U, FLOAT V, FLOAT UL, FLOAT VL);
    void DrawTileRect_102550(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL);
    void DrawTileFull_102590(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL);
    void DrawTileAspect_102600(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL, BYTE Align);
};

#pragma auto_inline(off)
// Draws a material as a nine-slice box (UE2 UCanvas::DrawTileStretched with
// an explicit source rectangle); X/Y/W/H are fractions of the clip area.
void UCanvas::DrawTileStretched_1021c0(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT W, FLOAT H,
                                       FLOAT U, FLOAT V, FLOAT UL, FLOAT VL)
{
    FLOAT AWidth = W * ClipX;
    FLOAT &AHeight = H;
    AHeight = H * ClipY;
    CurX = X * ClipX;
    CurY = Y * ClipY;
    if (Mat && Style)
    {
        // Get the midpoints of the image.
        FLOAT ImageMidX = (FLOAT)appFloor(UL * 0.5f);
        FLOAT ImageMidY = (FLOAT)appFloor(VL * 0.5f);
        // Hold the fill areas.
        FLOAT FillX = AWidth - UL;
        FLOAT FillY = AHeight - VL;
        FLOAT MidX, MidY;
        // Draw the spans first: top and bottom.
        if (UL < AWidth)
        {
            MidX = ImageMidX;
            MidY = (VL > AHeight) ? AHeight * 0.5f : ImageMidY;
            DrawTile(Mat, ImageMidX + CurX, CurY, FillX, MidY, ImageMidX + U, V, 1.0f, MidY, 0, DrawColor);
            DrawTile(Mat, ImageMidX + CurX, AHeight + CurY - MidY, FillX, MidY, ImageMidX + U, V + VL - MidY, 1.0f, MidY, 0, DrawColor);
        }
        else
            MidX = AWidth * 0.5f;
        // Left and right.
        if (VL < AHeight)
        {
            MidY = ImageMidY;
            DrawTile(Mat, CurX, ImageMidY + CurY, MidX, FillY, U, ImageMidY + V, MidX, 1.0f, 0, DrawColor);
            DrawTile(Mat, AWidth + CurX - MidX, ImageMidY + CurY, MidX, FillY, U + UL - MidX, ImageMidY + V, MidX, 1.0f, 0, DrawColor);
        }
        else
            MidY = AHeight * 0.5f;
        // Center.
        if (VL < AHeight && UL < AWidth)
            DrawTile(Mat, MidX + CurX, MidY + CurY, FillX, FillY, MidX + U, MidY + V, 1.0f, 1.0f, 0, DrawColor);
        // Draw the 4 corners.
        DrawTile(Mat, CurX, CurY, MidX, MidY, U, V, MidX, MidY, 0, DrawColor);
        DrawTile(Mat, AWidth + CurX - MidX, CurY, MidX, MidY, U + UL - MidX, V, MidX, MidY, 0, DrawColor);
        DrawTile(Mat, CurX, AHeight + CurY - MidY, MidX, MidY, U, V + VL - MidY, MidX, MidY, 0, DrawColor);
        DrawTile(Mat, AWidth + CurX - MidX, AHeight + CurY - MidY, MidX, MidY, U + UL - MidX, V + VL - MidY, MidX, MidY, 0, DrawColor);
    }
}

void UCanvas::DrawTileRect_102550(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL)
{
    if (Style)
        DrawTile(Mat, X, Y, XL, YL, 0, 0, XL, YL, 0, DrawColor);
}

void UCanvas::DrawTileFull_102590(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL)
{
    if (Style)
    {
        FLOAT USize = (FLOAT)Mat->MaterialUSize();
        FLOAT VSize = (FLOAT)Mat->MaterialVSize();
        DrawTile(Mat, X, Y, XL, YL, 0, 0, USize, VSize, 0, DrawColor);
    }
}

// Fits the whole material into the box keeping its aspect ratio; Align 1
// centres it, 2 pushes it to the right/bottom, anything else to the left/top.
void UCanvas::DrawTileAspect_102600(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL, BYTE Align)
{
    if (!Style)
        return;
    FLOAT USize = (FLOAT)Mat->MaterialUSize();
    FLOAT VSize = (FLOAT)Mat->MaterialVSize();
    if (USize <= 0.f || VSize <= 0.f)
        return;
    FLOAT MatRatio = VSize / USize;
    FLOAT BoxRatio = YL / XL;
    if (MatRatio == BoxRatio)
    {
        DrawTile(Mat, X, Y, XL, YL, 0, 0, USize, VSize, 0, DrawColor);
        return;
    }
    if (MatRatio > BoxRatio)
    {
        FLOAT NewXL = BoxRatio / MatRatio * XL;
        FLOAT NewX = X;
        if (Align == 1)
            NewX = (XL - NewXL) * 0.5f + X;
        else if (Align == 2)
            NewX = XL - NewXL + X;
        DrawTile(Mat, NewX, Y, NewXL, YL, 0, 0, USize, VSize, 0, DrawColor);
        return;
    }
    FLOAT NewYL = MatRatio / BoxRatio * YL;
    FLOAT NewY = Y;
    if (Align == 1)
        NewY = (YL - NewYL) * 0.5f + Y;
    else if (Align == 2)
        NewY = YL - NewYL + Y;
    DrawTile(Mat, X, NewY, XL, NewYL, 0, 0, USize, VSize, 0, DrawColor);
}

#pragma auto_inline(on)

// Scaffolding for the link, not part of the unit: a stand-in DrawTile body
// so the linker gives it retail's register convention, and drivers.
void ExtPrepare(UCanvas *, UMaterial *);
void ExtTile(UCanvas *, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FColor);
#pragma auto_inline(off)
void UCanvas::DrawTile(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                  FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, FColor Color)
{
    ExtPrepare(this, Material);
    ExtTile(this, X, Y, XL, YL, U, V, UL, VL, Z, Color);
    ExtPrepare(this, 0);
}
#pragma auto_inline(on)
void Driver_1021c0(UCanvas *C, UMaterial *M, FLOAT a, FLOAT b, FLOAT c, FLOAT d, FLOAT e, FLOAT f, FLOAT g, FLOAT h)
{
    C->DrawTileStretched_1021c0(M, a, b, c, d, e, f, g, h);
}
void Driver_102550(UCanvas *C, UMaterial *M, FLOAT a, FLOAT b, FLOAT c, FLOAT d)
{
    C->DrawTileRect_102550(M, a, b, c, d);
}
void Driver_102590(UCanvas *C, UMaterial *M, FLOAT a, FLOAT b, FLOAT c, FLOAT d)
{
    C->DrawTileFull_102590(M, a, b, c, d);
}
void Driver_102600(UCanvas *C, UMaterial *M, FLOAT a, FLOAT b, FLOAT c, FLOAT d, BYTE Al)
{
    C->DrawTileAspect_102600(M, a, b, c, d, Al);
}
