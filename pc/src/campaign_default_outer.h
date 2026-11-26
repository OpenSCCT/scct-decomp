/* campaign_default_outer.h -- fallback outer-object global and helper */
#ifndef CAMPAIGN_DEFAULT_OUTER_H
#define CAMPAIGN_DEFAULT_OUTER_H

struct Object;

extern struct Object *default_outer_object;
struct Object *__cdecl default_outer(void);

#endif
