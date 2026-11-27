#include "versus_static_mesh_arrays.h"

INT FArray::Add(INT Count, INT ElementSize)
{
    const INT Index = ArrayNum;
    ArrayNum += Count;
    if (ArrayNum > ArrayMax)
    {
        ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
        const INT Bytes = ArrayMax * ElementSize;
        if (!Data)
            Data = GMalloc->Malloc(Bytes, L"FArray::Add");
        else
            Data = GMalloc->Realloc(Data, Bytes, L"FArray");
    }
    return Index;
}
