// USkeletalMeshInstance channel helpers (RVA 0xb5ac0, 0xb5b90).
// Reflected vtable USkeletalMeshInstance@30a048 slots 53 and 54.
// Method names follow UE2 SetAnimFrame; slot names other than the reflected ones are assumed.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef double DOUBLE;


template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }

struct FName { INT Index; };

// 144-byte animation channel (see versus_skeletal_channels.c).
struct MeshAnimChannel {
    unsigned char Prefix[8];
    FName AnimSeqName;      // +0x08
    FLOAT AnimRate;         // +0x0c
    FLOAT AnimFrame;        // +0x10
    FLOAT AnimLast;         // +0x14
    FLOAT TweenRate;        // +0x18
    unsigned char Rest[0x90 - 0x1c];
};

class USkeletalMeshInstance {
public:
    virtual void VSlot00();
    virtual void VSlot01();
    virtual void VSlot02();
    virtual void VSlot03();
    virtual void VSlot04();
    virtual void VSlot05();
    virtual void VSlot06();
    virtual void VSlot07();
    virtual void VSlot08();
    virtual void VSlot09();
    virtual void VSlot10();
    virtual void VSlot11();
    virtual void VSlot12();
    virtual void VSlot13();
    virtual void VSlot14();
    virtual void VSlot15();
    virtual void VSlot16();
    virtual void VSlot17();
    virtual void VSlot18();
    virtual void VSlot19();
    virtual void VSlot20();
    virtual void VSlot21();
    virtual void VSlot22();
    virtual void VSlot23();
    virtual void VSlot24();
    virtual void VSlot25();
    virtual void VSlot26();
    virtual void VSlot27();
    virtual void VSlot28();
    virtual void VSlot29();
    virtual void VSlot30();
    virtual void VSlot31();
    virtual void VSlot32();
    virtual void VSlot33();
    virtual void VSlot34();
    virtual void VSlot35();
    virtual void VSlot36();
    virtual void VSlot37();
    virtual void VSlot38();
    virtual void VSlot39();
    virtual void VSlot40();
    virtual void *FindAnimSequence(FName SeqName);       // slot 41 (+0xa4)
    virtual void VSlot42();
    virtual void VSlot43();
    virtual void VSlot44();
    virtual FLOAT AnimGetFrameCount(void *Seq);          // slot 45 (+0xb4)
    virtual void VSlot46();
    virtual void VSlot47();
    virtual void VSlot48();
    virtual void VSlot49();
    virtual void VSlot50();
    virtual UBOOL IsAnimPlaying(INT Channel);            // slot 51 (+0xcc), name assumed
    UBOOL SetAnimFrame(FLOAT NewFrame, INT Channel);
    UBOOL IsAnimBeforeStart(INT Channel);

    unsigned char Pad[0x100 - 4];
    MeshAnimChannel *Blends;   // +0x100 (TArray data)
    INT BlendsNum;             // +0x104
};

UBOOL USkeletalMeshInstance::SetAnimFrame(FLOAT NewFrame, INT Channel)
{
    if (Channel >= 0 && Channel < BlendsNum) {
        void *Seq = FindAnimSequence(Blends[Channel].AnimSeqName);
        FLOAT FrameCount = AnimGetFrameCount(Seq);
        if (FrameCount > 0.0001f)
            NewFrame /= FrameCount;
        Blends[Channel].AnimFrame = Max(Min(NewFrame, 1.f), 0.f);
        Blends[Channel].AnimRate = 0.f;
        Blends[Channel].TweenRate = 0.f;
        return 1;
    }
    return 0;
}

UBOOL USkeletalMeshInstance::IsAnimBeforeStart(INT Channel)
{
    if (BlendsNum > Channel && Channel >= 0 && Blends[Channel].AnimFrame < 0.0 && IsAnimPlaying(Channel))
        return 1;
    return 0;
}
