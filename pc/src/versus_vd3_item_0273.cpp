// Destructor at RVA 0x690f0. Class names are neutral: no RTTI or strings
// identify the class. Four interface pointers at +0x24..+0x30 are released
// through vtable slot 2, then the member at +0x48 and the base are destroyed.

struct UnnamedInterface_690f0 {
    virtual long __stdcall QueryInterface(const void *Iid, void **Out);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
};

struct UnnamedMember_1ef20 {
    ~UnnamedMember_1ef20();   // FUN_1091ef20
    int Data[4];
};

struct UnnamedBase_68ff0 {
    virtual ~UnnamedBase_68ff0() throw();   // FUN_10968ff0
    int BaseData[8];
};

struct UnnamedClass_690f0 : UnnamedBase_68ff0 {
    virtual ~UnnamedClass_690f0();
    UnnamedInterface_690f0 *Interface0;
    UnnamedInterface_690f0 *Interface1;
    UnnamedInterface_690f0 *Interface2;
    UnnamedInterface_690f0 *Interface3;
    int Pad[5];
    UnnamedMember_1ef20 Member;
};

UnnamedClass_690f0::~UnnamedClass_690f0()
{
    if (Interface0) Interface0->Release();
    if (Interface1) Interface1->Release();
    if (Interface2) Interface2->Release();
    if (Interface3) Interface3->Release();
}
