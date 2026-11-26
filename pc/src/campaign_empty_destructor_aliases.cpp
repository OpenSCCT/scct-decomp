// campaign_empty_destructor_aliases.cpp -- cleanup thunks to the empty destructor at 0x49d570.
#include "campaign_unidentified_empty_destructor.h"

// cleanup_4a7420
extern "C" void __fastcall cleanup_4a7420(void *object)
{
    ((UnkType_10d9d570 *)object)->~UnkType_10d9d570();
}

// cleanup_4ab2d0
extern "C" void __fastcall cleanup_4ab2d0(void *object)
{
    ((UnkType_10d9d570 *)object)->~UnkType_10d9d570();
}
