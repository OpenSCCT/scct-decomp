/* sound_assert_stubs.c -- exported sound assertion stubs */

/* The first three values are forwarded unchanged by the in-image caller. */
void __stdcall _snd_assert_message(unsigned long arg1, unsigned long arg2,
                                   unsigned long arg3, const char *message)
{
}

/* The export has three stack arguments; their types and names remain unknown. */
void __stdcall _snd_assert(unsigned long arg1, unsigned long arg2, unsigned long arg3)
{
}
