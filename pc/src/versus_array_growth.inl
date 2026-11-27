extern const TCHAR FArrayAddTag[] = L"FArray::Add";
extern const TCHAR FArrayTag[] = L"FArray";

INT FArray::Add(INT Count, INT ElementSize)
{
    const INT Index = ArrayNum;
    ArrayNum += Count;
    if (ArrayNum > ArrayMax)
    {
        ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
        if (!Data)
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArrayAddTag);
        else
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, FArrayTag);
    }
    return Index;
}
