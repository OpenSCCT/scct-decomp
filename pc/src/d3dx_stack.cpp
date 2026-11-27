// D3DX8 cd3dxstack.obj, DWORD and string stack storage.

#include "d3dx_buffer.h"
#include "windows_dispatch_types.h"

static const HRESULT E_OUTOFMEMORY = (HRESULT)0x8007000EL;
static const HRESULT E_FAIL = (HRESULT)0x80004005L;
static const unsigned int StackGrowth = 16;

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

class CD3DXDwStack {
public:
    CD3DXDwStack();
    ~CD3DXDwStack();
    HRESULT Push(DWORD value);
    HRESULT Pop(DWORD *value);
    HRESULT GetLastError();

private:
    DWORD *values;
    unsigned int count;
    unsigned int capacity;
    HRESULT error;
};

CD3DXDwStack::CD3DXDwStack() : values(0), count(0), capacity(0), error(S_OK) {}

CD3DXDwStack::~CD3DXDwStack() {
    if (values)
        delete[] values;
}

HRESULT CD3DXDwStack::Push(DWORD value) {
    if (count == capacity) {
        DWORD *grown = new DWORD[capacity + StackGrowth];
        if (!grown) {
            return error = E_OUTOFMEMORY;
        }
        if (values) {
            memcpy(grown, values, count * sizeof(DWORD));
            delete[] values;
        }
        capacity += StackGrowth;
        values = grown;
    }
    values[count++] = value;
    return S_OK;
}

HRESULT CD3DXDwStack::Pop(DWORD *value) {
    if (!count) {
        if (value) {
            *value = 0;
        }
        return error = E_FAIL;
    }
    --count;
    if (value) {
        *value = values[count];
    }
    return S_OK;
}

class CD3DXSzStack {
public:
    CD3DXSzStack();
    ~CD3DXSzStack();
    HRESULT Push(char *value);
    HRESULT GetLastError();
    HRESULT GenerateStringBuffer(ID3DXBuffer **buffer);

private:
    char **values;
    unsigned int count;
    unsigned int capacity;
    HRESULT error;
    unsigned int totalLength;
};

CD3DXSzStack::CD3DXSzStack() : values(0), count(0), capacity(0), error(S_OK), totalLength(0) {}

CD3DXSzStack::~CD3DXSzStack() {
    if (values) {
        for (unsigned int i = 0; i < count; ++i) {
            if (values[i])
                delete[] values[i];
        }
        delete[] values;
    }
}

extern "C" unsigned int __cdecl strlen(const char *);
#pragma intrinsic(strlen)

HRESULT CD3DXSzStack::Push(char *value) {
    if (count == capacity) {
        char **grown = new char *[capacity + StackGrowth];
        if (!grown)
            return error = E_OUTOFMEMORY;
        if (values) {
            memcpy(grown, values, count * sizeof(char *));
            delete[] values;
        }
        capacity += StackGrowth;
        values = grown;
    }
    if (value) {
        unsigned int length = strlen(value);
        char *copy = new char[length + 1];
        if (!copy)
            return error = E_OUTOFMEMORY;
        memcpy(copy, value, length);
        copy[length] = 0;
        totalLength += length;
        values[count] = copy;
    } else {
        values[count] = 0;
    }
    ++count;
    return S_OK;
}

HRESULT CD3DXSzStack::GetLastError()
{
    HRESULT last = error;
    error = S_OK;
    return last;
}

HRESULT CD3DXDwStack::GetLastError()
{
    HRESULT last = error;
    error = S_OK;
    return last;
}

HRESULT CD3DXSzStack::GenerateStringBuffer(ID3DXBuffer **buffer)
{
    *buffer = 0;
    if (!totalLength)
        return S_OK;

    CD3DXBuffer *result = new CD3DXBuffer;
    if (!result)
        return E_OUTOFMEMORY;
    HRESULT hr = result->Init(totalLength + count + 1);
    if (FAILED(hr)) {
        delete result;
        return hr;
    }

    char *out = static_cast<char *>(result->GetBufferPointer());
    for (unsigned int i = 0; i < count; ++i) {
        if (values[i]) {
            unsigned int length = strlen(values[i]);
            memcpy(out, values[i], length);
            out += length;
            *out++ = '\n';
        }
    }
    *out = 0;
    *buffer = result;
    return S_OK;
}
