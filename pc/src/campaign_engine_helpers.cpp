// campaign_engine_helpers.cpp -- UECanvas line drawing and the damping helpers
#include "unreal_script.h"
#include "unreal_math.h"
#include "unreal_containers.h"
#include "campaign_canvas.h"

// UECanvas::DrawLine
void UECanvas::DrawLine(INT X, INT Y, INT XL, INT YL, const FColor &InColor, INT Alpha, UMaterial *Material)
{
    if (!Material)
        return;
    Color.R = InColor.R;
    Color.G = InColor.G;
    Color.B = InColor.B;
    if (Alpha == -1)
        Color.A = InColor.A;
    else
        Color.A = Alpha;
    CurX = X;
    CurY = Y;
    Material->DrawTile(this, Material->unk_34, XL, YL, 0.0f, 0.0f, 1.0f, 1.0f);
}

// DampFloat
FLOAT DampFloat(FLOAT Current, FLOAT Target, FLOAT Rate, FLOAT DeltaTime)
{
    FLOAT MaxDelta = Rate * DeltaTime;
    return Clamp(Target - Current, -MaxDelta, MaxDelta) + Current;
}

// DampInt
INT DampInt(INT Current, INT Target, FLOAT Rate, FLOAT DeltaTime)
{
    FLOAT MaxDelta = Rate * DeltaTime;
    return (INT)Clamp((FLOAT)Target - Current, -MaxDelta, MaxDelta) + Current;
}

// DampVec
FVector DampVec(const FVector &Current, const FVector &Target, FLOAT Rate, FLOAT DeltaTime)
{
    FLOAT MaxDelta = Rate * DeltaTime;
    FVector Delta = Target - Current;
    FLOAT Size = Delta.Size();
    if (Size > MaxDelta)
        Delta *= MaxDelta / Size;
    return Delta + Current;
}

// UECanvas::DrawRectangle
void UECanvas::DrawRectangle(INT X, INT Y, INT XL, INT YL, INT Thickness, const FColor &Color, INT Alpha, UMaterial *Material)
{
    DrawLine(X, Y, XL, Thickness, Color, Alpha, Material);
    DrawLine(X, Y + YL - Thickness, XL, Thickness, Color, Alpha, Material);
    DrawLine(X, Y + Thickness, Thickness, YL - 2 * Thickness, Color, Alpha, Material);
    DrawLine(X + XL - Thickness, Y + Thickness, Thickness, YL - 2 * Thickness, Color, Alpha, Material);
}
