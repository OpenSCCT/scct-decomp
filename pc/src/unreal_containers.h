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

extern "C" void *__cdecl _alloca(unsigned int Size);
extern "C" void *__cdecl memset(void *Dest, int Value, unsigned int Count);
#pragma intrinsic(memset)

// Stack storage that lasts until the calling function returns.
#define appAlloca(size) ((size == 0) ? 0 : _alloca((size + 7) & ~7))

// appMemzero
inline void appMemzero(void *Dest, INT Count)
{
    memset(Dest, 0, Count);
}

// The engine's allocator: 7 virtual functions; the units use Realloc and Free.
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
    void Realloc(INT ElementSize);
    INT Num() const { return ArrayNum; }
};

// A dynamic array of T.
template<class T> class TArray : public FArray {
public:
    ~TArray() { Remove(0, ArrayNum, sizeof(T)); }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    T &Last() { return ((T *)Data)[ArrayNum - 1]; }
    // Whether Item is in the array; Index receives the position of its first copy.
    UBOOL FindItem(const T &Item, INT &Index) const
    {
        for (Index = 0; Index < ArrayNum; Index++)
            if (((T *)Data)[Index] == Item)
                return 1;
        return 0;
    }
    // Appends Count zeroed elements; returns the index of the first.
    INT AddZeroed(INT Count = 1)
    {
        INT Index = ArrayNum;
        ArrayNum += Count;
        Realloc(sizeof(T));
        appMemzero((T *)Data + Index, Count * sizeof(T));
        return Index;
    }
};

INT appGetVarArgs(TCHAR *Dest, INT Count, const TCHAR *&Fmt);
#define GET_VARARGS(Msg, Len, Fmt) appGetVarArgs(Msg, Len, Fmt)

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
    FString operator+(const TCHAR *Str) const;
    FString operator+(const FString &Str) const { return operator+(*Str); }
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
    static FString Printf(const TCHAR *Fmt, ...);
};

INT appAtoi(const TCHAR *Str);
FLOAT appAtof(const TCHAR *Str);
INT appStrcmp(const TCHAR *A, const TCHAR *B);
INT appStricmp(const TCHAR *A, const TCHAR *B);
const TCHAR *appStrstr(const TCHAR *String, const TCHAR *Find);
TCHAR *appFromAnsi(const ANSICHAR *Str);
TCHAR *appFromUnicode(const TCHAR *Str);
void appClipboardCopy(const TCHAR *Str);

extern TCHAR GTrue[];           // "True"
extern TCHAR GFalse[];          // "False"

#endif // SCCT_VERSUS

#endif // UNREAL_CONTAINERS_H
