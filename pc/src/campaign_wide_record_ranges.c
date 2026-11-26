struct WideText {
    unsigned reserved;
    union { unsigned short storage[8]; void *heap; } buffer;
    unsigned length, capacity;
};
struct WideRecord { struct WideText text; unsigned value; };
struct Argument { const void *address; };
/* The range stack argument packs a zero start and an all-elements count. */
extern void __fastcall copy_text(struct WideText *, struct Argument, unsigned __int64 range);

static __forceinline void assign_record(struct WideRecord *output, const struct WideRecord *input)
{
    struct Argument argument;
    argument.address = &input->text;
    copy_text(&output->text, argument, (unsigned __int64)~0u << 32);
    output->value = input->value;
}

struct WideRecord *copy_records(const struct WideRecord *first, const struct WideRecord *last,
                            struct WideRecord *output)
{
    for (; first != last; ++first, ++output)
        assign_record(output, first);
    return output;
}

struct WideRecord *copy_backward(const struct WideRecord *first, const struct WideRecord *last,
                             struct WideRecord *output_end)
{
    if (first != last) {
        do {
            assign_record(--output_end, --last);
        } while (last != first);
    }
    return output_end;
}

extern void __cdecl free_buffer(void *buffer);

void destroy_records(struct WideRecord *first, struct WideRecord *last)
{
    for (; first != last; ++first) {
        if (first->text.capacity >= 8)
            free_buffer(first->text.buffer.heap);
        first->text.capacity = 7;
        first->text.length = 0;
        first->text.buffer.storage[0] = 0;
    }
}
