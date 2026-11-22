#include "campaign_class_singletons.h"

struct RuntimeClass;
struct Object;
extern struct RuntimeClass *load_subclass(struct RuntimeClass *, struct Object *, const unsigned short *,
                                  const unsigned short *, unsigned, void *);

#define DEFINE_CLASS_LOAD(Type, Package) \
    struct RuntimeClass *load_subclass_##Type(struct Object *outer, const unsigned short *name, const unsigned short *file, unsigned flags, void *sandbox) \
    { \
        if (!class_##Type) { \
            class_##Type = create_##Type(package_##Package); \
            register_##Type(); \
        } \
        return load_subclass(class_##Type, outer, name, file, flags, sandbox); \
    }

DEFINE_CLASS_LOAD(URenderDevice, Engine)
