// campaign_leaf_74b1f0.cpp -- stdcall function at VA 0x1104b1f0: divides its first argument by its
// second as floats, scales the quotient by 65536 and truncates it to an integer (16.16 fixed
// point). All names are invented.

// Unk_1104b1f0
int __stdcall Unk_1104b1f0(int Numerator, int Denominator)
{
    return (int)((float)Numerator / Denominator * 65536.0f);
}
