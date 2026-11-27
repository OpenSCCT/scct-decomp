#ifndef VERSUS_MGM_INTERPOLATOR_H
#define VERSUS_MGM_INTERPOLATOR_H

#include "versus_build.h"
#include "unreal_types.h"

class MgmKeyframe;

// The MGM INTERPOLATION name table uses these modes in file order.
enum EMgmInterpolationMode {
    MGMINTERP_None,
    MGMINTERP_Linear,
    MGMINTERP_Square,
    MGMINTERP_Root,
    MGMINTERP_Sin,
    MGMINTERP_Circle,
    MGMINTERP_CircleDecel,
    MGMINTERP_Count
};

struct MgmKeyInterpolation {
    FLOAT Duration, Elapsed;
    EMgmInterpolationMode Mode;
    INT unk_0c;
    const MgmKeyframe *From, *To;
};

class MgmInterpolator {
public:
    MgmInterpolator();
    ~MgmInterpolator();
    void BuildTables(INT Count);
    FLOAT GetCoefficient(EMgmInterpolationMode Mode, INT Index) const;
    FLOAT Mix(FLOAT From, FLOAT To, const MgmKeyInterpolation &Blend);

private:
    INT SampleCount;
    FLOAT *Tables[MGMINTERP_Count];
};

extern MgmInterpolator *GMgmInterpolator;

#endif
