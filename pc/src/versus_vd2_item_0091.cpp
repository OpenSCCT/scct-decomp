// Work item 0091: Versus RVA 0x158b0-0x1599a.
// 0x158b0 and 0x158d0 are link-time-optimised (this in EAX); 0x15920 is a
// class destructor with an exception frame.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum { INDEX_NONE = -1 };

class FName {
public:
    INT Index;
    INT GetIndex() const { return Index; }
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
};
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

class UObject {
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    INT Index;
    DWORD Reserved[5];
    DWORD ObjectFlags;
    FName Name;      // +0x20
    UObject *Class;  // +0x24
    int ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed)) {
            ObjectFlags = (ObjectFlags & ~(RF_DebugDestroy | RF_Destroyed)) | RF_Destroyed;
            Destroy();
            return 1;
        }
        return 0;
    }
};

// Name-keyed hash of a struct's fields: entries are {field, next index}.
struct FFieldHashEntry {
    UObject *Field;
    INT Next;
};
struct FFieldHash {
    INT HashCount;
    FFieldHashEntry *Entries;
};

class UStruct : public UObject {
public:
    UStruct *SuperField;            // +0x28
    unsigned char Pad2C[0x80 - 0x2c];
    FFieldHash FieldHash;           // +0x80

    UBOOL IsChildOf(const UStruct *SomeBase) const;
};

// RVA 0x158b0: walk the SuperField chain looking for SomeBase.
UBOOL UStruct::IsChildOf(const UStruct *SomeBase) const
{
    for (const UStruct *Struct = this; Struct; Struct = Struct->SuperField)
        if (Struct == SomeBase)
            return 1;
    return 0;
}

// RVA 0x158d0: look a field up by name in a struct's field hash and then in
// its parents' hashes. Callers pass the struct and its hash together.
UObject *__stdcall FindFieldInHash(UStruct *Struct, FFieldHash *Hash, FName InName)
{
    for (;;) {
        if (Hash->HashCount) {
            FFieldHashEntry *Entry = &Hash->Entries[(Hash->HashCount - 1) & InName.GetIndex()];
            for (UObject *Field = Entry->Field; Field; Field = Entry->Field) {
                if (Field->Name == InName)
                    return Field;
                if (!Entry->Next)
                    break;
                Entry = &Hash->Entries[Entry->Next];
            }
        }
        UStruct *Super = Struct->SuperField;
        if (!Super)
            return 0;
        Struct = Super;
        Hash = &Struct->FieldHash;
    }
}

// RVA 0x15920: destructor of the class with vtable 0x10c0ce60 (relative
// 0x30ce60; name unknown), whose parent's destructor is at 0x0cc80.
class UnnamedClass30D6A0 : public UObject { public: virtual ~UnnamedClass30D6A0(); };

class UnnamedClass30CE60 : public UnnamedClass30D6A0 {
public:
    struct Member30 { ~Member30(); };  // destroyed by 0x1ef20
    virtual ~UnnamedClass30CE60();
    unsigned char Pad28[0x30 - 0x28];
    Member30 Field30;
};
UnnamedClass30CE60::~UnnamedClass30CE60() { ConditionalDestroy(); }

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_158b0(const UStruct *S, const UStruct *B)
{
    Escape((void *)S->IsChildOf(B));
}
void Driver_158d0(UStruct *S, UStruct *T, FName N, FName M)
{
    Escape(FindFieldInHash(S, &S->FieldHash, N)); Escape(FindFieldInHash(T, &T->FieldHash, M));
    Escape(FindFieldInHash(S, &S->FieldHash, M)); Escape(FindFieldInHash(T, &T->FieldHash, N));
}
