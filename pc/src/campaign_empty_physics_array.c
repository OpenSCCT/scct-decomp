#include "campaign_array_storage.h"
struct Array *__fastcall initialize_array(struct Array *self)
{
    self->buffer.bytes = 0;
    self->count = 0;
    self->capacity = 0x80000000u;
    return self;
}
