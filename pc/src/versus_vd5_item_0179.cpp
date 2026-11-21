// Work item 0179: RVA 0xdfee0-0xdffe2. LTCG (VC7.0 /GL) unit.
// Class names are neutral: no strings or vtable labels name these classes.
// The base (vtable 0x10c0e918) is 0x40 bytes; its copy constructor (0xe0020)
// and TArray<BYTE>'s copy constructor (0xe1a90) are defined here only so the
// linker gives them their retail register conventions; they belong to other items.
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef unsigned long DWORD;
typedef int INT;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;
extern const TCHAR FArray_Tag[];   // malloc tag at 0x10c10944
void appMemcpy(void *Dest, const void *Src, INT Count);

class FArray
{
public:
    FArray(INT InNum, INT ElementSize)
        : Data(0), ArrayNum(InNum), ArrayMax(InNum)
    {
        if (ArrayMax)
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArray_Tag);
        else
            Data = 0;
    }
    ~FArray()
    {
        if (Data) { GMalloc->Free(Data); Data = 0; }
        ArrayMax = 0;
        ArrayNum = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);

    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T> class TArray : public FArray
{
public:
    TArray(const TArray &Other) : FArray(Other.ArrayNum, sizeof(T))
    {
        appMemcpy(Data, Other.Data, ArrayNum * sizeof(T));
    }
    ~TArray();   // 0xf250, published separately
    void Remove(INT Index, INT Count = 1) { FArray::Remove(Index, Count, sizeof(T)); }
};

class UnnamedBase_e0020
{
public:
    DWORD Pad[15];
    UnnamedBase_e0020(const UnnamedBase_e0020 &Other);
    ~UnnamedBase_e0020() {}
    virtual void Unnamed0();
};

class UnnamedClass_dff30 : public UnnamedBase_e0020
{
public:
    TArray<BYTE> Bytes;   // 0x40
    _WORD W4C;            // 0x4c
    _WORD W4E;            // 0x4e
    UnnamedClass_dff30(const UnnamedClass_dff30 &Other);
    ~UnnamedClass_dff30();
    virtual void Unnamed0();
};

class __declspec(novtable) UnnamedClass_dffa0 : public UnnamedBase_e0020
{
public:
    TArray<BYTE> Bytes;   // 0x40
    ~UnnamedClass_dffa0();
    virtual void Unnamed0() = 0;
};

class UnnamedClass_dfee0 : public UnnamedClass_dff30
{
public:
    DWORD D50, D54, D58, D5C, D60, D64;
    BYTE B68, B69, B6A;
    UnnamedClass_dfee0(const UnnamedClass_dfee0 &Other);
    virtual void Unnamed0();
};

// 0xe0020 (other item; here for its calling convention)
UnnamedBase_e0020::UnnamedBase_e0020(const UnnamedBase_e0020 &Other)
{
    Pad[0] = Other.Pad[0];
    Pad[1] = Other.Pad[1];
    Pad[2] = Other.Pad[2];
    Pad[3] = Other.Pad[3];
    Pad[4] = Other.Pad[4];
    Pad[5] = Other.Pad[5];
    Pad[6] = Other.Pad[6];
    Pad[7] = Other.Pad[7];
    Pad[8] = Other.Pad[8];
    Pad[9] = Other.Pad[9];
    Pad[10] = Other.Pad[10];
    Pad[11] = Other.Pad[11];
    Pad[12] = Other.Pad[12];
    Pad[13] = Other.Pad[13];
    Pad[14] = Other.Pad[14];
}

// 0xdff30
#pragma inline_depth(0)
UnnamedClass_dff30::UnnamedClass_dff30(const UnnamedClass_dff30 &Other)
    : UnnamedBase_e0020(Other), Bytes(Other.Bytes), W4C(Other.W4C), W4E(Other.W4E)
{
}

#pragma inline_depth()

// 0xdffa0. Retail stores no vtable of its own before destroying the array,
// only the base vtable after it: the class is declared novtable.
UnnamedClass_dffa0::~UnnamedClass_dffa0()
{
}

// 0xdfee0
UnnamedClass_dfee0::UnnamedClass_dfee0(const UnnamedClass_dfee0 &Other)
    : UnnamedClass_dff30(Other),
      D50(Other.D50), D54(Other.D54), D58(Other.D58), D5C(Other.D5C), D60(Other.D60), D64(Other.D64),
      B68(Other.B68), B69(Other.B69), B6A(Other.B6A)
{
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *P) { return P; }
void Driver_dfee0(UnnamedClass_dfee0 *Dst, const UnnamedClass_dfee0 *Src)
{
    Escape(&GMalloc);
    new ((void *)Dst) UnnamedClass_dfee0(*Src);
}
void Driver_dffa0(UnnamedClass_dffa0 *Obj)
{
    Obj->~UnnamedClass_dffa0();
}
void Driver_e0020(UnnamedBase_e0020 *Dst, const UnnamedBase_e0020 *Src)
{
    new ((void *)&Dst[0]) UnnamedBase_e0020(Src[0]);
    new ((void *)&Dst[1]) UnnamedBase_e0020(Src[1]);
    new ((void *)&Dst[2]) UnnamedBase_e0020(Src[2]);
    new ((void *)&Dst[3]) UnnamedBase_e0020(Src[3]);
}
