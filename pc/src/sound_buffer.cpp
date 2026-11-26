#include "sound_buffer_methods.h"

/* FAKEMATCH: wraps one stack argument of a C++ member call; the original passes the value itself. */
typedef struct
{
    SoundDword value;
} WordArg;
/* FAKEMATCH: wraps one stack argument of a C++ member call; the original passes the value itself. */
typedef struct
{
    SoundDword *value;
} OutArg;

/* Method positions follow IDirectSoundBuffer8, IDirectSound3DBuffer and IUnknown. */
typedef struct
{
    void *query_interface, *add_ref;
    SoundDword(__stdcall *release)(DirectSoundBuffer *);
    void *get_caps;
    SoundResult(__stdcall *get_position)(DirectSoundBuffer *, SoundDword *, SoundDword *);
    void *get_format, *get_volume, *get_pan, *get_frequency;
    SoundResult(__stdcall *get_status)(DirectSoundBuffer *, SoundDword *);
    void *initialize, *lock;
    SoundResult(__stdcall *play)(DirectSoundBuffer *, SoundDword, SoundDword, SoundDword);
    SoundResult(__stdcall *set_position)(DirectSoundBuffer *, SoundDword);
    void *set_format;
    SoundResult(__stdcall *set_volume)(DirectSoundBuffer *, long);
    SoundResult(__stdcall *set_pan)(DirectSoundBuffer *, long);
    SoundResult(__stdcall *set_frequency)(DirectSoundBuffer *, SoundDword);
    SoundResult(__stdcall *stop)(DirectSoundBuffer *);
    void *unlock, *restore, *set_fx;
    SoundResult(__stdcall *acquire_resources)(DirectSoundBuffer *, SoundDword, SoundDword, SoundDword *);
} BufferMethods;
struct DirectSoundBuffer
{
    const BufferMethods *methods;
};
typedef struct
{
    void *query_interface, *add_ref;
    SoundDword(__stdcall *release)(Spatial *);
    void *parameters[15];
    SoundResult(__stdcall *set_mode)(Spatial *, SoundDword, SoundDword);
} SpatialMethods;
struct Spatial
{
    const SpatialMethods *methods;
};
typedef struct
{
    void *query_interface, *add_ref;
    SoundDword(__stdcall *release)(Unknown *);
} UnknownMethods;
struct Unknown
{
    const UnknownMethods *methods;
};
extern "C" void __stdcall SND_fn_vDestroyTimer(long timer);
enum
{
    DS3D_NORMAL = 0,
    DS3D_DISABLE = 2,
    DS3D_DEFERRED = 1,
    DS_NO_VIRTUALIZATION = 0x0878000a
};
#define DSERR_INVALIDCALL ((SoundResult)0x88780032)

#pragma code_seg(".text$V75e000")
extern "C" SoundBuffer *__fastcall initialize_sound_buffer(SoundBuffer *self)
{
    self->methods = &SoundBufferMethods;
    self->played = 0;
    self->has_spatial = 0;
    self->spatial_enabled = 0;
    self->field10 = 0;
    self->buffer = 0;
    self->spatial = 0;
    self->other_interface = 0;
    self->field1c = 0;
    self->field20 = 0;
    self->field24 = 0;
    self->field2c = 0;
    self->field30 = 0;
    self->field34 = 0;
    self->field38 = 0;
    self->timer = -2;
    self->field48 = 0;
    self->field4c = 0;
    return self;
}

#pragma code_seg(".text$V75e050")
extern "C" void __fastcall release_sound_buffer(SoundBuffer *self)
{
    self->methods = &SoundBufferMethods;
    if (self->spatial)
    {
        self->spatial->methods->release(self->spatial);
        self->spatial = 0;
    }
    if (self->buffer)
    {
        self->buffer->methods->release(self->buffer);
        self->buffer = 0;
    }
    if (self->other_interface)
    {
        self->other_interface->methods->release(self->other_interface);
        self->other_interface = 0;
    }
    if (self->timer != -2)
    {
        SND_fn_vDestroyTimer(self->timer);
        self->timer = -2;
    }
}

#pragma code_seg(".text$V75e0b0")
extern "C" SoundDword __fastcall buffer_spatial_mode(SoundBuffer *self)
{
    return self->spatial_enabled;
}

#pragma code_seg(".text$V75e0c0")
void SoundBuffer::SetSpatialMode(SoundDword enabled)
{
    if (spatial_enabled != enabled)
    {
        spatial_enabled = enabled;
        if (enabled)
            spatial->methods->set_mode(spatial, DS3D_NORMAL, DS3D_DEFERRED);
        else
            spatial->methods->set_mode(spatial, DS3D_DISABLE, DS3D_DEFERRED);
    }
}

#pragma code_seg(".text$V75e0f0")
extern "C" SoundResult __fastcall play_sound_buffer(SoundBuffer *self, WordArg reserved, WordArg priority,
                                    WordArg flags)
{
    SoundResult hr;
    if (self->buffer)
    {
        hr = self->buffer->methods->play(self->buffer, reserved.value, priority.value, flags.value);
        if (hr == 0 || hr == DS_NO_VIRTUALIZATION)
            self->played = 1;
    }
    else
    {
        hr = DSERR_INVALIDCALL;
    }
    return hr;
}

#pragma code_seg(".text$V75e130")
extern "C" SoundResult __fastcall set_buffer_pan(SoundBuffer *self, WordArg value)
{
    return self->buffer->methods->set_pan(self->buffer, value.value);
}

#pragma code_seg(".text$V75e150")
extern "C" SoundResult __fastcall set_buffer_volume(SoundBuffer *self, WordArg value)
{
    return self->buffer->methods->set_volume(self->buffer, value.value);
}

#pragma code_seg(".text$V75e170")
extern "C" SoundResult __fastcall set_buffer_frequency(SoundBuffer *self, WordArg value)
{
    return self->buffer->methods->set_frequency(self->buffer, value.value);
}

#pragma code_seg(".text$V75e190")
SoundResult SoundBuffer::SetPosition(SoundDword position)
{
    return buffer->methods->set_position(buffer, position);
}

#pragma code_seg(".text$V75e1b0")
extern "C" SoundResult __fastcall get_buffer_cursors(SoundBuffer *self, OutArg play, OutArg write)
{
    return self->buffer->methods->get_position(self->buffer, play.value, write.value);
}

#pragma code_seg(".text$V75e1d0")
extern "C" SoundResult __fastcall stop_sound_buffer(SoundBuffer *self)
{
    return self->buffer->methods->stop(self->buffer);
}

#pragma code_seg(".text$V75e1e0")
extern "C" SoundResult __fastcall acquire_buffer_resources(SoundBuffer *self, WordArg flags, WordArg count,
                                           OutArg result)
{
    return self->buffer->methods->acquire_resources(self->buffer, flags.value, count.value,
                                                    result.value);
}

#pragma code_seg(".text$V75e200")
extern "C" SoundResult __fastcall get_buffer_status(SoundBuffer *self, OutArg status)
{
    return self->buffer->methods->get_status(self->buffer, status.value);
}
