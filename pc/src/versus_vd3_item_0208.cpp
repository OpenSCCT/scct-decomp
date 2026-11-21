// Item 0208: RVA 0x51780. Builds two four-vector arrays on the stack from
// eight vectors passed by reference and hands them to FUN_109511d0.
// Names are neutral: the callee's role is not yet recovered.

struct FVector
{
    float X, Y, Z;
};

void UnnamedHelper_511d0(FVector *A, FVector *B);

void UnnamedFunc_51780(const FVector &A0, const FVector &A1, const FVector &A2, const FVector &A3,
                       const FVector &B0, const FVector &B1, const FVector &B2, const FVector &B3)
{
    FVector A[4];
    FVector B[4];
    A[0] = A0;
    A[1] = A1;
    A[2] = A2;
    A[3] = A3;
    B[0] = B0;
    B[1] = B1;
    B[2] = B2;
    B[3] = B3;
    UnnamedHelper_511d0(A, B);
}

// Scaffolding for the link, not part of the unit.
void Driver_51780(FVector *V)
{
    UnnamedFunc_51780(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);
}
