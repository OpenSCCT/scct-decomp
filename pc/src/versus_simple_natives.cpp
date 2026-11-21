// UnrealScript natives from the Steam Versus payload that read scalar
// parameters, finish the parameter list and call one method of their class.
// The called method is named after the native; its own name is not recorded.
struct FFrame;
class UObject {
public:
    int Index;
};
typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

struct FFrame {
    void *OutputDeviceTable;
    void *Node;
    UObject *Object;
    unsigned char *Code;
    void *Locals;
    void Step(UObject *Context, void *const Result)
    {
        int B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_INT(Var) int Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT(Var) float Var = 0.0f; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class ASBasePawn : public UObject {
public:
    void execExecuteAction(FFrame &Stack, void *const Result);
    void ExecuteAction(int A0);
};

class ASGadget : public UObject {
public:
    void execGetUniqueIDByClass(FFrame &Stack, void *const Result);
    int GetUniqueIDByClass();
};

class ASWeaponDefense : public UObject {
public:
    void execGetAccuracy(FFrame &Stack, void *const Result);
    float GetAccuracy();
};

class UCanvas : public UObject {
public:
    void execRenderMotionTracking(FFrame &Stack, void *const Result);
    void RenderMotionTracking(int A0, int A1, int A2);
};

void UCanvas::execRenderMotionTracking(FFrame &Stack, void *const Result)
{
    P_GET_INT(A0);
    P_GET_INT(A1);
    P_GET_INT(A2);
    P_FINISH;
    RenderMotionTracking(A0, A1, A2);
}

void ASWeaponDefense::execGetAccuracy(FFrame &Stack, void *const Result)
{
    P_FINISH;
    *(float *)Result = GetAccuracy();
}

void ASGadget::execGetUniqueIDByClass(FFrame &Stack, void *const Result)
{
    P_FINISH;
    *(int *)Result = GetUniqueIDByClass();
}

void ASBasePawn::execExecuteAction(FFrame &Stack, void *const Result)
{
    P_GET_INT(A0);
    P_FINISH;
    ExecuteAction(A0);
}
