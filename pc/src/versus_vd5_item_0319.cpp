/*
 * Work item 0319 (wave 3): Versus RVA 0x10a6c0-0x10a839.
 *
 * All four functions come from an object compiled with /GL and linked with
 * /LTCG (register or stack-this calling conventions, no prologue on the
 * thiscall ones). Class names are neutral: no vtable labels or strings tie
 * them to a known Unreal class.
 *
 *  0x10a6c0  operator<<(FArchive&, UnnamedMip_a6c0&)   Ar in ESI, struct in EDI
 *  0x10a730  UnnamedResource_a730 constructor           this on stack, ret 0x14
 *  0x10a7c0  UnnamedStrings_a7c0 constructor            this in EAX
 *  0x10a7e0  UnnamedStrings_a7c0 destructor             this on stack, ret 4
 *
 * Status (try_ltcg.py, /O2 /Gy /GX): 0x10a730, 0x10a7c0, 0x10a7e0 match.
 * 0x10a6c0 is a near miss: every instruction from the third Serialize call
 * on matches, but this link passes Ar in EAX (saved into ESI) instead of ESI
 * and gives the 0x9e5b80 TLazyArray serializer Ar in ESI instead of ECX.
 * Retail's choice probably depends on the real 0x9e5b80 body (TLazyArray
 * operator<<, about 490 bytes) and its other callers; the stand-in body
 * here only gives the linker something to choose a convention for.
 */
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef DWORD UBOOL;

#pragma pack(push, 4)   /* Unreal builds use 4-byte packing (/Zp4) */

inline void *operator new(unsigned int, void *Mem) { return Mem; }

class FArchive
{
public:
	virtual ~FArchive();
	virtual void Serialize(void *V, INT Length);      /* vtable +0x04 */
	virtual void V08(); virtual void V0c(); virtual void V10(); virtual void V14();
	virtual void V18(); virtual void V1c(); virtual void V20(); virtual void V24();
	virtual void V28(); virtual void V2c(); virtual void V30(); virtual void V34();
	virtual void V38(); virtual void V3c();
	virtual void V40(void *P);                         /* vtable +0x40 */
	INT ArVer;                                         /* +0x04 */
	INT ArPad[2];
	INT ArIsLoading;                                   /* +0x10 */
};

class FString
{
public:
	TCHAR *Data;
	INT    ArrayNum;
	INT    ArrayMax;
	FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
	~FString();                                       /* 0x48b0 */
};

/* 0x9e5b80: LTCG convention, Ar in ECX, object in EAX. Defined so the
 * linker picks a register convention; its body is not part of this unit. */
struct UnnamedPair_a6c0 { DWORD Data; INT Num; INT Max; BYTE Pad[12]; };
__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedPair_a6c0 &P)
{
	INT SeekPos = 0;
	if (Ar.ArIsLoading)
	{
		if (Ar.ArVer <= 0x3d)
		{
			Ar.V40(&P);
			Ar.Serialize(&SeekPos, 4);
			Ar.V28();
			return Ar;
		}
		Ar.Serialize(&SeekPos, 4);
		Ar.V40(&P);
		Ar.V3c();
		return Ar;
	}
	Ar.V28();
	Ar.Serialize(&P.Num, 4);
	Ar.V3c();
	return Ar;
}

/* 0x12050 (published as CeilLog2_12050). */
__declspec(noinline) BYTE CeilLog2_12050(DWORD N)
{
	BYTE Bits = 0;
	while ((1u << Bits) < N)
		Bits++;
	return Bits;
}

struct UnnamedMip_a6c0
{
	DWORD             Unknown00;
	UnnamedPair_a6c0  A;          /* +0x04 */
	UnnamedPair_a6c0  B;          /* +0x1c */
	BYTE              Format;     /* +0x34 */
	INT               USize;      /* +0x38 */
	INT               VSize;      /* +0x3c */
	DWORD             Unknown40[2];
	INT               Unknown48;  /* +0x48 */
	BYTE              UBits;      /* +0x4c */
	BYTE              VBits;      /* +0x4d */
};

/* 0x10a6c0 */
__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedMip_a6c0 &M)
{
	Ar << M.A;
	Ar << M.B;
	Ar.Serialize(&M.Format, 1);
	Ar.Serialize(&M.USize, 4);
	Ar.Serialize(&M.VSize, 4);
	Ar.Serialize(&M.Unknown48, 4);
	M.UBits = CeilLog2_12050(M.USize);
	M.VBits = CeilLog2_12050(M.VSize);
	return Ar;
}

/* 0x10a250: render-resource base constructor (vtable, cache id from a
 * global counter). LTCG gave it this in ESI. */
extern unsigned __int64 GUnnamedCacheCounter_a250;
class UnnamedBase_a250
{
public:
	DWORD Unknown04, Unknown08, Unknown0C;
	unsigned __int64 CacheId;    /* +0x10 */
	INT Revision;                /* +0x18 */
	__declspec(noinline) UnnamedBase_a250()
	{
		Unknown04 = Unknown08 = Unknown0C = 0;
		CacheId = GUnnamedCacheCounter_a250++ * 0x100 + 0xe1;
		Revision = 0;
	}
	virtual ~UnnamedBase_a250();
};

class UnnamedObject_a730
{
public:
	virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
	virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
	virtual void V08(); virtual void V09(); virtual void V0a(); virtual void V0b();
	virtual void V0c(); virtual void V0d(); virtual void V0e(); virtual void V0f();
	virtual void V10(); virtual void V11(); virtual void V12(); virtual void V13();
	virtual void V14(); virtual void V15(); virtual void V16(); virtual void V17();
	virtual void V18(); virtual void V19(); virtual void V1a(); virtual void V1b();
	virtual void V1c(); virtual void V1d(); virtual void V1e(); virtual void V1f();
	virtual UBOOL Test80();                          /* vtable +0x80 */
};

struct UnnamedMember_a730
{
	INT A, B;
	UnnamedMember_a730() : A(0), B(0) {}
	~UnnamedMember_a730();
};

class __declspec(novtable) UnnamedResource_a730 : public UnnamedBase_a250
{
public:
	INT                  Unknown1c;
	UnnamedObject_a730  *Object;     /* +0x20 */
	DWORD                Flags;      /* +0x24 */
	INT                  Unknown28;
	INT                  Unknown2c;
	UnnamedMember_a730   Member;     /* +0x30 */

	UnnamedResource_a730(UnnamedObject_a730 *InObject, DWORD InFlags, INT In28, INT In2c);
};

/* 0x10a730 */
UnnamedResource_a730::UnnamedResource_a730(UnnamedObject_a730 *InObject, DWORD InFlags, INT In28, INT In2c)
	: Unknown1c(0), Object(InObject), Flags(InFlags), Unknown28(In28), Unknown2c(In2c)
{
	if (Object->Test80())
		Flags |= 0x80000;
	else
		Flags &= ~0x80000;
}

/* 0x10a7c0 / 0x10a7e0 */
class UnnamedStrings_a7c0
{
public:
	DWORD   Unknown00[5];
	FString S14;
	FString S20;
	FString S2c;
	__declspec(noinline) UnnamedStrings_a7c0() {}
	~UnnamedStrings_a7c0() {}
};

#pragma pack(pop)

/* Scaffolding for the link, not part of the unit. */
void Escape(void *);
void Driver_10a6c0(FArchive &Ar, UnnamedMip_a6c0 &M) { Ar << M; }
void Driver_10a730(void *Mem, UnnamedObject_a730 *O, DWORD F, INT A, INT B)
{
	new (Mem) UnnamedResource_a730(O, F, A, B);
}
void Driver_10a7c0(void *Mem) { new (Mem) UnnamedStrings_a7c0; }
void Driver_10a7e0(UnnamedStrings_a7c0 *S) { S->~UnnamedStrings_a7c0(); }
