// RVA 0x15b50: constructor of a small settings object that asks its owner to
// fill it in (LTCG: this on the stack, Owner in ECX, ret 4). Class names are neutral: no labels identify them.
typedef int INT;

// Non-polymorphic base with a destructor (gives the exception frame).
struct UnnamedBase_15b50
{
    INT A, B, C, D, E, F, G, H, I, J, K, L, M, N, O;
    UnnamedBase_15b50()
        : A(0xaf), B(2000), C(0), D(0), E(0), F(0), G(0),
          H(1), I(1), J(1), K(0), L(0), M(3), N(0), O(-1) {}
    ~UnnamedBase_15b50();
};

// Polymorphic derived: vtable at 0 (0x10c0cd40), base at 4.
class UnnamedClass_15b50;
struct UnnamedResult_15b50 : UnnamedBase_15b50
{
    INT P, Q;
    UnnamedResult_15b50(UnnamedClass_15b50 *Owner);
    virtual ~UnnamedResult_15b50();
};

class UnnamedClass_15b50
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0C();
    virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1C();
    virtual void V20(); virtual void V24();
    virtual void Fill(UnnamedResult_15b50 &Out);
};

// The derived constructor asks the owner to fill the new object in.
UnnamedResult_15b50::UnnamedResult_15b50(UnnamedClass_15b50 *Owner)
    : P(0), Q(0)
{
    Owner->Fill(*this);
}

// Scaffolding for the link, not part of the unit.
void Use_15b50(UnnamedResult_15b50 &);
void Driver_15b50(UnnamedClass_15b50 *Owner)
{
    UnnamedResult_15b50 R(Owner);
    Use_15b50(R);
}
