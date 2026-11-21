// USkeletalMeshInstance vtable slot 51: IsAnimating(INT Channel).
// Channel layout follows pc/src/versus_skeletal_channels.c (144-byte channels).
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

struct MeshAnimChannel {
    unsigned char Pad0[8];
    INT AnimSeq;
    FLOAT AnimRate;
    FLOAT AnimFrame;
    FLOAT AnimLast;
    FLOAT TweenRate;
    unsigned char Rest[0x90 - 0x1c];
};

class USkeletalMeshInstance {
public:
    unsigned char Pad0[0x100]; // vtable included; slot 51 per retail vtable
    MeshAnimChannel *Blends;
    INT BlendsNum;
    UBOOL IsAnimating(INT Channel);
};

UBOOL USkeletalMeshInstance::IsAnimating(INT Channel)
{
    if (BlendsNum > Channel && Channel >= 0 && Blends[Channel].AnimSeq) {
        if (Blends[Channel].AnimFrame >= 0.f ? Blends[Channel].AnimRate != 0.f : Blends[Channel].TweenRate != 0.f)
            return 1;
    }
    return 0;
}
