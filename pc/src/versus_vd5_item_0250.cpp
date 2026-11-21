// Work item 0250: DXT5 block decompression and a small counted-id object.
typedef unsigned long DWORD;
typedef int INT;
typedef unsigned short TCHAR;
typedef unsigned __int64 QWORD;

template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

// RVA 0xf3820: decode DXT5 blocks into 32-bit ARGB pixels.
// LTCG: Dest in ECX, Height in EAX, Src and Width on the stack.
void DecompressDXT5(DWORD *Dest, const DWORD *Src, INT Width, INT Height)
{
    INT BlockW = Min(4, Width);
    INT BlockH = Min(4, Height);
    DWORD *End = Dest + Width * Height;
    const DWORD *In = Src;
    DWORD *Block = Dest;
    for (INT by = 0; by < Max(Height / 4, 1); by++)
    {
        for (INT bx = 0; bx < Max(Width / 4, 1); bx++)
        {
            DWORD AlphaLo = In[0];
            DWORD AlphaHi = In[1];
            DWORD Colors  = In[2];
            DWORD Indices = In[3];
            In += 4;

            DWORD A0 = AlphaLo & 0xff;
            DWORD A1 = (AlphaLo >> 8) & 0xff;
            DWORD Alpha[8];
            DWORD Color[4];
            if (A0 > A1)
            {
                Alpha[2] = ((6 * A0 + 1 * A1) / 7) << 24;
                Alpha[3] = ((5 * A0 + 2 * A1) / 7) << 24;
                Alpha[4] = ((4 * A0 + 3 * A1) / 7) << 24;
                Alpha[5] = ((3 * A0 + 4 * A1) / 7) << 24;
                Alpha[6] = ((2 * A0 + 5 * A1) / 7) << 24;
                Alpha[7] = ((1 * A0 + 6 * A1) / 7) << 24;
            }
            else
            {
                Alpha[2] = ((4 * A0 + 1 * A1) / 5) << 24;
                Alpha[3] = ((3 * A0 + 2 * A1) / 5) << 24;
                Alpha[4] = ((2 * A0 + 3 * A1) / 5) << 24;
                Alpha[5] = ((1 * A0 + 4 * A1) / 5) << 24;
                Alpha[6] = 0;
                Alpha[7] = 0xff000000;
            }
            Alpha[0] = A0 << 24;
            Alpha[1] = A1 << 24;

            // Expand the two RGB565 end points to 8 bits per channel, in place.
            DWORD R0 = (((Colors & 0xf800) << 5) | (Colors & 0xe000)) << 3;
            DWORD G0 = ((Colors & 0x07e0) << 5) | ((Colors >> 1) & 0x300);
            DWORD B0 = ((Colors & 0x001f) << 3) | ((Colors >> 2) & 0x7);
            DWORD R1 = ((Colors & 0xf8000000) | ((Colors >> 5) & 0x7000000)) >> 8;
            DWORD G1 = (((Colors >> 6) & 0x180000) | (Colors & 0x7e00000)) >> 11;
            DWORD B1 = (((Colors >> 5) & 0xe000) | (Colors & 0x1f0000)) >> 13;
            Color[0] = B0 | G0 | R0;
            Color[1] = B1 | G1 | R1;
            Color[2] = (((G1 * 11 + G0 * 21) & 0x1fe000) | ((B1 * 11 + B0 * 21) & 0x1fe0) | ((R1 * 11 + R0 * 21) & 0x1fe00000)) >> 5;
            Color[3] = (((G1 * 21 + G0 * 11) & 0x1fe000) | ((B1 * 21 + B0 * 11) & 0x1fe0) | ((R1 * 21 + R0 * 11) & 0x1fe00000)) >> 5;

            DWORD AlphaBits = AlphaLo >> 16;
            DWORD *Row = Block;
            for (INT y = 0; y < BlockH; y++)
            {
                switch (y)
                {
                case 1: AlphaBits = (AlphaLo >> 28) | (AlphaHi << 4); break;
                case 2: AlphaBits = AlphaHi >> 8; break;
                }
                DWORD *Pixel = Row;
                for (INT x = 0; x < BlockW; x++, Pixel++)
                {
                    if (Pixel >= End)
                        return;
                    *Pixel = Alpha[AlphaBits & 7] | Color[Indices & 3];
                    Indices >>= 2;
                    AlphaBits >>= 3;
                }
                Row += Width;
            }
            Block += BlockW;
        }
        Block += Width * 3;
    }
}

// RVA 0xf3c10: constructor of an unnamed object with a vtable (0x10c04118),
// a 64-bit id taken from a global counter, an owner value and a flag.
// LTCG: this in ESI, InOwner in EAX. Names are neutral; the class is not identified.
#pragma pack(push, 4)
extern QWORD UnnamedClass_3c10_NextId;
class UnnamedClass_3c10
{
public:
    QWORD Id;
    INT Owner;
    INT Flag;
    UnnamedClass_3c10(INT InOwner);
    virtual void Func0();
    virtual INT Func1();
    virtual INT Func2();
    virtual INT Func3();
    virtual INT Func4();
    virtual INT Func5();
    virtual INT Func6();
    virtual INT Func7();
};
#pragma pack(pop)
UnnamedClass_3c10::UnnamedClass_3c10(INT InOwner)
    : Owner(InOwner)
{
    QWORD NewId = UnnamedClass_3c10_NextId++ * 0x100 + 0xe0;
    Id = NewId;
    Flag = 1;
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *P) { return P; }
void Escape(void *);
class FMalloc { public: virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0; };
extern FMalloc *GMalloc;
extern const TCHAR DXTTag[];
void Driver_f3820(const DWORD *S, INT W, INT H, DWORD **Out)
{
    DWORD *D = (DWORD *)GMalloc->Malloc(W * H * 4, DXTTag);
    *Out = D;
    DecompressDXT5(D, S, W, H);
}
struct FInner_3c10 { char Pad[0xc0]; INT Owner; };
struct FOuter_3c10 { INT Pad; FInner_3c10 *Inner; INT Run0(); INT Run1(); INT Run2(); INT Run3(); INT Run4(); INT Run5(); INT Run6(); };
INT FOuter_3c10::Run0()
{
    if (Inner->Owner)
        return UnnamedClass_3c10(Inner->Owner).Func1();
    return 4;
}
INT FOuter_3c10::Run1()
{
    if (Inner->Owner)
        return UnnamedClass_3c10(Inner->Owner).Func2();
    return 4;
}
INT FOuter_3c10::Run2()
{
    if (Inner->Owner)
        return UnnamedClass_3c10(Inner->Owner).Func3();
    return 4;
}
INT FOuter_3c10::Run3()
{
    if (Inner->Owner)
        return UnnamedClass_3c10(Inner->Owner).Func4();
    return 4;
}
INT FOuter_3c10::Run4()
{
    if (Inner->Owner)
        return UnnamedClass_3c10(Inner->Owner).Func5();
    return 4;
}
INT FOuter_3c10::Run5()
{
    if (Inner->Owner)
        return UnnamedClass_3c10(Inner->Owner).Func6();
    return 4;
}
INT FOuter_3c10::Run6()
{
    if (Inner->Owner)
        return UnnamedClass_3c10(Inner->Owner).Func7();
    return 4;
}
void Driver_f3c10(FOuter_3c10 *O)
{
    O->Run0();
    O->Run1();
    O->Run2();
    O->Run3();
    O->Run4();
    O->Run5();
    O->Run6();
}
