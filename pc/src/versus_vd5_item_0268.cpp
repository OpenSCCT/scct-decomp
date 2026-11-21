// Work item 0268: two LTCG helpers at RVA 0xf8d10 / 0xf8d50.
// Neutral names: no symbol evidence. Each tests whether an object's
// referenced record (+0x24) is the global record, or its counter (+0x110)
// is a multiple of the global record's period (+0x10c).
typedef unsigned long DWORD;
typedef DWORD UBOOL;

struct UnnamedRecord_f8d10
{
    char Pad0[0x10c];
    DWORD Period;     // 0x10c
    DWORD Counter;    // 0x110
};

struct UnnamedObject_f8d10
{
    char Pad0[0x24];
    UnnamedRecord_f8d10 *Record; // 0x24
};

struct UnnamedClass_f8d10
{
    __declspec(noinline) UBOOL CheckA(UnnamedObject_f8d10 *Obj);
    __declspec(noinline) UBOOL CheckB(UnnamedObject_f8d10 *Obj);
};

extern UnnamedRecord_f8d10 *GRecord_c92420;
extern UnnamedRecord_f8d10 *GRecord_c9241c;

UBOOL UnnamedClass_f8d10::CheckA(UnnamedObject_f8d10 *Obj)
{
    if (GRecord_c92420)
    {
        if (Obj->Record != GRecord_c92420)
            return Obj->Record->Counter % GRecord_c92420->Period == 0;
        return 1;
    }
    return 0;
}

UBOOL UnnamedClass_f8d10::CheckB(UnnamedObject_f8d10 *Obj)
{
    if (GRecord_c9241c)
    {
        if (Obj->Record != GRecord_c9241c)
            return Obj->Record->Counter % GRecord_c9241c->Period == 0;
        return 1;
    }
    return 0;
}

// Scaffolding for the link, not part of the unit (several callers keep the
// helpers out of line, as in retail).
void Escape(void *);
void Use(UBOOL);
void Driver_f8d10(UnnamedClass_f8d10 *C, UnnamedObject_f8d10 *O, UnnamedObject_f8d10 *P, UnnamedObject_f8d10 *Q)
{
    Escape(&GRecord_c92420);
    Use(C->CheckA(O)); Use(C->CheckA(P)); Use(C->CheckA(Q));
}
void Driver_f8d50(UnnamedClass_f8d10 *C, UnnamedObject_f8d10 *O, UnnamedObject_f8d10 *P, UnnamedObject_f8d10 *Q)
{
    Escape(&GRecord_c9241c);
    Use(C->CheckB(O)); Use(C->CheckB(P)); Use(C->CheckB(Q));
}
