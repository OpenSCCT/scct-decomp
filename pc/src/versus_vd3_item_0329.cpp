// Work item 0329: Versus RVA 0x90c90-0x90e54 (VC7.0 /GL, linked /LTCG).
// Owner class is an actor-like object; names are neutral (UnnamedOwner_90c90)
// because no strings or vtable labels identify it.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef unsigned char BYTE;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
inline void operator delete(void *Ptr, const TCHAR *Tag) { GMalloc->Free(Ptr); }

extern const TCHAR NewTag_90c90[];   // retail 0x10c109d8

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray();
    void Remove(INT Index, INT Count, INT ElementSize);   // 0x109119c0
    INT Num() const { return ArrayNum; }
};

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1) { FArray::Remove(Index, Count, sizeof(T)); }
    __declspec(noinline) INT RemoveItem(const T &Item)   // 0x10a0bd60
    {
        INT OriginalNum = ArrayNum;
        for (INT Index = 0; Index < ArrayNum; Index++)
            if ((*this)(Index) == Item)
                Remove(Index--);
        return OriginalNum - ArrayNum;
    }
};

class UnnamedOwner_90c90;

// Neutral names: an element of the 4-byte array at Model+0xbc.
struct UnnamedCellRef { unsigned short Index; unsigned short Pad; };
struct UnnamedModel_13c { char Pad[0xbc]; UnnamedCellRef *Cells; };
struct UnnamedLevel_1a4
{
    char Pad0[0x13c];
    UnnamedModel_13c *Model;                        // +0x13c
    char Pad140[0x4a8c - 0x140];
    TArray<UnnamedOwner_90c90 *> *CellLists;        // +0x4a8c (data of a TArray<TArray<>>)
};

class UnnamedOwner_90c90;

// 0xf8-byte helper built lazily at +0x12c (ctor at 0x10a14ad0).
struct FVector { FLOAT X, Y, Z; };
extern FVector *GCacheVecA;             // retail 0x10ccacc4
extern FVector *GCacheVecB;             // retail 0x10ccacc0

class UnnamedCache_12c
{
public:
    UnnamedOwner_90c90 *Owner;          // +0x00
    INT Revision;                       // +0x04
    INT Pad08;
    INT Field0c;                        // +0x0c
    char Pad10[0x90 - 0x10];
    FVector A0, A1;                     // +0x90
    char PadA8[0xc0 - 0xa8];
    INT Fieldc0, Fieldc4;               // +0xc0
    INT Padc8;
    FVector B0, B1;                     // +0xcc
    INT Pade4;
    INT Fielde8, Fieldec, Fieldf0, Fieldf4;  // +0xe8
    __declspec(noinline) UnnamedCache_12c(UnnamedOwner_90c90 *InOwner);
};

class UnnamedOwner_90c90
{
public:
    char Pad0[0x12c];
    UnnamedCache_12c *Cache;            // +0x12c
    class UnnamedRender_130 *Cache130;  // +0x130
    INT Revision;                       // +0x134
    char Pad138[0x1a4 - 0x138];
    UnnamedLevel_1a4 *Level;            // +0x1a4
    char Pad1a8[0x1c4 - 0x1a8];
    TArray<INT> Cells;                  // +0x1c4
    char Pad1d0[0x250 - 0x1d0];
    INT InCells;                        // +0x250
    char Pad254[0x2d2 - 0x254];
    BYTE Kind2d2;                       // +0x2d2 (0x16 selects the large variant)
    BYTE Pad2d3[0x2e8 - 0x2d3];
    DWORD Flags2e8;                     // +0x2e8

    __declspec(noinline) UnnamedCache_12c *GetCache();
    class UnnamedRender_130 *GetRender();
    void Invalidate();
    __declspec(noinline) void RebuildCache();   // 0x10990e60
};

// 0x40-byte object at +0x130; Update() is 0x10a1de70.
class UnnamedRender_130
{
public:
    UnnamedOwner_90c90 *Owner;          // +0x00
    INT Revision;                       // +0x04
    char Pad08[0x34 - 0x08];
    DWORD Flags;                        // +0x34
    INT Pad38;
    FLOAT Scale;                        // +0x3c

    UnnamedRender_130(UnnamedOwner_90c90 *InOwner)
    {
        Owner = InOwner;
        Flags &= 0xfffffe03;
        Scale = 1.f;
        Revision = -1;
        Update();
    }
    __declspec(noinline) void Update();
};


extern const TCHAR NewTag_92980[];   // retail 0x10c10944

// 0x2a4-byte variant (ctor 0x10992980).
class UnnamedRenderLarge_130 : public UnnamedRender_130
{
public:
    char Pad40[0x280 - 0x40];
    FArray A;                           // +0x280
    FArray B;                           // +0x28c
    void *CData;                        // +0x298
    INT CNum, CMax;                     // +0x29c
    __declspec(noinline) UnnamedRenderLarge_130(UnnamedOwner_90c90 *InOwner);
};

UnnamedRender_130 *UnnamedOwner_90c90::GetRender()
{
    if (!Cache130) {
        if (Kind2d2 == 0x16)
            Cache130 = new(NewTag_90c90) UnnamedRenderLarge_130(this);
        else
            Cache130 = new(NewTag_90c90) UnnamedRender_130(this);
    }
    if (Cache130->Revision != Revision)
        Cache130->Update();
    return Cache130;
}

void UnnamedOwner_90c90::Invalidate()
{
    Revision++;
    if (InCells) {
        for (INT i = 0; i < Cells.Num(); i++)
            Level->CellLists[Level->Model->Cells[Cells(i)].Index].RemoveItem(this);
    }
}

UnnamedCache_12c *UnnamedOwner_90c90::GetCache()
{
    if (!Cache)
        Cache = new(NewTag_90c90) UnnamedCache_12c(this);
    if (Cache->Revision != Revision)
        RebuildCache();
    return Cache;
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit: simplified stand-ins for the
// out-of-line callees (0x10a14ad0, 0x10990e60, 0x10992980, 0x10a1de70) so LTCG
// picks their retail register conventions, plus the driver.
void Escape(void *);
extern UnnamedOwner_90c90 *ExtOwner;
UnnamedCache_12c::UnnamedCache_12c(UnnamedOwner_90c90 *InOwner)
{
    Owner = InOwner; Revision = -1; Field0c = 0;
    A0 = *GCacheVecA; A1 = *GCacheVecB;
    Fieldc0 = 0; Fieldc4 = 0;
    B0 = *GCacheVecA; B1 = *GCacheVecB;
    Fielde8 = 0; Fieldec = 0; Fieldf0 = 0; Fieldf4 = 0;
}
INT Sink(INT, INT, INT, INT, INT, INT);
void UnnamedOwner_90c90::RebuildCache()
{
    INT Local[20];
    if (Revision & 0x8000) return;
    INT a = Sink(1, 2, 3, 4, 5, (INT)Cache);
    INT b = Sink(a, 2, 3, 4, 5, (INT)Local);
    INT c = Sink(a, b, 3, 4, 5, (INT)Local);
    INT d = Sink(a, b, c, 4, 5, (INT)Local);
    INT e = Sink(a, b, c, d, 5, (INT)Local);
    Sink(a, b, c, d, e, (INT)Local);
    Sink(a, b, c, d, e, (INT)Local);
    Cache->Revision = Revision + a + b + c + d + e;
}
UnnamedRenderLarge_130::UnnamedRenderLarge_130(UnnamedOwner_90c90 *InOwner)
:   UnnamedRender_130(InOwner)
{
    CNum = CMax = ((InOwner->Flags2e8 >> 17) & 1) * 4;
    CData = CNum ? GMalloc->Malloc(CNum * 4, NewTag_92980) : 0;
}
void UnnamedRender_130::Update()
{
    INT Local[24];
    UnnamedOwner_90c90 *O = Owner;
    if (!O) return;
    Sink(O->Kind2d2, 2, 3, 4, 5, (INT)Local);
    Sink(O->Pad2d3[0], 2, 3, 4, 5, (INT)Local);
    Revision = O->Revision;
}
void Driver_90c90(UnnamedOwner_90c90 *O) { Escape(&GMalloc); Escape(O->GetCache()); Escape(O->GetCache()); Escape(O); Escape(O->GetCache()); Escape(O->GetRender()); Escape(O); Escape(O->GetRender()); O->Invalidate(); Escape(O); O->Invalidate(); }
