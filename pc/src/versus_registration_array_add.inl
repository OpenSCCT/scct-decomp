#include "versus_registration_arrays.h"

inline INT FArray::Add(INT Count, INT ElementSize)
{
    INT Index = ArrayNum;
    if ((ArrayNum += Count) > ArrayMax) {
        ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
        if (Data == 0)
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArrayAddTag);
        else
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, FArrayTag);
    }
    return Index;
}
