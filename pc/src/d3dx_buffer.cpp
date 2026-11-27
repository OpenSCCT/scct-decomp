#include "d3dx_buffer.h"

#define E_OUTOFMEMORY ((HRESULT)0x8007000eL)

CD3DXBuffer::CD3DXBuffer()
{
    ReferenceCount = 1;
    Buffer = 0;
    BufferSize = 0;
}

CD3DXBuffer::~CD3DXBuffer()
{
    if (Buffer)
        delete[] Buffer;
}

HRESULT CD3DXBuffer::Init(unsigned long size)
{
    BufferSize = size;
    Buffer = new unsigned char[size];
    return Buffer ? S_OK : E_OUTOFMEMORY;
}

unsigned long __stdcall CD3DXBuffer::AddRef()
{
    return ++ReferenceCount;
}

unsigned long __stdcall CD3DXBuffer::Release()
{
    unsigned long references = ReferenceCount--;
    if (references == 1)
        delete this;
    return references - 1;
}

void *__stdcall CD3DXBuffer::GetBufferPointer()
{
    return Buffer;
}

unsigned long __stdcall CD3DXBuffer::GetBufferSize()
{
    return BufferSize;
}
