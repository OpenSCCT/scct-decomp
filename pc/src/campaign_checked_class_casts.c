/* Checked class casts. In this build the failure report is compiled out, but the
   class singleton is still initialized and the superclass chain still walked
   before the object pointer is returned unchanged. */
struct RuntimeClass {
    unsigned char object_fields[0x28];
    struct RuntimeClass *super_class;
};

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

#define DEFINE_CHECKED_CLASS_CAST(Type, Package)                                  struct Type;                                                                  extern struct RuntimeClass *class_##Type;                                     extern struct RuntimeClass *create_##Type(const unsigned short *package);     extern void register_##Type(void);                                            struct Type *cast_##Type(struct EngineObject *object)                          {                                                                                 if (object) {                                                                     if (!class_##Type) {                                                              class_##Type = create_##Type(package_##Package);                              register_##Type();                                                        }                                                                             has_class(object, class_##Type);                                          }                                                                             return (struct Type *)object;                                             }

extern const unsigned short package_Core[];
extern const unsigned short package_Engine[];

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
