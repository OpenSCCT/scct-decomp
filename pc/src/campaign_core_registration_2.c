#include "campaign_class_registration.h"
#include "campaign_class_singletons.h"
#include "campaign_globals.h"

CLASS_GETTER(UClass, Core)
CLASS_GETTER(UField, Core)
CLASS_GETTER(UObject, Core)
CLASS_GETTER(UStruct, Core)

#define object_system_initialized() object_system_ready
REGISTER_RUNTIME_CLASS(UEnum, UField, UStruct)
void register_UObject(void) {
    get_UObject();
    class_UObject->super_class = 0;
    class_UObject->within = class_UObject;
    class_UObject->object_class = get_UClass();
    if (object_system_ready) {
        struct RuntimeClass *actual = class_UObject->object_class;
        if (actual == get_UClass())
            class_UObject->methods->register_class(class_UObject);
    }
}
