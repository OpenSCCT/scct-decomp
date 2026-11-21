// Work item 0030: Versus RVA 0x68b0-0x6c86 (launcher/splash window code).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef unsigned char BYTE;

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR*);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR*, const TCHAR*);
extern "C" __declspec(dllimport) TCHAR* __cdecl wcscpy(TCHAR*, const TCHAR*);

typedef void* HWND;
typedef void* HINSTANCE;
typedef void* HBITMAP;
typedef void* HICON;
typedef void* HGDIOBJ;
typedef long LONG;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef int BOOL;
typedef DWORD UBOOL;
typedef INT (__stdcall *DLGPROC)(HWND, UINT, WPARAM, LPARAM);

extern "C" __declspec(dllimport) HWND __stdcall GetDlgItem(HWND hDlg, INT nIDDlgItem);
extern "C" __declspec(dllimport) INT __stdcall GetSystemMetrics(INT nIndex);
extern "C" __declspec(dllimport) BOOL __stdcall SetWindowPos(HWND hWnd, HWND hWndInsertAfter, INT X, INT Y, INT cx, INT cy, UINT uFlags);
extern "C" __declspec(dllimport) BOOL __stdcall UpdateWindow(HWND hWnd);
extern "C" __declspec(dllimport) BOOL __stdcall SetForegroundWindow(HWND hWnd);
extern "C" __declspec(dllimport) BOOL __stdcall DeleteObject(HGDIOBJ ho);

#define SM_CXSCREEN      0
#define SM_CYSCREEN      1
#define HWND_TOPMOST     ((HWND)-1)
#define HWND_NOTOPMOST   ((HWND)-2)
#define SWP_NOSIZE       0x0001
#define SWP_NOMOVE       0x0002
#define SWP_SHOWWINDOW   0x0040
#define STM_SETIMAGE     0x0172
#define IMAGE_BITMAP     0
#define WM_SETICON       0x0080
#define ICON_BIG         1

// Unicode/ANSI OS wrappers imported from the Window/Core layer (Unreal "...X" helpers).
__declspec(dllimport) UINT __stdcall GetWindowsDirectoryX(TCHAR* Buffer, UINT Size);
__declspec(dllimport) UINT __stdcall GetSystemDirectoryX(TCHAR* Buffer, UINT Size);
__declspec(dllimport) DWORD __stdcall GetModuleFileNameX(void* Module, TCHAR* Buffer, DWORD Size);
__declspec(dllimport) HWND __stdcall CreateDialogParamX(HINSTANCE hInstance, const TCHAR* Template, HWND hWndParent, DLGPROC DialogProc, LPARAM InitParam);
__declspec(dllimport) LONG __stdcall SendMessageX(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
__declspec(dllimport) HICON __stdcall LoadIconX(HINSTANCE hInstance, const TCHAR* IconName);

extern HINSTANCE hInstance;
extern HWND hWndSplash;
INT __stdcall SplashDialogProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
HBITMAP LoadFileToBitmap(const TCHAR* Filename, INT& SizeX, INT& SizeY);

#define MAKEINTRESOURCEW(i) ((const TCHAR*)((DWORD)((unsigned short)(i))))
#define IDDIALOG_Splash 119
#define IDC_Logo        1024
#define IDICON_Setup    128

// Unreal Window.h bitmap holder.
class FWindowsBitmap
{
public:
	INT SizeX, SizeY, Keep;
	FWindowsBitmap(UBOOL InKeep = 0)
	: SizeX(0), SizeY(0), Keep(InKeep), hBitmap(0)
	{}
	~FWindowsBitmap()
	{
		if (hBitmap && !Keep)
			DeleteObject(hBitmap);
	}
	UBOOL LoadFile(const TCHAR* Filename)
	{
		if (hBitmap)
			DeleteObject(hBitmap);
		hBitmap = LoadFileToBitmap(Filename, SizeX, SizeY);
		return hBitmap != 0;
	}
	HBITMAP GetBitmapHandle()
	{
		return hBitmap;
	}
private:
	HBITMAP hBitmap;
};

// RVA 0x68b0: Unreal's InitSplash. Near match (vc71 /O2 /Gy /GX): only the load of
// Filename is scheduled later than retail. The retail build keeps the bitmap's size and
// handle in registers, which the explicit copies below reproduce.
void InitSplash(const TCHAR* Filename)
{
	HBITMAP hBitmap = 0;
	INT SizeX = 0, SizeY = 0;
	FWindowsBitmap Bitmap(1);
	if (Filename)
	{
		Bitmap.LoadFile(Filename);
		SizeX = Bitmap.SizeX;
		SizeY = Bitmap.SizeY;
		hBitmap = Bitmap.GetBitmapHandle();
	}
	hWndSplash = CreateDialogParamX(hInstance, MAKEINTRESOURCEW(IDDIALOG_Splash), 0, SplashDialogProc, 0);
	if (hWndSplash)
	{
		HWND hWndLogo = GetDlgItem(hWndSplash, IDC_Logo);
		if (hWndLogo)
		{
			SetWindowPos(hWndSplash, HWND_TOPMOST, (GetSystemMetrics(SM_CXSCREEN) - SizeX) / 2, (GetSystemMetrics(SM_CYSCREEN) - SizeY) / 2, SizeX, SizeY, SWP_SHOWWINDOW);
			SetWindowPos(hWndSplash, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			SendMessageX(hWndLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
			UpdateWindow(hWndSplash);
		}
	}
}

inline INT appStrlen(const TCHAR* S) { return wcslen(S); }
inline INT appStricmp(const TCHAR* A, const TCHAR* B) { return _wcsicmp(A, B); }
inline TCHAR* appStrcpy(TCHAR* Dest, const TCHAR* Src) { return wcscpy(Dest, Src); }

extern TCHAR GWindowsDir[256];
extern TCHAR GSystemDir[256];
extern TCHAR GModuleFile[256];

// RVA 0x69e0: cache the OS directories and the executable path, mapping .ICD to .EXE.
void InitLauncherPaths()
{
	GetWindowsDirectoryX(GWindowsDir, 256);
	GetSystemDirectoryX(GSystemDir, 256);
	GetModuleFileNameX(0, GModuleFile, 256);
	if (appStricmp(GModuleFile + appStrlen(GModuleFile) - 4, L".ICD") == 0)
		appStrcpy(GModuleFile + appStrlen(GModuleFile) - 4, L".EXE");
}

// Minimal Unreal Window.h shapes (statically linked into this module).
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
};

class FCommandTarget
{
public:
	virtual void Unused();
};

class WWindow : public FCommandTarget
{
public:
	HWND hWnd;
	BYTE Pad08[0x38];                                            // WWindow is 0x40 bytes here
	virtual ~WWindow();
	virtual void V02(); virtual void V03(); virtual void V04(); virtual void V05();
	virtual void V06(); virtual void V07(); virtual void V08(); virtual void V09();
	virtual void V10();
	virtual void SetText(const TCHAR* Text);                     // slot 11 (+0x2c)
	operator HWND() const { return hWnd; }
};

class WLabel : public WWindow
{
};

class WWizardDialog : public WWindow
{
public:
	BYTE PadWizard[0x2FC - 0x40];
	void OnInitDialog();                                         // RVA 0x216a80
};

// Setup wizard window (vtable 0x10c0ea18). The class name is a guess from
// Unreal's Setup.cpp (WFilerWizard); members follow the constructor at RVA 0x6b20.
class WFilerWizard : public WWizardDialog
{
public:
	WLabel LogoStatic;                                           // +0x2fc
	FWindowsBitmap LogoBitmap;                                   // +0x33c
	void* Manager;                                               // +0x34c
	FString Title;                                               // +0x350

	virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
	virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
	virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
	virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
	virtual void V28(); virtual void V29(); virtual void V30(); virtual void V31();
	virtual void V32(); virtual void V33(); virtual void V34(); virtual void V35();
	virtual void V36();
	virtual void OnInitDialog();                                 // slot 37 (RVA 0x6bc0)
	virtual void V38(); virtual void V39(); virtual void V40(); virtual void V41();
	virtual void V42(); virtual void V43(); virtual void V44(); virtual void V45();
	virtual void V46(); virtual void V47(); virtual void V48(); virtual void V49();
	virtual void V50(); virtual void V51(); virtual void V52(); virtual void V53();
	virtual void V54(); virtual void V55(); virtual void V56(); virtual void V57();
	virtual void V58(); virtual void V59(); virtual void V60();
	virtual void RefreshPage();                                  // slot 61 (+0xf4), name unknown
};

// RVA 0x6a80 (WFilerWizard destructor) and RVA 0x6b20 (constructor) take `this` on the
// stack, end in ret 4 and omit EH state stores: link-time-optimised code, not attempted.

// RVA 0x6bc0
void WFilerWizard::OnInitDialog()
{
	WWizardDialog::OnInitDialog();
	SendMessageX(hWnd, WM_SETICON, ICON_BIG, (WPARAM)LoadIconX(hInstance, MAKEINTRESOURCEW(IDICON_Setup)));
	RefreshPage();
	SendMessageX(hWnd, WM_SETICON, ICON_BIG, (WPARAM)LoadIconX(hInstance, MAKEINTRESOURCEW(IDICON_Setup)));
	LogoBitmap.LoadFile(L"..\\Help\\Logo.bmp");
	SendMessageX(LogoStatic.hWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LogoBitmap.GetBitmapHandle());
	SetText(*Title);
	SetForegroundWindow(hWnd);
}
