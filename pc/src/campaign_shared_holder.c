struct Shared;
struct SharedMethods { void (__fastcall *destroy)(struct Shared *, unsigned, unsigned); };
struct Shared { const struct SharedMethods *methods; unsigned references; };
struct SharedHolder { struct Shared *shared; };
extern void __cdecl release_memory(struct SharedHolder *);
struct SharedHolder *__fastcall delete_holder(struct SharedHolder *self, unsigned unused, unsigned flags)
{
    struct Shared *shared = self->shared;
    if (shared) {
        if (shared->references <= 1)
            shared->methods->destroy(shared, unused, 1);
        else
            --shared->references;
    }
    if (flags & 1) release_memory(self);
    return self;
}
