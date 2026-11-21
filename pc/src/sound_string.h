/* sound_string.h -- string services of the sound library (sndstr.c) */
#ifndef SOUND_STRING_H
#define SOUND_STRING_H

/* The rebuild has no C runtime headers, so the runtime functions the sound sources call are
   declared here. */
unsigned int __cdecl strlen(const char *s);
char *__cdecl strcpy(char *dest, const char *src);
char *__cdecl strcat(char *dest, const char *src);
int __cdecl strcmp(const char *s1, const char *s2);
char *__cdecl strncpy(char *dest, const char *src, unsigned int count);
char *__cdecl strncat(char *dest, const char *src, unsigned int count);
int __cdecl sprintf(char *buffer, const char *format, ...);

long __stdcall SND_fn_lStriCmp(const char *s1, const char *s2);
char *__stdcall SND_fn_lStrLwr(char *s);
void __stdcall SND_fn_vStrncpy(char *dest, const char *src, unsigned int size);
void __stdcall SND_fn_vStrncat(char *dest, const char *src, unsigned int size);

#endif
