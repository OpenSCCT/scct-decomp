enum EImgStyle { ISTY_Normal, ISTY_Stretched, ISTY_Scaled };

static inline FColor GUIShade(BYTE Intensity)
{
    FColor Color;
    Color.R = Color.G = Color.B = Intensity;
    Color.A = 255;
    return Color;
}

void UGUIStyles::Draw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height)
{
    if (MenuState > 5)
        return;

    if (delegateOnDraw(Canvas, MenuState, Left, Top, Width, Height))
        return;

    if (!Images[MenuState])
        return;

    if (MenuState == 4)
        Canvas->DrawColor = GUIShade(64);
    else
        Canvas->DrawColor = GUIShade(128);

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
            Canvas->DrawTile(M, Left, Top, mW, mH, 0, 0, mW, mH, 0, GUIShade(128));
            break;
        case ISTY_Stretched:
            Canvas->DrawTileStretched(M, Left, Top, Width, Height);
            break;
        case ISTY_Scaled:
            Canvas->DrawTileScaled(M, Left, Top, Width, Height);
            break;
    }
}
