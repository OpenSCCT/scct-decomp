// Work item 0184: TArray<BYTE> copy constructor (0xe1a90), LTCG build:
// `this` on the stack (ret 4), source array in EDI.
typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;

void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count);

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

extern const TCHAR FArray_ProtectedCstor[]; // L"Farray::protectedcstor" (writable .data)

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
protected:
    FArray(INT InNum, INT ElementSize) : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (ArrayMax == 0)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArray_ProtectedCstor);
    }
public:
    ~FArray();
};

template<class T> class TArray : public FArray {
public:
    TArray(const TArray &Other) : FArray(Other.ArrayNum, sizeof(T))
    {
        appMemcpy(Data, Other.Data, ArrayNum * sizeof(T));
    }
};

template class TArray<BYTE>;

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
void Driver_e1a90(TArray<BYTE> *Dest, const TArray<BYTE> &Src)
{
    Escape(&GMalloc);
    new (Dest) TArray<BYTE>(Src);
}
