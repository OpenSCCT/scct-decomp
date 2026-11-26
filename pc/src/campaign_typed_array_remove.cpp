#include "campaign_array_object.h"

extern "C" {
#include "campaign_globals.h"
}

template<const unsigned short *Tag, int ElementSize>
void Array::RemoveTyped(int index, int amount)
{
    Remove<Tag>(index, amount, ElementSize);
}

template void Array::RemoveTyped<array_tag_7b78d8, 2>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 1>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 4>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 8>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 12>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 16>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 20>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 24>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 28>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 32>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 36>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 40>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 44>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 48>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 52>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 56>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 60>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 64>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 68>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 72>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 76>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 80>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 120>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 132>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 136>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 148>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 156>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 176>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 192>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 376>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 416>(int, int);
template void Array::RemoveTyped<array_tag_7b7b08, 1100>(int, int);
template void Array::RemoveTyped<array_tag_7b8f84, 1>(int, int);
template void Array::RemoveTyped<array_tag_7ba13c, 4>(int, int);
template void Array::RemoveTyped<array_tag_7ba17c, 4>(int, int);
template void Array::RemoveTyped<array_tag_7bc158, 4>(int, int);
template void Array::RemoveTyped<array_tag_7bc180, 12>(int, int);
template void Array::RemoveTyped<array_tag_7be9a8, 1>(int, int);
template void Array::RemoveTyped<array_tag_7cddbc, 4>(int, int);
template void Array::RemoveTyped<array_tag_7db4cc, 4>(int, int);
template void Array::RemoveTyped<array_tag_831360, 4>(int, int);
