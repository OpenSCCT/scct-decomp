// Work item 0226: Versus RVA 0xef160-0xef1fc.
// 0xef160 Serialize and 0xef1b0 Destroy of an unidentified UObject subclass
// (names neutral: UnnamedClass_ef160). Its parent's Serialize (RVA 0x915f50,
// vtable slot 10) and Destroy (RVA 0x915ce0, slot 9) are also unidentified.
// Layout: TArray<UObject*> at +0x2c, owned objects at +0x38, +0x40, and
// serialized object references at +0x78, +0x7c.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class UObject;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);                    // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);                 // RVA 0x4550
};
template<class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void Slot08(); virtual void Slot0c(); virtual void Slot10();
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    virtual FArchive &operator<<(UObject *&Res);            // +0x18
    INT ArVer, ArNetVer, ArLicenseeVer, ArIsLoading, ArIsSaving;
};

FArchive &operator<<(FArchive &Ar, TArray<UObject *> &A);   // RVA 0xf85a0

class FUnknown
{
public:
    virtual DWORD QueryInterface(const void *RIID, void **PPInterface);
    virtual DWORD AddRef();
    virtual DWORD Release();
};

class UObject : public FUnknown
{
public:
    virtual ~UObject();                                     // +0x0c
    virtual void Slot10(); virtual void Slot14(); virtual void Slot18();
    virtual void Slot1c(); virtual void Slot20();
    virtual void Destroy();                                 // +0x24
    virtual void Serialize(FArchive &Ar);                   // +0x28
    virtual void Slot2c(); virtual void Slot30(); virtual void Slot34();
    virtual void Slot38(); virtual void Slot3c(); virtual void Slot40();
    virtual void Slot44(); virtual void Slot48(); virtual void Slot4c();
    virtual void Slot50(); virtual void Slot54(); virtual void Slot58();
    virtual void Slot5c();                                  // +0x5c
    INT Pad04[10];
};

// Parent class, unidentified: Destroy at RVA 0x915ce0, Serialize at 0x915f50.
class UnnamedBase_915f50 : public UObject
{
public:
    void Destroy();
    void Serialize(FArchive &Ar);
    UnnamedBase_915f50();
};

class UnnamedClass_ef160 : public UnnamedBase_915f50
{
public:
    TArray<UObject *> Objects;   // +0x2c
    UObject *Object38;           // +0x38
    INT Pad3c;
    UObject *Object40;           // +0x40
    INT Pad44[13];
    UObject *Object78;           // +0x78
    UObject *Object7c;           // +0x7c

    // Reached only through the vtable in retail; noinline keeps the
    // scaffolding driver from absorbing it in the LTCG link.
    UnnamedClass_ef160();
    __declspec(noinline) void Serialize(FArchive &Ar);
    void Destroy();
};

void UnnamedClass_ef160::Serialize(FArchive &Ar)
{
    UnnamedBase_915f50::Serialize(Ar);
    Ar << Objects << Object38 << Object40 << Object78 << Object7c;
}

void UnnamedClass_ef160::Destroy()
{
    delete Object38;
    while (Objects.Num())
        delete Objects(0);
    Slot5c();
    delete Object40;
    UnnamedBase_915f50::Destroy();
}

// Scaffolding for the link, not part of the unit. operator<< (RVA 0xf85a0,
// matched in versus_vd2_item_0112.cpp) is defined so the link gives it its
// whole-program convention (Ar in EAX, array in EBX); the constructor emits
// the vtable so Serialize keeps the ordinary thiscall convention.
void Escape(void *);
// Stand-in for the compact index serializer (RVA 0x1ea40).
__declspec(noinline) FArchive &SerializeIndex(FArchive &Ar, INT &Value)
{
    if (!Ar.ArIsLoading && !Ar.ArIsSaving) {
        Ar.Serialize(&Value, sizeof(INT));
        return Ar;
    }
    DWORD V = Value >= 0 ? Value : -Value;
    unsigned char B0 = (unsigned char)((Value >= 0 ? 0 : 0x80) + (V < 0x40 ? V : (V & 0x3f) + 0x40));
    Value = 0;
    Ar.Serialize(&B0, 1);
    if (B0 & 0x40) {
        V >>= 6;
        unsigned char B1 = (unsigned char)(V < 0x80 ? V : (V & 0x7f) + 0x80);
        Ar.Serialize(&B1, 1);
        if (B1 & 0x80) {
            V >>= 7;
            unsigned char B2 = (unsigned char)(V < 0x80 ? V : (V & 0x7f) + 0x80);
            Ar.Serialize(&B2, 1);
            if (B2 & 0x80) {
                V >>= 7;
                unsigned char B3 = (unsigned char)(V < 0x80 ? V : (V & 0x7f) + 0x80);
                Ar.Serialize(&B3, 1);
                if (B3 & 0x80) {
                    V >>= 7;
                    unsigned char B4 = (unsigned char)V;
                    Ar.Serialize(&B4, 1);
                    Value = B4;
                }
                Value = (Value << 7) + (B3 & 0x7f);
            }
            Value = (Value << 7) + (B2 & 0x7f);
        }
        Value = (Value << 7) + (B1 & 0x7f);
    }
    Value = (Value << 6) + (B0 & 0x3f);
    if (B0 & 0x80)
        Value = -Value;
    return Ar;
}
__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<UObject *> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(UObject *), A.ArrayMax * sizeof(UObject *));
    if (Ar.ArIsLoading) {
        INT NewNum;
        SerializeIndex(Ar, NewNum);
        A.Empty(sizeof(UObject *), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << A(A.FArray::Add(1, sizeof(UObject *)));
    } else {
        SerializeIndex(Ar, A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}
UnnamedBase_915f50::UnnamedBase_915f50() {}
UnnamedClass_ef160::UnnamedClass_ef160() {}
UnnamedClass_ef160 *Driver_ctor() { return new UnnamedClass_ef160; }
void Driver_ef160(UnnamedClass_ef160 *O, FArchive *Ar) { O->UnnamedClass_ef160::Serialize(*Ar); }
void Driver_ef1b0(UnnamedClass_ef160 *O) { O->UnnamedClass_ef160::Destroy(); }
