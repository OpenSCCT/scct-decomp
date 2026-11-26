// campaign_wide_record_ranges.cpp -- copy and destruction of records containing wide strings
struct WideText {
    unsigned reserved;
    union { unsigned short storage[8]; void *heap; } buffer;
    unsigned length, capacity;

    WideText &Assign(const WideText &source, unsigned start, unsigned count);
};
struct WideRecord { struct WideText text; unsigned value; };
static __forceinline void assign_record(struct WideRecord *output, const struct WideRecord *input)
{
    output->text.Assign(input->text, 0, ~0u);
    output->value = input->value;
}

extern "C" struct WideRecord *copy_records(const struct WideRecord *first, const struct WideRecord *last,
                            struct WideRecord *output)
{
    for (; first != last; ++first, ++output)
        assign_record(output, first);
    return output;
}

extern "C" struct WideRecord *copy_backward(const struct WideRecord *first, const struct WideRecord *last,
                             struct WideRecord *output_end)
{
    if (first != last) {
        do {
            assign_record(--output_end, --last);
        } while (last != first);
    }
    return output_end;
}

extern "C" void __cdecl free_buffer(void *buffer);

extern "C" void destroy_records(struct WideRecord *first, struct WideRecord *last)
{
    for (; first != last; ++first) {
        if (first->text.capacity >= 8)
            free_buffer(first->text.buffer.heap);
        first->text.capacity = 7;
        first->text.length = 0;
        first->text.buffer.storage[0] = 0;
    }
}
