/* RVA 0x4450: FArray::Insert(Index, Count, ElementSize) specialised by link-time
   code generation: this arrives in EAX and ElementSize in EBX (a custom register
   convention only /GL whole-program optimisation produces), Index and Count on
   the stack, ret 8. Written as the UE2 FArray::Insert body; the custom convention
   is reproduced by try_ltcg.py with the driver below. */
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag) = 0;
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag) = 0;
    virtual void Free(void* Original) = 0;
};
extern FMalloc* GMalloc;
extern "C" __declspec(dllimport) void* __cdecl memmove(void* Dest, const void* Src, unsigned int Count);

class FArray
{
public:
    void Insert(INT Index, INT Count, INT ElementSize);
protected:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
};

void FArray::Insert(INT Index, INT Count, INT ElementSize)
{
    INT OldNum = ArrayNum;
    if ((ArrayNum += Count) > ArrayMax)
    {
        ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
        if (!Data)
            Data = GMalloc->Malloc(ArrayMax * ElementSize, (const TCHAR*)L"FArray::Insert");
        else
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, (const TCHAR*)L"FArray");
    }
    memmove((unsigned char*)Data + (Index + Count) * ElementSize,
            (unsigned char*)Data + Index * ElementSize,
            (OldNum - Index) * ElementSize);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_4450(FArray *A, INT Index, INT Count, INT ElementSize)
{
    Escape(&GMalloc);
    A->Insert(Index, Count, ElementSize);
    A->Insert(Count, Index, ElementSize);
}
