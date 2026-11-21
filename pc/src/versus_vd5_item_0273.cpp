// RVA 0xfc090: constructor of an unnamed polymorphic record (vtable at 0x10c03ef4).
// No evidence for the class name; neutral name used.
// LTCG custom convention: this in EAX, first argument in ECX, four on the stack.
typedef int INT;
typedef float FLOAT;

// Field B is a FLOAT: only then does LTCG pass just the first argument in ECX, as retail does.
class UnnamedClass_fc090
{
public:
    UnnamedClass_fc090(INT InA, FLOAT InB, INT InC, INT InD, INT InE);
    virtual void Func0();

    INT A;
    FLOAT B;
    INT C;
    INT D;
    INT E;
};

// Retail keeps this out of line.
#pragma auto_inline(off)
UnnamedClass_fc090::UnnamedClass_fc090(INT InA, FLOAT InB, INT InC, INT InD, INT InE)
    : A(InA), B(InB), C(InC), D(InD), E(InE)
{
}
#pragma auto_inline(on)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *P) { return P; }
void Driver_fc090(void *Mem, INT a, FLOAT b, INT c, INT d, INT e)
{
    Escape(new (Mem) UnnamedClass_fc090(a, b, c, d, e));
}
