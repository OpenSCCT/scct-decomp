// campaign_leaf_02f1f0.cpp -- one function at file offset 0x2f1f0, preferred VA 0x1092f1f0. It
// returns its first float argument when that is at most the second, and the second otherwise. It
// has no this pointer. The class, method and parameter names are invented; the offset and the bytes
// are the binary's.

class UnkType_1092f1f0
{
public:
    static float UnkMin(float First, float Second);
};

// UnkType_1092f1f0::UnkMin
float UnkType_1092f1f0::UnkMin(float First, float Second)
{
    if ( First <= Second )
    {
        return First;
    }
    return Second;
}
