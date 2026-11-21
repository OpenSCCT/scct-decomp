// Work item 0109: RVA 0x1b9a0.
// An FArchive subclass's operator<<(UObject*&) that tags objects reached from
// a root (it bumps a per-object counter in an owner array, sets tag flags and
// recurses into the Outer). Class names below are neutral guesses.
typedef unsigned long DWORD;
typedef int INT;
typedef DWORD UBOOL;

class UObject
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10();
    virtual UBOOL IsPendingKill(); // vtable +0x2c
    INT Index;          // +0x04
    void *HashNext;     // +0x08
    void *StateFrame;   // +0x0c
    void *_Linker;      // +0x10
    INT _LinkerIndex;   // +0x14
    UObject *Outer;     // +0x18
    DWORD ObjectFlags;  // +0x1c
};

struct UnnamedOwner_1b9a0
{
    char Pad[0xe8];
    INT *Counts;        // +0xe8, indexed by UObject::Index
};

class FArchive
{
public:
    virtual void V00(); virtual void V01(); virtual void V02();
    virtual void V03(); virtual void V04(); virtual void V05();
    virtual FArchive &operator<<(UObject *&Obj); // vtable +0x18
    char ArPad[0x40];
};

// Neutral name: the concrete archive class is not identified.
class FArchiveTagUsed_1b9a0 : public FArchive
{
public:
    UnnamedOwner_1b9a0 *Owner; // +0x44
    FArchive &operator<<(UObject *&Obj);
};

FArchive &FArchiveTagUsed_1b9a0::operator<<(UObject *&Obj)
{
    if (Obj && !Obj->IsPendingKill())
    {
        if (!(Obj->ObjectFlags & 0x4000) || (Obj->ObjectFlags & 4))
        {
            Owner->Counts[Obj->Index]++;
            if (!(Obj->ObjectFlags & 0x10))
            {
                Obj->ObjectFlags |= 8;
                if (!(Obj->ObjectFlags & 0x400000))
                    Obj->ObjectFlags |= 0x40000;
                if (!(Obj->ObjectFlags & 0x100000))
                    Obj->ObjectFlags |= 0x10000;
                if (!(Obj->ObjectFlags & 0x200000))
                    Obj->ObjectFlags |= 0x20000;
                UObject *Outer = Obj->Outer;
                if (Outer)
                    *this << Outer;
            }
        }
    }
    return *this;
}
