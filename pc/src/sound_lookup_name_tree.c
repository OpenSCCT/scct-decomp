#include "sound_error.h"
#include "sound_name_tree.h"
#include "sound_string.h"

unsigned long __fastcall sound_lookup_event_name(SoundEventNames *tree, SoundNameArg name)
{
    SoundCRC crc;
    SoundNameKey key;
    SoundNameKeyArg search;
    SoundNameNode *node;
    char message[256];
    unsigned long result;
    sound_construct_crc(&crc);
    key.methods = sound_name_key_methods;
    key.editor_id = (unsigned long)-1;
    key.crc = sound_crc_name(&crc, name);
    search.key = &key;
    node = sound_find_name_node(tree, search);
    if (tree->cursor == tree->sentinel) {
        sprintf(message, "ERROR: Cannot find the following event in the *.et? table!", name.text);
        SND_fn_vDisplayErrorEx(E_uwSndGenericWarning, message, 3);
        sound_destroy_crc(&crc);
        return (unsigned long)-1;
    }
    result = node->key.editor_id;
    sound_destroy_crc(&crc);
    return result;
}
