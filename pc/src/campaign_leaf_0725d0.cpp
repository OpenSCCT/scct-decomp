// campaign_leaf_0725d0.cpp -- one function at file offset 0x725d0, preferred VA 0x109725d0. It
// limits its first float argument to the range from the second up to the third: it returns the
// second when the first is less than it, the third when the first is at or above the third, and
// the first otherwise. It has no this pointer. The class, method and parameter names are invented;
// the offset and the bytes are the binary's.

class UnkType_109725d0
{
public:
    static float UnkClamp(float Value, float Low, float High);
};

// UnkType_109725d0::UnkClamp
float UnkType_109725d0::UnkClamp(float Value, float Low, float High)
{
    if ( Value < Low )
    {
        return Low;
    }
    if ( Value < High )
    {
        return Value;
    }
    return High;
}
