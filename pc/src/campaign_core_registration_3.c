#include "campaign_class_registration.h"
#include "campaign_class_singletons.h"
#include "campaign_globals.h"

CLASS_GETTER(UClass, Core)
CLASS_GETTER(UFactory, Core)
CLASS_GETTER(UObject, Core)

#define object_system_initialized() object_system_ready
REGISTER_RUNTIME_CLASS(UCommandlet, UObject, UObject)
REGISTER_RUNTIME_CLASS(ULanguage, UObject, UObject)
REGISTER_RUNTIME_CLASS(ULinker, UObject, UObject)
REGISTER_RUNTIME_CLASS(UPackage, UObject, UObject)
REGISTER_RUNTIME_CLASS(USubsystem, UObject, UObject)
REGISTER_RUNTIME_CLASS(UTextBuffer, UObject, UObject)
REGISTER_RUNTIME_CLASS(UTextBufferFactory, UFactory, UObject)
