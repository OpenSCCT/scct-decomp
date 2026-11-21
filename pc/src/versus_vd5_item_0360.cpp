// Work item 0360: Versus RVA 0x1148d0-0x114c38.
// Class and member names are neutral (no vtable labels or strings identify them).

typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef int INT;
typedef float FLOAT;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector &operator=(const FVector &V) { X = V.X; Y = V.Y; Z = V.Z; return *this; }
};

// Object with a boolean test at vtable slot 0x70.
struct UnnamedTestable
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual INT Test();
};

struct UnnamedSlot_1148d0 { UnnamedTestable *Obj; INT Pad[2]; };   // 12 bytes

struct UnnamedOwner_1148d0
{
    BYTE Pad0[0xdc];
    UnnamedSlot_1148d0 *Slots;   // 0xdc
    INT NumSlots;                // 0xe0
};

// UObject::Class at 0x24 and UStruct::SuperField at 0x28 match Unreal Engine 2.
struct UClass_1148d0
{
    BYTE Pad0[0x28];
    UClass_1148d0 *SuperField;   // 0x28
};

struct UnnamedGroup_1148d0
{
    BYTE Pad0[0x24];
    UClass_1148d0 *Class;        // 0x24
    BYTE Pad28[0x68 - 0x28];
    UnnamedTestable **Items;     // 0x68
    INT NumItems;                // 0x6c

    __forceinline INT IsA(UClass_1148d0 *SomeBase) const
    {
        for (UClass_1148d0 *C = Class; C; C = C->SuperField)
            if (C == SomeBase)
                return 1;
        return 0;
    }
};

struct UnnamedNode_1148d0;
struct UnnamedChild_1148d0 { UnnamedNode_1148d0 *Node; INT Pad[3]; };   // 16 bytes

struct UnnamedNode_1148d0
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94();
    virtual UnnamedTestable *GetSlotObject(INT Index);   // 0x98

    BYTE Pad4[0x100 - 4];
    UnnamedOwner_1148d0 *Owner;        // 0x100
    BYTE Pad104[0x1bc - 0x104];
    UnnamedGroup_1148d0 *Group;        // 0x1bc
    BYTE Pad1c0[0x228 - 0x1c0];
    UnnamedTestable *Single;           // 0x228
    BYTE Pad22c[0x240 - 0x22c];
    UnnamedTestable **Items;           // 0x240
    INT NumItems;                      // 0x244
    BYTE Pad248[0x2d9 - 0x248];
    BYTE Kind;                         // 0x2d9
    BYTE Pad2da[0x2e8 - 0x2da];
    DWORD Flags;                       // 0x2e8
    BYTE Pad2ec[0x2f8 - 0x2ec];
    INT HasChildren;                   // 0x2f8
    UnnamedChild_1148d0 *Children;     // 0x2fc
    INT NumChildren;                   // 0x300
};

struct UnnamedDefaults_1148d0 { BYTE Pad0[0x40]; UnnamedTestable *Default; };

extern UnnamedDefaults_1148d0 *GUnnamedDefaults_1148d0;   // 0x10cc28ac
extern UClass_1148d0 GUnnamedClass_1148d0;   // 0x10cc19c8, a private static class object

INT Func_1148d0(UnnamedNode_1148d0 *Node)
{
    if (Node->Flags & 0x10000000)
        return 0;

    UnnamedOwner_1148d0 *Owner;
    UnnamedGroup_1148d0 *Group;
    if (Node->Kind == 8 && (Owner = Node->Owner) != 0)
    {
        for (INT i = 0; i < Owner->NumSlots; i++)
        {
            UnnamedTestable *Obj = Node->GetSlotObject(i);
            if (!Obj)
                Obj = Owner->Slots[i].Obj;
            if (!Obj)
                Obj = GUnnamedDefaults_1148d0->Default;
            if (Obj && Obj->Test())
                return 1;
            Owner = Node->Owner;
        }
    }
    else if (Node->Kind == 2 && (Group = Node->Group) != 0 && Group->IsA(&GUnnamedClass_1148d0))
    {
        for (INT i = 0; i < Group->NumItems; i++)
            { UnnamedTestable *Obj = Group->Items[i]; if (Obj && Obj->Test()) return 1; }
    }
    else if (Node->Kind == 13 && Node->HasChildren)
    {
        if (Node->NumItems)
        {
            for (INT i = 0; i < Node->NumItems; i++)
                { UnnamedTestable *Obj = Node->Items[i]; if (Obj && Obj->Test()) return 1; }
        }
        else
        {
            if (Node->Single)
                return Node->Single->Test();
            for (INT i = 0; i < Node->NumChildren; i++)
                if (Func_1148d0(Node->Children[i].Node))
                    return 1;
        }
    }
    else if (Node->Kind == 9 || Node->Kind == 3 || Node->Kind == 11 || Node->Kind == 10 || Node->Kind == 1)
    {
        return 1;
    }

    if (Node->Kind == 2)
    {
        for (INT i = 0; i < Node->NumItems; i++)
            { UnnamedTestable *Obj = Node->Items[i]; if (Obj && Obj->Test()) return 1; }
    }
    return 0;
}

// 0x114ad0: constructor-like initialiser, this in EAX and the argument in ECX (LTCG).
extern FVector *GUnnamedVectorA_114ad0;   // 0x10ccacc4
extern FVector *GUnnamedVectorB_114ad0;   // 0x10ccacc0

struct UnnamedState_114ad0
{
    void *Owner;        // 0x00
    INT Index;          // 0x04
    INT Pad08;
    INT Field0c;        // 0x0c
    BYTE Pad10[0x90 - 0x10];
    FVector A0;         // 0x90
    FVector B0;         // 0x9c
    BYTE Pada8[0xc0 - 0xa8];
    INT Fieldc0;        // 0xc0
    INT Fieldc4;        // 0xc4
    INT Padc8;
    FVector A1;         // 0xcc
    FVector B1;         // 0xd8
    INT Pade4;
    INT Fielde8;        // 0xe8
    INT Fieldec;        // 0xec
    INT Fieldf0;        // 0xf0
    INT Fieldf4;        // 0xf4

    void Init(void *InOwner);
};

void UnnamedState_114ad0::Init(void *InOwner)
{
    Owner = InOwner;
    Index = -1;
    Field0c = 0;
    A0 = *GUnnamedVectorA_114ad0;
    B0 = *GUnnamedVectorB_114ad0;
    Fieldc0 = 0;
    Fieldc4 = 0;
    A1 = *GUnnamedVectorA_114ad0;
    B1 = *GUnnamedVectorB_114ad0;
    Fielde8 = 0;
    Fieldec = 0;
    Fieldf0 = 0;
    Fieldf4 = 0;
}

// 0x114b90: returns a bounding box from scaled extents (LTCG: this in ECX, result in EAX).
extern const FLOAT GUnnamedLimit_114b90;   // 0x10c10a40
extern const FLOAT GUnnamedOne_114b90;     // 0x10c109fc

// Bounding box. The constructor (0x81ad0) and operator+= (0x4f820) live in other
// LTCG objects; they are defined here only so the linker gives them the retail
// register conventions (this in ESI / ECX, points in EDX and EDI).
struct FBox
{
    FVector Min, Max;

    __declspec(noinline) FBox(const FVector &A, const FVector &B);
    __declspec(noinline) FBox &operator+=(const FVector &Other);
};

inline FLOAT MinF(FLOAT A, FLOAT B) { return (A <= B) ? A : B; }
inline FLOAT MaxF(FLOAT A, FLOAT B) { return (A >= B) ? A : B; }

FBox &FBox::operator+=(const FVector &Other)
{
    if (Min.X - Max.X == GUnnamedOne_114b90)
    {
        Min.X = MinF(Min.X, Other.X);
        Min.Y = MinF(Min.Y, Other.Y);
        Min.Z = MinF(Min.Z, Other.Z);
        Max.X = MaxF(Max.X, Other.X);
        Max.Y = MaxF(Max.Y, Other.Y);
        Max.Z = MaxF(Max.Z, Other.Z);
    }
    else
    {
        Max = Other;
        Min = Max;
    }
    return *this;
}

FBox::FBox(const FVector &A, const FVector &B) : Min(A), Max(B)
{
    Min = *GUnnamedVectorA_114ad0;
    Max = *GUnnamedVectorB_114ad0;
    *this += A;
    *this += B;
}

struct UnnamedActor_114b90
{
    BYTE Pad0[0x148];
    FLOAT Blend;        // 0x148
    FLOAT Base;         // 0x14c
    FLOAT ExtentB;      // 0x150
    FLOAT ExtentA;      // 0x154
    BYTE Pad158[0x168 - 0x158];
    FLOAT Scale;        // 0x168
    BYTE Pad16c[0x2d2 - 0x16c];
    BYTE Type;          // 0x2d2

    FBox GetBox();
};

FBox UnnamedActor_114b90::GetBox()
{
    FVector Ext;
    Ext.X = Base * Scale;
    if (Type == 0x16 && Blend < GUnnamedLimit_114b90)
    {
        FLOAT F = (GUnnamedOne_114b90 - Blend) * Scale + Blend;
        Ext.Y = F * ExtentA;
        Ext.Z = F * ExtentB;
    }
    else
    {
        Ext.Y = ExtentA;
        Ext.Z = ExtentB;
    }
    return FBox(FVector(0.f, -Ext.Y, -Ext.Z), Ext);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_114ad0(UnnamedState_114ad0 *S, void *O)
{
    Escape(&GUnnamedVectorA_114ad0);
    Escape(&GUnnamedVectorB_114ad0);
    S->Init(O);
}
FBox Driver_114b90(UnnamedActor_114b90 *A) { return A->GetBox(); }
INT Driver_1148d0(UnnamedNode_1148d0 *N) { Escape(&GUnnamedDefaults_1148d0); return Func_1148d0(N); }
