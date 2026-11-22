// versus_leaf_0042d0.cpp -- the function at file offset 0x42d0, VA 0x109042d0, 7 bytes. It loads
// its float argument onto the x87 stack, takes the square root and returns in st(0).
// The class and method names are invented; the offset and the bytes are the binary's.

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

class UnkType_109042d0
{
public:
    static float UnkFunc_109042d0(float Value);
};

// UnkType_109042d0::UnkFunc_109042d0
float UnkType_109042d0::UnkFunc_109042d0(float Value)
{
    return (float)sqrt(Value);
}
