// campaign_cleanup_4f9ae0.cpp -- cleanup thunk at VA 0x10df9ae0.
#include "campaign_unidentified_empty_destructor.h"

// cleanup_4f9ae0
extern "C" void __fastcall cleanup_4f9ae0(void *object)
{
    ((UnkType_10d9d570 *)object)->~UnkType_10d9d570();
}
