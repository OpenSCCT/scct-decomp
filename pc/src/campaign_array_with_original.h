/* A scratch array: the shared Array, then the block it was built on and that block's element count. */
#include "campaign_array_storage.h"

struct ArrayWithOriginal {
    struct Array array;
    void *original;
    int original_count;
};
