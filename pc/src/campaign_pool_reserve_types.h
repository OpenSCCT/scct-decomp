/* campaign_pool_reserve_types.h -- shared reservation pool layouts. */
#ifndef CAMPAIGN_POOL_RESERVE_TYPES_H
#define CAMPAIGN_POOL_RESERVE_TYPES_H

struct ReservationBlock { void *base, *cursor; unsigned used, capacity; };
struct ReservationPool { unsigned reserved; struct ReservationBlock *first, *end, *limit; unsigned char active; };
struct PoolParameterWord { unsigned value; };
struct ReservationBlockArg { struct ReservationBlock *value; };

#endif
