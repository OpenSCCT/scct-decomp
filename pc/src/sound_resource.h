/* sound_resource.h -- a sound resource as it is kept in memory */
#ifndef SOUND_RESOURCE_H
#define SOUND_RESOURCE_H

/* The structure's name and the names Id, eType and uRes are those of the sibling builds'
   _tdstBlockResourceMem, whose layout is another one; ulDataSize, hFirstElementOpt and
   lNumberOfElementsOpt are the sibling's names for the same values. Every other member name
   is invented from the way the recovered code uses the member. A member named unk_ is
   copied or skipped without a known meaning. */

/* The enumerators are the sibling build's. This build's values of TYPE_SAMPLE,
   TYPE_MULTITRACK and TYPE_SILENCE are fixed by the functions that unload each type; they
   are the sibling's numbering with its *_OLD entries dropped. Types 5 and 9 are handled by
   recovered code but nothing names them. */
typedef enum _tdeTypeResource {
    TYPE_INVALID = 0,
    TYPE_SAMPLE = 1,
    TYPE_MULTITRACK = 6,
    TYPE_SILENCE = 8
} tdeTypeResource;

typedef struct _tdstBlockResourceMem tdstBlockResourceMem;

/* TYPE_SAMPLE */
typedef struct _tdstTypeSampleMem {
    int bBalance;                   /* guess: the game may pan it. Every type starts with it. */
    unsigned long ulDataSize;
    unsigned long unk_08;
    unsigned long unk_0c;
    int owned;                      /* the library allocated sample_data */
    int use_external;               /* the data is in a file of its own */
    unsigned long payload_address;
    unsigned long external_field;
    unsigned long unk_20;
    unsigned long channels;
    int external;
    void *sample_data;
    unsigned long buffer_size;
} tdstTypeSampleMem;

/* An element of a resource of eType 5. */
typedef struct _tdstType5Element {
    tdstBlockResourceMem *resource;
    unsigned long unk_04[4];
} tdstType5Element;

/* eType 5: a resource made of other resources. */
typedef struct _tdstType5Mem {
    int bBalance;
    unsigned char unk_04[0x2c];
    tdstType5Element *elements;
    long count;
} tdstType5Mem;

/* One track of a multitrack resource. */
typedef struct _tdstMultiTrackElement {
    unsigned long unk_00[2];
    unsigned long channels;
    unsigned long unk_0c[3];
} tdstMultiTrackElement;

/* TYPE_MULTITRACK */
typedef struct _tdstTypeMultiTrackMem {
    int bBalance;
    unsigned char unk_04[0x10];
    int use_external;               /* the data is in a file of its own */
    void *data;
    unsigned char unk_1c[0x10];
    tdstMultiTrackElement *hFirstElementOpt;
    long lNumberOfElementsOpt;
} tdstTypeMultiTrackMem;

/* eType 9. */
typedef struct _tdstType9Mem {
    int bBalance;
    unsigned char unk_04[0x38];
    unsigned long channels;
} tdstType9Mem;

struct _tdstBlockResourceMem {
    unsigned long Id;               /* the identifier the sound editor gave it */
    tdeTypeResource eType;
    unsigned long unk_08;
    int bIsLoaded;                  /* guess, from the sibling's header member of that name */
    union {
        tdstTypeSampleMem stSample;
        tdstType5Mem stType5;
        tdstTypeMultiTrackMem stMultiTrack;
        tdstType9Mem stType9;
        unsigned char unk_10[0x58];
    } uRes;
};

/* A sample resource as a bank file stores it. Members are named after the memory members
   they fill; the structure's full size is not known. */
typedef struct _tdstBlockResourceDisk {
    unsigned long Id;
    tdeTypeResource eType;
    unsigned long unk_08;
    unsigned long data_offset;
    unsigned long internal_offset;
    unsigned long unk_14;
    int bBalance;
    unsigned long ulDataSize;
    unsigned long unk_20;
    unsigned long unk_24;
    int owned;
    int use_external;
    unsigned long unk_30;
    unsigned long channels;
    int external;
    unsigned long external_field;
    unsigned long external_offset;
} tdstBlockResourceDisk;

#endif
