// Item 0023 (LTCG retry): Versus RVA 0x5e10, a constructor. Names are neutral;
// the evidence (two vtables, a destructible secondary base, a member object
// built from one argument) does not identify the Unreal classes.

// Pure interface at offset 0 (no vptr store of its own survives).
struct UnnamedInterface_5e10
{
	virtual void Method0() = 0;
};

// +0x08/+0x0c: the two constructor arguments.
struct UnnamedPair_5e10
{
	int Field08;
	int Field0C;
	UnnamedPair_5e10(int A, int B) : Field08(A), Field0C(B) {}
};

// +0x10: enabled flag plus one value.
struct UnnamedPairA_5e10
{
	int Enabled;
	int Value;
	UnnamedPairA_5e10() : Value(0) {}
};

// +0x18: enabled flag plus two values.
struct UnnamedPairB_5e10
{
	int Enabled;
	int Value;
	int Extra;
	UnnamedPairB_5e10() : Value(0), Extra(0) {}
};

// +0x10..+0x3b.
struct UnnamedState_5e10
{
	UnnamedPairA_5e10 First;
	UnnamedPairB_5e10 Second;
	int Field24;
	int Field28;
	int Field2C;
	int Field30;
	int Field34;
	int Field38;
	UnnamedState_5e10()
	{
		First.Enabled = 1;
		Second.Enabled = 1;
		Field24 = 0;
		Field28 = 0;
		Field2C = 0;
		Field30 = 0;
		Field34 = 0;
		Field38 = 0;
	}
};

// Secondary base at offset 4 (vtable 0x10c0dc2c).
struct UnnamedBase_5e10
{
	UnnamedPair_5e10 Pair;
	UnnamedState_5e10 State;
	UnnamedBase_5e10(int A, int B) : Pair(A, B) {}
	virtual ~UnnamedBase_5e10();
};

// Member at offset 0x3c, constructed by FUN_109046c0.
struct UnnamedMember_46c0
{
	int Data[3];
	UnnamedMember_46c0(int Arg);
	~UnnamedMember_46c0();
};

// Vtables 0x10c0e730 (offset 0) and 0x10c0e720 (offset 4).
struct UnnamedObject_5e10 : public UnnamedInterface_5e10, public UnnamedBase_5e10
{
	UnnamedMember_46c0 Member;
	int Field48;
	int Field4C;

	UnnamedObject_5e10(int A, int MemberArg, int B, int C);
	virtual void Method0();
	virtual ~UnnamedObject_5e10();
};

// Retail RVA 0x5e10. Link-time code generation gave it a custom convention:
// A in ECX, MemberArg in EDX, this, B and C on the stack (ret 0xc).
UnnamedObject_5e10::UnnamedObject_5e10(int A, int MemberArg, int B, int C)
: UnnamedBase_5e10(B, A), Member(MemberArg), Field48(C), Field4C(0)
{}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Where) { return Where; }
UnnamedObject_5e10 *Driver_5e10(void *Mem, int A, int M, int B, int C)
{
	return new (Mem) UnnamedObject_5e10(A, M, B, C);
}
UnnamedObject_5e10 *Driver2_5e10(void *Mem, int A, int M, int B, int C)
{
	return new (Mem) UnnamedObject_5e10(A, M, B, C);
}
