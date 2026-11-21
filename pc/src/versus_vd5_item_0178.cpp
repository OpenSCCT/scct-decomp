// Work item 0178: RVA 0xdfcb0, LTCG function (this in ESI).
// Class and member names are neutral: no vtable label or string evidence.
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;

class UnnamedNode_dfcb0 {
public:
    virtual ~UnnamedNode_dfcb0();
    char Pad04[0x50 - 0x04];
    UnnamedNode_dfcb0 *Next;    // 0x50
    char Pad54[0x71 - 0x54];
    BYTE Dirty;                 // 0x71
    BYTE Pad72;
    BYTE bDone;                 // 0x73
};

struct UnnamedCounter_dfcb0 {
    char Pad00[0xb8];
    INT Num;                    // 0xb8
};

class UnnamedOwner_dfcb0 {
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Flush(INT Force);  // vtable +0xc
    char Pad04[0x28 - 0x04];
    UnnamedCounter_dfcb0 *Counter;  // 0x28
    char Pad2c[0x38 - 0x2c];
    INT Count;                      // 0x38
    char Pad3c[0x44 - 0x3c];
    UnnamedNode_dfcb0 *Head;        // 0x44
    char Pad48[0x56 - 0x48];
    _WORD Flags;                    // 0x56

    void ReleaseDone();
};

void UnnamedOwner_dfcb0::ReleaseDone()
{
    INT Dirty = 0;
    while (Head && Head->bDone) {
        Dirty |= Head->Dirty;
        UnnamedNode_dfcb0 *Node = Head;
        Head = Head->Next;
        delete Node;
        Count--;
        Counter->Num--;
    }
    if (Dirty || ((Flags & 1) && (Flags & 0x10)))
        Flush(1);
}

// Scaffolding for the link, not part of the unit.
void Driver_dfcb0(UnnamedOwner_dfcb0 *O) { O->ReleaseDone(); }
