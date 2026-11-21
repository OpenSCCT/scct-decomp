// Versus RVA 0x524f0: distance between two line segments. The algorithm is
// Dave Eberly's segment/segment SqrDistance (Magic Software), with each segment
// given as two end points and the closest-point parameters dropped. The name is
// neutral: no symbol or string names it.
// Built with /GL and linked /LTCG: P0 arrives in ECX, P1 in ESI, Q0 in EAX, Q1 in EDX.

typedef float FLOAT;

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
};

template <class T> inline T Abs(const T A) { return (A >= (T)0) ? A : -A; }
inline FLOAT appSqrt(FLOAT Value) { return (FLOAT)sqrt(Value); }

FLOAT SegmentSegmentDist(const FVector &P0, const FVector &P1, const FVector &Q0, const FVector &Q1)
{
    FVector kDiff = P0 - Q0;
    FVector D0 = P1 - P0;
    FVector D1 = Q1 - Q0;
    FLOAT fA00 = D0 | D0;
    FLOAT fA01 = -D0 | D1;
    FLOAT fA11 = D1 | D1;
    FLOAT fB0 = kDiff | D0;
    FLOAT fC = kDiff | kDiff;
    FLOAT fDet = Abs(fA00 * fA11 - fA01 * fA01);
    FLOAT fB1, fS, fT, fSqrDist, fTmp;

    if (fDet >= 0.0001f)
    {
        // line segments are not parallel
        fB1 = -kDiff | D1;
        fS = fA01 * fB1 - fA11 * fB0;
        fT = fA01 * fB0 - fA00 * fB1;

        if (fS >= 0.0f)
        {
            if (fS <= fDet)
            {
                if (fT >= 0.0f)
                {
                    if (fT <= fDet)  // region 0 (interior)
                    {
                        FLOAT fInvDet = 1.0f / fDet;
                        fS *= fInvDet;
                        fT *= fInvDet;
                        fSqrDist = fS * (fA00 * fS + fA01 * fT + 2.0f * fB0) +
                                   fT * (fA01 * fS + fA11 * fT + 2.0f * fB1) + fC;
                    }
                    else  // region 3 (side)
                    {
                        fTmp = fA01 + fB0;
                        if (fTmp >= 0.0f)
                            fSqrDist = fA11 + 2.0f * fB1 + fC;
                        else if (-fTmp >= fA00)
                            fSqrDist = fA00 + fA11 + fC + 2.0f * (fB1 + fTmp);
                        else
                        {
                            fS = -fTmp / fA00;
                            fSqrDist = fTmp * fS + fA11 + 2.0f * fB1 + fC;
                        }
                    }
                }
                else  // region 7 (side)
                {
                    if (fB0 >= 0.0f)
                        fSqrDist = fC;
                    else if (-fB0 >= fA00)
                        fSqrDist = fA00 + 2.0f * fB0 + fC;
                    else
                    {
                        fS = -fB0 / fA00;
                        fSqrDist = fB0 * fS + fC;
                    }
                }
            }
            else
            {
                if (fT >= 0.0)
                {
                    if (fT <= fDet)  // region 1 (side)
                    {
                        fTmp = fA01 + fB1;
                        if (fTmp >= 0.0f)
                            fSqrDist = fA00 + 2.0f * fB0 + fC;
                        else if (-fTmp >= fA11)
                            fSqrDist = fA00 + fA11 + fC + 2.0f * (fB0 + fTmp);
                        else
                        {
                            fT = -fTmp / fA11;
                            fSqrDist = fTmp * fT + fA00 + 2.0f * fB0 + fC;
                        }
                    }
                    else  // region 2 (corner)
                    {
                        fTmp = fA01 + fB0;
                        if (-fTmp <= fA00)
                        {
                            if (fTmp >= 0.0f)
                                fSqrDist = fA11 + 2.0f * fB1 + fC;
                            else
                            {
                                fS = -fTmp / fA00;
                                fSqrDist = fTmp * fS + fA11 + 2.0f * fB1 + fC;
                            }
                        }
                        else
                        {
                            fTmp = fA01 + fB1;
                            if (fTmp >= 0.0f)
                                fSqrDist = fA00 + 2.0f * fB0 + fC;
                            else if (-fTmp >= fA11)
                                fSqrDist = fA00 + fA11 + fC + 2.0f * (fB0 + fTmp);
                            else
                            {
                                fT = -fTmp / fA11;
                                fSqrDist = fTmp * fT + fA00 + 2.0f * fB0 + fC;
                            }
                        }
                    }
                }
                else  // region 8 (corner)
                {
                    if (-fB0 < fA00)
                    {
                        if (fB0 >= 0.0f)
                            fSqrDist = fC;
                        else
                        {
                            fS = -fB0 / fA00;
                            fSqrDist = fB0 * fS + fC;
                        }
                    }
                    else
                    {
                        fTmp = fA01 + fB1;
                        if (fTmp >= 0.0f)
                            fSqrDist = fA00 + 2.0f * fB0 + fC;
                        else if (-fTmp >= fA11)
                            fSqrDist = fA00 + fA11 + fC + 2.0f * (fB0 + fTmp);
                        else
                        {
                            fT = -fTmp / fA11;
                            fSqrDist = fTmp * fT + fA00 + 2.0f * fB0 + fC;
                        }
                    }
                }
            }
        }
        else
        {
            if (fT >= 0.0f)
            {
                if (fT <= fDet)  // region 5 (side)
                {
                    if (fB1 >= 0.0f)
                        fSqrDist = fC;
                    else if (-fB1 >= fA11)
                        fSqrDist = fA11 + 2.0f * fB1 + fC;
                    else
                    {
                        fT = -fB1 / fA11;
                        fSqrDist = fB1 * fT + fC;
                    }
                }
                else  // region 4 (corner)
                {
                    fTmp = fA01 + fB0;
                    if (fTmp < 0.0f)
                    {
                        if (-fTmp >= fA00)
                            fSqrDist = fA00 + fA11 + fC + 2.0f * (fB1 + fTmp);
                        else
                        {
                            fS = -fTmp / fA00;
                            fSqrDist = fTmp * fS + fA11 + 2.0f * fB1 + fC;
                        }
                    }
                    else
                    {
                        if (fB1 >= 0.0f)
                            fSqrDist = fC;
                        else if (-fB1 >= fA11)
                            fSqrDist = fA11 + 2.0f * fB1 + fC;
                        else
                        {
                            fT = -fB1 / fA11;
                            fSqrDist = fB1 * fT + fC;
                        }
                    }
                }
            }
            else  // region 6 (corner)
            {
                if (fB0 < 0.0f)
                {
                    if (-fB0 >= fA00)
                        fSqrDist = fA00 + 2.0f * fB0 + fC;
                    else
                    {
                        fS = -fB0 / fA00;
                        fSqrDist = fB0 * fS + fC;
                    }
                }
                else
                {
                    if (fB1 >= 0.0f)
                        fSqrDist = fC;
                    else if (-fB1 >= fA11)
                        fSqrDist = fA11 + 2.0f * fB1 + fC;
                    else
                    {
                        fT = -fB1 / fA11;
                        fSqrDist = fB1 * fT + fC;
                    }
                }
            }
        }
    }
    else
    {
        // line segments are parallel
        if (fA01 > 0.0f)
        {
            // direction vectors form an obtuse angle
            if (fB0 >= 0.0f)
                fSqrDist = fC;
            else if (-fB0 <= fA00)
            {
                fS = -fB0 / fA00;
                fSqrDist = fB0 * fS + fC;
            }
            else
            {
                fB1 = -kDiff | D1;
                fTmp = fA00 + fB0;
                if (-fTmp >= fA01)
                    fSqrDist = fA00 + fA11 + fC + 2.0f * (fA01 + fB0 + fB1);
                else
                {
                    fT = -fTmp / fA01;
                    fSqrDist = fA00 + 2.0f * fB0 + fC + fT * (fA11 * fT + 2.0f * (fA01 + fB1));
                }
            }
        }
        else
        {
            // direction vectors form an acute angle
            if (-fB0 >= fA00)
                fSqrDist = fA00 + 2.0f * fB0 + fC;
            else if (fB0 <= 0.0f)
            {
                fS = -fB0 / fA00;
                fSqrDist = fB0 * fS + fC;
            }
            else
            {
                fB1 = -kDiff | D1;
                if (fB0 >= -fA01)
                    fSqrDist = fA11 + 2.0f * fB1 + fC;
                else
                {
                    fT = -fB0 / fA01;
                    fSqrDist = fC + fT * (2.0f * fB1 + fA11 * fT);
                }
            }
        }
    }

    return appSqrt(Abs(fSqrDist));
}

// Scaffolding for the link, not part of the unit: retail callers load
// ECX = P0, ESI = P1, EAX = Q0, EDX = Q1.
void Sink(FLOAT);
void Driver_524f0(const FVector &P0, const FVector &P1, const FVector &Q0, const FVector &Q1)
{
    Sink(SegmentSegmentDist(P0, P1, Q0, Q1));
}
