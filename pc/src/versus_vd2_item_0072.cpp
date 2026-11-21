/*
 * Work item 0072: Versus RVA 0x11ec0-0x121bc.
 *
 * 0x11ec0, 0x11f90 and 0x120e0 take arguments in EAX/ESI, a register
 * convention only link-time code generation (/GL) produces; they cannot be
 * matched by a plain /c compile and are not reconstructed here.
 *   0x11f90 looks like a word-boundary, case-insensitive appStrfind used by
 *   0x120e0, which has the shape of Parse(Stream, Match, Value, MaxLen)
 *   (quoted values, cut at the first delimiter).
 */
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef char *va_list;

extern "C" void *__cdecl memset(void *, int, unsigned int);
extern "C" __declspec(dllimport) TCHAR *__cdecl _itow(int, TCHAR *, int);
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf(TCHAR *, unsigned int, const TCHAR *, va_list);
#pragma intrinsic(memset)

/* 0x11f50: formats an integer into a shared static buffer.
   Neutral name; the buffer (VA 0x10d4f670, 20 TCHARs) was a local static.
   Near miss: retail clears it with the generic rep stosd/stosb pair
   (count in ECX/EBX), which a plain compile folds to rep stosd x10; most
   likely LTCG output like its EAX-convention neighbours. */
extern TCHAR IntToString_11f50_Buffer[20];

void __cdecl IntToString_11f50(INT Value)
{
	memset(IntToString_11f50_Buffer, 0, sizeof(IntToString_11f50_Buffer));
	_itow(Value, IntToString_11f50_Buffer, 10);
}

/* 0x12050: number of bits needed to hold values below N (ceil(log2 N)),
   via a 256-entry log table. ECX is unused. Neutral name. */
extern const BYTE CeilLogTable_12050[256];

BYTE __fastcall CeilLog2_12050(DWORD Unused, DWORD N)
{
	N--;
	if (N == (DWORD)-1)
		return 0;
	if (N <= 0x10000)
	{
		BYTE Shift = (N > 0x100) ? 8 : 0;
		return CeilLogTable_12050[N >> Shift] + Shift;
	}
	BYTE Shift = (N > 0x1000000) ? 24 : 16;
	return CeilLogTable_12050[N >> Shift] + Shift;
}

/* 0x120a0: UE2 appThrowf. TempStr (VA 0x10d4d670) was a local static. */
extern TCHAR appThrowf_TempStr[4096];

void appThrowf(const TCHAR *Fmt, ...)
{
	va_list ArgPtr = (va_list)&Fmt + sizeof(Fmt);
	_vsnwprintf(appThrowf_TempStr, 4096, Fmt, ArgPtr);
	throw (const TCHAR *)appThrowf_TempStr;
}
