// Work item 0061: Versus RVA 0xf570-0xf817.
// Only RVA 0xf780 uses a standard calling convention; the other five functions pass
// arguments in EAX/EBX/ESI (link-time-generated custom conventions) and are not
// reproduced here.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR*, const TCHAR*);

inline INT appStricmp(const TCHAR* A, const TCHAR* B) { return _wcsicmp(A, B); }

// Unreal Engine 2 FString (TArray<TCHAR>: Data, ArrayNum, ArrayMax).
class FString
{
public:
	TCHAR* Data;
	INT ArrayNum;
	INT ArrayMax;

	const TCHAR* operator*() const
	{
		return ArrayNum ? Data : L"";
	}
	UBOOL operator==(const FString& Other) const;
};

// RVA 0xf780: case-insensitive FString comparison.
UBOOL FString::operator==(const FString& Other) const
{
	return appStricmp(**this, *Other) == 0;
}
