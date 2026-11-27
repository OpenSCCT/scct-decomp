#include "versus_mgm_keyframes.h"

static inline DWORD PackMgmKeyframeColor(INT Alpha, INT Red, INT Green, INT Blue)
{
    return ((((DWORD)Alpha << 8 | Red) << 8 | Green) << 8) | Blue;
}

void MgmKeyframe::SetRotation(FLOAT Value)
{
    Rotation = Value;
}

FLOAT MgmKeyframe::GetRotation() const
{
    return Rotation;
}

void MgmPositionKeyframe::GetPosition(MgmPoint &Out) const
{
    Out.X = Position.X;
    Out.Y = Position.Y;
}

void MgmPositionKeyframe::SetPosition(const MgmPoint &In)
{
    Position.X = In.X;
    Position.Y = In.Y;
}

void MgmPositionKeyframe::CopyFrom(const MgmKeyframe &Other)
{
    const MgmPositionKeyframe &Source = static_cast<const MgmPositionKeyframe &>(Other);
    Rotation = Source.Rotation;
    StateColor = Source.StateColor;
    Position.X = Source.Position.X;
    Position.Y = Source.Position.Y;
}

void MgmPositionKeyframe::Translate(const MgmPositionKeyframe &Offset)
{
    Position.X += Offset.Position.X;
    Position.Y += Offset.Position.Y;
}

void MgmRectKeyframe::GetPosition(MgmPoint &Position) const
{
    Position.X = Region.Left;
    Position.Y = Region.Top;
}

void MgmRectKeyframe::SetPosition(const MgmPoint &Position)
{
    Region.SetPosition(Position);
}

void MgmRectKeyframe::Translate(const MgmPositionKeyframe &Offset)
{
    Region.Translate(Offset.Position.X, Offset.Position.Y);
}

void MgmRectKeyframe::CopyFrom(const MgmKeyframe &Other)
{
    const MgmRectKeyframe &Source = static_cast<const MgmRectKeyframe &>(Other);
    Rotation = Source.Rotation;
    StateColor = Source.StateColor;
    Region.Left = Source.Region.Left;
    Region.Right = Source.Region.Right;
    Region.Top = Source.Region.Top;
    Region.Bottom = Source.Region.Bottom;
}

void MgmImage::CopyFrom(const MgmKeyframe &Other)
{
    const MgmImage &Source = static_cast<const MgmImage &>(Other);
    MgmRectKeyframe::CopyFrom(Other);
    RotationCenter.X = Source.RotationCenter.X;
    RotationCenter.Y = Source.RotationCenter.Y;
    Tiling.X = Source.Tiling.X;
    Tiling.Y = Source.Tiling.Y;
    Offset.X = Source.Offset.X;
    Offset.Y = Source.Offset.Y;
    Color[0] = Source.Color[0];
    Color[1] = Source.Color[1];
    Color[2] = Source.Color[2];
    Color[3] = Source.Color[3];
}

MgmRectKeyframe::MgmRectKeyframe()
{
}

MgmPositionKeyframe::MgmPositionKeyframe()
{
    Position.X = 0;
    Position.Y = 0;
}

MgmImage::MgmImage()
{
    RotationCenter.X = 5;
    RotationCenter.Y = 5;
    Tiling.X = 1.0f;
    Tiling.Y = 1.0f;
    Offset.X = 0.0f;
    Offset.Y = 0.0f;
    Color[0] = 0xffffffff;
    Color[1] = 0xffffffff;
    Color[2] = 0xffffffff;
    Color[3] = 0xffffffff;
}

void MgmKeyframe::Interpolate(const MgmKeyInterpolation &Blend)
{
    const MgmKeyframe &FromFrame = *Blend.From;
    const MgmKeyframe &ToFrame = *Blend.To;
    Rotation = GMgmInterpolator->Mix(FromFrame.Rotation, ToFrame.Rotation, Blend);
    const DWORD From = FromFrame.StateColor;
    const DWORD To = ToFrame.StateColor;
    BYTE Blue = (BYTE)(GMgmInterpolator->Mix(From & 0xff, To & 0xff, Blend) + 0.5f);
    BYTE Green = (BYTE)(GMgmInterpolator->Mix((From >> 8) & 0xff, (To >> 8) & 0xff, Blend) + 0.5f);
    BYTE Red = (BYTE)(GMgmInterpolator->Mix((From >> 16) & 0xff, (To >> 16) & 0xff, Blend) + 0.5f);
    BYTE Alpha = (BYTE)(GMgmInterpolator->Mix(From >> 24, To >> 24, Blend) + 0.5f);
    StateColor = PackMgmKeyframeColor(Alpha, Red, Green, Blue);
}

void MgmPositionKeyframe::Interpolate(const MgmKeyInterpolation &Blend)
{
    MgmKeyframe::Interpolate(Blend);
    const MgmPositionKeyframe &From = static_cast<const MgmPositionKeyframe &>(*Blend.From);
    const MgmPositionKeyframe &To = static_cast<const MgmPositionKeyframe &>(*Blend.To);
    Position.X = (short)GMgmInterpolator->Mix(From.Position.X, To.Position.X, Blend);
    Position.Y = (short)GMgmInterpolator->Mix(From.Position.Y, To.Position.Y, Blend);
}

void MgmRectKeyframe::Interpolate(const MgmKeyInterpolation &Blend)
{
    MgmKeyframe::Interpolate(Blend);
    const MgmRectKeyframe &From = static_cast<const MgmRectKeyframe &>(*Blend.From);
    const MgmRectKeyframe &To = static_cast<const MgmRectKeyframe &>(*Blend.To);
    Region.Left = (short)GMgmInterpolator->Mix(From.Region.Left, To.Region.Left, Blend);
    Region.Right = (short)GMgmInterpolator->Mix(From.Region.Right, To.Region.Right, Blend);
    Region.Top = (short)GMgmInterpolator->Mix(From.Region.Top, To.Region.Top, Blend);
    Region.Bottom = (short)GMgmInterpolator->Mix(From.Region.Bottom, To.Region.Bottom, Blend);
}

void MgmImage::Interpolate(const MgmKeyInterpolation &Blend)
{
    MgmRectKeyframe::Interpolate(Blend);
    const MgmImage &From = static_cast<const MgmImage &>(*Blend.From);
    const MgmImage &To = static_cast<const MgmImage &>(*Blend.To);
    RotationCenter.X = (short)GMgmInterpolator->Mix(From.RotationCenter.X, To.RotationCenter.X, Blend);
    RotationCenter.Y = (short)GMgmInterpolator->Mix(From.RotationCenter.Y, To.RotationCenter.Y, Blend);
    Tiling.X = GMgmInterpolator->Mix(From.Tiling.X, To.Tiling.X, Blend);
    Tiling.Y = GMgmInterpolator->Mix(From.Tiling.Y, To.Tiling.Y, Blend);
    Offset.X = GMgmInterpolator->Mix(From.Offset.X, To.Offset.X, Blend);
    Offset.Y = GMgmInterpolator->Mix(From.Offset.Y, To.Offset.Y, Blend);

    for (INT i = 0; i < 4; ++i) {
        FLOAT FromChannel = From.Color[i] & 0xff;
        FLOAT ToChannel = To.Color[i] & 0xff;
        INT Blue = (INT)GMgmInterpolator->Mix(FromChannel, ToChannel, Blend);
        FromChannel = (From.Color[i] & 0xff00) >> 8;
        ToChannel = (To.Color[i] & 0xff00) >> 8;
        INT Green = (INT)GMgmInterpolator->Mix(FromChannel, ToChannel, Blend);
        FromChannel = (From.Color[i] & 0xff0000) >> 16;
        ToChannel = (To.Color[i] & 0xff0000) >> 16;
        INT Red = (INT)GMgmInterpolator->Mix(FromChannel, ToChannel, Blend);
        FromChannel = (From.Color[i] & 0xff000000) >> 24;
        ToChannel = (To.Color[i] & 0xff000000) >> 24;
        INT Alpha = (INT)GMgmInterpolator->Mix(FromChannel, ToChannel, Blend);
        Color[i] = PackMgmKeyframeColor(Alpha, Red, Green, Blue);
    }
}
