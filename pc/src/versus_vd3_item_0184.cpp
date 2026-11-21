// UObject::execMirrorVectorByNormal (0x47030) and UObject::execIsNullVector
// (0x47130). The x86 native handler ABI passes the receiver in ecx, followed
// by the script frame and result pointer on the stack.
typedef float FLOAT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

struct Frame;
struct Object;
typedef void (__fastcall *Native)(Object *, unsigned int, Frame *, void *);
struct Frame {
    void *frame_prefix[2];
    Object *object;
    unsigned char *code;
};
#define HANDLER(name, result_type) \
    extern "C" void __fastcall name(Object *self, void *unused_edx, Frame *frame, result_type *result)
#define DISPATCH ((Native const *)0x10c819d8u)

static __forceinline void step(Frame *frame, void *result)
{
    Object *receiver = frame->object;
    unsigned int opcode = *frame->code++;
    DISPATCH[opcode](receiver, opcode, frame, result);
}

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector SafeNormal() const; // 0x50d30; LTCG passes the result in ecx, this in edx
};

HANDLER(execMirrorVectorByNormal, FVector)
{
    FVector V;
    FVector N;
    step(frame, &V);
    step(frame, &N);
    ++frame->code;
    N = N.SafeNormal();
    *result = V - N * 2.f * (N | V);
}

HANDLER(execIsNullVector, UBOOL)
{
    FVector V;
    step(frame, &V);
    ++frame->code;
    *result = V.X == 0.0 && V.Y == 0.0 && V.Z == 0.0;
}

// Scaffolding for the link, not part of the unit: retail reaches the handler
// through the native table, so take its address.
extern "C" void *Driver_47030() { return (void *)&execMirrorVectorByNormal; }

// FVector::SafeNormal (retail 0x50d30), reproduced here only so the link
// sees its definition and gives it the same register convention as retail.
extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
__declspec(noinline) FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return FVector(0.f, 0.f, 0.f);
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}
