// RVA 0x99310: scale an FColor by a float brightness (LTCG: this in EDI).
typedef unsigned char BYTE;
typedef int INT;
typedef float FLOAT;

template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

struct FColor {
    BYTE B, G, R, A;
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA) : B(InB), G(InG), R(InR), A(InA) {}
    FColor Brighten(FLOAT Scale) const;
};

FColor FColor::Brighten(FLOAT Scale) const
{
    INT S = (INT)(Scale * 255.f);
    return FColor(
        (BYTE)Clamp<INT>(R * S / 255, 0, 255),
        (BYTE)Clamp<INT>(G * S / 255, 0, 255),
        (BYTE)Clamp<INT>(B * S / 255, 0, 255),
        (BYTE)Clamp<INT>(A * S / 255, 0, 255));
}

// Scaffolding for the link, not part of the unit.
void Driver_99310(FColor *Out, const FColor *C, FLOAT F) { *Out = C->Brighten(F); }
