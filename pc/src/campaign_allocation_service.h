#ifndef CAMPAIGN_ALLOCATION_SERVICE_H
#define CAMPAIGN_ALLOCATION_SERVICE_H

struct Context;

#ifdef __cplusplus
extern "C" {
#endif
struct Context *__cdecl get_context(void);
void __cdecl release_block(struct Context *context, unsigned char *block, unsigned category);
#ifdef __cplusplus
}
#endif

#endif
