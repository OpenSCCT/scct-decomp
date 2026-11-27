// Work item 0256 (RVA 0xf4c20-0xf4d94): FMipmap constructors and
// TArray<FMipmap>::~TArray (UE2 UnTex.h / UnTemplate.h). VC7.0 /O2 /Gy /GX /GL, /LTCG. The array destructor and Remove use /Ob1.
//
// FMipmap layout: FMipmapBase 0x00-0x0d (DataPtr, USize, VSize, UBits, VBits),
// TLazyArray<BYTE> DataArray at 0x10 (FLazyLoader vtable 0x10, SavedAr 0x14,
// SavedPos 0x18, TArray<BYTE> Data/ArrayNum/ArrayMax at 0x1c/0x20/0x24).
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short TCHAR;
typedef unsigned char BYTE;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

// Retail 0x10c10944.
extern const TCHAR FArray_ProtectedCstorTag[]; // L"Farray::protectedcstor"

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize) : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (!ArrayMax)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArray_ProtectedCstorTag);
    }
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize); // retail 0x119c0
};

template <class T> class TArray : public FArray
{
public:
    TArray() : FArray() {}
    TArray(INT InNum) : FArray(InNum, sizeof(T)) {}
    ~TArray();
    void Remove(INT Index, INT Count = 1);
};

class FArchive;

class FLazyLoader
{
public:
    FArchive *SavedAr;
    INT SavedPos;
    FLazyLoader() : SavedAr(0), SavedPos(0) {}
    virtual void Load() = 0;
    virtual void Unload() = 0;
};

template <class T> class TLazyArray : public FLazyLoader, public TArray<T>
{
public:
    TLazyArray(INT InNum = 0) : FLazyLoader(), TArray<T>(InNum) {}
    void Load();
    void Unload();
};

struct FMipmapBase
{
    BYTE *DataPtr;
    INT USize, VSize;
    BYTE UBits, VBits;
    FMipmapBase() {}
    FMipmapBase(BYTE InUBits, BYTE InVBits)
        : DataPtr(0), USize(1 << InUBits), VSize(1 << InVBits), UBits(InUBits), VBits(InVBits)
    {
    }
};

struct FMipmap : public FMipmapBase
{
    TLazyArray<BYTE> DataArray;
    FMipmap();
    FMipmap(BYTE InUBits, BYTE InVBits);
    FMipmap(BYTE InUBits, BYTE InVBits, INT InSize);
    ~FMipmap(); // retail 0xf49e0
};

// 0xf4d10
FMipmap::FMipmap()
{
}

// 0xf4c20
FMipmap::FMipmap(BYTE InUBits, BYTE InVBits)
    : FMipmapBase(InUBits, InVBits), DataArray(USize * VSize)
{
}

// 0xf4ca0
FMipmap::FMipmap(BYTE InUBits, BYTE InVBits, INT InSize)
    : FMipmapBase(InUBits, InVBits), DataArray(InSize)
{
}

// 0xf4da0 TArray<FMipmap>::Remove
template <class T> void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        ((T *)Data)[i].~T();
    FArray::Remove(Index, Count, sizeof(T));
}

// 0xf4d30
template <class T> TArray<T>::~TArray()
{
    Remove(0, ArrayNum);
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *P) { return P; }
void Driver_f4c20(FMipmap *M, BYTE U, BYTE V, INT S, TArray<FMipmap> *A)
{
    Escape(&GMalloc);
    new (M) FMipmap(U, V);
    new (M + 1) FMipmap(U, V, S);
    new (M + 2) FMipmap;
    A->~TArray();
}
