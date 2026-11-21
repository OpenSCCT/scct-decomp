#include "sound_async_worker.h"
#include "sound_memory.h"

void __cdecl sound_reset_file_cache(void)
{
    long i;
    EnterCriticalSection(&cache_lock);
    for (i = 0; i < 4; ++i) {
        cache_entries[i].handle = INVALID_HANDLE_VALUE;
        SND_fn_vMemsetSnd(cache_entries[i].path, 0, sizeof(cache_entries[i].path));
    }
    LeaveCriticalSection(&cache_lock);
}
