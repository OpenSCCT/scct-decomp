// campaign_import_SetWindowPos.h -- a function imported from USER32.dll.
// The retail import table names it SetWindowPos.

#ifndef CAMPAIGN_IMPORT_SETWINDOWPOS_H
#define CAMPAIGN_IMPORT_SETWINDOWPOS_H

#include "campaign_import_HWND.h"

#define HWND_TOPMOST ((HWND)-1)
#define HWND_NOTOPMOST ((HWND)-2)

#define SWP_NOSIZE 0x0001
#define SWP_NOMOVE 0x0002
#define SWP_NOACTIVATE 0x0010
#define SWP_SHOWWINDOW 0x0040

extern "C" __declspec(dllimport)
int __stdcall SetWindowPos(
    HWND Window,
    HWND InsertAfter,
    int X,
    int Y,
    int Width,
    int Height,
    unsigned int Flags);

#endif
