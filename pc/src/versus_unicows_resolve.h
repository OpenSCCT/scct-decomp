#ifndef VERSUS_UNICOWS_RESOLVE_H
#define VERSUS_UNICOWS_RESOLVE_H

typedef void (__stdcall *UnicowsEntry)(void);

#ifdef __cplusplus
extern "C" {
#endif

extern const char advapi32_dll[];
void __stdcall ResolveThunk(const char *module, const char *name, void *slot,
                            UnicowsEntry overrideEntry, UnicowsEntry fallback);

#ifdef __cplusplus
}
#endif

#endif
