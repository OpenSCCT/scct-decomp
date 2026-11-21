// RVA 0x10e940. Class and member names are neutral: no vtable label or string
// evidence identifies them.
typedef unsigned long DWORD;
typedef unsigned char BYTE;

struct UnnamedVTCall70 { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c(); virtual void Notify70(); };

struct UnnamedVTCall6c { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void SetState6c(int); };

struct Leaf30 { char pad[0x4a4]; DWORD Field4a4; };
struct Leaf { char pad0[0x30]; Leaf30 *Sub30; char pad34[0x44 - 0x34]; DWORD Field44;
    char pad48[0x6c - 0x48]; UnnamedVTCall70 *Obj6c; };
struct Node2c { char pad[0x2c]; Leaf **Leaves; };

struct Ctrl : UnnamedVTCall6c { char pad[0xf0 - 4]; };
struct CtrlHolder { char pad[0xf0]; Ctrl *Ctrl; };
struct Ctrl_ { char padv[4]; char pad[0x30 - 4]; Node2c *Sub30; };
struct Flag4a0 { char pad[0x4a0]; BYTE Field4a0; };

struct Pawn_10e940 {
    char pad0[0x1a0]; Flag4a0 *Field1a0; CtrlHolder *Field1a4;
    char pad1a8[0x2de - 0x1a8]; BYTE Field2de;
    char pad2df[0x4f0 - 0x2df]; DWORD Field4f0; char pad4f4[0x4fc - 0x4f4]; DWORD Field4fc;
    char pad500[0x5f0 - 0x500]; DWORD Field5f0;
};

void FUN_1098fdb0();

struct UnnamedClass_10e940 {
    char pad0[0x30]; Pawn_10e940 *Field30; char pad34[0x44 - 0x34]; DWORD Field44;
    char pad48[0x6c - 0x48]; DWORD Field6c;
    void Possess(Pawn_10e940 *P);
};

static inline Leaf *FirstLeaf(Pawn_10e940 *P)
{
    return ((Ctrl_ *)P->Field1a4->Ctrl)->Sub30->Leaves[0];
}

void UnnamedClass_10e940::Possess(Pawn_10e940 *P)
{
    Leaf *L = FirstLeaf(P);
    L->Sub30->Field4a4 = 0;
    L->Field44 = Field44;
    P->Field2de = 3;
    P->Field4f0 = 0x4000;
    P->Field4fc = 5;
    FUN_1098fdb0();
    FirstLeaf(P)->Obj6c->Notify70();
    P->Field1a4->Ctrl->SetState6c(1);
    P->Field1a0->Field4a0 = 0;
    P->Field5f0 |= 0x4000;
    Field30 = P;
    Field6c = 3;
}
