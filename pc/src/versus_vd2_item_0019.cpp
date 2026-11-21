// Work item 0019: Versus RVA 0x5940-0x59fe.
// Neutral names: no symbol evidence beyond the published record-deletion
// units (destroy_005890 is a stdcall record destructor).

struct Record_5940;

typedef void (__fastcall *RecordMethod)(Record_5940 *self);

// Vtable at 0x10c0df60 (only the slots used here are named).
struct Record_5940_Vtbl {
    RecordMethod slot[6];
};

struct Record_5940 {
    const Record_5940_Vtbl *vtbl; // 0x00
    int pad[3];                   // 0x04
    unsigned long flags;          // 0x10
};

extern const Record_5940_Vtbl Record_5940_vtable; // 0x10c0df60
void __stdcall destroy_005890(Record_5940 *self);

// Runs the base-part teardown when the scope ends (models the base
// destructor call the compiler places after the derived body).
struct BaseTeardown_5940 {
    Record_5940 *rec;
    ~BaseTeardown_5940() { destroy_005890(rec); }
};

// RVA 0x5940: derived record destructor; marks the record closed once and
// calls its close method (vtable slot 5) before the base teardown.
// The record handle is passed by value; MSVC destroys by-value arguments in
// the callee, so its destructor supplies the trailing base teardown.
void __stdcall destroy_005940(BaseTeardown_5940 base)
{
    base.rec->vtbl = &Record_5940_vtable;
    Record_5940 *self = base.rec;
    if (!(self->flags & 1)) {
        self->flags |= 1;
        Record_5940_vtable.slot[5](self);
    }
}

// RVA 0x59a0 (FUN_109059a0): not written. It receives its object in ESI with
// no stack or ECX argument (a constructor: calls FUN_10904cd0(self,
// DAT_10c91c10), then fills seven 3-dword sub-objects at +0x40..+0x88 with
// vtable 0x10c0f060 and zeros, then stores vtable 0x10c0df60 and returns
// self). That register convention is link-time-optimised code that cl cannot
// reproduce from a standalone unit.
