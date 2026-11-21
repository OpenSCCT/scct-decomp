/* no-game-data: synthetic */
/* Reads the radius by offset instead of through a typed member. */
float object_radius( void *object ) {
	return *(float *)( (char *)object + 0x58 );
}

/* Passes a member's address by offset: a review finding, not a blocked match. */
void *object_child( void *object ) {
	return (unsigned char *)object + 16;
}
