// Work item w4 0058: Versus RVA 0x134940-0x134db2 (4 functions).
// UE2 FStatGraph-style stat graph methods (class/method names inferred from
// structure and algorithm; no symbol strings in these four functions).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

extern "C" __declspec(dllimport) INT __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR __cdecl towupper(TCHAR);
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

extern DWORD GCRCTable[256];

inline INT appStricmp(const TCHAR *A, const TCHAR *B) { return _wcsicmp(A, B); }
inline FLOAT appSqrt(FLOAT A) { return (FLOAT)sqrt(A); }
inline INT appFloor(FLOAT F) { return (INT)floor(F); }

template<class T> inline T Min(const T A, const T B)
{
    return (A <= B) ? A : B;
}

template<class T> inline T Max(const T A, const T B)
{
    return (A >= B) ? A : B;
}

template<class T> inline T Clamp(const T X, const T MinVal, const T MaxVal)
{
    return X < MinVal ? MinVal : X < MaxVal ? X : MaxVal;
}

// 0x1090f6b0: outside this item, defined so the link gives it its retail convention.
__declspec(noinline) DWORD appStrihash(const TCHAR *Data)
{
    DWORD Hash = 0;
    while (*Data)
    {
        TCHAR Ch = towupper(*Data++);
        unsigned char B = (unsigned char)Ch;
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
        B = (unsigned char)(Ch >> 8);
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
    }
    return Hash;
}

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
};

class FString : public TArray<TCHAR>
{
public:
    FString(const FString &Other);   // 0x10904640
    ~FString();                      // 0x109048b0
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
    UBOOL operator==(const FString &Other) const { return appStricmp(**this, *Other) == 0; }
};

inline DWORD GetTypeHash(const FString &S) { return appStrihash(*S); }

template <class TK, class TI> class TMapBase
{
public:
    class TPair
    {
    public:
        INT HashNext;
        TK Key;
        TI Value;
    };

    TArray<TPair> Pairs;
    INT *Hash;
    INT HashCount;

    // 0x1091f690: outside this item, defined so the link gives it its retail convention.
    __declspec(noinline) TI *Find(const TK &Key)
    {
        for (INT i = Hash[GetTypeHash(Key) & (HashCount - 1)]; i != -1; i = Pairs(i).HashNext)
            if (Pairs(i).Key == Key)
                return &Pairs(i).Value;
        return 0;
    }
};

template <class TK, class TI> class TMap : public TMapBase<TK, TI>
{
};

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FVector V, FLOAT InW) : FVector(V), W(InW) {}
};

template<class T, class U> inline T Lerp(const T &A, const T &B, const U &Alpha)
{
    return A + (B - A) * Alpha;
}

extern FVector *GHSVWhite;

// 0x109f22d0: outside this item, defined so the link gives it its retail convention.
__declspec(noinline) FPlane FGetHSV(BYTE H, BYTE S, BYTE V)
{
    FLOAT FH = H;
    FLOAT FS = S;
    FLOAT Brightness = V * (1.4f / 255.f);
    Brightness = Brightness / (0.01f + appSqrt(Brightness)) * 0.7f;
    Brightness = Clamp(Brightness, 0.f, 1.f);
    FVector Hue = (FH < 86.f) ? FVector((85.f - FH) * (1.f / 85.f), FH * (1.f / 85.f), 0.f)
                : (FH < 171.f) ? FVector(0.f, (170.f - FH) * (1.f / 85.f), (FH - 85.f) * (1.f / 85.f))
                : FVector((FH - 170.f) * (1.f / 85.f), 0.f, (255.f - FH) * (1.f / 84.f));
    return FPlane(Lerp(Hue, *GHSVWhite, FS * (1.f / 255.f)) * Brightness, 1.f);
}

struct FColor
{
    BYTE B, G, R, A;
    FColor() {}
    FColor(const FPlane &P);
};

// 0x109f8870: outside this item, defined so the link gives it its retail convention.
__declspec(noinline) FColor::FColor(const FPlane &P)
:   B((BYTE)Clamp(appFloor(P.Z * 256.f), 0, 255))
,   G((BYTE)Clamp(appFloor(P.Y * 256.f), 0, 255))
,   R((BYTE)Clamp(appFloor(P.X * 256.f), 0, 255))
,   A((BYTE)Clamp(appFloor(P.W * 256.f), 0, 255))
{
}

struct FStatGraphLine
{
    DWORD unk_00;          // +0x00
    TArray<FLOAT> Data;    // +0x04
    INT DataPos;           // +0x10
    BYTE unk_14[0x10];     // +0x14
    FLOAT YRange[2];       // +0x24
    FLOAT unk_2c;          // +0x2c
    UBOOL bAutoScale;      // +0x30
};

extern void ExternalAddLine(void *, const FString &, FColor, FLOAT, FLOAT);

class FStatGraph
{
public:
    BYTE unk_00[0x08];
    TMap<FString, DWORD> GetLineIndex;   // +0x08
    TArray<FStatGraphLine> Lines;        // +0x1c

    // 0x10a34720: outside this item, defined so the link gives it its retail
    // stack-this convention.
    __declspec(noinline) void AddLine(FString LineName, FColor Color, FLOAT YRangeMin, FLOAT YRangeMax)
    {
        ExternalAddLine(this, LineName, Color, YRangeMin, YRangeMax);
    }

    __declspec(noinline) void AddLineAutoRange(FString LineName, FColor Color);
    __declspec(noinline) void AddDataPoint(FString LineName, FLOAT Data, UBOOL bAutoAdd);
    __declspec(noinline) void UpdateAutoScale();
};

// RVA 0x134940: FStatGraph::AddLineAutoRange (inferred name).
void FStatGraph::AddLineAutoRange(FString LineName, FColor Color)
{
    AddLine(LineName, Color, 0.f, 0.f);
    DWORD *LineIndex = GetLineIndex.Find(LineName);
    FStatGraphLine *Line = &Lines(*LineIndex);
    Line->bAutoScale = 1;
}

// RVA 0x1349d0: FStatGraph::AddDataPoint (inferred name).
void FStatGraph::AddDataPoint(FString LineName, FLOAT Data, UBOOL bAutoAdd)
{
    DWORD *LineIndex = GetLineIndex.Find(LineName);
    if (!LineIndex)
    {
        if (!bAutoAdd)
            return;
        BYTE Hue = (BYTE)((Lines.Num() * 40) % 255);
        FColor NewColor(FGetHSV(Hue, 128, 255));
        NewColor.A = 255;
        AddLineAutoRange(LineName, NewColor);
        LineIndex = GetLineIndex.Find(LineName);
        if (!LineIndex)
            return;
    }

    FStatGraphLine *Line = &Lines(*LineIndex);
    Line->Data(Line->DataPos) = Data;
    Line->DataPos++;
    if (Line->DataPos > 255)
        Line->DataPos = 0;

    if (Line->bAutoScale)
    {
        Line->YRange[0] = Min(Line->YRange[0], Data);
        Line->YRange[1] = Max(Line->YRange[1], Data);
    }
}

extern TArray<FString> GStatGraphFilters;   // 0x10cbf698

// RVA 0x134b00: FindStatGraphFilter (inferred name).
INT FindStatGraphFilter(FString FilterName)
{
    INT Index = -1;
    for (INT i = 0; i < GStatGraphFilters.Num() && Index == -1; i++)
    {
        if (GStatGraphFilters(i) == FilterName)
            Index = i;
    }
    return Index;
}

// RVA 0x134b80: FStatGraph::UpdateAutoScale (inferred name).
void FStatGraph::UpdateAutoScale()
{
    for (INT i = 0; i < Lines.Num(); i++)
    {
        FStatGraphLine &Line = Lines(i);
        if (Line.bAutoScale)
        {
            Line.YRange[0] = 0.f;
            Line.YRange[1] = 0.f;
            for (INT j = 0; j < 256; j++)
            {
                Line.YRange[0] = Min(Line.YRange[0], Line.Data(j));
                Line.YRange[1] = Max(Line.YRange[1], Line.Data(j));
            }
        }
    }
}

// ---- Scaffolding for the link, not part of the unit ----
void Escape(void *);
void Driver_134940(FStatGraph *G, FString S, FColor C)
{
    Escape(&GCRCTable);
    G->AddLineAutoRange(S, C);
}
void Driver_1349d0(FStatGraph *G, FString S, FLOAT D, UBOOL B)
{
    Escape(&GCRCTable);
    Escape(&GHSVWhite);
    G->AddDataPoint(S, D, B);
}
void Driver_134b80(FStatGraph *G)
{
    G->UpdateAutoScale();
}
