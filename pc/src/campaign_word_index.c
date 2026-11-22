#include "campaign_array_storage.h"
int __fastcall find_word(const struct Array *array, unsigned unused_edx, const unsigned *value)
{
    int i;
    for (i = 0; i < array->count; ++i)
        if (((const unsigned *)array->buffer.bytes)[i] == *value)
            return i;
    return -1;
}
