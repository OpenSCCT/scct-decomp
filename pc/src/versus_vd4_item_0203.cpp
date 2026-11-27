// Item 0203: FMatrix helpers (UnMath.h), LTCG custom calling conventions.
typedef float FLOAT;

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

class FPlane : public FVector
{
public:
    FLOAT W;
    FPlane() {}
    FPlane(FVector V, FLOAT InW) : FVector(V), W(InW) {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
};

class FMatrix
{
public:
    FLOAT M[4][4];

    FPlane TransformFPlane(const FPlane &P) const;   // 0x4fe60, called
    FVector TransformFVector(const FVector &V) const;
};

// RVA 0x4ff40: this on the stack (ret 4), V in EAX, result in ESI.
// Matched with /O2 /Ob1 /Gy: at /Ob2 the LTCG inliner folds it into the driver.
FVector FMatrix::TransformFVector(const FVector &V) const
{
    return TransformFPlane(FPlane(V.X, V.Y, V.Z, 1.0f));
}

// Scaffolding for the link, not part of the unit.
void Sink(FVector *);
void Driver_4ff40(const FMatrix *M, const FVector *V, FVector *Out)
{
    Out[0] = M->TransformFVector(V[0]); Sink(Out);
    Out[1] = M->TransformFVector(V[1]); Sink(Out);
    Out[2] = M->TransformFVector(V[2]); Sink(Out);
    Out[3] = M->TransformFVector(V[3]); Sink(Out);
    Out[4] = M->TransformFVector(V[4]); Sink(Out);
    Out[5] = M->TransformFVector(V[5]); Sink(Out);
    Out[6] = M->TransformFVector(V[6]); Sink(Out);
    Out[7] = M->TransformFVector(V[7]); Sink(Out);
    Out[8] = M->TransformFVector(V[8]); Sink(Out);
    Out[9] = M->TransformFVector(V[9]); Sink(Out);
    Out[10] = M->TransformFVector(V[10]); Sink(Out);
    Out[11] = M->TransformFVector(V[11]); Sink(Out);
    Out[12] = M->TransformFVector(V[12]); Sink(Out);
    Out[13] = M->TransformFVector(V[13]); Sink(Out);
    Out[14] = M->TransformFVector(V[14]); Sink(Out);
    Out[15] = M->TransformFVector(V[15]); Sink(Out);
}
