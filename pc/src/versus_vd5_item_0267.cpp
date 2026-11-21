// Work item 0267: six LTCG helpers at RVA 0xf8b90..0xf8cd0.
// Each tests whether an object's owner (field 0x24) is a given global entry,
// or whether the owner's counter at 0x110 is a multiple of that entry's period
// at 0x10c. Retail calls them from the list-sorting code around 0xf5100: the
// lists object is pushed as `this` (unused) and the tested object arrives in
// EAX. The same test for 0x10c9241c and 0x10c92420 is inlined into that caller.
// Names are neutral: the globals and classes are unidentified.
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef int INT;

struct UnnamedPeriodic
{
    char Pad000[0x10c];
    DWORD Period;        // 0x10c
    DWORD Counter;       // 0x110
};

struct UnnamedOwned
{
    char Pad000[0x24];
    UnnamedPeriodic *Owner; // 0x24
};

extern UnnamedPeriodic *GUnnamed_10c9241c;
extern UnnamedPeriodic *GUnnamed_10c92420;
extern UnnamedPeriodic *GUnnamed_10c92424;
extern UnnamedPeriodic *GUnnamed_10c92428;
extern UnnamedPeriodic *GUnnamed_10c9242c;
extern UnnamedPeriodic *GUnnamed_10c92430;
extern UnnamedPeriodic *GUnnamed_10c92434;
extern UnnamedPeriodic *GUnnamed_10c92438;

struct UnnamedList { UnnamedOwned **Data; INT Num, Max; INT Add(INT Count, INT Size); };

struct UnnamedLists_f5100
{
    char Pad000[0x5c];
    UnnamedList Lists[8];

    UBOOL Test_41c(UnnamedOwned *Obj);
    UBOOL Test_420(UnnamedOwned *Obj);
    UBOOL Test_f8b90(UnnamedOwned *Obj);
    UBOOL Test_f8bd0(UnnamedOwned *Obj);
    UBOOL Test_f8c10(UnnamedOwned *Obj);
    UBOOL Test_f8c50(UnnamedOwned *Obj);
    UBOOL Test_f8c90(UnnamedOwned *Obj);
    UBOOL Test_f8cd0(UnnamedOwned *Obj);
};

#define DEFINE_PERIODIC_TEST(Name, Global) \
UBOOL UnnamedLists_f5100::Name(UnnamedOwned *Obj) \
{ \
    if (Global) \
    { \
        if (Obj->Owner != Global) \
            return Obj->Owner->Counter % Global->Period == 0; \
        return 1; \
    } \
    return 0; \
}

DEFINE_PERIODIC_TEST(Test_41c, GUnnamed_10c9241c)
DEFINE_PERIODIC_TEST(Test_420, GUnnamed_10c92420)
DEFINE_PERIODIC_TEST(Test_f8b90, GUnnamed_10c92438)
DEFINE_PERIODIC_TEST(Test_f8bd0, GUnnamed_10c92434)
DEFINE_PERIODIC_TEST(Test_f8c10, GUnnamed_10c92430)
DEFINE_PERIODIC_TEST(Test_f8c50, GUnnamed_10c9242c)
DEFINE_PERIODIC_TEST(Test_f8c90, GUnnamed_10c92428)
DEFINE_PERIODIC_TEST(Test_f8cd0, GUnnamed_10c92424)

// Scaffolding for the link, not part of the unit: mimics the retail caller
// around 0xf5100, which inlines the first two tests and calls the rest.
void Escape(void *);
inline void AddTo(UnnamedList &A, UnnamedOwned *O) { A.Data[A.Add(1, 4)] = O; }
void Driver_f5100(UnnamedLists_f5100 *L, UnnamedOwned *O)
{
    Escape(&GUnnamed_10c9241c); Escape(&GUnnamed_10c92420); Escape(&GUnnamed_10c92438);
    Escape(&GUnnamed_10c92434); Escape(&GUnnamed_10c92430); Escape(&GUnnamed_10c9242c);
    Escape(&GUnnamed_10c92428); Escape(&GUnnamed_10c92424);
    if (L->Test_41c(O)) AddTo(L->Lists[0], O);
    else if (L->Test_420(O)) AddTo(L->Lists[1], O);
    else if (L->Test_f8cd0(O)) AddTo(L->Lists[2], O);
    else if (L->Test_f8c90(O)) AddTo(L->Lists[3], O);
    else if (L->Test_f8c50(O)) AddTo(L->Lists[4], O);
    else if (L->Test_f8c10(O)) AddTo(L->Lists[5], O);
    else if (L->Test_f8bd0(O)) AddTo(L->Lists[6], O);
    else if (L->Test_f8b90(O)) AddTo(L->Lists[7], O);
}
// Second scaffolding caller with the order reversed, so the linker keeps
// Test_f8cd0 out of line as retail does.
void Driver_f8cd0(UnnamedLists_f5100 *L, UnnamedOwned *O)
{
    Escape(&GUnnamed_10c9241c); Escape(&GUnnamed_10c92420); Escape(&GUnnamed_10c92438);
    Escape(&GUnnamed_10c92434); Escape(&GUnnamed_10c92430); Escape(&GUnnamed_10c9242c);
    Escape(&GUnnamed_10c92428); Escape(&GUnnamed_10c92424);
    if (L->Test_41c(O)) AddTo(L->Lists[0], O);
    else if (L->Test_420(O)) AddTo(L->Lists[1], O);
    else if (L->Test_f8b90(O)) AddTo(L->Lists[7], O);
    else if (L->Test_f8bd0(O)) AddTo(L->Lists[6], O);
    else if (L->Test_f8c10(O)) AddTo(L->Lists[5], O);
    else if (L->Test_f8c50(O)) AddTo(L->Lists[4], O);
    else if (L->Test_f8c90(O)) AddTo(L->Lists[3], O);
    else if (L->Test_f8cd0(O)) AddTo(L->Lists[2], O);
}
