// UTexRotator virtual at vtable slot 8 (RVA 0xaa060). Field names are neutral.
typedef unsigned long DWORD;
typedef unsigned char BYTE;

void UnnamedFunc_16f70(); // FUN_10916f70, takes no arguments

class UTexRotator
{
public:
    virtual void Slot8();
    BYTE Pad04[0x1c - 4];
    DWORD ObjectFlags;          // 0x1c
    BYTE Pad20[0x98 - 0x20];
    BYTE Dirty;                 // 0x98
    BYTE Pad99[0xa8 - 0x99];
    DWORD Flags_a8;             // 0xa8
};

void UTexRotator::Slot8()
{
    ObjectFlags |= 0x20000000;
    if (ObjectFlags & 0x100)
        UnnamedFunc_16f70();
    if (Flags_a8 & 1) {
        Flags_a8 &= ~1;
        Dirty = 1;
    }
}
