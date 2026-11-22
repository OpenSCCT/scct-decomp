struct OwnedRecord {
    const void *const *methods;
    unsigned reserved[3];
    void *storage;
};
struct DeleteFlags { unsigned value; };
extern const void *const record_methods[];
extern void __stdcall release_allocation(void *pointer);

struct OwnedRecord *__fastcall delete_owned_record(struct OwnedRecord *self, struct DeleteFlags flags)
{
    self->methods = record_methods;
    release_allocation(self->storage);
    if (flags.value & 1) release_allocation(self);
    return self;
}
