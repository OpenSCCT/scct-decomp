// Work item 0226: Versus RVA 0x55c50-0x5600f.
// RVAs 0x55cf0, 0x55dc0, 0x55e30 and 0x55f20 are UArrayProperty vtable slots
// 27..30 (vtable 0x10d0d380). The two functions before them loop over Inner
// (0x58) Count (0x5c) times: by layout this is UFixedArrayProperty (name
// inferred from UE2, not from a label). Virtual names for slots 27, 36, 37
// are guesses from the argument shapes.
// Bit 31 of PropertyFlags selects an 8-byte array header (Data, Num) instead
// of the 12-byte FArray (Data, Num, Max); the name CPF_CompactArray is ours.

typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef short SWORD;

#define CPF_CompactArray 0x80000000

class UObject;
class UProperty;

class FMalloc
{
public:
	virtual void *Malloc(DWORD Count, const unsigned short *Tag);
	virtual void *Realloc(void *Original, DWORD Count, const unsigned short *Tag);
	virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArchive
{
public:
	virtual ~FArchive();
	virtual void Serialize(void *V, INT Length);
	virtual void SerializeBits(void *V, INT LengthBits);
	virtual void SerializeInt(DWORD &Value, DWORD Max);
	virtual void Preload(UObject *Object);
	UBOOL IsLoading() { return ArIsLoading; }
	UBOOL IsSaving() { return ArIsSaving; }
	friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
	DWORD ArVer;
	DWORD ArNetVer;
	DWORD ArLicenseeVer;
	UBOOL ArIsLoading;        // 0x10
	UBOOL ArIsSaving;         // 0x14
};

struct FCompactIndex { INT Value; };
FArchive &operator<<(FArchive &Ar, FCompactIndex &I);
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

// 12-byte dynamic array.
class FArray
{
public:
	void *Data;
	INT ArrayNum;
	INT ArrayMax;
	void Empty()
	{
		ArrayNum = 0;
		if (Data) { GMalloc->Free(Data); Data = 0; ArrayMax = 0; }
	}
	INT __stdcall AddZeroed(INT ElementSize, INT Count); // LTCG: this on the stack
};

// 8-byte dynamic array (no ArrayMax); FSArray after the retail tag "FSArray::Add".
class FSArray
{
public:
	void *Data;
	INT ArrayNum;
	void Empty()
	{
		ArrayNum = 0;
		if (Data) { GMalloc->Free(Data); Data = 0; }
	}
	INT __stdcall AddZeroed(INT ElementSize, INT Count); // LTCG: this on the stack
};

class UObject
{
public:
	virtual void Virtual00();
	virtual void Virtual01();
	virtual void Virtual02();
	virtual void Virtual03();
	virtual void Virtual04();
	virtual void Virtual05();
	virtual void Virtual06();
	virtual void Virtual07();
	virtual void Virtual08();
	virtual void Virtual09();
	virtual void Virtual10();
	virtual void Virtual11();
	virtual void Virtual12();
	virtual void Virtual13();
	virtual void Virtual14();
	virtual void Virtual15();
	virtual void Virtual16();
	virtual void Virtual17();
	virtual void Virtual18();
	virtual void Virtual19();
	virtual void Virtual20();
	virtual void Virtual21();
	virtual void Virtual22();
	virtual void Virtual23();
	virtual void Virtual24();
	virtual void Virtual25();
	virtual INT GetPropertiesSize();      // 0x68, UStruct

	DWORD Fields04[5];
	UObject *Outer;           // 0x18
	DWORD Fields1C[3];
};

class UField : public UObject
{
public:
	UField *SuperField;       // 0x28
	UField *Next;             // 0x2c
};

class UProperty : public UField
{
public:
	SWORD ArrayDim;           // 0x30
	SWORD ElementSize;        // 0x32
	DWORD PropertyFlags;      // 0x34
	INT Category;             // 0x38
	INT Offset;               // 0x3c
	DWORD Fields40[6];

	virtual void CleanupDestroyed(BYTE *Data);                          // 0x6c
	virtual INT Link(FArchive &Ar, UProperty *Prev);                     // 0x70
	virtual UBOOL Identical(const void *A, const void *B);              // 0x74
	virtual void SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes); // 0x78
	virtual void Virtual31();
	virtual void Virtual32();
	virtual void Virtual33();
	virtual void Virtual34();
	virtual void Virtual35();
	virtual void CopyCompleteValue(void *Dest, void *Src, UObject *SuperObject); // 0x90
	virtual void DestroyValue(void *Dest);                              // 0x94
};

class UArrayProperty : public UProperty
{
public:
	UProperty *Inner;         // 0x58

	INT ArrayNum(const void *A)
	{
		return (PropertyFlags & CPF_CompactArray) ? ((FSArray *)A)->ArrayNum : ((FArray *)A)->ArrayNum;
	}
	BYTE *ArrayData(const void *A)
	{
		return (PropertyFlags & CPF_CompactArray) ? (BYTE *)((FSArray *)A)->Data : (BYTE *)((FArray *)A)->Data;
	}
	void CleanupDestroyed(BYTE *Data);
	INT Link(FArchive &Ar, UProperty *Prev);
	UBOOL Identical(const void *A, const void *B);
	void SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes);
};

class UFixedArrayProperty : public UProperty
{
public:
	UProperty *Inner;         // 0x58
	INT Count;                // 0x5c

	void CopyCompleteValue(void *Dest, void *Src, UObject *SuperObject);
	void DestroyValue(void *Dest);
};

// 0x55c50
void UFixedArrayProperty::CopyCompleteValue(void *Dest, void *Src, UObject *SuperObject)
{
	for (INT i = 0; i < Count; i++)
		Inner->CopyCompleteValue((BYTE *)Dest + i * Inner->ElementSize, Src ? (BYTE *)Src + i * Inner->ElementSize : 0, 0);
}

// 0x55cb0
void UFixedArrayProperty::DestroyValue(void *Dest)
{
	for (INT i = 0; i < Count; i++)
		Inner->DestroyValue((BYTE *)Dest + i * Inner->ElementSize);
}

// 0x55cf0
void UArrayProperty::CleanupDestroyed(BYTE *Data)
{
	if (PropertyFlags & CPF_CompactArray)
	{
		INT Size = Inner->ElementSize * Inner->ArrayDim;
		for (INT i = 0; i < ArrayDim; i++, Data += ElementSize)
		{
			BYTE *P = (BYTE *)((FSArray *)Data)->Data;
			for (INT j = ((FSArray *)Data)->ArrayNum; j > 0; j--, P += Size)
				Inner->CleanupDestroyed(P);
		}
	}
	else
	{
		INT Size = Inner->ElementSize * Inner->ArrayDim;
		for (INT i = 0; i < ArrayDim; i++, Data += ElementSize)
		{
			BYTE *P = (BYTE *)((FArray *)Data)->Data;
			for (INT j = ((FArray *)Data)->ArrayNum; j > 0; j--, P += Size)
				Inner->CleanupDestroyed(P);
		}
	}
}

// 0x55dc0
INT UArrayProperty::Link(FArchive &Ar, UProperty *Prev)
{
	Ar.Preload(Inner);
	Inner->Link(Ar, 0);
	ElementSize = (PropertyFlags & CPF_CompactArray) ? sizeof(FSArray) : sizeof(FArray);
	Offset = (Outer->GetPropertiesSize() + 3) & ~3;
	if (!(PropertyFlags & 0x1000))
		PropertyFlags |= 0x400000;
	return Offset - Outer->GetPropertiesSize();
}

// 0x55e30 (near: 75 bytes differ; retail keeps A in ESI across the flag test
// and gives the FArray arm its own registers, which no tried form reproduces)
UBOOL UArrayProperty::Identical(const void *A, const void *B)
{
	INT n;
	BYTE *P, *Q;
	if (PropertyFlags & CPF_CompactArray)
	{
		n = ((FSArray *)A)->ArrayNum;
		if (n != (B ? ((FSArray *)B)->ArrayNum : 0))
			return 0;
		P = (BYTE *)((FSArray *)A)->Data;
		Q = B ? (BYTE *)((FSArray *)B)->Data : 0;
	}
	else
	{
		if ((n = ((FArray *)A)->ArrayNum) != (B ? ((FArray *)B)->ArrayNum : 0))
			return 0;
		P = (BYTE *)((FArray *)A)->Data;
		Q = B ? (BYTE *)((FArray *)B)->Data : 0;
	}
	INT Size = Inner->ElementSize;
	if (Q)
	{
		for (INT i = 0; i < n; i++, P += Size, Q += Size)
			if (!Inner->Identical(P, Q))
				return 0;
	}
	else
	{
		for (INT i = 0; i < n; i++, P += Size)
			if (!Inner->Identical(P, 0))
				return 0;
	}
	return 1;
}

// 0x55f20
void UArrayProperty::SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes)
{
	INT Size = Inner->ElementSize;
	INT n;
	if (PropertyFlags & CPF_CompactArray)
	{
		FSArray *Array = (FSArray *)Value;
		n = Array->ArrayNum;
		Ar << AR_INDEX(n);
		if (Ar.IsLoading())
		{
			Array->Empty();
			Array->AddZeroed(Size, n);
		}
	}
	else
	{
		FArray *Array = (FArray *)Value;
		n = Array->ArrayNum;
		Ar << AR_INDEX(n);
		if (Ar.IsLoading())
		{
			Array->Empty();
			Array->AddZeroed(Size, n);
		}
	}
	BYTE *P = (BYTE *)((FArray *)Value)->Data;
	INT ElementMax = (MaxReadBytes > 0 && n) ? MaxReadBytes / n : 0;
	for (INT i = 0; i < n; i++, P += Size)
		Inner->SerializeItem(Ar, P, ElementMax);
}

// ---- Stand-in for a callee of another unit, defined so the link gives it
// its retail register convention (archive in ESI, index in EDI). Copied from
// item 0136/0116. Not part of this unit's match. ----
// 0x1ea40
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
	if (!Ar.IsLoading() && !Ar.IsSaving()) {
		Ar.Serialize(&I.Value, 4);
	} else {
		INT Original = I.Value;
		DWORD V = Original >= 0 ? Original : -Original;
		BYTE B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
		I.Value = 0;
		Ar << B0;
		if (B0 & 0x40) {
			V >>= 6;
			BYTE B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
			Ar << B1;
			if (B1 & 0x80) {
				V >>= 7;
				BYTE B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
				Ar << B2;
				if (B2 & 0x80) {
					V >>= 7;
					BYTE B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
					Ar << B3;
					if (B3 & 0x80) {
						V >>= 7;
						BYTE B4 = V;
						Ar << B4;
						I.Value = B4;
					}
					I.Value = (I.Value << 7) + (B3 & 0x7f);
				}
				I.Value = (I.Value << 7) + (B2 & 0x7f);
			}
			I.Value = (I.Value << 7) + (B1 & 0x7f);
		}
		I.Value = (I.Value << 6) + (B0 & 0x3f);
		if (B0 & 0x80)
			I.Value = -I.Value;
	}
	return Ar;
}

// Scaffolding for the LTCG link, not part of the unit: constructing the
// classes emits their vtables, which reference the virtuals above.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
void Driver_55f20(void *Mem1, void *Mem2)
{
	Escape(&GMalloc);
	Escape(new(Mem1) UArrayProperty);
	Escape(new(Mem2) UFixedArrayProperty);
}
