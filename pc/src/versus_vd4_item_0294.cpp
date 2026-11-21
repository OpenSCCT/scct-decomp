// Item 0294: RVA 0x78220. Class and member names are neutral guesses
// (no vtable label or string evidence ties them to Unreal names).
// Built in an LTCG object: the record helper at 0x6cc60 takes its
// record in EBX.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

void appMemcpy(void *Dest, const void *Src, INT Count);   // retail 0x40a0

// Interface at owner+0x46a4; its methods take `this` on the stack.
struct UnnamedNotify_46a4 {
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26(); virtual void Slot27();
    virtual void Slot28(); virtual void Slot29(); virtual void Slot30(); virtual void Slot31();
    virtual void Slot32(); virtual void Slot33(); virtual void Slot34(); virtual void Slot35();
    virtual void Slot36();
    virtual void __stdcall SetText(INT Index, const char *Text);              // +0x94
    virtual void Slot38(); virtual void Slot39(); virtual void Slot40(); virtual void Slot41();
    virtual void Slot42(); virtual void Slot43(); virtual void Slot44(); virtual void Slot45();
    virtual void Slot46(); virtual void Slot47(); virtual void Slot48(); virtual void Slot49();
    virtual void Slot50(); virtual void Slot51(); virtual void Slot52(); virtual void Slot53();
    virtual void Slot54(); virtual void Slot55(); virtual void Slot56(); virtual void Slot57();
    virtual void Slot58(); virtual void Slot59(); virtual void Slot60(); virtual void Slot61();
    virtual void Slot62();
    virtual void __stdcall SetChannel(DWORD Index, INT Kind, DWORD Value);    // +0xfc
};

struct UnnamedOwner_108;

struct UnnamedChannel {          // 0x34 bytes, array at record+0x958
    DWORD Value;                 // +0x00
    DWORD Pad04[2];
    DWORD Active;                // +0x0c
    DWORD Pad10[9];
};

// Sub-record at owner+0x2fb58.
struct UnnamedRecord_2fb58 {
    UnnamedOwner_108 *Owner;     // +0x000
    char Pad004[0x204];
    char Names[11][0x40];          // +0x208
    DWORD Flags;                 // +0x4c8
    char Pad4cc[0x958 - 0x4cc];
    UnnamedChannel Channels[1];  // +0x958

    void SetName(INT Index, const char *Text)
    {
        appMemcpy(Names[Index], Text, 0x40);
        Flags |= 1 << Index;
    }
    void SetFlag(INT Index) { Flags |= 1 << Index; }
    void ResetChannels();        // retail 0x6cc60
};

struct UnnamedOwner_108 {
    char Pad0[0x41d0];
    DWORD NumChannels;              // +0x41d0
    char Pad1[0x46a4 - 0x41d4];
    UnnamedNotify_46a4 *Notifier;   // +0x46a4
    char Pad2[0x2fb58 - 0x46a8];
    UnnamedRecord_2fb58 Record;     // +0x2fb58
};

struct UnnamedNameHolder {
    char Pad0[0xb8];
    char Name[0x40];                // +0xb8
};

struct UnnamedSource_78220 {
    char Pad0[0x108];
    UnnamedOwner_108 *Owner;        // +0x108
    char Pad1[0x2af10 - 0x10c];
    UnnamedNameHolder *NameHolder;  // +0x2af10
};

struct UnnamedClass_78220 {
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10();
    virtual void Finish(UnnamedSource_78220 *Src); // +0x2c
    void Apply(UnnamedSource_78220 *Src);
};

void UnnamedClass_78220::Apply(UnnamedSource_78220 *Src)
{
    Src->Owner->Record.SetName(9, Src->NameHolder->Name);
    Src->Owner->Notifier->SetText(3, Src->NameHolder->Name);
    Src->Owner->Record.SetFlag(10);
    Src->Owner->Record.ResetChannels();
    Finish(Src);
}

// Scaffolding for the link, not part of the unit (retail 0x6cc60 lives in
// another item; modelled here so the linker picks its EBX convention).
__declspec(noinline) void UnnamedRecord_2fb58::ResetChannels()
{
    for (DWORD i = 0; i < Owner->NumChannels; i++) {
        UnnamedChannel &C = Channels[i];
        if (C.Value != i) {
            Owner->Notifier->SetChannel(i, 0xb, i);
            C.Value = i;
        }
        if (C.Active) {
            Owner->Notifier->SetChannel(i, 0x18, 0);
            C.Active = 0;
        }
    }
}
void Escape(void *);
typedef void (UnnamedClass_78220::*ApplyFn)(UnnamedSource_78220 *);
void Driver_78220(UnnamedClass_78220 *C, UnnamedSource_78220 *S) { ApplyFn F = &UnnamedClass_78220::Apply; Escape(&F); C->Apply(S); }
