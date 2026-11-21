// Item 0117 (LTCG retry): TArray<T*>::~TArray at RVA 0x1ef20.
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short TCHAR;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    ~FArray()
    {
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);
};

class UObject;

template <class T> class TArray : public FArray {
public:
    ~TArray() { Remove(0, ArrayNum); }
    void Remove(INT Index, INT Count = 1) { FArray::Remove(Index, Count, sizeof(T)); }
};

template class TArray<UObject *>;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_1ef20(TArray<UObject *> *A)
{
    Escape(&GMalloc);
    A->~TArray();
}
