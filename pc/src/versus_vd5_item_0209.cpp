#include "versus_polygon_splitting.inl"

// Original link roots for the FPoly::Area and FPoly::Split receipts.
void Escape(void *);
FLOAT Driver_e7110(FPoly *P) { return P->Area(); }
void Driver_e74f0(FPoly *P, const FVector *N, const FVector *B, INT NoOverflow, INT *Out)
{
    Escape((void *)&GMath_Zero);
    *Out = P->Split(*N, *B, NoOverflow);
}
