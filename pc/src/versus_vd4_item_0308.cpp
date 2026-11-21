// Work item 0308: RVA 0x81b40 and 0x81b80.
// Both functions come from a /GL object linked with /LTCG: the output pointer
// arrives in EAX (and `this` in ECX for 0x81b80).
typedef float FLOAT;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    // An explicit copy constructor is needed: it makes (Min + Max) a memory
    // temporary, as retail does.
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
};

struct FBox
{
    FVector Min;
    FVector Max;
    FVector GetCenter() const;
};

// Neutral names: two global vector pointers (0x10ccacc4 and 0x10ccacc0) whose
// real names are unknown.
extern FVector *GUnnamedVectorA_81b40; // 0x10ccacc4
extern FVector *GUnnamedVectorB_81b40; // 0x10ccacc0

#pragma auto_inline(off)

// RVA 0x81b40: copy the two global vectors into Out[0] and Out[1].
// Neutral name; Out arrives in EAX.
void GetUnnamedVectors_81b40(FVector *Out)
{
    Out[0] = *GUnnamedVectorA_81b40;
    Out[1] = *GUnnamedVectorB_81b40;
}

// RVA 0x81b80.
FVector FBox::GetCenter() const
{
    return FVector((Min + Max) * 0.5f);
}

#pragma auto_inline(on)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_81b40(FVector *Out, FVector *Out2)
{
    Escape(&GUnnamedVectorA_81b40);
    Escape(&GUnnamedVectorB_81b40);
    GetUnnamedVectors_81b40(Out);
    Escape(Out);
    GetUnnamedVectors_81b40(Out2);
    Escape(Out2);
}
void Driver_81b80(const FBox *Box, FVector *Out, FVector *Out2)
{
    *Out = Box->GetCenter();
    Escape(Out);
    *Out2 = Box[1].GetCenter();
    Escape(Out2);
}
