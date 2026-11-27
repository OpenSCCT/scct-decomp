#include "versus_build.h"
#include "versus_native_class_types.h"
#include "versus_canvas.h"
#include "versus_canvas_util.h"
#include "versus_material.h"
#include "versus_output_device.h"
#include "versus_viewport_types.h"
#include "versus_gui_controller_types.h"
#include "versus_gui_list_types.h"
#include "versus_gui_style_types.h"

extern "C" __declspec(dllimport) DOUBLE __cdecl floor(DOUBLE Value);
static const EName GUI_OnDrawItem = (EName)53449;

void UCanvas::DrawTile(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
    FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, FColor Color)
{
    Material = GetStyleMaterial(Material);
    FLOAT SY = (FLOAT)Viewport->SizeY;
    FLOAT SX = (FLOAT)Viewport->SizeX;
    FLOAT X1 = SX * X;
    FLOAT Y1 = SY * Y;
    FLOAT X2 = (X + XL) * SX;
    FLOAT Y2 = (Y + YL) * SY;
    const FLOAT ScaleX = 1.f / 640.f;
    const FLOAT ScaleY = 1.f / 480.f;
    pCanvasUtil->DrawTile(X1 * ScaleX, Y1 * ScaleY, X2 * ScaleX, Y2 * ScaleY,
        U, V, U + UL, V + VL, 0.f, Material, Color);
}

void UCanvas::DrawTile(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL, FLOAT Z, FColor Color)
{
    DrawTile(Material, X, Y, XL, YL, 0.f, 0.f, (FLOAT)Material->MaterialUSize(),
        (FLOAT)Material->MaterialVSize(), Z, Color);
}

void UGUIListBase::delegateOnDrawItem(UCanvas *Canvas, INT Item, FLOAT X, FLOAT Y,
    FLOAT W, FLOAT H, UBOOL bSelected)
{
    struct FItemDrawParms {
        UCanvas *Canvas;
        INT Item;
        FLOAT X, Y, W, H;
        UBOOL bSelected;
    } Parms = {Canvas, Item, X, Y, W, H, bSelected};
    ProcessDelegate(GUI_OnDrawItem, &__OnDrawItem__Delegate, &Parms, 0);
}

void UGUIMultiColumnList::Draw(UCanvas *Canvas)
{
    if (bHotTrack && Controller->HasMouseMoved()
        && PerformInBounds(Controller->MouseX, Controller->MouseY)) {
        Index = Top + (INT)floor((Controller->MouseY - ClientBounds[1]) / ItemHeight);
        if (Index >= ItemCount)
            Index = ItemCount - 1;
    }

    if (bDrawArrow) {
        if (Top > 0)
            Canvas->DrawTile(ArrowUp, ActualLeft() + (FLOAT)(ActualWidth() * 0.5f) - 8.f,
                ActualTop() - 16.f, 16.f, 16.f, 0.f, ArrowColor);
        if (Top + ItemsPerPage < ItemCount)
            Canvas->DrawTile(ArrowDown, ActualLeft() + (FLOAT)(ActualWidth() * 0.5f) - 8.f,
                ActualTop() + ActualHeight(), 16.f, 16.f, 0.f, ArrowColor);
    }

    if (bDrawColumn) {
        if (!bVisible || !Style || (!ItemCount && !bVisibleWhenEmpty))
            return;
        INT X = (INT)ActualLeft();
        for (INT Column = 0; Column < ColumnWidths.Num(); ++Column) {
            Style->Draw(Canvas, MenuState, X + CellSpacing * 0.5f, ActualTop(),
                ColumnWidths(Column) - CellSpacing * 0.5f, ActualHeight());
            X += ColumnWidths(Column);
        }
        INT Y = (INT)ClientBounds[1];
        for (INT Row = 0; Row < ItemsPerPage; ++Row) {
            BYTE OldState = MenuState;
            if (Row + Top < ItemCount) {
                UBOOL bSelected = Row + Top == Index;
                if (__OnDrawItem__Delegate.Object && !__OnDrawItem__Delegate.Object->IsPendingKill())
                    delegateOnDrawItem(Canvas, Row + Top, ClientBounds[0], (FLOAT)Y,
                        ClientBounds[2] - ClientBounds[0], (FLOAT)ItemHeight, bSelected);
            }
            MenuState = OldState;
            Y += ItemHeight;
        }
    } else {
        UGUIVertList::Draw(Canvas);
    }
}

#include "versus_gui_style_draw.inl"
