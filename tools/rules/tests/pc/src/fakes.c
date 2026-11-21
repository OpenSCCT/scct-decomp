/* no-game-data: synthetic */
struct Padded {
	int		kind;
	char	pad[12];
	int		gap[2];
	int		unk_18;
};

#define STEP( x ) do { ( x )++; } while ( 0 )

/* Every statement here steers a compiler; none is source. */
int fake_steering( struct Padded *item, int value ) {
	volatile int	carrier = value;
	int				unused;

	if ( value ) {
	}
	do {
		value = value;
	} while ( 0 );
	;
	STEP( value );
	return carrier + 0;
}

/* The second parameter stands in for EDX. */
int __fastcall fake_method( struct Padded *self, int reserved_edx, int value ) {
	return self->kind + value;
}

/* An assembly body is verbatim, not matched. */
int fake_asm( void ) {
	__asm { mov eax, 1 }
}
