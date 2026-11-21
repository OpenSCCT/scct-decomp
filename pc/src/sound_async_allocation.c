/* sound_async_allocation.c -- creates and destroys asynchronous read requests */
#include "sound_async_worker.h"
#include "sound_memory.h"

/* sound_alloc_stream_request: a request with its mutex and a buffer of the given size */
AsyncRequest *__cdecl sound_alloc_stream_request(unsigned long bytes)
{
    AsyncRequest *request = SND_fn_pvMallocSnd(sizeof(AsyncRequest));
    if (!request)
        goto failed;
    request->mutex = CreateMutexA(0, 0, 0);
    if (!request->mutex)
        goto free_request;
    request->buffer = SND_fn_pvMallocSnd(bytes);
    if (!request->buffer)
        goto close_mutex;
    return request;

close_mutex:
    CloseHandle(request->mutex);
free_request:
    SND_fn_vFreeSnd(request);
failed:
    return 0;
}

/* sound_dispose_stream_request */
void __cdecl sound_dispose_stream_request(AsyncRequest *request)
{
    SND_fn_vFreeSnd(request->buffer);
    request->buffer = 0;
    CloseHandle(request->mutex);
    SND_fn_vFreeSnd(request);
}
