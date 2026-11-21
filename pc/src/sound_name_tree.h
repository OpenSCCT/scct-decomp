#ifndef SOUND_NAME_TREE_H
#define SOUND_NAME_TREE_H

/* The names of sound events, kept by the CRC of each name in a balanced tree. The tree, its
   keys and the CRC calculator are C++ objects: their member functions are written here as
   __fastcall functions that take the object in ECX, with each stack argument wrapped in a
   structure. That is a stand-in for C++ and open work. Every name in this header is
   invented. */

typedef struct SoundCRC {
    const void *methods;
    unsigned long table[256];
} SoundCRC;

/* FAKEMATCH: wraps one stack argument of a C++ member call; the original passes the value itself. */
typedef struct SoundNameArg { const char *text; } SoundNameArg;
typedef struct SoundNameKey {
    const void *methods;
    unsigned long editor_id;
    unsigned long crc;
} SoundNameKey;
typedef struct SoundNameNode {
    SoundNameKey key;
    struct SoundNameNode *lower, *upper;
    int field_14, level;
} SoundNameNode;
typedef struct SoundEventNames {
    SoundNameNode *root, *sentinel, *cursor;
} SoundEventNames;
/* FAKEMATCH: wraps one stack argument of a C++ member call; the original passes the value itself. */
typedef struct SoundNameKeyArg { const SoundNameKey *key; } SoundNameKeyArg;

/* The tree of the loaded project's event names. */
extern SoundEventNames *sound_event_names;

/* Whether the project was loaded with its event names. */
extern unsigned long event_name_support;

void __cdecl sound_set_event_name_support(unsigned long setting);
unsigned long __cdecl sound_get_event_name_support(void);
unsigned long __fastcall sound_lookup_event_name(SoundEventNames *tree, SoundNameArg name);

extern const char sound_crc_methods[];
extern const char sound_name_key_methods[];
SoundCRC *__fastcall sound_construct_crc(SoundCRC *crc);
void __fastcall sound_destroy_crc(SoundCRC *crc);
unsigned long __fastcall sound_crc_name(const SoundCRC *crc, SoundNameArg name);
SoundNameNode *__fastcall sound_find_name_node(SoundEventNames *tree, SoundNameKeyArg argument);

#endif
