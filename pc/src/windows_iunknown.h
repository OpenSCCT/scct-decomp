#ifndef WINDOWS_IUNKNOWN_H
#define WINDOWS_IUNKNOWN_H

#include "campaign_import_GUID.h"
#include "campaign_import_HRESULT.h"

typedef unsigned long ULONG;
typedef const GUID &REFGUID;
typedef const GUID &REFIID;

extern "C" __declspec(selectany) const GUID IID_IUnknown =
    {0, 0, 0, {0xc0, 0, 0, 0, 0, 0, 0, 0x46}};

struct IUnknown {
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void **ppvObj) = 0;
    virtual ULONG __stdcall AddRef() = 0;
    virtual ULONG __stdcall Release() = 0;
};

#endif
