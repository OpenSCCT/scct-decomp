struct ArrayAllocator;

#ifdef __cplusplus
extern "C" {
#endif
extern struct ArrayAllocator *array_allocator;
#ifdef __cplusplus
}

/* Behavioral names for the allocator's first three observed virtual slots. */
class ArrayAllocatorVirtual {
public:
    virtual void *Allocate(unsigned bytes, const unsigned short *tag) = 0;
    virtual unsigned char *Resize(unsigned char *buffer, int bytes, const unsigned short *tag) = 0;
    virtual void Release(void *buffer) = 0;
};
#endif
