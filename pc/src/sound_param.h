/* sound_param.h -- the parameters of a sound, as the game gives them and as a renderer takes them */
#ifndef SOUND_PARAM_H
#define SOUND_PARAM_H

#include "sound_real.h"
#include "sound_space.h"
#include "sound_vector.h"

/* A microphone that may hear the sound. */
typedef struct _MicroLink {
    long lId;                       /* the microphone's handle: its description's address */
    int bLinked;
} MicroLink;

/* Only the first member is recovered; the structure's size is not known. */
typedef struct _ExtraSoundParam {
    RollOffParam stRollOff;         /* used when iFlags has bit 2 */
} ExtraSoundParam;

/* Bits of iFlags that the recovered code reads:
     bit 0  the sound has no position: volume and pan are used as given
     bit 1  no Doppler effect
     bit 2  xExtra.stRollOff replaces the default roll-off */
typedef struct _SoundParam {
    SndReal Freq;                   /* pitch ratio */
    SndReal rVol_dB;
    unsigned char ucPan;            /* 0 to 128, 64 is the centre */
    SndVector Pos;
    SndVector Vit;                  /* speed */
    int iFlags;
    int iNbLinks;                   /* entries of astMicro in use */
    unsigned char unk_2c[0x68];
    MicroLink astMicro[1];
    ExtraSoundParam xExtra;
} SoundParam;

/* The position and orientation the game gives a microphone. */
typedef struct _MicroParam {
    SndVector pos;
    SndVector vit;                  /* speed */
    SndVector dirnor;               /* the direction it faces */
    SndVector dirtan;               /* its right-hand side */
} MicroParam;

/* How a renderer wants a position expressed. No symbol names the enumerators, so the
   recovered code uses the values:
     0  a left-right pan
     1  a left-right pan and a front-back pan
     2  an angle in degrees */
typedef int tdePositionFormat;

/* A sound's parameters for one renderer. Only the type's name is evidenced; the member
   names are invented. */
typedef struct _PrivateSoundParam {
    SndReal pitch;                  /* pitch ratio, Doppler included */
    SndReal volume;                 /* decibels, distance attenuation included */
    tdePositionFormat format;
    union {
        struct {
            unsigned char pan;      /* 0 to 128, 64 is the centre */
            unsigned char dolby;    /* 0 to 128, front to back */
        } channels;
        int angle;                  /* degrees */
    } position;
} PrivateSoundParam;

#endif
