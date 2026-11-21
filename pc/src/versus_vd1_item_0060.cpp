// Work item 0060: Core string/math helpers (UnMisc / UnVcWin32 style).
// Names follow Unreal Engine 2 conventions (appTimestamp, appSRand, appFloor,
// appRound, appSprintf); the matching behaviour is identical to UE2's
// published implementations.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef char* va_list;

extern "C" __declspec(dllimport) TCHAR* __cdecl _wstrdate(TCHAR*);
extern "C" __declspec(dllimport) TCHAR* __cdecl _wstrtime(TCHAR*);
extern "C" __declspec(dllimport) TCHAR* __cdecl wcscat(TCHAR*, const TCHAR*);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR*);
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf(TCHAR*, unsigned int, const TCHAR*, va_list);

extern INT GSRandSeed;
extern FLOAT GSRandTemp; // 1.0f, at 0x10c71320

inline INT appTrunc(double F) { return (INT)F; }
inline INT appFloorInline(FLOAT F) { return appTrunc(floor(F)); }
inline FLOAT appFractional(FLOAT Value) { return Value - appFloorInline(Value); }

// RVA 0xf3e0
const TCHAR* appTimestamp()
{
	static TCHAR Result[1024];
	*Result = 0;
	_wstrdate(Result);
	wcscat(Result, (const TCHAR*)L" ");
	_wstrtime(Result + wcslen(Result));
	return Result;
}

// RVA 0xf450
FLOAT appSRand()
{
	GSRandSeed = (GSRandSeed * 196314165) + 907633515;
	union { FLOAT f; INT i; } Result;
	Result.i = (*(INT*)&GSRandTemp & 0xff800000) | (GSRandSeed & 0x007fffff);
	return appFractional(Result.f);
}

// RVA 0xf4b0
INT appFloor(FLOAT F)
{
	return appTrunc(floor(F));
}

// RVA 0xf4d0
INT appRound(FLOAT F)
{
	return appFloor(F + 0.5f);
}

// RVA 0xf4f0
INT appSprintf(TCHAR* Dest, const TCHAR* Fmt, ...)
{
	return _vsnwprintf(Dest, 1024, Fmt, (va_list)(&Fmt + 1));
}
