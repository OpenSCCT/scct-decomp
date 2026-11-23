// campaign_import_GetMenuState.h -- a function imported from USER32.dll.
// The retail import table names it GetMenuState.

#ifndef CAMPAIGN_IMPORT_GETMENUSTATE_H
#define CAMPAIGN_IMPORT_GETMENUSTATE_H

#include "campaign_import_HMENU.h"

#define MF_BYCOMMAND 0x00000000L
#define MF_CHECKED 0x00000008L

extern "C" __declspec(dllimport)
unsigned int __stdcall GetMenuState(HMENU Menu, unsigned int Id, unsigned int Flags);

#endif
