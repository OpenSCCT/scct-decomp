#include "campaign_class_registration.h"
#include "campaign_class_singletons.h"
#include "campaign_globals.h"

CLASS_GETTER(UClass, Core)
CLASS_GETTER(ULinker, Core)
CLASS_GETTER(UObject, Core)

#define object_system_initialized() object_system_ready
REGISTER_RUNTIME_CLASS(ULinkerLoad, ULinker, UObject)
REGISTER_RUNTIME_CLASS(ULinkerSave, ULinker, UObject)
