// Work item 0223: RVA 0xee520, constructor of an unidentified USubsystem
// subclass (UObject at 0, FExec vtable at +0x28). LTCG: `this` on the stack,
// ret 4. Class and member names are neutral guesses.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum EName { NAME_None = 0 };

struct FName
{
    INT Index;
    FName() {}
    FName(INT N) : Index(N) {}
};

class FOutputDevice;
class UClass;

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray();
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};
template <class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray() {}
};

class UObject
{
public:
    UObject() {}
    virtual ~UObject();
    INT ObjPad[9];   // 0x04..0x27

    static UObject *StaticAllocateObject(UClass *Class, UObject *InOuter, FName Name, DWORD SetFlags,
                                         UObject *Template, FOutputDevice *Error, UObject *Ptr,
                                         UObject *SubobjectRoot);       // 0x1d380
    static UObject *StaticFindObject(UClass *ObjectClass, UObject *InObjectPackage,
                                     FName A, FName B, FName ObjectName, UBOOL ExactClass); // 0x17720
    static UObject *GObjTransientPkg;    // 0x10c925b4
};

class FExec
{
public:
    virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar);
};

class USubsystem : public UObject, public FExec
{
public:
    USubsystem() {}
    virtual ~USubsystem();
};

extern FOutputDevice *GError;            // 0x10c71aa8
extern TCHAR GCmdLine[];                 // 0x10c92680
extern const TCHAR Text_Switch_ee520[];  // 0x10c4956c, the command-line switch tested
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find);

// UE2 ParseParam (retail 0x121c0, its own unit; Stream in EDI, Param in ESI).
// Defined here so the link gives it its retail register convention.
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

class UFound_ee520                       // class of the objects looked up
{
public:
    static UClass PrivateStaticClass;    // 0x10cc8610
    static UClass *StaticClass() { return &PrivateStaticClass; }
};
template <class T> T *FindObjectFast(UObject *Outer, FName A, FName B, FName C, DWORD Flags)
{
    return (T *)UObject::StaticFindObject(T::StaticClass(), Outer, A, B, C, Flags);
}
extern UObject Object_10cc52a8;          // package passed to the finder
struct FHelperPart_ee520                 // 20-byte member, ctor at 0x4f670
{
    FHelperPart_ee520();
    ~FHelperPart_ee520();
    INT Raw[5];
};
class UHelper_ee520 : public UObject     // object created by the constructor
{
public:
    TArray<INT> Array28;
    FHelperPart_ee520 PartA, PartB;
    TArray<INT> Array5C;
    static UClass PrivateStaticClass;    // 0x10cc83e0
    static UClass *StaticClass() { return &PrivateStaticClass; }
    void *operator new(unsigned int Size, UObject *Outer = UObject::GObjTransientPkg, FName Name = NAME_None, DWORD SetFlags = 0)
    {
        return UObject::StaticAllocateObject(StaticClass(), Outer, Name, SetFlags, 0, GError, 0, 0);
    }
    UHelper_ee520();                      // 0x3eb10
    virtual ~UHelper_ee520();
};

// 0x3eb10 belongs to another unit; defined here (approximately) so the link
// sees a body and gives it its retail convention (`this` on the stack).
UHelper_ee520::UHelper_ee520()
{
}

class UnnamedSubsystem_ee520 : public USubsystem
{
public:
    UnnamedSubsystem_ee520();
    virtual ~UnnamedSubsystem_ee520();

    TArray<INT> Array2C;       // 0x2c
    INT Pad38[2];
    UHelper_ee520 *Helper;     // 0x40
    INT Field44;               // 0x44
    INT Field48;               // 0x48
    INT Pad4C[10];
    UBOOL bSwitch;             // 0x74
    UFound_ee520 *Found78;          // 0x78
    UFound_ee520 *Found7C;          // 0x7c
    INT Pad80[3];
    INT Field8C;               // 0x8c
    INT Pad90[27];
    INT FieldFC;               // 0xfc
    INT Field100;              // 0x100
};

UnnamedSubsystem_ee520::UnnamedSubsystem_ee520()
{
    Field44 = 0;
    Field48 = 0;
    Field8C = 0;
    FieldFC = 0;
    Field100 = 0;
    Found78 = FindObjectFast<UFound_ee520>(&Object_10cc52a8, FName(0), FName(0), FName(0x254), 0);
    Found7C = FindObjectFast<UFound_ee520>(&Object_10cc52a8, FName(0), FName(0), FName(0x255), 0);
    Helper = new UHelper_ee520;
    bSwitch = ParseParam(GCmdLine, Text_Switch_ee520);
}

// Scaffolding for the link, not part of the unit.

void Driver_ee520(UnnamedSubsystem_ee520 *P) { P->UnnamedSubsystem_ee520::UnnamedSubsystem_ee520(); }
