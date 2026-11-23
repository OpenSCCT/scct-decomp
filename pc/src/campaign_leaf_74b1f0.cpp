// campaign_leaf_74b1f0.cpp -- one function at file offset 0x74b1f0, preferred VA 0x1104b1f0. A
// stdcall function that returns the quotient of its two integer arguments as a 16.16 fixed-point
// value, truncated toward zero. The function and parameter names are invented; the offset is the
// binary's.

// Unk_1104b1f0
int __stdcall Unk_1104b1f0(int Numerator, int Denominator)
{
    return (int)( (float)Numerator / Denominator * 65536.0f );
}
