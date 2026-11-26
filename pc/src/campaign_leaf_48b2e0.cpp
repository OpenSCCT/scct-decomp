// campaign_leaf_48b2e0.cpp -- mutex member destructor at VA 0x10d8b2e0.
#include "campaign_leaf_49b700_lock.h"

extern "C" void __fastcall destroy_mutex(void *mutex);

// UnkType_10d9b700_Lock::~UnkType_10d9b700_Lock calls the matched mutex destroyer.
UnkType_10d9b700_Lock::~UnkType_10d9b700_Lock()
{
    destroy_mutex(this);
}
