// Work item 0150: Versus RVA 0x402b0-0x40540.
// Unreal Engine 2 builds with 4-byte structure packing (/Zp4).
#pragma pack(push, 4)
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned __int64 QWORD;

extern TCHAR GEmptyTCHAR[]; // 0x10c10928, the empty string ""

class FArray
{
public:
	void* Data;
	INT ArrayNum;
	INT ArrayMax;
};

template<class T> inline T Clamp(T X, T Min, T Max)
{
	return X < Min ? Min : X < Max ? X : Max;
}

class FString : protected FArray
{
public:
	FString(const TCHAR* In);
	~FString();
	const TCHAR* operator*() const
	{
		return ArrayNum ? (const TCHAR*)Data : GEmptyTCHAR;
	}
	INT Len() const
	{
		return ArrayNum ? ArrayNum - 1 : 0;
	}
	FString Right(INT Count) const;
};

// RVA 0x40310
FString FString::Right(INT Count) const
{
	return FString(**this + Len() - Clamp(Count, 0, Len()));
}

enum { NAME_PROBEMIN = 300, NAME_PROBEMAX = 364 };

class FName
{
public:
	INT Index;
	INT GetIndex() const { return Index; }
};

struct FStateFrame
{
	char Pad[0x1c];
	QWORD ProbeMask;
};

class UObject
{
public:
	virtual ~UObject();
	INT Index;
	UObject* HashNext;
	FStateFrame* StateFrame;
	UBOOL IsProbing(FName ProbeName);
};

// RVA 0x40450
UBOOL UObject::IsProbing(FName ProbeName)
{
	return ProbeName.GetIndex() < NAME_PROBEMIN
		|| ProbeName.GetIndex() >= NAME_PROBEMAX
		|| !StateFrame
		|| (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
}
#pragma pack(pop)
