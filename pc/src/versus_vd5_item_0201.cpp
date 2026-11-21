// Work item 0201: Versus RVA 0xe57d0-0xe5aed. Unoptimised (/Od) code.
// Under /Od, VC7 lays locals out by a hash of their names (declaration order breaks
// ties), so the local names below were chosen to reproduce the retail frame.
// The unit's own functions were built without optimisation; the array accessor
// they call (instantiated from a shared header) was optimised.
#pragma optimize("", off)
typedef unsigned long DWORD;
typedef int INT;

// Neutral name: a PCM sound buffer that halves its sample rate in place
// (a [1 2 1] low-pass filter with error carry, then decimation by two).
class UnnamedClass_e57d0 {
public:
    void *vtbl;
    DWORD *Rate;            // +0x04
    DWORD pad08[2];
    unsigned short *Bits;   // +0x10
    DWORD pad14[4];
    void *Data;             // +0x24
    DWORD pad28;
    DWORD DataSize;         // +0x2c
    DWORD pad30[3];
    DWORD Samples;          // +0x3c
    void HalveRate();
};

void UnnamedClass_e57d0::HalveRate()
{
    if (*Bits == 16) {
        INT Sum;
        DWORD k;
        INT Carry;
        INT Next;
        DWORD Pairs;
        DWORD NumWords;
        INT Value;
        INT Out;
        INT Last;
        short *SrcPtr;
        INT Mid;
        NumWords = DataSize >> 1;
        Carry = 0;
        Pairs = NumWords >> 1;
        Last = *(short *)Data;
        SrcPtr = (short *)Data;
        for (k = 0; k < Pairs; k++) {
            Mid = SrcPtr[k * 2];
            Next = SrcPtr[k * 2 + 1];
            Sum = Last + 0x20000 + Mid + Mid + Next;
            Last = Next;
            Value = Carry + Sum;
            Out = (Value + 2) & 0x3fffc;
            if (Out > 0x3fffc)
                Out = 0x3fffc;
            SrcPtr[k] = (short)((Out >> 2) - 0x8000);
            Carry = Value - Out;
        }
        Samples = Pairs * 2;
        *Rate = *Rate >> 1;
    } else if (*Bits == 8) {
        INT Sum;
        DWORD k;
        INT Carry;
        INT Next;
        INT Value;
        INT Out;
        INT Last;
        DWORD NumOut;
        unsigned char *SrcPtr;
        INT Mid;
        Carry = 0;
        NumOut = DataSize >> 1;
        SrcPtr = (unsigned char *)Data;
        Last = *SrcPtr;
        for (k = 0; k < NumOut; k++) {
            Mid = SrcPtr[k * 2];
            Next = SrcPtr[k * 2 + 1];
            Sum = Last + Mid + Mid + Next;
            Last = Next;
            Value = Carry + Sum;
            Out = (Value + 2) & 0x3fc;
            if (Out > 0x3fc)
                Out = 0x3fc;
            SrcPtr[k] = (unsigned char)(Out >> 2);
            Carry = Value - Out;
        }
        Samples = NumOut;
        *Rate = *Rate >> 1;
    }
}

// ---------------------------------------------------------------------------
// RVA 0xe59d0: UI3DL2Listener::PostEditChange (UI3DL2Listener vtable slot 16).
// The parent call lands on UObject's empty virtual at 0x68f20.
class UObject {
public:
    virtual ~UObject();
    virtual void PostEditChange();
};

class UI3DL2Listener : public UObject {
public:
    char Pad04[0x94];
    DWORD Updated;          // +0x98
    void PostEditChange();
};

void UI3DL2Listener::PostEditChange()
{
    UObject::PostEditChange();
    Updated = 1;
}

// ---------------------------------------------------------------------------
// RVA 0xe59f0-0xe5aed: an object iterator over a TArray of object pointers
// (the shape of Unreal's TObjectIterator). Compiled /Od under LTCG, so the
// array accessor at 0xac2d0 takes the array in EAX and the index in EDX.
class UClass;
class UnnamedClass_4bc0
{
public:
    char Pad00[0x24];
    UnnamedClass_4bc0* Children; // +0x24
    UnnamedClass_4bc0* Next;     // +0x28
    int Contains(UnnamedClass_4bc0* Other);
};

class FObjectArray {
public:
    UnnamedClass_4bc0 **Data;
    INT ArrayNum;
    INT ArrayMax;
    UnnamedClass_4bc0 *&operator()(INT i);
    INT Num() { return ArrayNum; }
};

// Not part of this unit's matches (RVA 0xac2d0); defined so the LTCG link gives it
// the retail register convention.
#pragma optimize("", on)
UnnamedClass_4bc0 *&FObjectArray::operator()(INT i)
{
    return Data[i];
}
#pragma optimize("", off)

// RVA 0xe59f0: neutral name; a thin array wrapper forwarding to the accessor.
class UnnamedArray_e59f0 : public FObjectArray {
public:
    UnnamedClass_4bc0 *&operator()(INT i);
};

UnnamedClass_4bc0 *&UnnamedArray_e59f0::operator()(INT i)
{
    return FObjectArray::operator()(i);
}

FObjectArray *GetObjectArray_4ba0();          // RVA 0x4ba0
UnnamedClass_4bc0 *GetFilterClass_4c60();     // RVA 0x4c60

class FIndexIterator_c700 {
public:
    FObjectArray *Array;    // +0x00
    INT Index;              // +0x04
    void Init(FObjectArray *InArray, INT InIndex); // RVA 0xc700
};

class UnnamedIterator_e5a10 : public FIndexIterator_c700 {
public:
    UnnamedIterator_e5a10();
    UnnamedIterator_e5a10 &operator++();
    UnnamedClass_4bc0 *operator*();
};

// Not part of this unit's matches (RVA 0xc700); defined (optimised) so the link
// gives it the retail register convention.
#pragma optimize("", on)
void FIndexIterator_c700::Init(FObjectArray *InArray, INT InIndex) { Array = InArray; Index = InIndex; }
#pragma optimize("", off)

// RVA 0xe5a10
UnnamedIterator_e5a10::UnnamedIterator_e5a10()
{
    // Skip, Num, Obj and Cls are dead locals (the same set as operator++);
    // the retail frame still reserves their slots.
    DWORD Skip;
    INT Num;
    UnnamedClass_4bc0 *Obj;
    UnnamedClass_4bc0 *Cls;
    FObjectArray *Source = GetObjectArray_4ba0();
    Init(Source, -1);
    ++*this;
}

// RVA 0xe5a40: advance to the next slot holding an object that passes the filter.
// Obj and Cls are dead locals; the retail frame still reserves their slots.
UnnamedIterator_e5a10 &UnnamedIterator_e5a10::operator++()
{
    DWORD Skip;
    INT Num;
    UnnamedClass_4bc0 *Obj;
    UnnamedClass_4bc0 *Cls;
    do {
        Index++;
        Num = Array->ArrayNum;
        Skip = Index < Num && (!(*Array)(Index) || !(*Array)(Index)->Contains(GetFilterClass_4c60()));
    } while (Skip);
    return *this;
}

// RVA 0xe5ad0
UnnamedClass_4bc0 *UnnamedIterator_e5a10::operator*()
{
    return (*Array)(Index);
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_e59f0(UnnamedArray_e59f0 *A, INT i) { Escape(&(*A)(i)); }
void Driver_e5a10(UnnamedIterator_e5a10 *It) { UnnamedIterator_e5a10 X; Escape(&X); Escape(*X); ++*It; Escape(**It); }
