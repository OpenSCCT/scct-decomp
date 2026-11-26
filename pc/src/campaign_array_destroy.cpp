#include "campaign_array_object.h"

extern "C" {
#include "campaign_globals.h"
}

/* Empty an array after removing its full live range. */
template<const unsigned short *Tag, int ElementSize>
void Array::Empty()
{
    int old_count = count;
    Remove<Tag>(0, old_count, ElementSize);
    if (data)
        reinterpret_cast<ArrayAllocatorVirtual *>(array_allocator)->Release(data);
    data = 0;
    capacity = 0;
    count = 0;
}

template void Array::Empty<array_tag_7b78d8, 2>();
template void Array::Empty<array_tag_7b7b08, 1>();
template void Array::Empty<array_tag_7b7b08, 4>();
template void Array::Empty<array_tag_7b7b08, 8>();
template void Array::Empty<array_tag_7b7b08, 12>();
template void Array::Empty<array_tag_7b7b08, 16>();
template void Array::Empty<array_tag_7b7b08, 20>();
template void Array::Empty<array_tag_7b7b08, 24>();
template void Array::Empty<array_tag_7b7b08, 28>();
template void Array::Empty<array_tag_7b7b08, 32>();
template void Array::Empty<array_tag_7b7b08, 36>();
template void Array::Empty<array_tag_7b7b08, 40>();
template void Array::Empty<array_tag_7b7b08, 44>();
template void Array::Empty<array_tag_7b7b08, 48>();
template void Array::Empty<array_tag_7b7b08, 52>();
template void Array::Empty<array_tag_7b7b08, 56>();
template void Array::Empty<array_tag_7b7b08, 60>();
template void Array::Empty<array_tag_7b7b08, 64>();
template void Array::Empty<array_tag_7b7b08, 68>();
template void Array::Empty<array_tag_7b7b08, 72>();
template void Array::Empty<array_tag_7b7b08, 76>();
template void Array::Empty<array_tag_7b7b08, 80>();
template void Array::Empty<array_tag_7b7b08, 100>();
template void Array::Empty<array_tag_7b7b08, 120>();
template void Array::Empty<array_tag_7b7b08, 132>();
template void Array::Empty<array_tag_7b7b08, 136>();
template void Array::Empty<array_tag_7b7b08, 148>();
template void Array::Empty<array_tag_7b7b08, 156>();
template void Array::Empty<array_tag_7b7b08, 176>();
template void Array::Empty<array_tag_7b7b08, 192>();
template void Array::Empty<array_tag_7b7b08, 376>();
template void Array::Empty<array_tag_7b7b08, 416>();
template void Array::Empty<array_tag_7b7b08, 1100>();
template void Array::Empty<array_tag_7ba13c, 4>();
template void Array::Empty<array_tag_7ba17c, 4>();
template void Array::Empty<array_tag_7bc158, 4>();
template void Array::Empty<array_tag_7bc180, 12>();
template void Array::Empty<array_tag_7be9a8, 1>();
template void Array::Empty<array_tag_7cddbc, 4>();
template void Array::Empty<array_tag_7db4cc, 4>();
template void Array::Empty<array_tag_831360, 4>();
