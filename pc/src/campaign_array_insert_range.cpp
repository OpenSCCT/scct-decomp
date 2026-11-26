#include "campaign_array_object.h"
#include "unreal_containers.h"

extern "C" {
#include "campaign_globals.h"
}

template<const unsigned short *Tag>
void Array::Insert(int index, int amount, int element_size)
{
    int old_count = count;
    count += amount;
    if (count > capacity) {
        capacity = count + (3 * count) / 8 + 2;
        data = static_cast<unsigned char *>(GMalloc->Realloc(data, capacity * element_size, Tag));
    }
    array_move(data + (index + amount) * element_size,
               data + index * element_size,
               (old_count - index) * element_size);
}

template void Array::Insert<array_add_tag_7b7b08>(int, int, int);
template void Array::Insert<array_add_tag_7ba13c>(int, int, int);
template void Array::Insert<array_add_tag_7bc158>(int, int, int);
template void Array::Insert<array_add_tag_7bc180>(int, int, int);
template void Array::Insert<array_add_tag_7be9a8>(int, int, int);
