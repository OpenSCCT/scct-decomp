// versus_leaf_0402a0.cpp -- the function at file offset 0x402a0, VA 0x109402a0, 7 bytes. It loads
// its float argument onto the x87 stack, takes the sine and returns in st(0) (fld, fsin, ret).
// The class and method names are invented; the offset and the bytes are the binary's.

extern "C" double __cdecl sin(double);
#pragma intrinsic(sin)

class UnkType_109402a0
{
public:
    static float UnkFunc_109402a0(float Value);
};

// UnkType_109402a0::UnkFunc_109402a0
float UnkType_109402a0::UnkFunc_109402a0(float Value)
{
    return (float)sin(Value);
}
