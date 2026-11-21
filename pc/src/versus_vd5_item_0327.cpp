// Work item 0327: Versus RVA 0x10c250-0x10c3e0.
enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };
typedef unsigned long DWORD;
typedef int INT;
typedef DWORD UBOOL;

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
    int Index;
    unsigned Reserved[5];
    unsigned ObjectFlags;
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

class UPrimitive : public UObject {
public:
    virtual ~UPrimitive();
    unsigned char UObjectData[0x50 - 0x20];
};

// Releases a member's storage (0x10c160 and 0x1fb4d0 in retail).
void __stdcall ReleaseMember_10c160(void *member);
void __stdcall ReleaseMember_1fb4d0(void *member);

// Class name unknown: a UPrimitive subclass with two members at 0x50 and 0x5c
// (vtable 0x10c03940 in retail).
class UnnamedPrimitive_10c250 : public UPrimitive {
public:
    struct Member50 { ~Member50() { ReleaseMember_10c160(this); } unsigned char Data[0xc]; };
    struct Member5C { ~Member5C() { ReleaseMember_1fb4d0(this); } unsigned char Data[0xc]; };
    virtual ~UnnamedPrimitive_10c250();
    Member50 Field50;
    Member5C Field5C;
};
UnnamedPrimitive_10c250::~UnnamedPrimitive_10c250() { ConditionalDestroy(); }

// Maps a key code to an internal code; returns 0 for unmapped keys.
// Neutral name: the caller and meaning of the output codes are not recovered.
UBOOL MapKeyCode_10c310(INT Key, DWORD *Out)
{
    switch (Key) {
    case 0x08: case 0x1b: case 0x2e: case 0xc9: *Out = 0x81; return 1;
    case 0x11: *Out = 0x11; return 1;
    case 0x70: *Out = 0x54; return 1;
    case 0x21: case 0x26: case 0xd4: *Out = 0x26; return 1;
    case 0x27: case 0xd5: *Out = 0x27; return 1;
    case 0x22: case 0x28: case 0xd6: *Out = 0x28; return 1;
    case 0x25: case 0xd7: *Out = 0x25; return 1;
    case 0x24: case 0xc8: *Out = 0x83; return 1;
    case 0x0d: case 0x20: case 0xca: *Out = 0x80; return 1;
    case 0x23: case 0xcb: *Out = 0x82; return 1;
    case 0xd3: *Out = 0x84; return 1;
    case 0xff: *Out = 0x8a; return 1;
    }
    if ((Key >= 'A' && Key <= 'Z') || (Key >= '0' && Key <= '9')) {
        *Out = 0;
        return 1;
    }
    return 0;
}

// Scaffolding for the link, not part of the unit.
UBOOL Driver_10c310(INT Key, DWORD *Out) { return MapKeyCode_10c310(Key, Out); }
