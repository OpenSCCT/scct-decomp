/* campaign_pool_reserve_types.h -- shared reservation pool layouts. */
#ifndef CAMPAIGN_POOL_RESERVE_TYPES_H
#define CAMPAIGN_POOL_RESERVE_TYPES_H

struct ReservationBlock { void *base, *cursor; unsigned used, capacity; };
struct ReservationPool { unsigned reserved; struct ReservationBlock *first, *end, *limit; unsigned char active; };
/* FAKEMATCH: this wrapper puts the reserve method's element count on the stack. */
struct PoolParameterWord { unsigned value; };
/* FAKEMATCH: the append method takes the block address. The C fastcall
   declaration uses a by-value struct to pass that address on the stack. */
struct ReservationBlockArg { struct ReservationBlock *value; };

#endif
