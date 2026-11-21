// Work item 0268: Versus RVA 0x67d70, LTCG (VC7.0 /GL, /LTCG).
// Neutral names: no vtable label or string identifies the class.
// The function draws/emits two four-point shapes through the helper at
// RVA 0x66bb0 (this in ESI, eight stack arguments), passing two tables of
// four (X,Y) float pairs: a vertical "diamond" and its horizontal twin.
typedef int INT;
typedef float FLOAT;

struct FPoint2 { FLOAT X, Y; };

class UnnamedClass_67d70
{
public:
    INT* Device;
    void Emit_66bb0(INT A, INT B, INT Count, const FPoint2* Points, INT C, INT D, INT E, INT F);
    void EmitPair_67d70(INT A, INT B, INT C, INT D, INT E, INT F);
};

void UnnamedClass_67d70::EmitPair_67d70(INT A, INT B, INT C, INT D, INT E, INT F)
{
    FPoint2 Vertical[4] = { { 0.f, 1.f }, { 0.f, 3.f }, { 0.f, -1.f }, { 0.f, -3.f } };
    FPoint2 Horizontal[4] = { { 1.f, 0.f }, { 3.f, 0.f }, { -1.f, 0.f }, { -3.f, 0.f } };
    Emit_66bb0(A, B, 4, Vertical, 1, 2, C, D);
    Emit_66bb0(E, A, 4, Horizontal, 2, 1, F, C);
}

// Scaffolding for the link, not part of the unit.
// The helper at RVA 0x66bb0 keeps `this` in ESI and its own body is large
// (it programs the render device); this stand-in only gives the linker a body
// that uses ESI for `this` the same way, so the caller is compiled as retail.
void ExternalSink(INT* Device, INT* Value);
__declspec(noinline) void UnnamedClass_67d70::Emit_66bb0(INT A, INT B, INT Count, const FPoint2* Points, INT C, INT D, INT E, INT F)
{
    ExternalSink(Device, &A);
    ExternalSink(Device, &B);
    ExternalSink(Device, &Count);
    ExternalSink(Device, &C);
    ExternalSink(Device, &D);
    ExternalSink(Device, &E);
    ExternalSink(Device, &F);
    ExternalSink(Device, (INT*)Points);
}

void Driver_67d70(UnnamedClass_67d70* Obj, INT A, INT B, INT C, INT D, INT E, INT F)
{
    Obj->EmitPair_67d70(A, B, C, D, E, F);
}
