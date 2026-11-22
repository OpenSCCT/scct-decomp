// campaign_leaf_3caca0.cpp -- a free function at VA 0x10ccaca0 that widens its float argument to
// double, passes it to the function at VA 0x10f333d0 and returns the result converted to int.
// guess: rounds down (floor). The function names are invented; the addresses are the binary's.

double Unk_10f333d0(double Value);

// Unk_10ccaca0
int Unk_10ccaca0(float Value)
{
    return (int)Unk_10f333d0(Value);
}
