// campaign_import_InvalidateRect.h -- a function imported from USER32.dll.
// The retail import table names it InvalidateRect.

#ifndef CAMPAIGN_IMPORT_INVALIDATERECT_H
#define CAMPAIGN_IMPORT_INVALIDATERECT_H

#include "campaign_import_HWND.h"
#include "campaign_import_RECT.h"

extern "C" __declspec(dllimport) int __stdcall InvalidateRect(HWND Window, const RECT* Rect,
                                                               int Erase);

#endif
