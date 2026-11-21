// Work item 0288: Versus RVA 0x100420, UCanvas::execWrapStringToArray
// (UnCanvas.cpp, Engine). Reads Text, the out array, the wrap width and an
// optional end-of-line string, then calls the wrapping helper at 0xfff80.
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
#define RESULT_DECL void *const Result

class UObject;
class UProperty;
class UFont;
class UCanvas;
struct FFrame;

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];
extern BYTE *GPropAddr;
extern UObject *GPropObject;
extern UProperty *GProperty;

// The default end-of-line text of the optional parameter (shared literal).
extern const TCHAR WrapStringToArray_DefaultEOL[];

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FString(const TCHAR *In);
    ~FString();
    TCHAR &operator()(INT i) { return Data[i]; }
    const TCHAR *operator*() const { return ArrayNum ? Data : L""; }
};

template <class T> class TArray {
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    TArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~TArray();
};

class UObject {
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20();
    virtual void NetDirty(UProperty *Property);                                 // +0x54
};

struct FFrame {
    void *VfTable;
    void *Node;                 // +0x04
    UObject *Object;            // +0x08
    BYTE *Code;                 // +0x0c

    __forceinline void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
    __forceinline void StepRef(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        GPropAddr = 0;
        (Context->*GNatives[B])(*this, Result);
    }
};

class UCanvas : public UObject {
public:
    void execWrapStringToArray(FFrame &Stack, RESULT_DECL);
};

// Retail helper at 0xfff80: stdcall, takes the canvas as its first argument.
void __stdcall WrapStringToArray(UCanvas *Canvas, const TCHAR *Text, TArray<FString> *OutArray,
                                 FLOAT dX, UFont *pFont, TCHAR EOL);

#define P_GET_STR(var) FString var; Stack.Step(Stack.Object, &var);
#define P_GET_STR_OPTX(var, def) FString var(def); Stack.Step(Stack.Object, &var);
#define P_GET_FLOAT(var) FLOAT var = 0.f; Stack.Step(Stack.Object, &var);
#define P_GET_TARRAY_REF(var, typ) TArray<typ> var##T; Stack.StepRef(Stack.Object, &var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    TArray<typ> *var = GPropAddr ? (TArray<typ> *)GPropAddr : &var##T;
#define P_FINISH Stack.Code++;

void UCanvas::execWrapStringToArray(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Text);
    P_GET_TARRAY_REF(OutArray, FString);
    P_GET_FLOAT(dX);
    P_GET_STR_OPTX(EOL, WrapStringToArray_DefaultEOL);
    P_FINISH;
    WrapStringToArray(this, *Text, OutArray, dX, 0, EOL(0));
}
