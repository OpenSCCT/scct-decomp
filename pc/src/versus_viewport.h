// versus_viewport.h -- layout recovered from rendering, input and actor access sites
#ifndef VERSUS_VIEWPORT_H
#define VERSUS_VIEWPORT_H

struct InputMethods;
struct PlayerActor;
struct Device;

struct Viewport {
    const struct InputMethods *methods;
    unsigned char unk_04[0x2c];
    struct PlayerActor *actor;
    unsigned char unk_34[0x3c];
    struct Device *device;
    unsigned char unk_74[0x20];
    int width, height;
    void *screen;
    unsigned char unk_a0[0x90];
    int frame_width, frame_height;
    unsigned char unk_138[8];
    void *surface;
    unsigned char unk_144[12];
    int active;
    unsigned char unk_154[0x38];
    void *first_person;
};

#endif
