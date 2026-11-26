/* sound_buffer_methods.h -- layout shared by the sound buffer and its cache. */
#ifndef SOUND_BUFFER_METHODS_H
#define SOUND_BUFFER_METHODS_H

typedef unsigned long SoundDword;
typedef long SoundResult;
struct SoundBuffer;
struct DirectSoundBuffer;
struct Spatial;
struct Unknown;

struct BufferVTable
{
    void (__fastcall *destroy)(SoundBuffer *, float stack_flags);
};

struct SoundBuffer
{
    const BufferVTable *methods;
    SoundDword played, has_spatial, spatial_enabled, field10;
    DirectSoundBuffer *buffer;
    Spatial *spatial;
    SoundDword field1c, field20, field24, field28, field2c, field30, field34, field38, field3c;
    Unknown *other_interface;
    long timer;
    SoundDword field48, field4c;

    void SetSpatialMode(SoundDword enabled);
    SoundResult SetPosition(SoundDword position);
};

/* The first retail slot points to SoundBuffer's scalar deleting destructor. */
extern "C" const BufferVTable SoundBufferMethods;

#endif
