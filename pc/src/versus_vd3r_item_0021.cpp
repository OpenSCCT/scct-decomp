// Work item 0021 (LTCG retry): Versus RVA 0x5b00.
// Class names are neutral: no vtable labels or strings identify these types.
typedef unsigned long DWORD;
typedef int INT;
typedef unsigned short TCHAR;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

// Base of the member at +0x44 (destructor at 0x5890).
class UnnamedBase_5890 {
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Close();
    UnnamedBase_5890();
    ~UnnamedBase_5890();
    INT A, B, C;
    DWORD Flags;
};

// Member at +0x44 (destructor at 0x5940).
class UnnamedMember_5940 : public UnnamedBase_5890 {
public:
    virtual void Close();
    ~UnnamedMember_5940()
    {
        if (!(Flags & 1)) {
            Flags |= 1;
            Close();
        }
    }
};

// Base class (destructor at 0x10b146b0, outside the LTCG unit).
class UnnamedBase_b146b0 {
public:
    UnnamedBase_b146b0();
    virtual ~UnnamedBase_b146b0();
    void operator delete(void *Ptr) { GMalloc->Free(Ptr); }
    INT Data[16];
};

// Its compiler-generated destructor is the function at 0x5b00 (a user-written
// destructor would store the vtable pointer, which retail does not).
class UnnamedClass_5b00 : public UnnamedBase_b146b0 {
public:
    UnnamedMember_5940 Member;
};

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_5b00() { UnnamedClass_5b00 Obj; Escape(&Obj); }
