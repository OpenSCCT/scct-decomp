// UInput key preprocessing and binding dispatch (UInput vtable slots 24, 25).
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

enum EInputKey { IK_None = 0 };
enum EInputAction { IST_None = 0, IST_Press = 1, IST_Hold = 2, IST_Release = 3 };

class FOutputDevice;
class UInput;

// Element of a per-key binding list; slot 1 executes the binding.
class FInputBindingHandler
{
public:
    virtual void Unknown0();
    virtual void Execute(UInput *Input);
};

template <class T> struct TArray
{
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

class UInput
{
public:
    BYTE Pad0[0xd68 - 4];
    INT CurrentAction;                          // 0xd68
    FLOAT CurrentDelta;                         // 0xd6c
    BYTE KeyDownTable[0xe74 - 0xd70];           // 0xd70
    TArray<FInputBindingHandler *> Bindings[1]; // 0xe74, one per key

    virtual UBOOL PreProcess(EInputKey iKey, EInputAction State, FLOAT Delta);
    virtual UBOOL Process(FOutputDevice &Ar, EInputKey iKey, EInputAction State, FLOAT Delta);
};

UBOOL UInput::PreProcess(EInputKey iKey, EInputAction State, FLOAT Delta)
{
    switch (State)
    {
    case IST_Release:
        if (KeyDownTable[iKey])
        {
            KeyDownTable[iKey] = 0;
            return 1;
        }
        return 0;
    case IST_Press:
        if (KeyDownTable[iKey])
            return 0;
        KeyDownTable[iKey] = 1;
        break;
    }
    return 1;
}

UBOOL UInput::Process(FOutputDevice &Ar, EInputKey iKey, EInputAction State, FLOAT Delta)
{
    TArray<FInputBindingHandler *> &List = Bindings[iKey];
    if (List.Num() > 0)
    {
        CurrentAction = State;
        CurrentDelta = Delta;
        for (INT i = 0; i < List.Num(); i++)
            List(i)->Execute(this);
        CurrentAction = IST_None;
        CurrentDelta = 0;
        return 1;
    }
    return 0;
}
