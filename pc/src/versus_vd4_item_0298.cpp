// RVA 0x7ac20: saturating per-channel add of two FColors (LTCG: this in EDI,
// hidden return pointer in ESI, argument by value on the stack).
typedef unsigned char BYTE;
typedef int INT;

template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

struct FColor
{
    BYTE B, G, R, A;
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA) : B(InB), G(InG), R(InR), A(InA) {}
    FColor operator+(FColor C) const;
};

FColor FColor::operator+(FColor C) const
{
    return FColor(
        (BYTE)Clamp((INT)R + (INT)C.R, 0, 255),
        (BYTE)Clamp((INT)G + (INT)C.G, 0, 255),
        (BYTE)Clamp((INT)B + (INT)C.B, 0, 255),
        (BYTE)Clamp((INT)A + (INT)C.A, 0, 255));
}

// Scaffolding for the link, not part of the unit.
void Sink(FColor *);
void Driver_7ac20(const FColor *A, FColor B)
{
    FColor Result = *A + B;
    Sink(&Result);
}
