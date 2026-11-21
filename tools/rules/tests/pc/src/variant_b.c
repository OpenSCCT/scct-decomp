/* no-game-data: synthetic */
#include "variant_b_build.h"
#include "variant.h"

/* Compiles the second build's declaration, which is marked as a fakematch. */
int variant_b_first( variant_t *value ) {
	return value->first;
}
