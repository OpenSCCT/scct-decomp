// Work item 0303: AERainVolume virtuals at 0x104cd0 / 0x104d10 and an LTCG helper at 0x104d30.
// Vtable slots are named neutrally (VFunc<index>); the slot meanings are not yet recovered.
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;

struct FVector { FLOAT X, Y, Z; };
struct FRainPair { FVector A, B; FRainPair() {} FRainPair(const FVector &InA, const FVector &InB); void Include(const FVector &P); };

class AActor
{
public:
    AActor();
    void *operator new(unsigned int);
    virtual void VFunc0();
    virtual void VFunc1();
    virtual void VFunc2();
    virtual void VFunc3();
    virtual void VFunc4();
    virtual void VFunc5();
    virtual void VFunc6();
    virtual void VFunc7(INT Mode);
    virtual void VFunc8();
    virtual void VFunc9();
    virtual void VFunc10();
    virtual void VFunc11();
    virtual void VFunc12();
    virtual void VFunc13();
    virtual void VFunc14();
    virtual void VFunc15();
    virtual void VFunc16();
    virtual void VFunc17(); virtual void VFunc18(); virtual void VFunc19();
    virtual void VFunc20(); virtual void VFunc21(); virtual void VFunc22(); virtual void VFunc23();
    virtual void VFunc24(); virtual void VFunc25(); virtual void VFunc26(); virtual void VFunc27();
    virtual void VFunc28(); virtual void VFunc29(); virtual void VFunc30(); virtual void VFunc31();
    virtual void VFunc32(); virtual void VFunc33(); virtual void VFunc34(); virtual void VFunc35();
    virtual void VFunc36(); virtual void VFunc37(); virtual void VFunc38(); virtual void VFunc39();
    virtual void VFunc40(); virtual void VFunc41(); virtual void VFunc42(); virtual void VFunc43();
    virtual INT VFunc44();
};

class AERainVolume : public AActor
{
public:
    char Pad[0x2f8 - 4];
    FLOAT Dir_2f8, Dir_2fc, Dir_300;
    char Pad304[0x314 - 0x304];
    FLOAT RainValue_314; // defaults to 80 when left at zero
    char Pad318[0x324 - 0x318];
    struct UnnamedRainData *Data_324;
    struct FRainPair Coords_328;
    void UpdateRain();   // 0x105fe0, LTCG (this in EAX); body below approximates it so the linker can choose EAX

    AERainVolume();
    virtual void VFunc8();
    virtual void VFunc16();
};

void AERainVolume::VFunc16()
{
    AActor::VFunc16();
    VFunc44();
    UpdateRain();
    if (RainValue_314 == 0.0)
        RainValue_314 = 80.f;
}

void AERainVolume::VFunc8()
{
    AActor::VFunc8();
    VFunc44();
    UpdateRain();
}

struct UnnamedRainData { char Pad[0x5c]; INT A_5c; char Pad60[0x78 - 0x60]; INT A_78; char Pad7c[0x8c - 0x7c]; INT A_8c; };
   // 0x81ad0 lives in another LTCG object; approximated so the call shapes match
extern FVector *GRainVecA, *GRainVecB;
// 0x81ad0 lives in another LTCG object; body approximated so the call shape matches.
// It looks like a min/max bound built from two points: reset to the global extremes, then grow by each.
FRainPair::FRainPair(const FVector &InA, const FVector &InB)
    : A(InA), B(InB)
{
    A = *GRainVecB; B = *GRainVecA;
    Include(InA);
    Include(InB);
}

void AERainVolume::UpdateRain()
{
    FVector V; V.X = -Dir_2f8; V.Y = -Dir_2fc; V.Z = 0.f;
    Coords_328 = FRainPair(V, *(FVector *)&Dir_2f8);
    UnnamedRainData *D = Data_324;
    D->A_5c = 0;
    D->A_78 = 0;
    D->A_8c = 0;
}

// 0x104d30: draws an AERainVolume (called from the scene actor-render loop for draw type 9
// after IsA(AERainVolume)); LTCG gave it register arguments Actor=EDI, Frame=EBX, RI=ESI.
class FRenderInterface
{
public:
    virtual void PushState();
    virtual void PopState();
    virtual void VFunc2(); virtual void VFunc3(); virtual void VFunc4(); virtual void VFunc5(); virtual void VFunc6();
    virtual void VFunc7(INT Mode);
};
struct UnnamedViewport_104d30 { char Pad[0x154]; INT Flag_154; };
struct FLevelSceneNode { INT Field0; UnnamedViewport_104d30 *Viewport; };

void __stdcall RenderRainVolume_104d70(AActor *Actor, FLevelSceneNode *Frame, FRenderInterface *RI);

void DrawRainVolume(AActor *Actor, FLevelSceneNode *Frame, FRenderInterface *RI)
{
    RI->PushState();
    RI->VFunc7(2);
    if (Actor->VFunc44()) {
        if (Frame->Viewport->Flag_154 == 0)
            RenderRainVolume_104d70(Actor, Frame, RI);
        RI->PopState();
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
AERainVolume::AERainVolume() {}
void Driver_104cd0() { Escape(new AERainVolume); }
bool IsRainVolume(AActor *A);
void DrawOther(AActor *A, FLevelSceneNode *F, FRenderInterface *RI);
void Driver_104d30(AActor **Actors, INT Num, FLevelSceneNode *F, FRenderInterface *RI, unsigned char *Types)
{
    for (INT i = 0; i < Num; i++) {
        AActor *A = Actors[i];
        if (Types[i] == 1) DrawOther(A, F, RI);
        else if (Types[i] == 9 && IsRainVolume(A)) DrawRainVolume(A, F, RI);
        else if (Types[i] == 5 && IsRainVolume(A)) DrawRainVolume(A, F + 1, RI);
        else if (Types[i] == 6 && IsRainVolume(A)) DrawRainVolume(A + 1, F, RI);
        else if (Types[i] == 7) DrawRainVolume(A, F, RI + 1);
        Escape(F);
    }
}
