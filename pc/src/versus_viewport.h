// versus_viewport.h -- layout recovered from rendering, input and actor access sites
#ifndef VERSUS_VIEWPORT_H
#define VERSUS_VIEWPORT_H

struct InputMethods;
struct PlayerActor;
struct URenderDevice;
struct FRenderInterface;

#pragma pack(push, 4)
struct Viewport {
    const struct InputMethods *methods;
    unsigned char unk_04[0x2c];
    struct PlayerActor *actor;
    unsigned char unk_34[0x3c];
    struct URenderDevice *device;
    unsigned char unk_74[0x20];
    double presented_lock_time;      // +0x94, copied from last_lock_time by Present
    unsigned unk_9c;
    unsigned char unk_a0[0x90];
    double last_lock_time;           // +0x130, set to appSeconds() by Lock
    unsigned char unk_138[8];
    struct FRenderInterface *render_interface;
    unsigned char unk_144[12];
    int pending_present;
    unsigned char unk_154[0x38];
    void *first_person;
};
#pragma pack(pop)

#endif
