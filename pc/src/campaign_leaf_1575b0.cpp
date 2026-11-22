// campaign_leaf_1575b0.cpp -- one function at file offset 0x1575b0, preferred VA 0x10a575b0. It
// returns 1.0 when the absolute difference of its first two arguments is less than its third, and
// 0.0 otherwise. It has no this pointer. The function and parameter names are invented; the offset
// and the bytes are the binary's.

extern "C" double __cdecl fabs(double Value);

// Unk_10a575b0
float Unk_10a575b0(float First, float Second, float Tolerance)
{
    return (float)( (float)fabs(First - Second) < Tolerance );
}
