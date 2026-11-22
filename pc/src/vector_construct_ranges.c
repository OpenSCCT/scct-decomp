/* vector_construct_ranges.c -- construct_words and construct_dwords: copy a range into output storage */

#define DEFINE_CONSTRUCT_RANGE(Type, Name) \
    Type *__stdcall construct_##Name(const Type *first, const Type *last, Type *out) \
    { \
        Type *dst = out; \
        while (first != last) { \
            if (dst) *dst = *first; \
            ++first; \
            ++dst; \
        } \
        return dst; \
    }

DEFINE_CONSTRUCT_RANGE(unsigned short, words)
DEFINE_CONSTRUCT_RANGE(unsigned, dwords)
