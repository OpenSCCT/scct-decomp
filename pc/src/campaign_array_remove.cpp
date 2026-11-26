#include "campaign_array_object.h"

extern "C" {
#include "campaign_globals.h"
}

template<const unsigned short *Tag>
void Array::Remove(int index, int amount, int element_size)
{
    if (amount) {
        array_move(data + index * element_size,
                   data + (index + amount) * element_size,
                   (count - index - amount) * element_size);
        count -= amount;
        if ((3 * count < 2 * capacity ||
             (capacity - count) * element_size >= 16384) &&
            (capacity - count > 64 || count == 0)) {
            int bytes;
            capacity = count;
            bytes = capacity * element_size;
            data = reinterpret_cast<ArrayAllocatorVirtual *>(array_allocator)->Resize(data, bytes, Tag);
        }
    }
}

template void Array::Remove<array_tag_7b78d8>(int, int, int);
template void Array::Remove<array_tag_7b7b08>(int, int, int);
template void Array::Remove<array_tag_7b8f84>(int, int, int);
template void Array::Remove<array_tag_7b9b70>(int, int, int);
template void Array::Remove<array_tag_7ba13c>(int, int, int);
template void Array::Remove<array_tag_7ba17c>(int, int, int);
template void Array::Remove<array_tag_7bc158>(int, int, int);
template void Array::Remove<array_tag_7bc180>(int, int, int);
template void Array::Remove<array_tag_7be9a8>(int, int, int);
template void Array::Remove<array_tag_7cddbc>(int, int, int);
template void Array::Remove<array_tag_7cf82c>(int, int, int);
template void Array::Remove<array_tag_7db4cc>(int, int, int);
template void Array::Remove<array_tag_831360>(int, int, int);
