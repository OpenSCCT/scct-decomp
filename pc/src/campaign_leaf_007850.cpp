// campaign_leaf_007850.cpp -- one function at file offset 0x7850, preferred VA 0x10907850. It
// limits its first integer argument to the range from the second up to the third, returning the
// second when the value is below it and the third when the value is at or above it. It has no this
// pointer. The class, method and parameter names are invented; the offset and the bytes are the
// binary's.

class UnkType_10907850
{
public:
    static int UnkClamp(int Value, int Low, int High);
};

// UnkType_10907850::UnkClamp
int UnkType_10907850::UnkClamp(int Value, int Low, int High)
{
    if (Value < Low)
    {
        return Low;
    }
    if (Value >= High)
    {
        return High;
    }
    return Value;
}
