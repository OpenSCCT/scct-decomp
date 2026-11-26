#include "campaign_leaf_49b700_lock.h"

extern "C" void __fastcall destroy_mutex(void *mutex);

UnkType_10d9b700_Lock::~UnkType_10d9b700_Lock()
{
    destroy_mutex(this);
}
