/* no-game-data: synthetic */
struct Record { int count; float scale; };

/* Returns the record's count. */
int record_count( struct Record *record ) {
	return record->count;
}
