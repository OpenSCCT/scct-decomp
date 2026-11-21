/* Item 0398: RVA 0xa7ba0 (InternalConstructor of an unidentified UObject
   subclass) and RVA 0xa7c00 (its base class constructor). Both were compiled
   with VC7.0 /GL and linked with /LTCG. The classes are unidentified, so
   neutral names are used. */
typedef int INT;
typedef unsigned short TCHAR;
typedef unsigned long DWORD;
enum EInternal { EC_Internal };
inline void *operator new(unsigned int, EInternal *Mem) { return Mem; }
inline void operator delete(void *, EInternal *) {}

class UObject {
public:
    virtual ~UObject();
    DWORD Pad[9];
};

/* Secondary interface base at +0x28. */
class FUnnamedInterface_a7c00 {
public:
    virtual void Dummy();
};

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize)
    {
        ArrayNum = InNum;
        ArrayMax = InNum;
        Data = 0;
        if (ArrayMax)
            Realloc(ElementSize);
    }
    void Realloc(INT ElementSize);
    ~FArray();
};

template <class T> class TArray : public FArray {
public:
    TArray() {}
    TArray(INT InNum) : FArray(InNum, sizeof(T)) {}
    ~TArray() {}
};

template <class T> class TTransArray : public TArray<T> {
public:
    UObject *Owner;
    TTransArray(UObject *InOwner, INT InNum = 0) : TArray<T>(InNum), Owner(InOwner) {}
    ~TTransArray() {}
};

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString(const TCHAR *In);
    FString(const FString &Other);
    ~FString();
};

/* Member at +0xf4, constructed out of line (RVA 0xa33490). Its constructor
   takes an optional name, passed as NULL here. */
class FUnnamedMember_a33490 {
public:
    FUnnamedMember_a33490(const TCHAR *InName);
    FString Name0;
    FString Name1;
    DWORD Value18;
    FString Name2;
    TArray<INT> Array28;
    FString Name3;
    DWORD Value40;
    DWORD Pad[(0x54 - 0x44) / 4];
};

class UnnamedClass_a7c00 : public UObject, public FUnnamedInterface_a7c00 {
public:
    TTransArray<INT> List0;
    TTransArray<INT> List1;
    TTransArray<INT> List2;
    TTransArray<INT> List3;
    TTransArray<INT> List4;
    TTransArray<INT> List5;
    TTransArray<INT> List6;
    TTransArray<INT> List7;
    TTransArray<INT> List8;
    TTransArray<INT> List9;
    TTransArray<INT> List10;
    TTransArray<INT> List11;
    DWORD Unknown_ec;
    DWORD Unknown_f0;
    FUnnamedMember_a33490 Member_f4;
    UnnamedClass_a7c00();
    void Dummy();
};

UnnamedClass_a7c00::UnnamedClass_a7c00()
: List0(this), List1(this), List2(this), List3(this), List4(this), List5(this), List6(this), List7(this), List8(this), List9(this), List10(this), List11(this), Member_f4(0)
{
}

/* Intermediate class: its vtable stores are dead and vanish. */
class UnnamedClass_a7ba0_Base : public UnnamedClass_a7c00 {
public:
    TArray<INT> Items;
    void Dummy();
};

class UnnamedClass_a7ba0 : public UnnamedClass_a7ba0_Base {
public:
    void Dummy();
    UnnamedClass_a7ba0() {}
    static void InternalConstructor(void *X) { new ((EInternal *)X) UnnamedClass_a7ba0(); }
};

/* Scaffolding for the link, not part of the unit: a stand-in body for the
   out-of-line member constructor at RVA 0xa33490 so the linker gives it the
   retail calling convention. */
extern DWORD GUnnamed_c922ac;
extern const TCHAR Text_ca7780[];
extern const TCHAR Text_ca77bc[];
extern const TCHAR Text_ca77a4[];
extern const TCHAR Text_ca77c8[];
FUnnamedMember_a33490::FUnnamedMember_a33490(const TCHAR *InName)
: Name0(Text_ca7780), Name1(Text_ca77bc), Value18(GUnnamed_c922ac),
  Name2(InName ? FString(InName) : FString(Text_ca77a4)), Name3(Text_ca77c8), Value40(1)
{
}

typedef void (*FCtor)(void *);
FCtor Driver_a7ba0() { return &UnnamedClass_a7ba0::InternalConstructor; }
