// Work item 0130: Versus RVA 0x3bdd0 (Core UnClass.cpp neighbourhood).
// LTCG function: Property in ECX, Context in EDX, Dest in EAX, Extra in EDI,
// Data on the stack (ret 4). The class compared against is a statically
// allocated UClass at 0x10cc8a70; BitMask at +0x58 makes it UBoolProperty.
// Names other than UObject's layout are neutral guesses.
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;

class UClass;
struct UnnamedContext_3bdd0
{
    BYTE Pad[0x10];
    INT Active;   // +0x10
};

class UProperty
{
public:
    virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0c();
    virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1c();
    virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2c();
    virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3c();
    virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4c();
    virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5c();
    virtual void Slot60(); virtual void Slot64(); virtual void Slot68(); virtual void Slot6c();
    virtual void Slot70(); virtual void Slot74();
    virtual void SetValue(UnnamedContext_3bdd0 *Context, DWORD *Dest, void *Extra); // +0x78

    INT Index;              // +0x04
    void *HashNext;         // +0x08
    void *StateFrame;       // +0x0c
    void *_Linker;          // +0x10
    INT _LinkerIndex;       // +0x14
    void *Outer;            // +0x18
    DWORD ObjectFlags;      // +0x1c
    INT Name;               // +0x20
    UClass *Class;          // +0x24
    BYTE Pad28[0x58 - 0x28];
    DWORD BitMask;          // +0x58 (UBoolProperty)

    void UnnamedSetProperty_3bdd0(UnnamedContext_3bdd0 *Context, DWORD *Dest, BYTE *Data, void *Extra);
};

extern UClass UBoolProperty_PrivateStaticClass; // 0x10cc8a70

__declspec(noinline) void UProperty::UnnamedSetProperty_3bdd0(UnnamedContext_3bdd0 *Context, DWORD *Dest, BYTE *Data, void *Extra)
{
    if (Class == &UBoolProperty_PrivateStaticClass) {
        if (Context->Active) {
            if (Data[1] & 0x80)
                *Dest |= BitMask;
            else
                *Dest &= ~BitMask;
        }
    } else {
        SetValue(Context, Dest, Extra);
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_3bdd0(UProperty *P, UnnamedContext_3bdd0 *C, DWORD *D, BYTE *B, void *E)
{
    Escape(&UBoolProperty_PrivateStaticClass);
    P->UnnamedSetProperty_3bdd0(C, D, B, E);
}
