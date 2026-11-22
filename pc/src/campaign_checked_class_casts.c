/* Checked class casts. In this build the failure report is compiled out, but the
   class singleton is still initialized and the superclass chain still walked
   before the object pointer is returned unchanged. */

#include "campaign_class_singletons.h"
#include "campaign_class_registration.h"
/* FAKEMATCH: the original members in this range are not recovered; these padding members are not
   named by offset and only push later members into place. */
struct EngineObject {
    unsigned char object_fields[0x24];
    struct RuntimeClass *type;
};

static int has_class(const struct EngineObject *object, const struct RuntimeClass *wanted)
{
    const struct RuntimeClass *type;
    for (type = object->type; type; type = type->super_class) {
        if (type == wanted)
            return 1;
    }
    return wanted == 0;
}

#define DEFINE_CHECKED_CLASS_CAST(Type, Package)                                  struct Type;                                                                                                                                                        struct Type *cast_##Type(struct EngineObject *object)                          {                                                                                 if (object) {                                                                     if (!class_##Type) {                                                              class_##Type = create_##Type(package_##Package);                              register_##Type();                                                        }                                                                             has_class(object, class_##Type);                                          }                                                                             return (struct Type *)object;                                             }

DEFINE_CHECKED_CLASS_CAST(UClassProperty, Core)
DEFINE_CHECKED_CLASS_CAST(UObjectProperty, Core)
DEFINE_CHECKED_CLASS_CAST(UArrayProperty, Core)
DEFINE_CHECKED_CLASS_CAST(UVolumeTexture, Engine)
DEFINE_CHECKED_CLASS_CAST(UTexture, Engine)
DEFINE_CHECKED_CLASS_CAST(UGameEngine, Engine)
DEFINE_CHECKED_CLASS_CAST(UViewport, Engine)
DEFINE_CHECKED_CLASS_CAST(UCanvas, Engine)
DEFINE_CHECKED_CLASS_CAST(UStructProperty, Core)
DEFINE_CHECKED_CLASS_CAST(UStruct, Core)
