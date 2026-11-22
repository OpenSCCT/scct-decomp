#include "campaign_fsarray.h"
#include "campaign_globals.h"

void __fastcall resize_fsarray(struct FSArray *array, struct ArraySize stride)
{
    struct ArrayTag tag;
    tag.text = fsarray_tag;
    array->buffer.bytes = resize_heap->methods->resize(
        resize_heap, array->buffer.bytes, array->buffer, array->count * stride.value, tag);
}
