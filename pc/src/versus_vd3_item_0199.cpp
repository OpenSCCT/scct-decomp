// Work item 0199: two small float helpers (RVA 0x4f020, 0x4f040).
// Names are neutral; no symbol evidence ties them to a specific UE2 function.

extern float FloatZero_10c109f8; // retail constant 0.0f at 0x10c109f8

// 0x4f020: absolute value (appFabs-style), compared against a global zero.
float Abs_4f020(float A)
{
    return (A >= FloatZero_10c109f8) ? A : -A;
}

// 0x4f040: three-way select.
float Select3_4f040(float A, float B, float C)
{
    if (A < B)
        return B;
    if (A < C)
        return A;
    return C;
}
