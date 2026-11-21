/* no-game-data: synthetic */
#ifndef VARIANT_H
#define VARIANT_H

/* Two builds declare the same structure differently. A unit is judged by the one it compiles. */
#ifdef VARIANT_B
/* FAKEMATCH: the second build's layout is a stand-in. */
typedef struct {
	int	first;
	int	stand_in;
} variant_t;
#else
typedef struct {
	int	first;
} variant_t;
#endif

#endif /* VARIANT_H */
