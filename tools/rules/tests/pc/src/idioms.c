/* no-game-data: synthetic */
/* idioms.c -- dense code a programmer of the era wrote; none of it is a finding */

#define HW_STATUS	( (volatile unsigned *)0x10003000 )	/* volatile: memory-mapped status register */

static const int	primes[] = { 2, 3, 5 };

/* Copies a terminated string and returns its length. */
int Idiom_Copy( char *dst, const char *src ) {
	const char	*start = src;

	while ( ( *dst++ = *src++ ) != 0 ) {
	}
	return (int)( src - start ) - 1;
}

/* Waits for the device, then sums the table. */
int Idiom_Sum( int count ) {
	int	total = 0;
	int	i;

	for ( ;; ) {
		if ( *HW_STATUS & 1 ) {	/* volatile: memory-mapped status register */
			break;
		}
	}
	for ( i = 0; i < 3; i++ ) {
		total += primes[i];
	}
	while ( --count ) {
		total++;
	}
	switch ( total ) {
	case 0: ;
	default:
		break;
	}
	if ( total < 0 ) {
		goto fail;
	}
	return total;
fail:
	return -1;
}
