#include "campaign_class_singletons.h"

struct RuntimeClass;
/* FAKEMATCH: this C vtable view skips the first twenty UObject slots, including
   ProcessEvent and Destroy, to reach the registration call at +0x50. */
struct ClassMethods {
    void *unk_0000[0x50 / 4];
    void (__fastcall *register_class)(struct RuntimeClass *);
};
/* FAKEMATCH: these byte arrays hide known UObject fields and UClass::ClassFlags
   within the abbreviated C view of the class descriptor. */
struct RuntimeClass {
    const struct ClassMethods *methods;
    unsigned char unk_0004[0x24 - 4];
    struct RuntimeClass *object_class;
    struct RuntimeClass *super_class;
    unsigned char unk_002c[0x28c - 0x2c];
    struct RuntimeClass *within;
};

extern int object_system_initialized(void);

#define CLASS_GETTER(Type, Package) \
    static __forceinline struct RuntimeClass *get_##Type(void) \
    { \
        if (!class_##Type) { \
            class_##Type = create_##Type(package_##Package); \
            register_##Type(); \
        } \
        return class_##Type; \
    }

#define REGISTER_RUNTIME_CLASS(Type, Parent, Within) \
    void register_##Type(void) \
    { \
        struct RuntimeClass *parent = get_##Parent(); \
        if (parent != class_##Type) \
            class_##Type->super_class = get_##Parent(); \
        else \
            class_##Type->super_class = 0; \
        class_##Type->within = get_##Within(); \
        class_##Type->object_class = get_UClass(); \
        if (object_system_initialized()) { \
            struct RuntimeClass *actual = class_##Type->object_class; \
            if (actual == get_UClass()) \
                class_##Type->methods->register_class(class_##Type); \
        } \
    }
