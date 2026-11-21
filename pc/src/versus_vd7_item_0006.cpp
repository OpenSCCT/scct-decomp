// Work item 0006: Versus RVA 0x123d00-0x123e13 (AActor::execHasAnim, AActor::execLinkSkelAnim).
// Retail compiled Engine with VC7.0 /GL and linked with /LTCG:
//   FOutputDevice::Logf (0x118d0): this in EBX.
//   USkeletalMeshInstance::AddAnimLinkup (0xb6d10): this in EBX, two stack arguments.
// The native functions themselves keep thiscall because they are registered in GNatives.

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef void *HMeshAnim;

#define RESULT_DECL void *const Result

struct FName
{
    INT Index;
};

class UClass;
struct FFrame;

class UObject
{
public:
    virtual ~UObject();

    BYTE unk_04[0x20];
    UClass *Class;

    UClass *GetClass() const { return Class; }
    UBOOL IsA(UClass *SomeBase) const;
};

typedef void (UObject::*Native)(FFrame &TheStack, RESULT_DECL);
extern Native GNatives[];

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
    virtual void Flush();
    void Logf(const TCHAR *Fmt, ...);
};

struct FFrame : public FOutputDevice
{
    void *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_NAME(Var) FName Var; Var.Index = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_OBJECT(Cls, Var) Cls *Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_OBJECT_OPTX(Cls, Var, Def) Cls *Var = Def; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class UClass : public UObject
{
public:
    UClass *SuperField;

    UClass *GetSuperClass() const { return SuperField; }
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->GetSuperClass())
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == 0;
}

class AActor;
class UMeshInstance;
class UMeshAnimation;

class UMesh : public UObject
{
public:
    UMeshInstance *MeshGetInstance(const AActor *Owner);
};

class USkeletalMesh : public UMesh
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class UMeshInstance : public UObject
{
public:
    virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04();
    virtual void V05(); virtual void V06(); virtual void V07(); virtual void V08();
    virtual void V09(); virtual void V10(); virtual void V11(); virtual void V12();
    virtual void V13(); virtual void V14(); virtual void V15(); virtual void V16();
    virtual void V17(); virtual void V18(); virtual void V19(); virtual void V20();
    virtual void V21(); virtual void V22(); virtual void V23(); virtual void V24();
    virtual void V25(); virtual void V26(); virtual void V27(); virtual void V28();
    virtual void V29(); virtual void V30(); virtual void V31(); virtual void V32();
    virtual void V33(); virtual void V34(); virtual void V35(); virtual void V36();
    virtual void V37(); virtual void V38(); virtual void V39(); virtual void V40();
    virtual HMeshAnim GetAnimNamed(FName InName); // slot 41, +0xa4
};

class USkeletalMeshInstance : public UMeshInstance
{
public:
    virtual void V42(); virtual void V43(); virtual void V44(); virtual void V45();
    virtual void V46(); virtual void V47(); virtual void V48(); virtual void V49();
    virtual void V50(); virtual void V51(); virtual void V52(); virtual void V53();
    virtual void V54(); virtual void V55(); virtual void V56(); virtual void V57();
    virtual void V58(); virtual void V59(); virtual void V60(); virtual void V61();
    virtual void V62(); virtual void V63(); virtual void V64(); virtual void V65();
    virtual void V66(); virtual void V67(); virtual void V68(); virtual void V69();
    virtual void V70(); virtual void V71();
    virtual void LinkupsChanged(); // slot 72, +0x120

    UBOOL AddAnimLinkup(UMeshAnimation *Anim, UMesh *NewMesh);
};

class AActor : public UObject
{
public:
    BYTE unk_28[0x1bc - 0x28];
    UMesh *Mesh; // 0x1bc
    BYTE unk_1c0[0x1d4 - 0x1c0];
    UMeshInstance *MeshInstance; // 0x1d4

    void execHasAnim(FFrame &Stack, RESULT_DECL);
    void execLinkSkelAnim(FFrame &Stack, RESULT_DECL);
};

extern const TCHAR Text_HasAnimNoMesh[]; // retail 0x10c47acc

// RVA 0x123d00: AActor::execHasAnim
void AActor::execHasAnim(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(Sequence);
    P_FINISH;

    if (Mesh)
    {
        Mesh->MeshGetInstance(this);
        *(DWORD *)Result = MeshInstance->GetAnimNamed(Sequence) != 0;
    }
    else
    {
        Stack.Logf(Text_HasAnimNoMesh);
    }
}

// RVA 0x123d80: AActor::execLinkSkelAnim
void AActor::execLinkSkelAnim(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UMeshAnimation, Anim);
    P_GET_OBJECT_OPTX(UMesh, NewMesh, 0);
    P_FINISH;

    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
    {
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->AddAnimLinkup(Anim, NewMesh);
    }
}

// ---- Scaffolding for the link, not part of the unit.
// Stand-in definitions of LTCG callees so the linker assigns retail register conventions.
typedef char *va_list;
typedef unsigned int size_t;
struct FLogFilter { INT unk_00; DWORD Flags; };
struct FLogOwner { BYTE unk_00[0x930]; FLogFilter *Filter; };
extern UBOOL GLogFilterActive;
extern FLogOwner *GLogOwner;
extern TCHAR GCmdLine[];
extern const TCHAR Text_LogFlushParam[];
extern const TCHAR Text_Logf[];

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf(TCHAR *Dest, size_t Count, const TCHAR *Fmt, va_list Args);
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find);

#pragma auto_inline(off)
UBOOL ParseParam(const TCHAR *Stream, const TCHAR *Param)
{
    const TCHAR *Start = Stream;
    if (*Stream)
    {
        while ((Start = appStrfind(Start + 1, Param)) != 0)
        {
            if (Start > Stream && (Start[-1] == '-' || Start[-1] == '/'))
                return 1;
        }
    }
    return 0;
}

void FOutputDevice::Logf(const TCHAR *Fmt, ...)
{
    if (!GLogFilterActive || !(GLogOwner->Filter->Flags & 0x1000))
    {
        TCHAR *Buffer = (TCHAR *)GMalloc->Malloc(0x10000, Text_Logf);
        _vsnwprintf(Buffer, 0x8000, Fmt, (va_list)&Fmt + sizeof(Fmt));
        Serialize(Buffer, 0x24c);
        GMalloc->Free(Buffer);
    }
    if (!ParseParam(GCmdLine, Text_LogFlushParam))
        Flush();
}

void ExtAddAnimLinkup(USkeletalMeshInstance *, UMeshAnimation **, UMesh **);
UBOOL USkeletalMeshInstance::AddAnimLinkup(UMeshAnimation *Anim, UMesh *NewMesh)
{
    if (!ParseParam(GCmdLine, Text_LogFlushParam))
    {
        ExtAddAnimLinkup(this, &Anim, &NewMesh);
        LinkupsChanged();
    }
    return 1;
}
#pragma auto_inline(on)

void Escape(void *);
extern Native Driver_Table[];

void Driver_123d00()
{
    Escape(&GNatives);
    Escape(&GMalloc);
    Driver_Table[0] = (Native)&AActor::execHasAnim;
}

void Driver_123d80()
{
    Escape(&GNatives);
    Escape(&USkeletalMesh::PrivateStaticClass);
    Driver_Table[1] = (Native)&AActor::execLinkSkelAnim;
}
