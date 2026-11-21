/* Work item 0059: TArray destructors and Min<DOUBLE> (Unreal Engine 2 UnTemplate.h shapes).
   FArray::Remove is the published remove_array (0x119c0); the two-field array whose
   Remove is remove_simple_array (0x11aa0) has no recovered name: FSimpleArray is neutral. */
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef double DOUBLE;
typedef unsigned short TCHAR;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FArray
{
public:
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayMax = 0;
        ArrayNum = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);

    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    ~TArray()
    {
        Remove(0, ArrayNum);
    }
    void Remove(INT Index, INT Count = 1)
    {
        FArray::Remove(Index, Count, sizeof(T));
    }
};

/* Versus array without a capacity field (unnamed in the retail build). */
class FSimpleArray
{
public:
    ~FSimpleArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);

    void *Data;
    INT ArrayNum;
};

template<class T> class TSimpleArray : public FSimpleArray
{
public:
    ~TSimpleArray()
    {
        Remove(0, ArrayNum);
    }
    void Remove(INT Index, INT Count = 1)
    {
        FSimpleArray::Remove(Index, Count, sizeof(T));
    }
};

struct FEightBytes { INT A, B; }; /* 8-byte element; real type unknown */

template TArray<BYTE>::~TArray();
template TSimpleArray<BYTE>::~TSimpleArray();
template TArray<FEightBytes>::~TArray();

template<class T> inline T Min(const T A, const T B)
{
    return (A <= B) ? A : B;
}
template DOUBLE Min(const DOUBLE, const DOUBLE);
