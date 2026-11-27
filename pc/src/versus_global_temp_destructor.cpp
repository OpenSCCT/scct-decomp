#include "versus_build.h"
#include "versus_owning_arrays.h"
#include "versus_global_temp_objects.h"

UGlobalTempObjects::~UGlobalTempObjects()
{
    ConditionalDestroy();
}
