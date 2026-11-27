#ifndef D3DX_BUFFER_H
#define D3DX_BUFFER_H

#include "campaign_import_GUID.h"
#include "campaign_import_HRESULT.h"

struct IUnknown {
    virtual HRESULT __stdcall QueryInterface(const GUID &iid, void **out) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
};

struct ID3DXBuffer : public IUnknown {
    virtual void *__stdcall GetBufferPointer() = 0;
    virtual unsigned long __stdcall GetBufferSize() = 0;
};

class CD3DXBuffer : public ID3DXBuffer {
public:
    CD3DXBuffer();
    HRESULT __stdcall QueryInterface(const GUID &iid, void **out);
    unsigned long __stdcall AddRef();
    unsigned long __stdcall Release();
    void *__stdcall GetBufferPointer();
    unsigned long __stdcall GetBufferSize();
    virtual ~CD3DXBuffer();
    virtual HRESULT Init(unsigned long size);

private:
    unsigned long ReferenceCount;
    unsigned long BufferSize;
    unsigned char *Buffer;
};

#endif
