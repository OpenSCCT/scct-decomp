#include "sound_async_worker.h"

void __stdcall SND_fn_vDesInitStreamAsyncSnd(void)
{
    sound_shutdown_async_io();
}
