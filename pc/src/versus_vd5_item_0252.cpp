// Work item 0252: RVA 0xf3d90. Names are neutral; the owning class is not
// identified. Entries are 0x28-byte records holding a polymorphic object at
// +0x10 and a cached value at +0x1c.
typedef unsigned long DWORD;
typedef int INT;

struct UnnamedEntryObject_f3d90
{
    virtual void Update();
};

struct UnnamedEntry_f3d90
{
    DWORD Pad00[4];
    UnnamedEntryObject_f3d90 Object;   // +0x10
    DWORD Pad14[2];
    DWORD Value;                       // +0x1c
    DWORD Pad20[2];
};

struct UnnamedOwner_f3d90
{
    char Pad00[0x70];
    UnnamedEntry_f3d90 *Entries;       // +0x70
    char Pad74[0xb4 - 0x74];
    DWORD Flags;                       // +0xb4
};

class UnnamedClass_f3d90
{
public:
    DWORD Pad00[3];
    UnnamedOwner_f3d90 *Owner;         // +0x0c

    DWORD GetEntryValue(INT Index);
};

DWORD UnnamedClass_f3d90::GetEntryValue(INT Index)
{
    if (!(Owner->Flags & 0x10))
        Owner->Entries[Index].Object.Update();
    return Owner->Entries[Index].Value;
}
