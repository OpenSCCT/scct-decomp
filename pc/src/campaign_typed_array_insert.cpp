#include "campaign_array_object.h"

extern "C" {
#include "campaign_globals.h"
}

template<const unsigned short *Tag, int ElementSize>
void Array::InsertTyped(int index, int amount)
{
    Insert<Tag>(index, amount, ElementSize);
}

template void Array::InsertTyped<array_add_tag_7b7b08, 4>(int, int);
template void Array::InsertTyped<array_add_tag_7b7b08, 8>(int, int);
template void Array::InsertTyped<array_add_tag_7b7b08, 12>(int, int);
template void Array::InsertTyped<array_add_tag_7b7b08, 16>(int, int);
template void Array::InsertTyped<array_add_tag_7b7b08, 20>(int, int);
template void Array::InsertTyped<array_add_tag_7b7b08, 32>(int, int);
template void Array::InsertTyped<array_add_tag_7b7b08, 36>(int, int);
template void Array::InsertTyped<array_add_tag_7b7b08, 80>(int, int);
template void Array::InsertTyped<array_add_tag_7b7b08, 148>(int, int);
template void Array::InsertTyped<array_add_tag_7bc158, 4>(int, int);
template void Array::InsertTyped<array_add_tag_7bc180, 12>(int, int);
