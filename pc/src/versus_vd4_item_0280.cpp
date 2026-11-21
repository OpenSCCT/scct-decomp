// Work item 0280: Versus RVA 0x6ab90 (LTCG, `this` in ESI).
// Names are neutral: the owning classes are not identified.
typedef int INT;
typedef unsigned long DWORD;

// COM-style interface (arguments pushed, `this` first, callee pops).
struct UnnamedDevice_6ab90;
struct UnnamedDeviceVtbl_6ab90
{
    void *Slots[88];
    void (__stdcall *Slot88)(UnnamedDevice_6ab90 *This, DWORD Value);   // +0x160
    void *Slot89;
    void (__stdcall *Slot90)(UnnamedDevice_6ab90 *This, DWORD Value);   // +0x168
};
struct UnnamedDevice_6ab90 { UnnamedDeviceVtbl_6ab90 *Vtbl; };

struct UnnamedDriver_6ab90
{
    char Pad0[0x46a4];
    UnnamedDevice_6ab90 *Device;            // +0x46a4
};

struct UnnamedState_6ab90
{
    UnnamedDriver_6ab90 *Driver;            // +0x00
    char Pad4[0xda4];
    DWORD Current;                          // +0xda8
};

class UnnamedNode_6ab90;

struct UnnamedOwner_6ab90
{
    char Pad0[0x40b8];
    UnnamedNode_6ab90 *Head;                // +0x40b8
    char Pad40bc[0x2fb58 - 0x40bc];
    UnnamedState_6ab90 State;               // +0x2fb58
};

class UnnamedNode_6ab90
{
public:
    void *Vtbl;                             // +0x00
    DWORD Handle;                           // +0x04
    DWORD Pad8;                             // +0x08
    UnnamedOwner_6ab90 *Owner;              // +0x0c
    UnnamedNode_6ab90 *Next;                // +0x10

    void Unlink();
};

void UnnamedNode_6ab90::Unlink()
{
    if (Owner->Head != this) {
        for (UnnamedNode_6ab90 *Node = Owner->Head; Node; Node = Node->Next) {
            if (Node->Next == this) {
                Node->Next = Next;
                break;
            }
        }
    } else {
        Owner->Head = Next;
    }
    DWORD H = Handle;
    Next = 0;
    if (H) {
        UnnamedState_6ab90 *State = &Owner->State;
        if (State->Current == H) {
            State->Current = 0;
            UnnamedDevice_6ab90 *Dev = State->Driver->Device;
            Dev->Vtbl->Slot88(Dev, 0);
        }
        UnnamedDevice_6ab90 *Dev = State->Driver->Device;
        Dev->Vtbl->Slot90(Dev, H);
    }
    Handle = 0;
}

// Scaffolding for the link, not part of the unit.
void Driver_6ab90(UnnamedNode_6ab90 *Node) { Node->Unlink(); }
