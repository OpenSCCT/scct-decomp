#ifndef VERSUS_MGM_KEYFRAMES_H
#define VERSUS_MGM_KEYFRAMES_H

#include "versus_build.h"
#include "unreal_types.h"

struct MgmPoint {
    short X, Y;
    MgmPoint() : X(0), Y(0) {}
};

struct MgmImageRegion {
    short Left, Right, Top, Bottom;
    MgmImageRegion() : Left(0), Right(20), Top(20), Bottom(0) {}

    void SetPosition(const MgmPoint &Position);
    void Translate(INT DeltaX, INT DeltaY);
};

class MgmKeyframeVisitor;
class MgmKeyframe;
struct MgmKeyInterpolation {
    FLOAT Duration, Elapsed;
    INT Mode;
    BYTE Unknown0c[4];
    const MgmKeyframe *From, *To;
};

class MgmInterpolator {
public:
    FLOAT Mix(FLOAT From, FLOAT To, const MgmKeyInterpolation &Blend);
};

extern MgmInterpolator *GMgmInterpolator;
class MgmPositionKeyframe;

// MGM serializes ROTATION and STATECOLOR for every keyframe.
class MgmKeyframe {
public:
    MgmKeyframe() : Rotation(0.0f), StateColor(0xffffffff) {}
    virtual ~MgmKeyframe();
    virtual void Accept(MgmKeyframeVisitor &Visitor);
    virtual void Interpolate(const MgmKeyInterpolation &Blend);
    virtual void CopyFrom(const MgmKeyframe &Other);
    virtual void Translate(const MgmPositionKeyframe &Offset);
    virtual void GetPosition(MgmPoint &Position) const;
    virtual void SetPosition(const MgmPoint &Position);
    virtual void SetRotation(FLOAT Value);
    virtual FLOAT GetRotation() const;

    FLOAT Rotation;
    DWORD StateColor;
};

class MgmPositionKeyframe : public MgmKeyframe {
public:
    MgmPositionKeyframe();
    virtual void Accept(MgmKeyframeVisitor &Visitor);
    virtual void Interpolate(const MgmKeyInterpolation &Blend);
    virtual void CopyFrom(const MgmKeyframe &Other);
    virtual void Translate(const MgmPositionKeyframe &Offset);
    virtual void GetPosition(MgmPoint &Out) const;
    virtual void SetPosition(const MgmPoint &In);
    MgmPoint Position;
};

class MgmRectKeyframe : public MgmKeyframe {
public:
    MgmRectKeyframe();
    virtual void Accept(MgmKeyframeVisitor &Visitor);
    virtual void Interpolate(const MgmKeyInterpolation &Blend);
    virtual void CopyFrom(const MgmKeyframe &Other);
    virtual void Translate(const MgmPositionKeyframe &Offset);
    virtual void GetPosition(MgmPoint &Position) const;
    virtual void SetPosition(const MgmPoint &Position);
    MgmImageRegion Region;
};

struct MgmAxisPair {
    FLOAT X, Y;
};

// An IMAGE keyframe stores a rotation center, tiling, offset, and four corner colors.
struct MgmImage : public MgmRectKeyframe {
    MgmImage();
    virtual void Accept(MgmKeyframeVisitor &Visitor);
    virtual void Interpolate(const MgmKeyInterpolation &Blend);
    virtual void CopyFrom(const MgmKeyframe &Other);

    MgmPoint RotationCenter;
    MgmAxisPair Tiling, Offset;
    DWORD Color[4];
};

#endif
