// campaign_import_DeleteObject.h -- a function imported from GDI32.dll.
// The retail import table names it DeleteObject.

#ifndef CAMPAIGN_IMPORT_DELETEOBJECT_H
#define CAMPAIGN_IMPORT_DELETEOBJECT_H

#include "campaign_import_HGDIOBJ.h"

extern "C" __declspec(dllimport) int __stdcall DeleteObject(HGDIOBJ Object);

#endif
