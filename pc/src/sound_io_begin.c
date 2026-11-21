/* sound_io_begin.c -- starts the asynchronous stream service */
#include "sound_async_worker.h"
#include "sound_error.h"
#include "sound_string.h"

/* SND_fn_bInitStreamAsyncSnd: warns when the streams need more prefetch than the limit */
int __stdcall SND_fn_bInitStreamAsyncSnd(unsigned long count, float limit)
{
    char message[256];
    float total;
    stream_count = count;
    total = count * stream_budget;
    if (total > limit) {
        sprintf(message,
                "The sound project's streaming prefetch buffer length is too small.  Current : %.1f > Max : %.1f",
                total, limit);
        SND_fn_vDisplayError(E_uwSndGenericWarning, message);
    }
    return sound_init_async_workers(count);
}
