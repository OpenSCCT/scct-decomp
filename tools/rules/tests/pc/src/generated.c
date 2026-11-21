/* no-game-data: synthetic */
/* Functions a macro defines are found under their pasted names. */
#define DEFINE_GETTER( Name, Table )			\
	extern int table_##Table[];					\
	int get_##Name( int index ) {				\
		return table_##Table[index];			\
	}

DEFINE_GETTER( red, colors )
DEFINE_GETTER( sub_401000, colors )
