// campaign_leaf_2e9d70.cpp -- free function at VA 0x10be9d70: returns Value times 5 up to 40,
// times 10 up to 80 and times 20 above that. The function and parameter names are invented; the
// constants are the binary's.

// Unk_10be9d70
float Unk_10be9d70(float Value)
{
    if ( Value <= 40.0f )
    {
        return Value * 5.0f;
    }
    if ( Value <= 80.0f )
    {
        return Value * 10.0f;
    }
    return Value * 20.0f;
}
