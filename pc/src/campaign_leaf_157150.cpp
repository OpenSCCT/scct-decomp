// campaign_leaf_157150.cpp -- returns the absolute value of its float argument with the x87 fabs
// instruction. File offset 0x157150, VA 0x10a57150. The class and method names are invented; the
// offsets are the binary's. fabs is the C runtime intrinsic, declared here by hand. The argument
// type is a guess.

class UnkType_10a57150
{
public:
    static float UnkMethod_10a57150(float value);
};

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

// UnkType_10a57150::UnkMethod_10a57150
float UnkType_10a57150::UnkMethod_10a57150(float value)
{
    return (float)fabs(value);
}
