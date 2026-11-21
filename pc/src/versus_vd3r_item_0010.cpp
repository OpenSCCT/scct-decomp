// Work item 0010 (LTCG retry): Versus RVA 0x4ed0.
// Class names are neutral: no vtable label or string identifies the classes.
//
// RVA 0x4ed0 is the constructor matching the destructor at 0x4e70. The base
// part is built by RVA 0x4cd0 (a __fastcall routine: owner in ECX, id in EDX,
// object and name on the stack). The class then holds six 12-byte callback
// objects (vtable 0x10c0f060, object, function): the first is copied from
// the by-value argument, the other five start empty.
typedef unsigned long DWORD;

// Callback object, vtable 0x10c0f060.
struct UnnamedCallback_4ed0
{
    void* Object;
    void* Function;
    UnnamedCallback_4ed0() : Object(0), Function(0) {}
    UnnamedCallback_4ed0(void* InObject, void* InFunction) : Object(InObject), Function(InFunction) {}
    virtual void Execute();
};

struct UnnamedBase_4cd0;

// RVA 0x4cd0: builds the base part of the object.
void __fastcall UnnamedBase_4cd0_Construct(void* Owner, int Id, UnnamedBase_4cd0* This, void* Name);

// The out-of-line routine at 0x4cd0 stores the base vtable itself, so the
// inline constructor here does not (novtable).
struct __declspec(novtable) UnnamedBase_4cd0
{
    DWORD Fields[15];
    virtual void Destroy();
    UnnamedBase_4cd0(void* Owner, int Id, void* Name) { UnnamedBase_4cd0_Construct(Owner, Id, this, Name); }
};

// Default name used when the caller passes none.
extern void* UnnamedClass_4ed0_DefaultName;

struct UnnamedClass_4ed0 : UnnamedBase_4cd0
{
    UnnamedCallback_4ed0 Callback;   // 0x40
    UnnamedCallback_4ed0 Extra1;     // 0x4c
    UnnamedCallback_4ed0 Extra2;     // 0x58
    UnnamedCallback_4ed0 Extra3;     // 0x64
    UnnamedCallback_4ed0 Extra4;     // 0x70
    UnnamedCallback_4ed0 Extra5;     // 0x7c
    DWORD Field88;
    DWORD Field8C;

    UnnamedClass_4ed0(void* Owner, int Id, void* Name, UnnamedCallback_4ed0 InCallback);
    virtual void Destroy();
};

// RVA 0x4ed0
UnnamedClass_4ed0::UnnamedClass_4ed0(void* Owner, int Id, void* Name, UnnamedCallback_4ed0 InCallback)
    : UnnamedBase_4cd0(Owner, Id, Name ? Name : UnnamedClass_4ed0_DefaultName), Callback(InCallback)
{
    Field8C = 0;
}

// Scaffolding for the link, not part of the unit.
inline void* operator new(unsigned int, void* Where) { return Where; }
void Escape(void*);
void Driver_4ed0(char* Mem, void* Owner, void* Name, void* Object, void* F1, void* F2, void* F3, void* F4)
{
    Escape(&UnnamedClass_4ed0_DefaultName);
    new (Mem + 0x44) UnnamedClass_4ed0(Owner, 0x454, Name, UnnamedCallback_4ed0(Object, F1));
    new (Mem + 0xe0) UnnamedClass_4ed0(Owner, 0x455, Name, UnnamedCallback_4ed0(Object, F2));
    new (Mem + 0x17c) UnnamedClass_4ed0(Owner, 0x422, Name, UnnamedCallback_4ed0(Object, F3));
    new (Mem + 0x218) UnnamedClass_4ed0(Owner, 3, Name, UnnamedCallback_4ed0(Object, F4));
}
