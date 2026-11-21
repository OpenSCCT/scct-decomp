/* no-game-data: synthetic */
struct Record { int count; };

extern int frame_total;

/* Adds the record's count to the frame total. */
void record_add( struct Record *record ) {
	frame_total += record->count;
}

/* Touches no shared declaration, so it passes although its neighbours do not. */
int record_seven( void ) {
	return 7;
}
