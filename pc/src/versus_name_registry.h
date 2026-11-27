#ifndef VERSUS_NAME_REGISTRY_H
#define VERSUS_NAME_REGISTRY_H

#include "versus_name.h"

#define RF_Native 0x04000000

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;                 // 0x10c73bf0

extern "C" __declspec(dllimport) INT __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) INT __cdecl wcscmp(const TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    INT Add(INT Count, INT ElementSize);                         // 0x109044e0
    void Remove(INT Index, INT Count, INT ElementSize);          // 0x109119c0
};

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Shrink()
    {
        if (ArrayMax != ArrayNum) {
            ArrayMax = ArrayNum;
            Data = GMalloc->Realloc(Data, ArrayMax * sizeof(T), L"FArray");
        }
    }
    // Inline growth used by FName::Hardcode (inlined in retail).
    INT AddInline(INT Count)
    {
        INT Index = ArrayNum;
        if ((ArrayNum += Count) > ArrayMax) {
            ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
            if (Data == 0)
                Data = GMalloc->Malloc(ArrayMax * sizeof(T), L"FArray::Add");
            else
                Data = GMalloc->Realloc(Data, ArrayMax * sizeof(T), L"FArray");
        }
        return Index;
    }
};

#include "versus_name_table.h"
extern TArray<INT> FName_Available;              // 0x10cc9e68, FName::Available
extern FNameEntry *FName_NameHash[4096];         // 0x10c7d4d8, FName::NameHash

FNameEntry *AllocateNameEntry(const TCHAR *Name, DWORD Index, DWORD Flags, FNameEntry *HashNext);

#endif
