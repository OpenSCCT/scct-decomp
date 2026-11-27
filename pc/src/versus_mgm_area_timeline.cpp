#include "versus_mgm.h"
#include "versus_mgm_content.h"

void MgmArea::SetVisible(BYTE Value, BYTE IncludeChildren)
{
    Visible = Value;
    if (IncludeChildren)
        for (MgmChild **It = Children; It != ChildrenEnd; ++It)
            (*It)->Visible = Value;
}

void MgmArea::SetPlaying(BYTE Value)
{
    if (Playing != Value) {
        Playing = Value;
        for (MgmChild **It = Children; It != ChildrenEnd; ++It)
            (*It)->Content->SetPlaying(Value);
    }
}

void MgmArea::SetTime(FLOAT Seconds, BYTE Update)
{
    Time = Seconds;
    for (MgmChild **It = Children; It != ChildrenEnd; ++It)
        (*It)->SetTime(Seconds, MillisecondsPerFrame, Update);
}

INT MgmArea::GetFrame() const
{
    FLOAT Frame = Time * 1000.0f / MillisecondsPerFrame;
    FLOAT Fraction = Frame;
    while (Fraction > 1.0f)
        Fraction -= 1.0f;
    if (Fraction >= 0.5f)
        Frame += 1.0f - Fraction;
    else
        Frame -= Fraction;
    return INT(Frame);
}

void MgmArea::Tick(FLOAT DeltaSeconds)
{
    if (Playing)
        Time += DeltaSeconds;
    for (MgmChild **It = Children; It != ChildrenEnd; ++It)
        (*It)->Tick(Time, DeltaSeconds, MillisecondsPerFrame, 1);
}

MgmImageRegion &MgmArea::GetBounds(MgmImageRegion &Bounds) const
{
    Bounds.Left = Bounds.Right = Bounds.Top = Bounds.Bottom = 0;
    for (MgmChild **It = Children; It != ChildrenEnd; ++It) {
        MgmImageRegion ChildBounds;
        ChildBounds.Left = 0;
        ChildBounds.Right = 0;
        ChildBounds.Top = 0;
        ChildBounds.Bottom = 0;
        (*It)->Content->GetBounds(ChildBounds);
        Bounds.Left = Bounds.Left < ChildBounds.Left ? Bounds.Left : ChildBounds.Left;
        Bounds.Right = Bounds.Right > ChildBounds.Right ? Bounds.Right : ChildBounds.Right;
        Bounds.Top = Bounds.Top < ChildBounds.Top ? Bounds.Top : ChildBounds.Top;
        Bounds.Bottom = Bounds.Bottom > ChildBounds.Bottom ? Bounds.Bottom : ChildBounds.Bottom;
    }
    return Bounds;
}

void MgmArea::SetFrame(INT Frame, BYTE Update)
{
    SetTime(MillisecondsPerFrame * Frame * 0.001f, Update);
}
