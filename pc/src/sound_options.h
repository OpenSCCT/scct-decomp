/* sound_options.h -- configuration stored in DARE.INI */
#ifndef SOUND_OPTIONS_H
#define SOUND_OPTIONS_H

/* The initializer builds this path from the sound directory and "DARE.INI". */
extern char sound_ini_path[256];

int __stdcall SND_fn_bGetOptions(const char *section, const char *key, char *value,
                                 unsigned long size);
void __stdcall SND_fn_vSetOptions(const char *section, const char *key, const char *value);

#endif
