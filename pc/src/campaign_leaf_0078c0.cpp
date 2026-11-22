// campaign_leaf_0078c0.cpp -- one function at file offset 0x78c0, preferred VA 0x109078c0. It returns
// its first float argument when that is at least the second, and the second otherwise. It has no
// this pointer. The class, method and parameter names are invented; the offset and the bytes are the
// binary's.

class UnkType_109078c0
{
public:
    static float UnkMax(float First, float Second);
};

// UnkType_109078c0::UnkMax
float UnkType_109078c0::UnkMax(float First, float Second)
{
    if (First >= Second)
    {
        return First;
    }
    return Second;
}
