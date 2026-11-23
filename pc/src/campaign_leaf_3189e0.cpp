// campaign_leaf_3189e0.cpp -- method at VA 0x10c189e0: with Phase advanced by 0.1 and wrapped below
// 1, and Margin 0.35 of Distance over 50 when Distance is below 50 (else 0), returns whether Phase
// is below 0.1 or above 0.95 less Margin when Wide is set, and otherwise whether it lies above 0.45
// less Margin and below 0.6. The object is not read. The class, method, parameter and local names
// are invented; the constants are the binary's.

class UnkType_10c189e0
{
public:
    int Unk_10c189e0(float Phase, int Wide, float Distance);
};

// UnkType_10c189e0::Unk_10c189e0
int UnkType_10c189e0::Unk_10c189e0(float Phase, int Wide, float Distance)
{
    float Margin;

    Phase += 0.1f;
    if ( Phase >= 1.0f )
    {
        Phase -= 1.0f;
    }
    Margin = 0.0f;
    if ( Distance < 50.0f )
    {
        Margin = Distance * 0.02f * 0.35;
    }
    if ( Wide )
    {
        if ( Phase < 0.1f || Phase > 0.95f - Margin )
        {
            return 1;
        }
    }
    else if ( Phase < 0.6f && Phase > 0.45f - Margin )
    {
        return 1;
    }
    return 0;
}
