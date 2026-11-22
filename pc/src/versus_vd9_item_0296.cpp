// UCanvas::execDrawTextJustified (Versus RVA 0x1027b0).
typedef int INT;
typedef unsigned char BYTE;
typedef float FLOAT;
typedef unsigned short TCHAR;

struct FFrame;
class UObject {
public:
    INT Dummy;
};
typedef void (UObject::*Native)(FFrame &Stack, void *Result);
extern Native GNatives[];

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FString();
    const TCHAR *operator*() const { return ArrayNum ? Data : L""; }
};

struct FFrame {
    void *VfTable;   // FOutputDevice
    void *Node;
    UObject *Object;
    BYTE *Code;
    __forceinline void Step(UObject *Context, void *Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

class UCanvas : public UObject {
public:
    void DrawTextJustified(BYTE Justification, FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, const TCHAR *Fmt, ...);
    void execDrawTextJustified(FFrame &Stack, void *Result);
};

void UCanvas::execDrawTextJustified(FFrame &Stack, void *Result)
{
    FString InText;  Stack.Step(Stack.Object, &InText);
    BYTE Justification = 0; Stack.Step(Stack.Object, &Justification);
    FLOAT X1 = 0; Stack.Step(Stack.Object, &X1);
    FLOAT Y1 = 0; Stack.Step(Stack.Object, &Y1);
    FLOAT X2 = 0; Stack.Step(Stack.Object, &X2);
    FLOAT Y2 = 0; Stack.Step(Stack.Object, &Y2);
    Stack.Code++;
    DrawTextJustified(Justification, X1, Y1, X2, Y2, *InText);
}

// UCanvas::DrawTextJustified lives at RVA 0x102e40: a printf-style member
// (_vsnwprintf into a 4096-character buffer). LTCG passes its this in ESI.
// Stand-in body so the link sees a definition (not part of the match).
typedef char *va_list;
extern "C" int _vsnwprintf(TCHAR *Buffer, unsigned Count, const TCHAR *Format, va_list Args);
void DrawTextJustifiedBody(UCanvas *, BYTE, FLOAT, FLOAT, FLOAT, FLOAT, const TCHAR *);
void UCanvas::DrawTextJustified(BYTE Justification, FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, const TCHAR *Fmt, ...)
{
    TCHAR Text[4096];
    va_list Args = (va_list)&Fmt + sizeof(Fmt);
    _vsnwprintf(Text, 4096, Fmt, Args);
    Dummy = 0;
    DrawTextJustifiedBody(this, Justification, X1, Y1, X2, Y2, Text);
    Dummy += Text[0];
}

// Scaffolding for the link, not part of the unit: the native table takes the address.
void Escape(void *);
void Driver_1027b0()
{
    void (UCanvas::*P)(FFrame &, void *) = &UCanvas::execDrawTextJustified;
    Escape(&P);
}
