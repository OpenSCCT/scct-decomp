#ifndef D3DX_BUFFER_H
#define D3DX_BUFFER_H

#include "windows_iunknown.h"

extern "C" __declspec(selectany) const GUID IID_ID3DXBuffer =
    {0x932e6a7e, 0xc68e, 0x45dd, {0xa7, 0xbf, 0x53, 0xd1, 0x9c, 0x86, 0xdb, 0x1f}};

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
