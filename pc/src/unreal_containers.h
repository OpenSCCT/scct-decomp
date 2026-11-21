// unreal_containers.h -- the engine's allocator interface, dynamic array and string
#ifndef UNREAL_CONTAINERS_H
#define UNREAL_CONTAINERS_H

#include "unreal_types.h"

#ifdef SCCT_VERSUS

// The untyped storage of every dynamic array.
class FArray {
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
};

// A dynamic array of T. Its destructor removes the elements, then frees the storage. The
// Versus executable keeps the destructors out of line.
template<class T> class TArray : public FArray {
public:
    ~TArray();
};

// A dynamic string: an array of TCHAR that includes the terminating zero.
class FString : public TArray<TCHAR> {
public:
    FString() {}
    FString(const FString &Other);
    ~FString();
    FString &operator=(const FString &Other);
};

#else // Campaign

#include "unreal_math.h"

// The engine's allocator: 7 virtual functions; the natives use Realloc and Free.
class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
};

extern FMalloc *GMalloc;

// The untyped storage of every dynamic array.
class FArray {
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);
    INT Num() const { return ArrayNum; }
};

// A dynamic array of T.
template<class T> class TArray : public FArray {
public:
    ~TArray() { Remove(0, ArrayNum, sizeof(T)); }
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

// A dynamic string: an array of TCHAR that includes the terminating zero.
class FString : public TArray<TCHAR> {
public:
    FString() {}
    FString(const FString &Other);
    FString(const TCHAR *In);
    FString(INT InCount, const TCHAR *InSrc);
    ~FString()
    {
        ArrayNum = 0;
        ArrayMax = 0;
        Data = GMalloc->Realloc(Data, 0, (const TCHAR *)L"FArray::_WORD");
    }
    FString &operator=(const TCHAR *Other);
    FString &operator=(const FString &Other);
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : (const TCHAR *)L""; }
    INT Len() const { return ArrayNum ? ArrayNum - 1 : 0; }
    FString Caps() const;
    FString Left(INT Count) const { return FString(Clamp(Count, 0, Len()), **this); }
    FString Right(INT Count) const { return FString(**this + Len() - Clamp(Count, 0, Len())); }
    FString Mid(INT Start, INT Count = 0x7fffffff) const
    {
        DWORD End = Start + Count;
        Start = Clamp((DWORD)Start, (DWORD)0, (DWORD)Len());
        End = Clamp((DWORD)End, (DWORD)Start, (DWORD)Len());
        return FString(End - Start, **this + Start);
    }
    INT InStr(const TCHAR *SubStr, UBOOL Right = 0) const;
};

INT appAtoi(const TCHAR *Str);
FLOAT appAtof(const TCHAR *Str);
INT appStrcmp(const TCHAR *A, const TCHAR *B);
INT appStricmp(const TCHAR *A, const TCHAR *B);
TCHAR *appFromAnsi(const ANSICHAR *Str);
TCHAR *appFromUnicode(const TCHAR *Str);
void appClipboardCopy(const TCHAR *Str);

extern TCHAR GTrue[];           // "True"
extern TCHAR GFalse[];          // "False"

#endif // SCCT_VERSUS

#endif // UNREAL_CONTAINERS_H
