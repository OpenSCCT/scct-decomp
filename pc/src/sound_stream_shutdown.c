/* sound_stream_shutdown.c -- stops the asynchronous stream service */
#include "sound_async_worker.h"

/* SND_fn_vDesInitStreamAsyncSnd */
void __stdcall SND_fn_vDesInitStreamAsyncSnd(void)
{
    sound_shutdown_async_io();
}
