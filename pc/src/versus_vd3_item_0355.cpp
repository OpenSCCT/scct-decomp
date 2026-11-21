// UESBPatch slot 48 (RVA 0x9ca30): adds an impulse, scaled by the inverse of
// the patch mass, to one particle's velocity. Field names are neutral guesses.
struct FVector
{
    float X, Y, Z;
    FVector() {}
    FVector(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator*(float Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator/(float Scale) const { float RScale = 1.f / Scale; return FVector(X * RScale, Y * RScale, Z * RScale); }
    FVector &operator+=(const FVector &V) { X += V.X; Y += V.Y; Z += V.Z; return *this; }
};

struct FESBParticle // 72 bytes
{
    char Pad00[0x34];
    FVector Velocity;
    char Pad40[0x08];
};

class UESBPatch
{
public:
    virtual void AddImpulse(int Index, const FVector &Impulse);
    char Pad04[0x6c];
    FESBParticle *Particles;   // 0x70
    char Pad74[0x130 - 0x74];
    float Mass;                // 0x130
};

void UESBPatch::AddImpulse(int Index, const FVector &Impulse)
{
    FVector Delta = Impulse / Mass;
    Particles[Index].Velocity += Delta;
}
