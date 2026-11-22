// campaign_leaf_3c1c20.cpp -- one function at file offset 0x3c1c20, preferred VA 0x10cc1c20. It
// clamps a double: Low when Value is below Low, High when it is not below High, otherwise Value.
// It has no this pointer. The function and parameter names are invented; the bytes are the
// binary's.

// Unk_10cc1c20
double Unk_10cc1c20(double Value, double Low, double High)
{
    return Value < Low ? Low : Value < High ? Value : High;
}
