// campaign_import_CoCreateInstance.h -- a function imported from ole32.dll.
// The retail import table names it CoCreateInstance.

#ifndef CAMPAIGN_IMPORT_COCREATEINSTANCE_H
#define CAMPAIGN_IMPORT_COCREATEINSTANCE_H

#include "campaign_import_GUID.h"
#include "campaign_import_HRESULT.h"

#define CLSCTX_INPROC_SERVER 0x1

extern "C" __declspec(dllimport)
HRESULT __stdcall CoCreateInstance(
    const GUID& ClassId,
    struct IUnknown* Outer,
    unsigned long Context,
    const GUID& InterfaceId,
    void** Object);

#endif
