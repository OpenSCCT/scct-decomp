// w4_item_0079.cpp -- Versus work item 0079 (RVA 0x144240)

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short TCHAR;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};

extern FMalloc *GMalloc;

class FArray {
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;

    void Empty()
    {
        ArrayNum = 0;
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};

// 0x1c-byte subobject constructed by 0x10a126e0 (vtable + FArray at +0x04)
struct FSubobject1C_144240 {
    void  *unk_00;
    FArray Items;
    BYTE   unk_10[0x0c];
};

// 0x2c-byte subobject constructed by 0x109a5140 (FArray at +0x20)
struct FSubobject2C_144240 {
    BYTE   unk_00[0x20];
    FArray Items;
};

// 0x18-byte stream-like subobject (vtable + 2 DWORDs + FArray at +0x0c)
struct FSubobject18_144240 {
    void  *unk_00;
    DWORD  unk_04;
    DWORD  unk_08;
    FArray Items;
};

// 0x110-byte element cleared by the caller at 0x1443e0 (neutral name; exact class name unverified).
class UnnamedClass_144240 {
public:
    FArray              Array_00;
    FArray              Array_0c;
    DWORD               unk_18;
    FArray              Array_1c;
    FArray              Array_28;
    FSubobject1C_144240 Sub_34;
    FSubobject1C_144240 Sub_50;
    FSubobject2C_144240 Sub_6c;
    FSubobject18_144240 Sub_98;
    FSubobject18_144240 Sub_b0;
    FSubobject18_144240 Sub_c8;
    FSubobject18_144240 Sub_e0;
    DWORD               Field_f8;
    DWORD               Field_fc;
    DWORD               Field_100;
    DWORD               Field_104;
    DWORD               Field_108;
    DWORD               Field_10c;

    void Clear();
};

// UnnamedClass_144240::Clear
void UnnamedClass_144240::Clear()
{
    Array_00.Empty();
    Array_0c.Empty();
    Array_1c.Empty();
    Array_28.Empty();
    Sub_34.Items.Empty();
    Sub_50.Items.Empty();
    Sub_6c.Items.Empty();
    Sub_98.Items.Empty();
    Sub_b0.Items.Empty();
    Sub_c8.Items.Empty();
    Sub_e0.Items.Empty();
    Field_f8 = 0;
    Field_fc = 0;
    Field_100 = 0;
    Field_104 = 0;
    Field_108 = 0;
    Field_10c = 0;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);

void Driver_144240(UnnamedClass_144240 *Obj)
{
    Escape(&GMalloc);
    Obj->Clear();
}
