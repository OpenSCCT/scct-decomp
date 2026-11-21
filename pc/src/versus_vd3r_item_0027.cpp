// Work item 0027 (LTCG retry): Versus RVA 0x6200, 0x6260, 0x62d0.
// A record of three FStrings plus two dwords (dtor 0x6200, copy ctor 0x6260)
// held at +0x3c of an owner whose first member (dtor RVA 0x5b50) is not yet
// identified (dtor 0x62d0). Names are neutral: no label identifies them.
// All three match under try_ltcg.py with /O2 /Ob1 /Gy /GX; /Ob1 keeps the
// out-of-line record destructor a call in 0x62d0, as retail has it.
typedef unsigned short TCHAR;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef int INT;

class FString
{
public:
    TCHAR* Data;
    INT ArrayNum;
    INT ArrayMax;
    FString(const FString& Other); // RVA 0x4640
    ~FString();                    // RVA 0x48b0
};

struct UnnamedRecord_6200
{
    FString A;      // +0x00
    FString B;      // +0x0c
    FString C;      // +0x18
    DWORD D;        // +0x24
    DWORD E;        // +0x28
    ~UnnamedRecord_6200();
    // RVA 0x6260: implicit copy constructor.
};

// RVA 0x6200
UnnamedRecord_6200::~UnnamedRecord_6200()
{
}

struct UnnamedMember_5b50
{
    BYTE Pad[0x3c];
    ~UnnamedMember_5b50();         // RVA 0x5b50
};

struct UnnamedOwner_62d0
{
    UnnamedMember_5b50 Head;       // +0x00
    UnnamedRecord_6200 Record;     // +0x3c
    // RVA 0x62d0: implicit destructor.
};

// Scaffolding for the link, not part of the unit.
inline void* operator new(unsigned int, void* Mem) { return Mem; }
void Driver_6200(UnnamedRecord_6200* Object)
{
    Object->~UnnamedRecord_6200();
}
UnnamedRecord_6200* Driver_6260(void* Mem, const UnnamedRecord_6200* Src)
{
    return new(Mem) UnnamedRecord_6200(*Src);
}
void Driver_62d0(UnnamedOwner_62d0* Object)
{
    Object->~UnnamedOwner_62d0();
}
