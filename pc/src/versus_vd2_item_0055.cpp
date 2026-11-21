// Work item 0055: Core Windows platform helpers (UnVcWin32.cpp in UE2).
// appMsgf (RVA 0xde00) and appSystemTime (RVA 0xdeb0).
// The other functions in this range (appClipboardCopy 0xdc40, appClipboardPaste
// 0xdc90, appLaunchURL 0xdf20, appCreateProc 0xdf70) take arguments in
// EDI/EAX/ECX: link-time code generation calling conventions, not matchable yet.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short WORD;
typedef char* va_list;

struct SYSTEMTIME
{
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
};

extern "C" __declspec(dllimport) void __stdcall GetLocalTime(SYSTEMTIME* lpSystemTime);
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf(TCHAR* Dest, unsigned int Count, const TCHAR* Fmt, va_list Args);

// Unicode/ANSI switching MessageBox pointer (TCHAR_CALL_OS wrapper).
extern int (__stdcall* pMessageBox)(void* hWnd, const TCHAR* Text, const TCHAR* Caption, unsigned int Type);

#define MB_OK       0x00000000L
#define MB_OKCANCEL 0x00000001L
#define MB_YESNO    0x00000004L
#define IDOK        1
#define IDYES       6

// TEXT("") was not folded: retail reads the empty literal's first character.
extern const TCHAR appMsgf_Empty[];
// Retail keeps one "Message" caption literal per call site.
extern const TCHAR appMsgf_MessageYesNo[];
extern const TCHAR appMsgf_MessageOkCancel[];
extern const TCHAR appMsgf_MessageOk[];

UBOOL appMsgf( INT Type, const TCHAR* Fmt, ... )
{
	TCHAR TempStr[4096] = { appMsgf_Empty[0] };
	va_list ArgPtr = (va_list)&Fmt + sizeof(Fmt);
	_vsnwprintf( TempStr, 4096, Fmt, ArgPtr );
	switch( Type )
	{
		case 1:
			return pMessageBox( 0, TempStr, appMsgf_MessageYesNo, MB_YESNO ) == IDYES;
		case 2:
			return pMessageBox( 0, TempStr, appMsgf_MessageOkCancel, MB_OKCANCEL ) == IDOK;
		default:
			pMessageBox( 0, TempStr, appMsgf_MessageOk, MB_OK );
	}
	return 1;
}

void appSystemTime( INT& Year, INT& Month, INT& DayOfWeek, INT& Day, INT& Hour, INT& Min, INT& Sec, INT& MSec )
{
	SYSTEMTIME st;
	GetLocalTime( &st );
	Year      = st.wYear;
	Month     = st.wMonth;
	DayOfWeek = st.wDayOfWeek;
	Day       = st.wDay;
	Hour      = st.wHour;
	Min       = st.wMinute;
	Sec       = st.wSecond;
	MSec      = st.wMilliseconds;
}
