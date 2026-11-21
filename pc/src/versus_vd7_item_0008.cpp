/* w4_item_0008.cpp -- AActor::execGetRootRotationDelta (Versus RVA 0x124230). */

typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

struct FRotator {
    INT Pitch, Yaw, Roll;
};

inline FRotator MakeRotator(INT Pitch, INT Yaw, INT Roll)
{
    FRotator R;
    R.Roll = Roll;
    R.Pitch = Pitch;
    R.Yaw = Yaw;
    return R;
}

struct FFrame {
    BYTE unk_0[0xc];
    BYTE *Code;
};

#define P_FINISH Stack.Code++

class UClass {
public:
    BYTE unk_0[0x28];
    UClass *SuperField;
};

class UObject {
public:
    BYTE unk_0[0x24];
    UClass *Class;

    UBOOL IsA(UClass *SomeBase) const
    {
        for (UClass *TempClass = Class; TempClass; TempClass = TempClass->SuperField)
            if (TempClass == SomeBase)
                return 1;
        return 0;
    }
};

class AActor;
class UMeshInstance;

class UMesh : public UObject {
public:
    UMeshInstance *MeshGetInstance(const AActor *InActor);
};

class USkeletalMesh : public UMesh {
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class UMeshInstance : public UObject {
};

struct UnnamedResult_b7f30 {
    BYTE unk_0[0x48];
    INT Value48;
};

struct UnnamedChannelOwner_b7f30 {
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual UnnamedResult_b7f30 *Find(INT Key);
};

struct UnnamedChannelEntry_b7f30 {
    UnnamedChannelOwner_b7f30 *Owner;
    INT unk_4[5];
};

struct UnnamedSettings_b7f30 {
    INT unk_0;
    INT Index;
    INT Key;
    BYTE unk_c[0x74 - 0xc];
    BYTE bInvert;
};

class USkeletalMeshInstance : public UMeshInstance {
public:
    BYTE unk_28[0xa8 - 0x28];
    UnnamedChannelEntry_b7f30 *Channels;
    BYTE unk_ac[0x100 - 0xac];
    UnnamedSettings_b7f30 *Settings;
    BYTE unk_104[0x194 - 0x104];
    FRotator Current;
    BYTE unk_1a0[0x1ac - 0x1a0];
    FRotator Previous;

    FRotator GetRootRotationDelta();
};

// USkeletalMeshInstance::GetRootRotationDelta (RVA 0xb7f30, published in
// versus_vd5_item_0126.cpp). Defined here so LTCG reproduces its custom
// calling convention (this in ESI, return buffer in EBX).
__declspec(noinline) FRotator USkeletalMeshInstance::GetRootRotationDelta()
{
    INT Delta = Previous.Yaw - Current.Yaw;
    Previous = Current;
    UnnamedChannelOwner_b7f30 *Owner = Channels[Settings->Index].Owner;
    UnnamedResult_b7f30 *R;
    if (Owner && (R = Owner->Find(Settings->Key)) != 0 && R->Value48 == 0) {
        if (Settings->bInvert)
            Delta = -Delta;
    } else if (!Settings->bInvert) {
        Delta = -Delta;
    }
    return MakeRotator(0, Delta, 0);
}

class AActor : public UObject {
public:
    BYTE unk_28[0x1bc - 0x28];
    UMesh *Mesh;
    BYTE unk_1c0[0x1d4 - 0x1c0];
    UMeshInstance *MeshInstance;

    void execGetRootRotationDelta(FFrame &Stack, void *const Result);
};

// AActor::execGetRootRotationDelta (RVA 0x124230)
void AActor::execGetRootRotationDelta(FFrame &Stack, void *const Result)
{
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass())) {
        Mesh->MeshGetInstance(this);
        *(FRotator *)Result = ((USkeletalMeshInstance *)MeshInstance)->GetRootRotationDelta();
    }
}
