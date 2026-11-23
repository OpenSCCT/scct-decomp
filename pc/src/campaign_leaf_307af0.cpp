// campaign_leaf_307af0.cpp -- free function at VA 0x10c07af0: clamps Value to 5..195 and returns
// it times 0.01 up to 100, and 100 over 200 less it above 100. The function and parameter names
// are invented; the constants are the binary's.

// Unk_10c07af0
float Unk_10c07af0(float Value)
{
    float Clamped = Value < 5.0f ? 5.0f : Value < 195.0f ? Value : 195.0f;

    if ( Clamped > 100.0f )
    {
        return 100.0f / ( 200.0f - Clamped );
    }
    return Clamped * 0.01f;
}
