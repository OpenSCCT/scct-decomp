/* sound_async_worker.h -- asynchronous file reads behind the sound streams.
   No symbol names these types, functions or globals: every name here is invented. */
#ifndef SOUND_ASYNC_WORKER_H
#define SOUND_ASYNC_WORKER_H

#include "sound_win32.h"

/* One read handed to a worker thread. */
typedef struct AsyncRequest {
    void *mutex;                    /* Win32 mutex */
    int done;
    unsigned char unk_08[4];
    void *file;                     /* Win32 file handle */
    char path[260];
    void *destination;
    void *buffer;
    unsigned long size;
    unsigned long start;
    unsigned long transferred;
} AsyncRequest;

/* A worker thread and the events that drive it. */
typedef struct StreamWorker {
    void *thread;
    unsigned long unk_04;
    void *mutex;
    unsigned char unk_0c[8];
    void *io_ready;
    void *wake;
    void *unk_1c;                   /* Win32 event */
    void *unk_20;                   /* Win32 event */
    void *stop;
} StreamWorker;

/* A file read asynchronously. */
typedef struct AsyncFile {
    char path[260];
    unsigned long initialized;
    void *file;                     /* Win32 file handle */
    AsyncRequest *request;
    StreamWorker *worker;
    struct AsyncFile *next;
} AsyncFile;

/* A file kept open between reads. */
typedef struct CacheEntry {
    char path[260];
    void *handle;                   /* Win32 file handle, INVALID_HANDLE_VALUE when free */
} CacheEntry;

extern CRITICAL_SECTION cache_lock;
extern CacheEntry cache_entries[4];

/* The number of streams the game asked for and the seconds of prefetch each one needs. */
extern unsigned long stream_count;
extern float stream_budget;

int __cdecl sound_init_async_workers(unsigned long count);
void __cdecl sound_shutdown_async_io(void);
AsyncRequest *__cdecl sound_alloc_stream_request(unsigned long bytes);
void __cdecl sound_dispose_stream_request(AsyncRequest *request);
void __cdecl sound_reset_file_cache(void);

#endif
