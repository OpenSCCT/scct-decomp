// Versus UObject vector/rotator script natives, RVA 0x46100-0x46450.
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef float FLOAT;
typedef unsigned short TCHAR;

class UObject;
struct FFrame;

struct FVector {
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator*(const FVector &V) const { return FVector(X * V.X, Y * V.Y, Z * V.Z); }
    FVector operator/(FLOAT Scale) const
    {
        FLOAT RScale = 1.0f / Scale;
        return FVector(X * RScale, Y * RScale, Z * RScale);
    }
};
inline FVector operator*(FLOAT Scale, const FVector &V) { return FVector(V.X * Scale, V.Y * Scale, V.Z * Scale); }

struct FRotator {
    INT Pitch, Yaw, Roll;
};

class FString {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    ~FString();
    FString &operator=(const FString &Other);
    static FString Printf(const TCHAR *Fmt, ...);
};

class FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
};

class UObject {
public:
    void execRotatorToString(FFrame &Stack, void *const Result);
    void execSubtract_PreVector(FFrame &Stack, void *const Result);
    void execMultiply_VectorFloat(FFrame &Stack, void *const Result);
    void execMultiply_FloatVector(FFrame &Stack, void *const Result);
    void execMultiply_VectorVector(FFrame &Stack, void *const Result);
    void execDivide_VectorFloat(FFrame &Stack, void *const Result);
};

typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
    void *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;
    void Step(UObject *Context, void *const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_FLOAT(Var) FLOAT Var = 0.0f; Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR(Var) FVector Var; Stack.Step(Stack.Object, &Var)
#define P_GET_ROTATOR(Var) FRotator Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

void UObject::execRotatorToString(FFrame &Stack, void *const Result)
{
    P_GET_ROTATOR(R);
    *(FString *)Result = FString::Printf((const TCHAR *)L"%i,%i,%i", R.Pitch & 65535, R.Yaw & 65535, R.Roll & 65535);
}

void UObject::execSubtract_PreVector(FFrame &Stack, void *const Result)
{
    P_GET_VECTOR(A);
    P_FINISH;
    *(FVector *)Result = -A;
}

void UObject::execMultiply_VectorFloat(FFrame &Stack, void *const Result)
{
    P_GET_VECTOR(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FVector *)Result = A * B;
}

void UObject::execMultiply_FloatVector(FFrame &Stack, void *const Result)
{
    P_GET_FLOAT(A);
    P_GET_VECTOR(B);
    P_FINISH;
    *(FVector *)Result = A * B;
}

void UObject::execMultiply_VectorVector(FFrame &Stack, void *const Result)
{
    P_GET_VECTOR(A);
    P_GET_VECTOR(B);
    P_FINISH;
    *(FVector *)Result = A * B;
}

void UObject::execDivide_VectorFloat(FFrame &Stack, void *const Result)
{
    P_GET_VECTOR(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FVector *)Result = A / B;
}
