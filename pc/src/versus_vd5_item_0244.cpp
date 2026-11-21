// Work item 0244: RVA 0xf24e0 and 0xf2540 (UTexture neighbours of versus_texture_frames.c).
typedef int INT;
typedef float FLOAT;
typedef unsigned char BYTE;

template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

class UTexture
{
public:
    // Slots 0-39 are inherited UObject/UBitmap/UMaterial virtuals not used here.
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void Slot04();
    virtual void Slot05();
    virtual void Slot06();
    virtual void Slot07();
    virtual void Slot08();
    virtual void Slot09();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();
    virtual void Slot33();
    virtual void Slot34();
    virtual void Slot35();
    virtual void Slot36();
    virtual void Slot37();
    virtual void Slot38();
    virtual void Slot39();
    virtual void Tick(FLOAT DeltaSeconds);       // 0xa0
    virtual void ConstantTimeTick();             // 0xa4
    virtual void Slot42();
    virtual void Slot43();
    virtual void Slot44();
    virtual void Prime();                        // 0xb4

    BYTE Pad04[0x84 - 4];
    FLOAT MinFrameRate;     // 0x84
    FLOAT MaxFrameRate;     // 0x88
    FLOAT Accumulator;      // 0x8c
};

void UTexture::Tick(FLOAT DeltaSeconds)
{
    Prime();
    if (MaxFrameRate == 0.f) {
        ConstantTimeTick();
        return;
    }
    FLOAT MinTime = 1.f / Clamp(MaxFrameRate, 0.1f, 100.f);
    FLOAT MaxTime = 1.f / Clamp(MinFrameRate, 0.1f, 100.f);
    Accumulator += DeltaSeconds;
    if (Accumulator < MinTime) {
        // Not yet time for the next frame.
    } else if (Accumulator < MaxTime) {
        ConstantTimeTick();
        Accumulator = 0.f;
    } else {
        ConstantTimeTick();
        Accumulator -= MaxTime;
        if (Accumulator > MaxTime)
            Accumulator = MaxTime;
    }
}

// 0xf24e0: neutral names; layout of the global and the object are not recovered.
struct UnnamedInfo_f24e0 { BYTE Pad[0x34]; INT Size; };
struct UnnamedGlobal_f24e0
{
    BYTE Pad00[0x7c];
    INT Offsets[9];                 // 0x7c
    UnnamedInfo_f24e0 *Info;        // 0xa0
};
extern UnnamedGlobal_f24e0 *GUnnamed_10c9245c;

struct UnnamedClass_f24e0
{
    BYTE Pad00[0x90];
    INT Position;   // 0x90
    INT MinPos;     // 0x94
    INT MaxPos;     // 0x98
    BYTE Pad9c[0xb8 - 0x9c];
    BYTE Slot;      // 0xb8
    __declspec(noinline) INT GetClampedPosition();
};

INT UnnamedClass_f24e0::GetClampedPosition()
{
    INT Pos;
    if (GUnnamed_10c9245c == 0)
        Pos = Position;
    else
        Pos = GUnnamed_10c9245c->Offsets[Slot] - GUnnamed_10c9245c->Info->Size / 2 + Position;
    return Clamp(Pos, MinPos, MaxPos);
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Use(INT);
void Driver_f24e0(UnnamedClass_f24e0 *P, UnnamedClass_f24e0 *Q, UnnamedClass_f24e0 *R, UnnamedClass_f24e0 *S)
{
    Escape(&GUnnamed_10c9245c);
    Use(P->GetClampedPosition()); Use(Q->GetClampedPosition()); Use(R->GetClampedPosition()); Use(S->GetClampedPosition());
}
