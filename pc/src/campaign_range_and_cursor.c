struct RangeState {
    void *first, *current;
    unsigned count;
    void *context;
};

struct RangeRecord { unsigned a, b, c, d; };
struct RangeCursor { const void *position; };

struct RangeState *__fastcall initialize_range(struct RangeState *state, unsigned unused_edx,
                                               void *first, void *context)
{
    state->first = first;
    state->current = first;
    state->count = 0;
    state->context = context;
    return state;
}

void __stdcall construct_record(struct RangeRecord *output, const struct RangeRecord *source)
{
    if (output) {
        output->a = source->a;
        output->b = source->b;
        output->c = source->c;
        output->d = source->d;
    }
}

unsigned char __fastcall cursor_differs(const struct RangeCursor *left, unsigned unused_edx,
                                        const struct RangeCursor *right)
{
    return left->position != right->position;
}
