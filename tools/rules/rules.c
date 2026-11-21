/* rules.c -- the project's code-rule checker (the `rules` command in AGENTS.md)
 *
 * Reads the unit manifests and the C and C++ sources they name, tests each source
 * against the rules in docs/code-rules/rules.md, and reports two numbers per
 * executable: bytes matched, and bytes matched under the rules. A unit whose bytes
 * match but whose source breaks a [match] rule is MATCH-PENDING.
 *
 * A finding belongs to the declaration or function it sits in. A unit's function is
 * charged with its own findings and with those of everything it names: the types,
 * globals, macros and inline helpers its source refers to, followed transitively.
 *
 * Build:  cc -std=c99 -O2 -Wall -Wextra -o rules tools/rules/rules.c
 * Usage:  rules [--root DIR] [--findings] [--units FILE] [--explain UNIT]
 *               [--json FILE] [--check] [--markdown]
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_MSC_VER)
#include <io.h>
#else
#include <dirent.h>
#endif

/*
===============================================================================

RULE TABLE

===============================================================================
*/

/* [match] rules block a match; the others are advisory and never change a count. */
enum {
	RULE_R1, RULE_R2, RULE_R4, RULE_R13, RULE_R17, RULE_R18,
	NUM_MATCH_RULES,
	RULE_R4_REVIEW = NUM_MATCH_RULES, RULE_R7, RULE_R12, RULE_R22, RULE_R25, RULE_R27,
	RULE_R33, RULE_R35, RULE_R37,
	NUM_RULES
};

static const char *const ruleNames[NUM_RULES] = {
	"R1", "R2", "R4", "R13", "R17", "R18",
	"R4", "R7", "R12", "R22", "R25", "R27", "R33", "R35", "R37"
};

/* Placeholder spellings reported as open naming work (R7). AGENTS.md lists them. */
static const char *const placeholderPrefixes[] = {
	"FUN_", "DAT_", "sub_", "unk_", "local_", "param_", "field_0x", "uStack", "iVar",
	"m_Unk", "UnkType_", "VirtualSlot", "virtual_slot", NULL
};

/* Numbered generic names: the word, then digits only. */
static const char *const numberedGenerics[] = {
	"temp", "tmp", "ptr", "result", "value", "var", "arg", "local", "v", "t", NULL
};

/* Filler members that stand for an unknown range without naming its offset (R27). */
static const char *const fillerWords[] = {
	"gap", "unknown", "unused", "reserved", "filler", "skip", "before", "after",
	"align", "alignment", NULL
};

/* Byte types whose pointer casts carry offset arithmetic (R4). */
static const char *const byteTypes[] = {
	"char", "BYTE", "byte", "u8", "uint8", "uint8_t", "uchar", "Uint8", NULL
};

/* Tokens the profile's compilers reject (R22). */
static const char *const dialectTokens[] = {
	"__attribute__", "regparm", "nullptr", "constexpr", "static_assert", "_Static_assert",
	"alignas", "noexcept", "decltype", NULL
};

/* Inline-assembly tokens of the dialect (R18). */
static const char *const asmTokens[] = {
	"__asm", "_asm", "__emit", "_emit", "naked", "INCLUDE_ASM", NULL
};

/*
===============================================================================

MEMORY AND STRINGS

===============================================================================
*/

/* Prints a message and stops: every error here is a broken input or a bug. */
static void Fatal( const char *format, ... ) {
	va_list args;

	va_start( args, format );
	fprintf( stderr, "rules: " );
	vfprintf( stderr, format, args );
	fprintf( stderr, "\n" );
	va_end( args );
	exit( 2 );
}

/* Allocates zeroed memory or stops. Nothing is freed: the run is short. */
static void *Alloc( size_t size ) {
	void *memory = calloc( 1, size ? size : 1 );

	if ( !memory ) {
		Fatal( "out of memory" );
	}
	return memory;
}

/* Grows an array to hold at least `need` elements of `size` bytes. */
static void *Grow( void *memory, int *capacity, int need, size_t size ) {
	int old = *capacity;

	if ( need <= old ) {
		return memory;
	}
	*capacity = old ? old * 2 : 64;
	if ( *capacity < need ) {
		*capacity = need;
	}
	memory = realloc( memory, (size_t)*capacity * size );
	if ( !memory ) {
		Fatal( "out of memory" );
	}
	memset( (char *)memory + (size_t)old * size, 0, (size_t)( *capacity - old ) * size );
	return memory;
}

/* Copies `length` bytes into a new terminated string. */
static char *CopyString( const char *text, int length ) {
	char *copy = Alloc( (size_t)length + 1 );

	memcpy( copy, text, (size_t)length );
	return copy;
}

/* Formats into a new string. */
static char *Format( const char *format, ... ) {
	char buffer[2048];
	va_list args;

	va_start( args, format );
	vsnprintf( buffer, sizeof( buffer ), format, args );
	va_end( args );
	return CopyString( buffer, (int)strlen( buffer ) );
}

/* Reads a whole file; returns NULL when it cannot be opened. */
static char *ReadFile( const char *path, int *length ) {
	FILE *file = fopen( path, "rb" );
	char *data;
	long size;

	if ( !file ) {
		return NULL;
	}
	fseek( file, 0, SEEK_END );
	size = ftell( file );
	fseek( file, 0, SEEK_SET );
	data = Alloc( (size_t)size + 1 );
	if ( size && fread( data, 1, (size_t)size, file ) != (size_t)size ) {
		Fatal( "cannot read %s", path );
	}
	fclose( file );
	*length = (int)size;
	return data;
}

/* True when `text` ends with `suffix`. */
static int EndsWith( const char *text, const char *suffix ) {
	size_t length = strlen( text );
	size_t tail = strlen( suffix );

	return length >= tail && !strcmp( text + length - tail, suffix );
}

/* True when `word` is one of a NULL-terminated list. */
static int InList( const char *word, const char *const *list ) {
	int i;

	for ( i = 0; list[i]; i++ ) {
		if ( !strcmp( word, list[i] ) ) {
			return 1;
		}
	}
	return 0;
}

/*
===============================================================================

SYMBOL TABLE

Identifier and punctuator spellings are interned, so tokens compare as integers.

===============================================================================
*/

static char **symbolText;
static int *symbolNext;
static int *symbolFirstNode;		/* head of the list of nodes with this name */
static int numSymbols, symbolCapacity, firstNodeCapacity;
static int symbolBuckets[1 << 16];

/* Interns a spelling and returns its index. Index 0 is never used. */
static int Intern( const char *text, int length ) {
	unsigned hash = 2166136261u;
	int i, symbol;

	for ( i = 0; i < length; i++ ) {
		hash = ( hash ^ (unsigned char)text[i] ) * 16777619u;
	}
	hash &= 0xffff;
	for ( symbol = symbolBuckets[hash]; symbol; symbol = symbolNext[symbol] ) {
		if ( (int)strlen( symbolText[symbol] ) == length && !memcmp( symbolText[symbol], text, (size_t)length ) ) {
			return symbol;
		}
	}
	if ( !numSymbols ) {
		numSymbols = 1;
	}
	i = symbolCapacity;
	symbolText = Grow( symbolText, &i, numSymbols + 1, sizeof( *symbolText ) );
	symbolNext = Grow( symbolNext, &symbolCapacity, numSymbols + 1, sizeof( *symbolNext ) );
	symbolFirstNode = Grow( symbolFirstNode, &firstNodeCapacity, numSymbols + 1, sizeof( *symbolFirstNode ) );
	symbol = numSymbols++;
	symbolText[symbol] = CopyString( text, length );
	symbolNext[symbol] = symbolBuckets[hash];
	symbolBuckets[hash] = symbol;
	symbolFirstNode[symbol] = -1;
	return symbol;
}

static int InternString( const char *text ) {
	return Intern( text, (int)strlen( text ) );
}

/* Keyword and punctuator symbols the parser tests by value. */
static int sLParen, sRParen, sLBrace, sRBrace, sLBracket, sRBracket, sSemi, sComma, sStar,
	sAssign, sColon, sScope, sTilde, sPlus, sMinus, sNot, sArrow, sAmp, sPaste, sLess, sGreater,
	sStruct, sClass, sUnion, sEnum, sTypedef, sExtern, sStatic, sInline, sInline2, sForceInline,
	sVolatile, sConst, sVirtual, sIf, sElse, sFor, sWhile, sDo, sThis, sOperator, sDeclspec,
	sAttribute, sFastcall, sNamespace, sUnsigned, sSigned, sVoid, sReturn, sRegister, sPublic,
	sPrivate, sProtected, sFriend, sTemplate, sSwitch, sCase, sDefault, sGoto, sSizeof;

static void InternKeywords( void ) {
	sLParen = InternString( "(" );		sRParen = InternString( ")" );
	sLBrace = InternString( "{" );		sRBrace = InternString( "}" );
	sLBracket = InternString( "[" );	sRBracket = InternString( "]" );
	sSemi = InternString( ";" );		sComma = InternString( "," );
	sStar = InternString( "*" );		sAssign = InternString( "=" );
	sColon = InternString( ":" );		sScope = InternString( "::" );
	sTilde = InternString( "~" );		sPlus = InternString( "+" );
	sMinus = InternString( "-" );		sNot = InternString( "!" );
	sArrow = InternString( "->" );		sAmp = InternString( "&" );
	sPaste = InternString( "##" );		sLess = InternString( "<" );
	sGreater = InternString( ">" );
	sStruct = InternString( "struct" );	sClass = InternString( "class" );
	sUnion = InternString( "union" );	sEnum = InternString( "enum" );
	sTypedef = InternString( "typedef" );	sExtern = InternString( "extern" );
	sStatic = InternString( "static" );	sInline = InternString( "inline" );
	sInline2 = InternString( "__inline" );	sForceInline = InternString( "__forceinline" );
	sVolatile = InternString( "volatile" );	sConst = InternString( "const" );
	sVirtual = InternString( "virtual" );	sIf = InternString( "if" );
	sElse = InternString( "else" );		sFor = InternString( "for" );
	sWhile = InternString( "while" );	sDo = InternString( "do" );
	sThis = InternString( "this" );		sOperator = InternString( "operator" );
	sDeclspec = InternString( "__declspec" );	sAttribute = InternString( "__attribute__" );
	sFastcall = InternString( "__fastcall" );	sNamespace = InternString( "namespace" );
	sUnsigned = InternString( "unsigned" );	sSigned = InternString( "signed" );
	sVoid = InternString( "void" );		sReturn = InternString( "return" );
	sRegister = InternString( "register" );	sPublic = InternString( "public" );
	sPrivate = InternString( "private" );	sProtected = InternString( "protected" );
	sFriend = InternString( "friend" );	sTemplate = InternString( "template" );
	sSwitch = InternString( "switch" );	sCase = InternString( "case" );
	sDefault = InternString( "default" );	sGoto = InternString( "goto" );
	sSizeof = InternString( "sizeof" );
}

/*
===============================================================================

SOURCE MODEL

===============================================================================
*/

typedef enum { T_ID, T_NUM, T_STR, T_PUNCT } tokenKind_t;

typedef struct {
	int kind;		/* tokenKind_t */
	int symbol;		/* interned spelling */
	int line;
} token_t;

/* Flags a comment leaves on the lines it covers. */
#define LF_COMMENT			0x01	/* a comment ends on this line */
#define LF_VOLATILE_NOTE	0x02	/* "volatile:" evidence note */
#define LF_EXCEPTION		0x04	/* RULE-EXCEPTION */
#define LF_QUIRK			0x08	/* BUG:, NOTE: or R36 */
#define LF_PROBE			0x10	/* marked as a probe */
#define LF_SDK_NOTE			0x20	/* names the SDK or file format */

typedef struct {
	int name;				/* symbol */
	int numParams;
	int params[16];			/* symbols */
	int begin, end;			/* range in the file's macro tokens */
	int line;
	int node;
} macro_t;

typedef struct {
	char *path;				/* edition-relative, forward slashes: "src/unit.c" */
	int isHeader;
	token_t *tokens;		/* code outside macro definitions */
	int *mates;				/* matching bracket for each code token, or -1 */
	int numTokens, tokenCapacity, mateCapacity;
	token_t *macroTokens;	/* replacement lists of every #define */
	int *macroMates;
	int numMacroTokens, macroTokenCapacity;
	macro_t *macros;
	int numMacros, macroCapacity;
	int *includes;			/* file indices */
	int numIncludes, includeCapacity;
	unsigned char *lineFlags;
	int numLines;
	unsigned char *reach;	/* reach[f]: this file sees file f through its includes */
} file_t;

typedef enum {
	N_TYPE,			/* struct, class, union or enum with a body, or a typedef */
	N_FORWARD,		/* "struct name;" */
	N_GLOBAL,
	N_FUNCTION,
	N_PROTOTYPE,
	N_MACRO
} nodeKind_t;

#define NF_STATIC		0x01
#define NF_INLINE		0x02
#define NF_EXTERN		0x04
#define NF_IN_MACRO		0x08	/* its tokens are macro tokens */
#define NF_GENERATED	0x10	/* a function a macro invocation defines */

typedef struct {
	int kind;				/* nodeKind_t */
	int name;				/* symbol */
	int file;
	int line;
	int begin, end;			/* token range, in code or macro tokens (NF_IN_MACRO) */
	int flags;
	int keyword;			/* struct, class, union or enum symbol, for types */
	unsigned bodyHash;		/* types and globals: hash of the declaration's spelling */
	unsigned matchMask;		/* [match] rules this node itself breaks */
	int nextSameName;
	int stamp;				/* closure visit marker */
	int *refs;				/* names a macro invocation builds by pasting */
	int numRefs, refCapacity;
} node_t;

typedef struct {
	int file;
	int line;
	int rule;
	int node;				/* owning node, or -1 for a file-level finding */
	char *message;
} finding_t;

static file_t *files;
static int numFiles, fileCapacity;
static node_t *nodes;
static int numNodes, nodeCapacity;
static finding_t *findings;
static int numFindings, findingCapacity;
static int currentEditionFirstFile;	/* files of other editions are never visible */

/* Records a finding against a node (or the file, when node is -1). */
static void Report( int file, int line, int rule, int node, const char *message ) {
	finding_t *finding;

	/* A recorded exception excuses a style rule, never a [match] rule. */
	if ( rule >= NUM_MATCH_RULES && line >= 1 && line <= files[file].numLines
		&& ( ( files[file].lineFlags[line] | files[file].lineFlags[line - 1] ) & LF_EXCEPTION ) ) {
		return;
	}
	findings = Grow( findings, &findingCapacity, numFindings + 1, sizeof( *findings ) );
	finding = &findings[numFindings++];
	finding->file = file;
	finding->line = line;
	finding->rule = rule;
	finding->node = node;
	finding->message = CopyString( message, (int)strlen( message ) );
	if ( node >= 0 && rule < NUM_MATCH_RULES ) {
		nodes[node].matchMask |= 1u << rule;
	}
}

/* Adds a node and links it under its name. */
static int AddNode( int kind, int name, int file, int line, int begin, int end, int flags ) {
	node_t *node;

	nodes = Grow( nodes, &nodeCapacity, numNodes + 1, sizeof( *nodes ) );
	node = &nodes[numNodes];
	node->kind = kind;
	node->name = name;
	node->file = file;
	node->line = line;
	node->begin = begin;
	node->end = end;
	node->flags = flags;
	node->nextSameName = symbolFirstNode[name];
	symbolFirstNode[name] = numNodes;
	return numNodes++;
}

/*
===============================================================================

LEXER

===============================================================================
*/

static const char *const punctuators[] = {
	"...", "<<=", ">>=", "->*", "::", "->", "++", "--", "<<", ">>", "<=", ">=", "==", "!=",
	"&&", "||", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "##", NULL
};

/* Appends a token to the code or macro stream. */
static void PushToken( file_t *file, int toMacro, int kind, const char *text, int length, int line ) {
	token_t *token;

	if ( toMacro ) {
		file->macroTokens = Grow( file->macroTokens, &file->macroTokenCapacity, file->numMacroTokens + 1,
			sizeof( token_t ) );
		token = &file->macroTokens[file->numMacroTokens++];
	} else {
		file->tokens = Grow( file->tokens, &file->tokenCapacity, file->numTokens + 1, sizeof( token_t ) );
		token = &file->tokens[file->numTokens++];
	}
	token->kind = kind;
	token->symbol = Intern( text, length );
	token->line = line;
}

/* Marks the lines a comment covers with what the comment says. */
static void NoteComment( file_t *file, const char *text, int length, int firstLine, int lastLine ) {
	char *copy = CopyString( text, length );
	int flags = 0;
	int line;

	if ( strstr( copy, "volatile:" ) ) {
		flags |= LF_VOLATILE_NOTE;
	}
	if ( strstr( copy, "RULE-EXCEPTION" ) ) {
		flags |= LF_EXCEPTION;
	}
	if ( strstr( copy, "BUG:" ) || strstr( copy, "NOTE:" ) || strstr( copy, "R36" ) ) {
		flags |= LF_QUIRK;
	}
	if ( strstr( copy, "PROBE" ) || strstr( copy, "probe:" ) ) {
		flags |= LF_PROBE;
	}
	if ( strstr( copy, "SDK" ) || strstr( copy, "file format" ) ) {
		flags |= LF_SDK_NOTE;
	}
	for ( line = firstLine; line <= lastLine; line++ ) {
		file->lineFlags[line] |= (unsigned char)flags;
	}
	file->lineFlags[lastLine] |= LF_COMMENT;
	free( copy );
}

static int FindFile( const char *path );
static int LoadFile( const char *editionDir, const char *path );

/* Resolves `name` beside the including file and records the include edge. */
static void AddInclude( const char *editionDir, int fileIndex, const char *name, int length ) {
	char path[1024];
	const char *slash = strrchr( files[fileIndex].path, '/' );
	int dirLength = slash ? (int)( slash - files[fileIndex].path ) + 1 : 0;
	int target;
	file_t *file;

	if ( dirLength + length >= (int)sizeof( path ) ) {
		return;
	}
	memcpy( path, files[fileIndex].path, (size_t)dirLength );
	memcpy( path + dirLength, name, (size_t)length );
	path[dirLength + length] = 0;
	target = LoadFile( editionDir, path );
	if ( target < 0 ) {
		return;		/* a system or SDK header: outside the project */
	}
	file = &files[fileIndex];
	file->includes = Grow( file->includes, &file->includeCapacity, file->numIncludes + 1, sizeof( int ) );
	file->includes[file->numIncludes++] = target;
}

/* Splits a file into code tokens, macro replacement lists and line notes. */
static void LexFile( const char *editionDir, int fileIndex, const char *text, int length ) {
	file_t *file = &files[fileIndex];
	const char *p = text;
	const char *end = text + length;
	int line = 1;
	int lineStart = 1;		/* only blanks since the last newline */
	int inDefine = 0;		/* tokens go to the macro stream until the line ends */
	int i;

	for ( i = 0; i < length; i++ ) {
		if ( text[i] == '\n' ) {
			file->numLines++;
		}
	}
	file->numLines += 2;
	file->lineFlags = Alloc( (size_t)file->numLines + 2 );

	while ( p < end ) {
		char c = *p;

		if ( c == '\\' && p + 1 < end && ( p[1] == '\n' || ( p[1] == '\r' && p + 2 < end && p[2] == '\n' ) ) ) {
			p += p[1] == '\n' ? 2 : 3;		/* line continuation */
			line++;
			continue;
		}
		if ( c == '\n' ) {
			if ( inDefine ) {
				file->macros[file->numMacros - 1].end = file->numMacroTokens;
				inDefine = 0;
			}
			line++;
			lineStart = 1;
			p++;
			continue;
		}
		if ( c == ' ' || c == '\t' || c == '\r' || c == '\f' || c == '\v' ) {
			p++;
			continue;
		}
		if ( c == '/' && p + 1 < end && p[1] == '/' ) {
			const char *start = p;

			while ( p < end && *p != '\n' ) {
				p++;
			}
			NoteComment( file, start, (int)( p - start ), line, line );
			continue;
		}
		if ( c == '/' && p + 1 < end && p[1] == '*' ) {
			const char *start = p;
			int firstLine = line;

			p += 2;
			while ( p + 1 < end && !( p[0] == '*' && p[1] == '/' ) ) {
				if ( *p == '\n' ) {
					line++;
				}
				p++;
			}
			p = p + 2 <= end ? p + 2 : end;
			NoteComment( file, start, (int)( p - start ), firstLine, line );
			continue;
		}
		if ( c == '#' && lineStart && !inDefine ) {
			const char *word;
			int wordLength;

			p++;
			while ( p < end && ( *p == ' ' || *p == '\t' ) ) {
				p++;
			}
			word = p;
			while ( p < end && isalpha( (unsigned char)*p ) ) {
				p++;
			}
			wordLength = (int)( p - word );
			lineStart = 0;
			if ( wordLength == 6 && !memcmp( word, "define", 6 ) ) {
				macro_t *macro;
				const char *name;

				while ( p < end && ( *p == ' ' || *p == '\t' ) ) {
					p++;
				}
				name = p;
				while ( p < end && ( isalnum( (unsigned char)*p ) || *p == '_' ) ) {
					p++;
				}
				file->macros = Grow( file->macros, &file->macroCapacity, file->numMacros + 1, sizeof( macro_t ) );
				macro = &file->macros[file->numMacros++];
				macro->name = Intern( name, (int)( p - name ) );
				macro->line = line;
				macro->numParams = -1;		/* object-like */
				macro->node = -1;
				if ( p < end && *p == '(' ) {
					macro->numParams = 0;
					p++;
					while ( p < end && *p != ')' && *p != '\n' ) {
						if ( isalpha( (unsigned char)*p ) || *p == '_' ) {
							const char *param = p;

							while ( p < end && ( isalnum( (unsigned char)*p ) || *p == '_' ) ) {
								p++;
							}
							if ( macro->numParams < 16 ) {
								macro->params[macro->numParams++] = Intern( param, (int)( p - param ) );
							}
						} else {
							p++;
						}
					}
					if ( p < end && *p == ')' ) {
						p++;
					}
				}
				macro->begin = macro->end = file->numMacroTokens;
				inDefine = 1;
				continue;
			}
			if ( wordLength == 7 && !memcmp( word, "include", 7 ) ) {
				while ( p < end && ( *p == ' ' || *p == '\t' ) ) {
					p++;
				}
				if ( p < end && *p == '"' ) {
					const char *name = ++p;

					while ( p < end && *p != '"' && *p != '\n' ) {
						p++;
					}
					AddInclude( editionDir, fileIndex, name, (int)( p - name ) );
					file = &files[fileIndex];		/* the file table may have moved */
				}
			} else if ( wordLength == 2 && !memcmp( word, "if", 2 ) ) {
				const char *q = p;

				while ( q < end && ( *q == ' ' || *q == '\t' ) ) {
					q++;
				}
				if ( q < end && *q == '0' && ( q + 1 == end || isspace( (unsigned char)q[1] ) ) ) {
					Report( fileIndex, line, RULE_R37, -1, "#if 0 block: no build compiles it" );
				}
			}
			/* the rest of any other directive is not code */
			while ( p < end && *p != '\n' ) {
				if ( *p == '\\' && p + 1 < end && ( p[1] == '\n' || p[1] == '\r' ) ) {
					p += p[1] == '\n' ? 1 : 2;
					line++;
				}
				p++;
			}
			continue;
		}
		lineStart = 0;
		if ( isalpha( (unsigned char)c ) || c == '_' || c == '$' ) {
			const char *start = p;

			while ( p < end && ( isalnum( (unsigned char)*p ) || *p == '_' || *p == '$' ) ) {
				p++;
			}
			PushToken( file, inDefine, T_ID, start, (int)( p - start ), line );
			continue;
		}
		if ( isdigit( (unsigned char)c ) || ( c == '.' && p + 1 < end && isdigit( (unsigned char)p[1] ) ) ) {
			const char *start = p;

			while ( p < end && ( isalnum( (unsigned char)*p ) || *p == '.' || *p == '_'
				|| ( ( *p == '+' || *p == '-' ) && ( p[-1] == 'e' || p[-1] == 'E' )
					&& !( start[0] == '0' && ( start[1] == 'x' || start[1] == 'X' ) ) ) ) ) {
				p++;
			}
			PushToken( file, inDefine, T_NUM, start, (int)( p - start ), line );
			continue;
		}
		if ( c == '"' || c == '\'' ) {
			const char *start = p++;

			while ( p < end && *p != c && *p != '\n' ) {
				if ( *p == '\\' && p + 1 < end ) {
					p++;
				}
				p++;
			}
			if ( p < end && *p == c ) {
				p++;
			}
			PushToken( file, inDefine, T_STR, start, (int)( p - start ), line );
			continue;
		}
		for ( i = 0; punctuators[i]; i++ ) {
			int size = (int)strlen( punctuators[i] );

			if ( p + size <= end && !memcmp( p, punctuators[i], (size_t)size ) ) {
				break;
			}
		}
		if ( punctuators[i] ) {
			PushToken( file, inDefine, T_PUNCT, p, (int)strlen( punctuators[i] ), line );
			p += strlen( punctuators[i] );
		} else {
			PushToken( file, inDefine, T_PUNCT, p, 1, line );
			p++;
		}
	}
	if ( inDefine ) {
		file->macros[file->numMacros - 1].end = file->numMacroTokens;
	}
}

/* Pairs every bracket in [begin, end) with its mate; unpaired ones get -1. */
static void MatchBrackets( const token_t *tokens, int *mates, int begin, int end ) {
	int *stack = Alloc( sizeof( int ) * (size_t)( end - begin + 1 ) );
	int depth = 0;
	int i;

	for ( i = begin; i < end; i++ ) {
		int symbol = tokens[i].symbol;

		mates[i] = -1;
		if ( tokens[i].kind != T_PUNCT ) {
			continue;
		}
		if ( symbol == sLParen || symbol == sLBrace || symbol == sLBracket ) {
			stack[depth++] = i;
		} else if ( symbol == sRParen || symbol == sRBrace || symbol == sRBracket ) {
			int open = symbol == sRParen ? sLParen : symbol == sRBrace ? sLBrace : sLBracket;

			if ( depth && tokens[stack[depth - 1]].symbol == open ) {
				depth--;
				mates[i] = stack[depth];
				mates[stack[depth]] = i;
			}
		}
	}
	free( stack );
}

static int FindFile( const char *path ) {
	int i;

	for ( i = currentEditionFirstFile; i < numFiles; i++ ) {
		if ( !strcmp( files[i].path, path ) ) {
			return i;
		}
	}
	return -1;
}

/* Loads and lexes an edition-relative source once; returns its index or -1. */
static int LoadFile( const char *editionDir, const char *path ) {
	char *full, *text;
	int length, index, i;

	index = FindFile( path );
	if ( index >= 0 ) {
		return index;
	}
	full = Format( "%s/%s", editionDir, path );
	text = ReadFile( full, &length );
	if ( !text ) {
		return -1;
	}
	files = Grow( files, &fileCapacity, numFiles + 1, sizeof( *files ) );
	index = numFiles++;
	files[index].path = CopyString( path, (int)strlen( path ) );
	files[index].isHeader = EndsWith( path, ".h" ) || EndsWith( path, ".hpp" ) || EndsWith( path, ".inl" );
	LexFile( editionDir, index, text, length );
	i = 0;
	files[index].mates = Grow( NULL, &i, files[index].numTokens + 1, sizeof( int ) );
	MatchBrackets( files[index].tokens, files[index].mates, 0, files[index].numTokens );
	i = 0;
	files[index].macroMates = Grow( NULL, &i, files[index].numMacroTokens + 1, sizeof( int ) );
	for ( i = 0; i < files[index].numMacros; i++ ) {
		MatchBrackets( files[index].macroTokens, files[index].macroMates, files[index].macros[i].begin,
			files[index].macros[i].end );
	}
	return index;
}

/*
===============================================================================

CODE CHECKS

These run over a function body, an inline method or a macro's replacement list.

===============================================================================
*/

static const char *Text( const token_t *token ) {
	return symbolText[token->symbol];
}

/* True when the token ends an operand: a name, a number, ")" or "]". */
static int EndsOperand( const token_t *token ) {
	return token->kind == T_ID || token->kind == T_NUM || token->symbol == sRParen || token->symbol == sRBracket;
}

/* True when the tokens at `i` spell a cast to a byte pointer; sets *close to its ")". */
static int IsBytePointerCast( const token_t *tokens, int i, int end, int *close ) {
	int j = i + 1;

	if ( tokens[i].symbol != sLParen ) {
		return 0;
	}
	while ( j < end && ( tokens[j].symbol == sConst || tokens[j].symbol == sUnsigned || tokens[j].symbol == sSigned ) ) {
		j++;
	}
	if ( j >= end || tokens[j].kind != T_ID || !InList( Text( &tokens[j] ), byteTypes ) ) {
		return 0;
	}
	j++;
	while ( j < end && tokens[j].symbol == sConst ) {
		j++;
	}
	if ( j + 1 >= end || tokens[j].symbol != sStar || tokens[j + 1].symbol != sRParen ) {
		return 0;
	}
	*close = j + 1;
	return 1;
}

/* True when the bracket group ending at `close` is a cast to a pointer type. */
static int IsPointerCast( const token_t *tokens, const int *mates, int close ) {
	int open = mates[close];

	return open >= 0 && close - open >= 3 && tokens[close - 1].symbol == sStar && tokens[open + 1].kind == T_ID;
}

static int DeclaratorParen( const token_t *tokens, const int *mates, int begin, int end );

/* Tests one code range for the token patterns of R4, R17, R18 and the advisories. */
static void ScanCode( int fileIndex, const token_t *tokens, const int *mates, int begin, int end, int node,
	int inMacro ) {
	int stack[256];
	int depth = 0;
	int i;

	for ( i = begin; i < end; i++ ) {
		const token_t *token = &tokens[i];
		const token_t *next = i + 1 < end ? &tokens[i + 1] : NULL;
		const token_t *previous = i > begin ? &tokens[i - 1] : NULL;
		int symbol = token->symbol;
		int close;

		if ( token->kind == T_ID ) {
			const char *text = Text( token );

			if ( symbol == sVolatile && !( ( files[fileIndex].lineFlags[token->line]
				| files[fileIndex].lineFlags[token->line - 1] ) & LF_VOLATILE_NOTE ) ) {
				Report( fileIndex, token->line, RULE_R17, node,
					"`volatile` on a local, a parameter or a cast, without a `// volatile: <evidence>` note" );
			}
			if ( symbol == sExtern && ( inMacro || i > begin ) && next && next->kind != T_STR ) {
				int semi = i + 1;

				while ( semi < end && tokens[semi].symbol != sSemi && tokens[semi].symbol != sLBrace ) {
					semi++;
				}
				if ( DeclaratorParen( tokens, mates, i + 1, semi ) < 0 ) {
					Report( fileIndex, token->line, RULE_R2, node,
						"`extern` global declared inside a macro or a function: declare it once, in a header" );
				} else {
					Report( fileIndex, token->line, RULE_R25, node,
						"prototype declared inside a macro or a function: it belongs in a header" );
				}
			}
			if ( InList( text, asmTokens ) ) {
				Report( fileIndex, token->line, RULE_R18, node, Format( "assembly token `%s`", text ) );
			} else if ( InList( text, dialectTokens ) ) {
				Report( fileIndex, token->line, RULE_R22, node,
					Format( "`%s` is not in the profile compiler's dialect", text ) );
			}
			if ( ( symbol == sIf || symbol == sFor || symbol == sWhile ) && next && next->symbol == sLParen
				&& mates[i + 1] > 0 && mates[i + 1] + 1 < end ) {
				const token_t *after = &tokens[mates[i + 1] + 1];
				int isDoTail = symbol == sWhile && previous && previous->symbol == sRBrace && mates[i - 1] > begin
					&& tokens[mates[i - 1] - 1].symbol == sDo;
				int j;

				if ( symbol == sIf && after->symbol == sSemi ) {
					Report( fileIndex, token->line, RULE_R17, node, "empty `if` statement" );
				} else if ( symbol == sIf && after->symbol == sLBrace && mates[mates[i + 1] + 1] == mates[i + 1] + 2 ) {
					Report( fileIndex, token->line, RULE_R17, node, "empty `if` block" );
				} else if ( !isDoTail && after->symbol != sLBrace && after->symbol != sSemi ) {
					Report( fileIndex, token->line, RULE_R35, node, Format( "`%s` body without braces", text ) );
				}
				if ( isDoTail && !inMacro && mates[i + 1] == i + 3 && !strcmp( Text( &tokens[i + 2] ), "0" ) ) {
					Report( fileIndex, token->line, RULE_R17, node, "`do { } while ( 0 )` outside a macro" );
				}
				if ( symbol == sIf ) {
					for ( j = i + 2; j < mates[i + 1]; j++ ) {
						if ( tokens[j].symbol == sAssign ) {
							Report( fileIndex, token->line, RULE_R35, node, "assignment inside an `if` condition" );
							break;
						}
					}
				}
			}
			if ( symbol == sElse && next ) {
				if ( next->symbol == sSemi ) {
					Report( fileIndex, token->line, RULE_R17, node, "empty `else` statement" );
				} else if ( next->symbol == sLBrace && mates[i + 1] == i + 2 ) {
					Report( fileIndex, token->line, RULE_R17, node, "empty `else` block" );
				} else if ( next->symbol != sLBrace && next->symbol != sIf ) {
					Report( fileIndex, token->line, RULE_R35, node, "`else` body without braces" );
				}
			}
			continue;
		}
		if ( token->kind != T_PUNCT ) {
			continue;
		}
		if ( symbol == sLParen || symbol == sLBracket ) {
			/* R4: *(type *)((char *)object + 0x58), or any byte-pointer cast of `this` */
			if ( symbol == sLParen && IsBytePointerCast( tokens, i, end, &close ) ) {
				int outer = depth ? stack[depth - 1] : -1;
				int reported = 0;

				if ( close + 1 < end && tokens[close + 1].symbol == sThis ) {
					Report( fileIndex, token->line, RULE_R4, node, "`this` cast to a byte pointer for offset arithmetic" );
					reported = 1;
				} else if ( outer > begin && tokens[outer].symbol == sLParen && mates[outer] > close
					&& tokens[outer - 1].symbol == sRParen && IsPointerCast( tokens, mates, outer - 1 ) ) {
					int last = mates[outer] - 1;

					if ( tokens[last].kind == T_NUM && ( tokens[last - 1].symbol == sPlus || tokens[last - 1].symbol == sMinus ) ) {
						Report( fileIndex, token->line, RULE_R4, node,
							Format( "fixed offset %s%s through a byte-pointer cast, then a dereference cast",
								Text( &tokens[last - 1] ), Text( &tokens[last] ) ) );
						reported = 1;
					}
				}
				if ( !reported && close + 3 < end && tokens[close + 1].kind == T_ID && tokens[close + 3].kind == T_NUM
					&& ( tokens[close + 2].symbol == sPlus || tokens[close + 2].symbol == sMinus ) ) {
					Report( fileIndex, token->line, RULE_R4_REVIEW, node,
						Format( "byte-pointer cast of `%s` %s %s: a member's address taken by offset",
							Text( &tokens[close + 1] ), Text( &tokens[close + 2] ), Text( &tokens[close + 3] ) ) );
				}
			} else if ( symbol == sLParen && previous && previous->symbol == sRParen && mates[i] == i + 4
				&& tokens[i + 1].kind == T_ID && tokens[i + 3].kind == T_NUM
				&& ( tokens[i + 2].symbol == sPlus || tokens[i + 2].symbol == sMinus )
				&& IsPointerCast( tokens, mates, i - 1 ) ) {
				/* *(type *)(self + 8): the object pointer is typed as bytes to avoid its real type */
				Report( fileIndex, token->line, RULE_R4_REVIEW, node,
					Format( "`%s %s %s` read through a pointer cast: a member reached by offset",
						Text( &tokens[i + 1] ), Text( &tokens[i + 2] ), Text( &tokens[i + 3] ) ) );
			}
			if ( depth < 256 ) {
				stack[depth++] = i;
			}
			continue;
		}
		if ( symbol == sRParen || symbol == sRBracket ) {
			if ( depth ) {
				depth--;
			}
			continue;
		}
		if ( symbol == sSemi && depth == 0 && previous ) {
			/* a bare ";" statement; "case X: ;", "label: ;" and empty loop bodies are allowed */
			int bare = previous->symbol == sLBrace || previous->symbol == sSemi;

			if ( previous->symbol == sRBrace && mates[i - 1] > begin ) {
				int before = tokens[mates[i - 1] - 1].symbol;

				bare = before == sRParen || before == sElse || before == sLBrace || before == sSemi
					|| before == sRBrace;
			}
			if ( bare ) {
				Report( fileIndex, token->line, RULE_R17, node, "bare `;` statement" );
			}
		}
		if ( ( symbol == sSemi || symbol == sLBrace || symbol == sRBrace ) && depth == 0 && next ) {
			/* self-assignment: "x = x;" at the start of a statement */
			int assign = -1;
			int j;

			for ( j = i + 1; j < end && tokens[j].symbol != sSemi && tokens[j].symbol != sLBrace
				&& tokens[j].symbol != sRBrace; j++ ) {
				if ( tokens[j].symbol == sAssign && assign < 0 ) {
					assign = j;
				}
			}
			if ( assign > i + 1 && j < end && tokens[j].symbol == sSemi && assign - ( i + 1 ) == j - ( assign + 1 ) ) {
				int k, same = 1;

				for ( k = 0; k < assign - ( i + 1 ); k++ ) {
					if ( tokens[i + 1 + k].symbol != tokens[assign + 1 + k].symbol ) {
						same = 0;
					}
				}
				if ( same ) {
					Report( fileIndex, tokens[assign].line, RULE_R17, node, "self-assignment" );
				}
			}
		}
		if ( next && next->kind == T_NUM && previous && EndsOperand( previous )
			&& ( i + 2 >= end || EndsOperand( &tokens[i + 2] ) == 0 || tokens[i + 2].symbol == sRParen
				|| tokens[i + 2].symbol == sRBracket ) ) {
			if ( symbol == sPlus && !strcmp( Text( next ), "0" ) ) {
				Report( fileIndex, token->line, RULE_R17, node, "`+ 0` steers the compiler" );
			} else if ( symbol == sStar && !strcmp( Text( next ), "1" ) && previous->symbol != sRParen ) {
				Report( fileIndex, token->line, RULE_R17, node, "`* 1` steers the compiler" );
			}
		}
		if ( symbol == sNot && next && next->symbol == sNot ) {
			Report( fileIndex, token->line, RULE_R35, node, "`!!` needs a look: sometimes human, often steering" );
		}
	}
}

/*
===============================================================================

NAMES

===============================================================================
*/

/* True for an address-like name: letters and underscores, then 6 to 8 hex digits
   that include a decimal digit (`sub_401000`, `r007710`, but not `defaced`). */
static int IsAddressLike( const char *name ) {
	int length = (int)strlen( name );
	int split;

	for ( split = 0; split <= length - 6; split++ ) {
		int i, digits = 0, ok = 1;

		if ( split > 0 && !( isalpha( (unsigned char)name[split - 1] ) || name[split - 1] == '_' ) ) {
			break;		/* the prefix may hold letters and underscores only */
		}
		if ( length - split > 8 ) {
			continue;
		}
		for ( i = split; i < length; i++ ) {
			if ( !isxdigit( (unsigned char)name[i] ) ) {
				ok = 0;
			}
			if ( isdigit( (unsigned char)name[i] ) ) {
				digits = 1;
			}
		}
		if ( ok && digits ) {
			return 1;
		}
	}
	return 0;
}

/* True for a disassembler, numbered or project placeholder name (R7). */
static int IsPlaceholder( const char *name ) {
	int i;

	for ( i = 0; placeholderPrefixes[i]; i++ ) {
		if ( !strncmp( name, placeholderPrefixes[i], strlen( placeholderPrefixes[i] ) ) ) {
			return 1;
		}
	}
	for ( i = 0; numberedGenerics[i]; i++ ) {
		size_t size = strlen( numberedGenerics[i] );

		if ( !strncmp( name, numberedGenerics[i], size ) && name[size] ) {
			const char *p = name + size;

			while ( isdigit( (unsigned char)*p ) ) {
				p++;
			}
			if ( !*p ) {
				return 1;
			}
		}
	}
	return IsAddressLike( name );
}

/* Lower-cases a name into a bounded buffer. */
static void LowerName( const char *name, char *out, size_t size ) {
	size_t i;

	for ( i = 0; name[i] && i + 1 < size; i++ ) {
		out[i] = (char)tolower( (unsigned char)name[i] );
	}
	out[i] = 0;
}

/* True for a padding member name: pad, _pad, pad3, padding_1c (R17). */
static int IsPaddingName( const char *name ) {
	char lower[64];
	const char *p = lower;

	LowerName( name, lower, sizeof( lower ) );
	while ( *p == '_' ) {
		p++;
	}
	if ( strncmp( p, "pad", 3 ) ) {
		return 0;
	}
	p += 3;
	if ( !strncmp( p, "ding", 4 ) ) {
		p += 4;
	}
	while ( isxdigit( (unsigned char)*p ) || *p == '_' || *p == 'x' ) {
		p++;
	}
	return !*p;
}

/* True for a filler member that names no offset: gap, unknown, before_level (R27). */
static int IsFillerName( const char *name ) {
	char lower[64];
	int i;

	LowerName( name, lower, sizeof( lower ) );
	for ( i = 0; fillerWords[i]; i++ ) {
		size_t size = strlen( fillerWords[i] );

		if ( !strncmp( lower, fillerWords[i], size )
			&& ( !lower[size] || lower[size] == '_' || isdigit( (unsigned char)lower[size] ) ) ) {
			return 1;
		}
	}
	return 0;
}

/* Reports a declared name that is a placeholder. */
static void CheckName( int fileIndex, int line, int node, const char *what, const char *name ) {
	if ( IsPlaceholder( name ) ) {
		Report( fileIndex, line, RULE_R7, node, Format( "placeholder %s name `%s`: open naming work", what, name ) );
	}
}

/*
===============================================================================

DECLARATION PARSER

===============================================================================
*/

static unsigned char *typeNameSeen;		/* by symbol: names a struct, class, union, enum or typedef */
static int typeNameCapacity;

static void MarkTypeName( int symbol ) {
	typeNameSeen = Grow( typeNameSeen, &typeNameCapacity, numSymbols + 1, 1 );
	typeNameSeen[symbol] = 1;
}

static int IsTypeName( int symbol ) {
	return symbol < typeNameCapacity && typeNameSeen[symbol];
}

/* True for a keyword that can begin or continue a type. */
static int IsTypeKeyword( const token_t *token ) {
	static const char *const words[] = {
		"int", "char", "short", "long", "float", "double", "void", "unsigned", "signed", "const", "volatile",
		"static", "register", "struct", "union", "enum", "class", "bool", "wchar_t", "__int64", "size_t",
		"DWORD", "WORD", "BYTE", "BOOL", "UINT", "INT", "FLOAT", "UBOOL", "QWORD", "SQWORD", "TCHAR", NULL
	};

	return token->kind == T_ID && ( InList( Text( token ), words ) || IsTypeName( token->symbol ) );
}

/* Hashes the spelling of [begin, end), skipping one symbol (the declared name). */
static unsigned HashTokens( const token_t *tokens, int begin, int end, int skipSymbol ) {
	unsigned hash = 2166136261u;
	int i;

	for ( i = begin; i < end; i++ ) {
		const char *p;

		if ( tokens[i].symbol == skipSymbol || tokens[i].symbol == sExtern ) {
			continue;
		}
		for ( p = Text( &tokens[i] ); *p; p++ ) {
			hash = ( hash ^ (unsigned char)*p ) * 16777619u;
		}
		hash = ( hash ^ ' ' ) * 16777619u;
	}
	return hash;
}

/* Counts the code tokens in [begin, end) that spell `symbol`. */
static int CountUses( const token_t *tokens, int begin, int end, int symbol ) {
	int i, count = 0;

	for ( i = begin; i < end; i++ ) {
		if ( tokens[i].symbol == symbol ) {
			count++;
		}
	}
	return count;
}

/* Finds the locals a function body declares: reports `volatile` locals and locals
   the body never mentions again (R17). Only plain declarations are recognised. */
static void ScanLocals( int fileIndex, const token_t *tokens, const int *mates, int begin, int end, int node ) {
	const file_t *file = &files[fileIndex];
	int i = begin;

	while ( i < end ) {
		int start = i;
		int sawType = 0;
		int j = i;

		/* statements begin after "{", "}" and ";" */
		if ( !( i == begin || tokens[i - 1].symbol == sLBrace || tokens[i - 1].symbol == sRBrace
			|| tokens[i - 1].symbol == sSemi ) ) {
			i++;
			continue;
		}
		while ( j < end && IsTypeKeyword( &tokens[j] ) ) {
			int symbol = tokens[j].symbol;

			if ( ( symbol == sStruct || symbol == sUnion || symbol == sEnum || symbol == sClass )
				&& j + 1 < end && tokens[j + 1].kind == T_ID ) {
				j++;		/* the tag */
			}
			sawType = 1;
			j++;
			/* a type name followed by another name ends the type: "Foo bar" */
			if ( j < end && tokens[j].kind == T_ID && IsTypeName( tokens[j - 1].symbol )
				&& !IsTypeKeyword( &tokens[j] ) ) {
				break;
			}
		}
		if ( !sawType ) {
			i++;
			continue;
		}
		/* declarators: [*] name [dimensions] [= initializer] , ... ; */
		for ( ;; ) {
			int name;

			while ( j < end && ( tokens[j].symbol == sStar || tokens[j].symbol == sConst
				|| tokens[j].symbol == sVolatile || tokens[j].symbol == sAmp ) ) {
				j++;
			}
			if ( j >= end || tokens[j].kind != T_ID || IsTypeKeyword( &tokens[j] ) ) {
				break;
			}
			name = j++;
			while ( j < end && tokens[j].symbol == sLBracket && mates[j] > 0 ) {
				j = mates[j] + 1;
			}
			if ( j < end && tokens[j].symbol == sAssign ) {
				while ( j < end && tokens[j].symbol != sSemi && tokens[j].symbol != sComma ) {
					j = ( tokens[j].symbol == sLParen || tokens[j].symbol == sLBrace || tokens[j].symbol == sLBracket )
						&& mates[j] > 0 ? mates[j] + 1 : j + 1;
				}
			}
			if ( j >= end || ( tokens[j].symbol != sSemi && tokens[j].symbol != sComma ) ) {
				break;		/* not a declaration after all: a call, a cast, an expression */
			}
			if ( CountUses( tokens, begin, end, tokens[name].symbol ) == 1
				&& !( file->lineFlags[tokens[name].line] & LF_QUIRK ) ) {
				Report( fileIndex, tokens[name].line, RULE_R17, node,
					Format( "local `%s` is declared and never used", Text( &tokens[name] ) ) );
			}
			CheckName( fileIndex, tokens[name].line, node, "local", Text( &tokens[name] ) );
			if ( tokens[j].symbol == sSemi ) {
				break;
			}
			j++;
		}
		i = j > start ? j : start + 1;
	}
}

/* Tests the members of a struct, class or union body in [begin, end). */
static void ScanMembers( int fileIndex, const token_t *tokens, const int *mates, int begin, int end, int node ) {
	const file_t *file = &files[fileIndex];
	int i = begin;

	while ( i < end ) {
		int start = i;
		int name = -1, paren = -1, isVirtual = 0, isVolatile = 0;

		/* one member runs to its ";"; an inline method body is checked as code */
		while ( i < end && tokens[i].symbol != sSemi ) {
			int symbol = tokens[i].symbol;

			if ( symbol == sLBrace && mates[i] > 0 ) {
				if ( paren >= 0 ) {
					ScanCode( fileIndex, tokens, mates, i + 1, mates[i], node, 0 );
					ScanLocals( fileIndex, tokens, mates, i + 1, mates[i], node );
					i = mates[i] + 1;
					if ( i < end && tokens[i].symbol != sSemi ) {
						i--;		/* a method body ends the member without a ";" */
					}
					break;
				}
				ScanMembers( fileIndex, tokens, mates, i + 1, mates[i], node );		/* nested type */
				i = mates[i] + 1;
				continue;
			}
			if ( symbol == sLParen && mates[i] > 0 ) {
				if ( paren < 0 ) {
					paren = i;
				}
				i = mates[i] + 1;
				continue;
			}
			if ( symbol == sColon && i == start + 1 ) {
				start = i + 1;		/* "public:" */
			}
			if ( symbol == sVirtual ) {
				isVirtual = 1;
			}
			if ( symbol == sVolatile ) {
				isVolatile = 1;
			}
			if ( tokens[i].kind == T_ID && paren < 0 && ( i + 1 >= end || tokens[i + 1].symbol != sScope ) ) {
				name = i;
			}
			if ( symbol == sLBracket && mates[i] > 0 ) {
				i = mates[i] + 1;
				continue;
			}
			if ( symbol == sColon && name >= 0 && i > start + 1 ) {
				while ( i < end && tokens[i].symbol != sSemi && tokens[i].symbol != sComma ) {
					i++;		/* a bitfield width */
				}
				continue;
			}
			i++;
		}
		if ( name >= 0 && !IsTypeKeyword( &tokens[name] ) ) {
			const char *text = Text( &tokens[name] );
			int line = tokens[name].line;

			if ( paren >= 0 && tokens[paren + 1].symbol != sStar && paren + 2 < end
				&& tokens[paren + 2].symbol != sStar ) {
				/* a method: only its name is tested */
				if ( isVirtual ) {
					char lower[64];

					LowerName( text, lower, sizeof( lower ) );
					if ( IsPaddingName( text ) || !strncmp( lower, "dummy", 5 ) ) {
						Report( fileIndex, line, RULE_R13, node, Format( "padding virtual `%s`", text ) );
					}
				}
				CheckName( fileIndex, line, node, "method", text );
			} else if ( paren < 0 ) {
				if ( IsPaddingName( text ) && !( file->lineFlags[line] & LF_SDK_NOTE ) ) {
					Report( fileIndex, line, RULE_R17, node, Format( "padding member `%s`", text ) );
				} else if ( IsFillerName( text ) ) {
					Report( fileIndex, line, RULE_R27, node,
						Format( "filler member `%s` names no offset: use `unk_<offset>` for an untouched range", text ) );
				} else {
					CheckName( fileIndex, line, node, "member", text );
				}
				if ( isVolatile && !( ( file->lineFlags[line] | file->lineFlags[line - 1] ) & LF_VOLATILE_NOTE ) ) {
					Report( fileIndex, line, RULE_R17, node,
						Format( "`volatile` member `%s` without a `// volatile: <evidence>` note", text ) );
				}
			}
		}
		i++;
	}
}

/* True when a comment ends just above `line`, or earlier on the same line. */
static int HasHeaderComment( const file_t *file, int line ) {
	return ( file->lineFlags[line] | file->lineFlags[line > 1 ? line - 1 : line]
		| file->lineFlags[line > 2 ? line - 2 : line] ) & LF_COMMENT;
}

/* Finds the name of the function whose parameter list opens at `paren`; joins a
   "Class::" qualifier and a destructor's "~". Returns a symbol, or 0. */
static int FunctionName( const token_t *tokens, int begin, int paren ) {
	char name[512];
	int i = paren - 1;
	int first;

	if ( i < begin || tokens[i].kind != T_ID ) {
		return 0;
	}
	first = i;
	if ( first - 1 >= begin && tokens[first - 1].symbol == sTilde ) {
		first--;
	}
	while ( first - 2 >= begin && tokens[first - 1].symbol == sScope && tokens[first - 2].kind == T_ID ) {
		first -= 2;
	}
	name[0] = 0;
	for ( i = first; i < paren; i++ ) {
		if ( strlen( name ) + strlen( Text( &tokens[i] ) ) + 1 >= sizeof( name ) ) {
			return 0;
		}
		strcat( name, Text( &tokens[i] ) );
	}
	return InternString( name );
}

/* Finds the parameter list of a declarator in [begin, end): the first "(" that
   follows a plain name. Returns its index, or -1. */
static int DeclaratorParen( const token_t *tokens, const int *mates, int begin, int end ) {
	int i;

	for ( i = begin; i < end; i++ ) {
		if ( tokens[i].symbol == sLParen ) {
			/* a constructor or destructor is named after its class: Class::Class(, ~Class( */
			if ( i > begin && tokens[i - 1].kind == T_ID && tokens[i - 1].symbol != sDeclspec
				&& tokens[i - 1].symbol != sAttribute
				&& ( !IsTypeKeyword( &tokens[i - 1] ) || ( i >= begin + 2
					&& ( tokens[i - 2].symbol == sScope || tokens[i - 2].symbol == sTilde ) ) ) ) {
				return i;
			}
			if ( mates[i] < 0 ) {
				return -1;
			}
			i = mates[i];
		} else if ( tokens[i].symbol == sAssign ) {
			return -1;
		}
	}
	return -1;
}

/* Reports a `__fastcall` function whose second parameter is never read: the shape
   of a C++ member function written in C, with a dummy standing in for EDX (R12). */
static void CheckDummyEdx( int fileIndex, const token_t *tokens, const int *mates, int begin, int paren,
	int bodyBegin, int bodyEnd, int node ) {
	int i, comma = -1, second = -1;

	for ( i = begin; i < paren; i++ ) {
		if ( tokens[i].symbol == sFastcall ) {
			break;
		}
	}
	if ( i == paren ) {
		return;
	}
	for ( i = paren + 1; i < mates[paren]; i++ ) {
		if ( tokens[i].symbol == sLParen && mates[i] > 0 ) {
			i = mates[i];
		} else if ( tokens[i].symbol == sComma ) {
			if ( comma >= 0 ) {
				break;
			}
			comma = i;
		} else if ( comma >= 0 && tokens[i].kind == T_ID ) {
			second = i;
		}
	}
	if ( second >= 0 && !IsTypeKeyword( &tokens[second] )
		&& CountUses( tokens, bodyBegin, bodyEnd, tokens[second].symbol ) == 0 ) {
		Report( fileIndex, tokens[second].line, RULE_R12, node,
			Format( "`__fastcall` with unused second parameter `%s`: a member function written as a free function",
				Text( &tokens[second] ) ) );
	}
}

/* Adds a function node for a definition and runs the code checks on its body. */
static void AddFunction( int fileIndex, int begin, int paren, int bodyOpen ) {
	file_t *file = &files[fileIndex];
	const token_t *tokens = file->tokens;
	int name = FunctionName( tokens, begin, paren );
	int flags = 0;
	int node, i;

	if ( !name ) {
		return;
	}
	for ( i = begin; i < paren; i++ ) {
		int symbol = tokens[i].symbol;

		if ( symbol == sStatic ) {
			flags |= NF_STATIC;
		} else if ( symbol == sInline || symbol == sInline2 || symbol == sForceInline ) {
			flags |= NF_INLINE;
		}
	}
	node = AddNode( N_FUNCTION, name, fileIndex, tokens[begin].line, begin, file->mates[bodyOpen] + 1, flags );
	ScanCode( fileIndex, tokens, file->mates, begin, file->mates[bodyOpen] + 1, node, 0 );
	ScanLocals( fileIndex, tokens, file->mates, bodyOpen + 1, file->mates[bodyOpen], node );
	CheckDummyEdx( fileIndex, tokens, file->mates, begin, paren, bodyOpen + 1, file->mates[bodyOpen], node );
	CheckName( fileIndex, tokens[begin].line, node, "function", symbolText[name] );
	if ( !HasHeaderComment( file, tokens[begin].line ) ) {
		Report( fileIndex, tokens[begin].line, RULE_R33, node,
			Format( "function `%s` has no header comment", symbolText[name] ) );
	}
}

/* Adds the nodes of one file-scope declaration in [begin, end) that ends in ";". */
static void AddDeclaration( int fileIndex, int begin, int end ) {
	file_t *file = &files[fileIndex];
	const token_t *tokens = file->tokens;
	int isExtern = 0, isTypedef = 0, isStatic = 0;
	int paren, i, node;

	if ( begin >= end ) {
		return;
	}
	for ( i = begin; i < end; i++ ) {
		if ( tokens[i].symbol == sExtern ) {
			isExtern = 1;
		} else if ( tokens[i].symbol == sTypedef ) {
			isTypedef = 1;
		} else if ( tokens[i].symbol == sStatic ) {
			isStatic = 1;
		}
	}
	if ( isExtern && begin + 1 < end && tokens[begin + 1].kind == T_STR ) {
		begin += 2;		/* extern "C" declaration */
	}
	if ( isTypedef ) {
		/* the typedef name is the last name, or the one inside "(*name)" */
		int name = -1;

		for ( i = begin; i < end; i++ ) {
			if ( tokens[i].kind == T_ID ) {
				name = i;
			}
			if ( tokens[i].symbol == sLParen && i + 2 < end && tokens[i + 2].kind == T_ID
				&& tokens[i + 1].symbol == sStar ) {
				name = i + 2;
				break;
			}
		}
		if ( name >= 0 ) {
			node = AddNode( N_TYPE, tokens[name].symbol, fileIndex, tokens[name].line, begin, end, 0 );
			nodes[node].keyword = sTypedef;
			nodes[node].bodyHash = HashTokens( tokens, begin, end, 0 );
			MarkTypeName( tokens[name].symbol );
		}
		return;
	}
	if ( end - begin == 2 && tokens[begin + 1].kind == T_ID
		&& ( tokens[begin].symbol == sStruct || tokens[begin].symbol == sClass || tokens[begin].symbol == sUnion ) ) {
		node = AddNode( N_FORWARD, tokens[begin + 1].symbol, fileIndex, tokens[begin].line, begin, end, 0 );
		nodes[node].keyword = tokens[begin].symbol;
		MarkTypeName( tokens[begin + 1].symbol );
		return;
	}
	paren = DeclaratorParen( tokens, file->mates, begin, end );
	if ( paren >= 0 ) {
		int name = FunctionName( tokens, begin, paren );

		if ( name ) {
			node = AddNode( N_PROTOTYPE, name, fileIndex, tokens[begin].line, begin, end,
				( isExtern ? NF_EXTERN : 0 ) | ( isStatic ? NF_STATIC : 0 ) );
			nodes[node].bodyHash = HashTokens( tokens, begin, end, 0 );
		}
		return;
	}
	/* variables: each declarator's name is the last name before "=", "[", "," or the end */
	i = begin;
	while ( i < end ) {
		int name = -1;
		int declEnd;

		while ( i < end && tokens[i].symbol != sComma && tokens[i].symbol != sAssign ) {
			if ( tokens[i].symbol == sLParen && i + 2 < end && tokens[i + 1].kind == T_ID
				&& tokens[i + 2].symbol == sStar && i + 3 < end && tokens[i + 3].kind == T_ID ) {
				name = i + 3;		/* (__cdecl *name)(...) */
				i = file->mates[i] > 0 ? file->mates[i] + 1 : i + 1;
				while ( i < end && tokens[i].symbol != sComma && tokens[i].symbol != sAssign ) {
					i++;
				}
				break;
			}
			if ( tokens[i].symbol == sLParen && i + 2 < end && tokens[i + 1].symbol == sStar
				&& tokens[i + 2].kind == T_ID ) {
				name = i + 2;		/* (*name)(...) */
				i = file->mates[i] > 0 ? file->mates[i] + 1 : i + 1;
				while ( i < end && tokens[i].symbol != sComma && tokens[i].symbol != sAssign ) {
					i++;
				}
				break;
			}
			if ( ( tokens[i].symbol == sLParen || tokens[i].symbol == sLBracket ) && file->mates[i] > 0 ) {
				i = file->mates[i] + 1;
				continue;
			}
			if ( tokens[i].kind == T_ID ) {
				name = i;
			}
			i++;
		}
		declEnd = i;
		while ( i < end && tokens[i].symbol != sComma ) {
			i = ( tokens[i].symbol == sLParen || tokens[i].symbol == sLBrace || tokens[i].symbol == sLBracket )
				&& file->mates[i] > 0 ? file->mates[i] + 1 : i + 1;
		}
		i++;
		if ( name < 0 || IsTypeKeyword( &tokens[name] ) ) {
			continue;
		}
		node = AddNode( N_GLOBAL, tokens[name].symbol, fileIndex, tokens[name].line, begin, end,
			( isExtern ? NF_EXTERN : 0 ) | ( isStatic ? NF_STATIC : 0 ) );
		nodes[node].bodyHash = HashTokens( tokens, begin, declEnd, tokens[name].symbol );
		CheckName( fileIndex, tokens[name].line, node, "global", Text( &tokens[name] ) );
		if ( isExtern && !file->isHeader ) {
			Report( fileIndex, tokens[name].line, RULE_R2, node,
				Format( "`extern` of global `%s` in a source file: declare it once, in a header", Text( &tokens[name] ) ) );
		}
		for ( declEnd = begin; declEnd < end; declEnd++ ) {
			if ( tokens[declEnd].symbol == sVolatile
				&& !( ( file->lineFlags[tokens[name].line] | file->lineFlags[tokens[name].line - 1] ) & LF_VOLATILE_NOTE ) ) {
				Report( fileIndex, tokens[name].line, RULE_R17, node,
					Format( "`volatile` global `%s` without a `// volatile: <evidence>` note", Text( &tokens[name] ) ) );
				break;
			}
		}
	}
}

/* Adds a type node for "struct name { ... }" whose body opens at `open`. */
static void AddType( int fileIndex, int begin, int open, int end ) {
	file_t *file = &files[fileIndex];
	const token_t *tokens = file->tokens;
	int keyword = 0, name = 0, i, node;
	int close = file->mates[open];

	for ( i = begin; i < open; i++ ) {
		int symbol = tokens[i].symbol;

		if ( symbol == sStruct || symbol == sClass || symbol == sUnion || symbol == sEnum ) {
			keyword = symbol;
			if ( i + 1 < open && tokens[i + 1].kind == T_ID ) {
				name = tokens[i + 1].symbol;
			}
			break;
		}
	}
	if ( !name ) {
		/* an anonymous body takes the name declared after it: typedef struct { } name_t; */
		for ( i = close + 1; i < end; i++ ) {
			if ( tokens[i].kind == T_ID ) {
				name = tokens[i].symbol;
			}
		}
	}
	if ( !name ) {
		return;
	}
	node = AddNode( N_TYPE, name, fileIndex, tokens[begin].line, begin, end, 0 );
	nodes[node].keyword = keyword;
	nodes[node].bodyHash = HashTokens( tokens, open, close + 1, 0 );
	MarkTypeName( name );
	CheckName( fileIndex, tokens[begin].line, node, "type", symbolText[name] );
	if ( keyword != sEnum ) {
		ScanMembers( fileIndex, tokens, file->mates, open + 1, close, node );
	}
	/* typedef struct tag { } name_t; also declares name_t */
	if ( tokens[begin].symbol == sTypedef ) {
		for ( i = close + 1; i < end; i++ ) {
			if ( tokens[i].kind == T_ID && tokens[i].symbol != name ) {
				int alias = AddNode( N_TYPE, tokens[i].symbol, fileIndex, tokens[i].line, begin, end, 0 );

				nodes[alias].keyword = sTypedef;
				nodes[alias].bodyHash = nodes[node].bodyHash;
				MarkTypeName( tokens[i].symbol );
			}
		}
	}
}

static int FindMacro( int name, int fromFile, macro_t **macro, int *macroFile );

/* Spells the name a macro builds from body tokens [first, last]: parameters are
   replaced by their arguments and "##" joins the pieces. */
static int PastedName( const token_t *body, int first, int last, const macro_t *macro, const token_t *tokens,
	int args[16][2], int numArgs ) {
	char name[512];
	int j;

	name[0] = 0;
	for ( j = first; j <= last; j++ ) {
		int k, param = -1;

		if ( body[j].symbol == sPaste ) {
			continue;
		}
		for ( k = 0; k < macro->numParams; k++ ) {
			if ( macro->params[k] == body[j].symbol ) {
				param = k;
			}
		}
		if ( param >= 0 && param < numArgs ) {
			for ( k = args[param][0]; k < args[param][1]; k++ ) {
				if ( strlen( name ) + strlen( Text( &tokens[k] ) ) + 1 < sizeof( name ) ) {
					strcat( name, Text( &tokens[k] ) );
				}
			}
		} else if ( strlen( name ) + strlen( Text( &body[j] ) ) + 1 < sizeof( name ) ) {
			strcat( name, Text( &body[j] ) );
		}
	}
	return name[0] ? InternString( name ) : 0;
}

/* Hashes a macro body range as it expands for one invocation. */
static unsigned HashExpansion( const token_t *body, int first, int last, const macro_t *macro, const token_t *tokens,
	int args[16][2], int numArgs ) {
	unsigned hash = 2166136261u;
	int j;

	for ( j = first; j <= last; j++ ) {
		int piece = PastedName( body, j, j, macro, tokens, args, numArgs );
		const char *p;

		for ( p = piece ? symbolText[piece] : ""; *p; p++ ) {
			hash = ( hash ^ (unsigned char)*p ) * 16777619u;
		}
		hash = ( hash ^ ' ' ) * 16777619u;
	}
	return hash;
}

/* Adds what one file-scope macro invocation defines: every "name(...) {" function
   and every "struct name {" type in the macro's replacement list, with the
   arguments pasted into the names. Each node also refers to every pasted name. */
static void AddGenerated( int fileIndex, int begin, int end, const macro_t *macro, int macroFile ) {
	file_t *file = &files[fileIndex];
	const token_t *tokens = file->tokens;
	const token_t *body = files[macroFile].macroTokens;
	const int *bodyMates = files[macroFile].macroMates;
	int args[16][2];
	int created[64];
	int numArgs = 0, numCreated = 0;
	int i, j, depth = 0;

	/* split the invocation's arguments at top-level commas */
	args[0][0] = begin + 2;
	for ( i = begin + 2; i < end - 1 && numArgs < 15; i++ ) {
		if ( ( tokens[i].symbol == sLParen || tokens[i].symbol == sLBracket ) && file->mates[i] > 0 ) {
			i = file->mates[i];
		} else if ( tokens[i].symbol == sComma ) {
			args[numArgs][1] = i;
			args[++numArgs][0] = i + 1;
		}
	}
	args[numArgs++][1] = end - 1;

	for ( i = macro->begin; i < macro->end; i++ ) {
		int symbol = body[i].symbol;

		if ( symbol == sLBrace ) {
			depth++;
		} else if ( symbol == sRBrace ) {
			depth--;
		} else if ( depth == 0 && ( symbol == sStruct || symbol == sClass || symbol == sUnion )
			&& i + 1 < macro->end && body[i + 1].kind == T_ID ) {
			int last = i + 1;

			while ( last + 2 < macro->end && body[last + 1].symbol == sPaste ) {
				last += 2;
			}
			if ( last + 1 < macro->end && body[last + 1].symbol == sLBrace && bodyMates[last + 1] > 0 ) {
				int name = PastedName( body, i + 1, last, macro, tokens, args, numArgs );

				if ( name && numCreated < 64 ) {
					j = AddNode( N_TYPE, name, fileIndex, tokens[begin].line, begin, end, NF_GENERATED );
					nodes[j].keyword = symbol;
					nodes[j].bodyHash = HashExpansion( body, last + 1, bodyMates[last + 1], macro, tokens, args, numArgs );
					MarkTypeName( name );
					created[numCreated++] = j;
				}
				i = bodyMates[last + 1];
			}
		} else if ( depth == 0 && symbol == sLParen && bodyMates[i] > 0 && bodyMates[i] + 1 < macro->end
			&& body[bodyMates[i] + 1].symbol == sLBrace && i > macro->begin && body[i - 1].kind == T_ID ) {
			int first = i - 1;
			int name;

			while ( first - 2 >= macro->begin && body[first - 1].symbol == sPaste ) {
				first -= 2;
			}
			name = PastedName( body, first, i - 1, macro, tokens, args, numArgs );
			if ( name && numCreated < 64 ) {
				j = AddNode( N_FUNCTION, name, fileIndex, tokens[begin].line, begin, end, NF_GENERATED );
				CheckName( fileIndex, tokens[begin].line, j, "function", symbolText[name] );
				created[numCreated++] = j;
			}
			i = bodyMates[i];
		}
	}
	/* a pasted name such as package_##Package never appears as a token of its own */
	for ( i = macro->begin; i + 2 < macro->end; i++ ) {
		int last = i;
		int name;

		if ( body[i].kind != T_ID || body[i + 1].symbol != sPaste ) {
			continue;
		}
		while ( last + 2 < macro->end && body[last + 1].symbol == sPaste ) {
			last += 2;
		}
		name = PastedName( body, i, last, macro, tokens, args, numArgs );
		for ( j = 0; name && j < numCreated; j++ ) {
			node_t *node = &nodes[created[j]];

			node->refs = Grow( node->refs, &node->refCapacity, node->numRefs + 1, sizeof( int ) );
			node->refs[node->numRefs++] = name;
		}
		i = last;
	}
}

/* Walks a file's code tokens at file scope and adds a node for every declaration. */
static void ParseFile( int fileIndex ) {
	file_t *file = &files[fileIndex];
	const token_t *tokens = file->tokens;
	int count = file->numTokens;
	int i = 0;

	while ( i < count ) {
		int begin = i;
		int j = i;
		macro_t *macro;
		int macroFile;

		if ( tokens[i].symbol == sRBrace || tokens[i].symbol == sSemi ) {
			i++;		/* the end of a namespace or extern "C" block, or a stray ";" */
			continue;
		}
		/* a macro invocation that defines functions needs no ";" */
		if ( tokens[i].kind == T_ID && i + 1 < count && tokens[i + 1].symbol == sLParen && file->mates[i + 1] > 0
			&& FindMacro( tokens[i].symbol, fileIndex, &macro, &macroFile ) ) {
			int close = file->mates[i + 1];
			int k, defines = 0;

			for ( k = macro->begin; k < macro->end; k++ ) {
				if ( files[macroFile].macroTokens[k].symbol == sLBrace ) {
					defines = 1;
				}
			}
			if ( defines ) {
				AddGenerated( fileIndex, i, close + 1, macro, macroFile );
				i = close + 1;
				if ( i < count && tokens[i].symbol == sSemi ) {
					i++;
				}
				continue;
			}
		}
		while ( j < count && tokens[j].symbol != sSemi && tokens[j].symbol != sLBrace ) {
			j = ( tokens[j].symbol == sLParen || tokens[j].symbol == sLBracket ) && file->mates[j] > 0
				? file->mates[j] + 1 : j + 1;
		}
		if ( j >= count ) {
			break;
		}
		if ( tokens[j].symbol == sSemi ) {
			AddDeclaration( fileIndex, begin, j );
			i = j + 1;
			continue;
		}
		if ( file->mates[j] < 0 ) {
			break;		/* unbalanced: stop rather than guess */
		}
		{
			int paren = DeclaratorParen( tokens, file->mates, begin, j );
			int hasAssign = 0, hasTag = 0, k;

			for ( k = begin; k < j; k++ ) {
				int symbol = tokens[k].symbol;

				if ( symbol == sAssign ) {
					hasAssign = 1;
				} else if ( symbol == sStruct || symbol == sClass || symbol == sUnion || symbol == sEnum ) {
					hasTag = 1;
				}
			}
			if ( tokens[begin].symbol == sNamespace || ( tokens[begin].symbol == sExtern && j == begin + 2
				&& tokens[begin + 1].kind == T_STR ) ) {
				i = j + 1;		/* step inside the block */
			} else if ( paren >= 0 && !hasAssign ) {
				AddFunction( fileIndex, begin, paren, j );
				i = file->mates[j] + 1;
			} else if ( hasTag && !hasAssign ) {
				int end = file->mates[j] + 1;

				while ( end < count && tokens[end].symbol != sSemi ) {
					end++;
				}
				AddType( fileIndex, begin, j, end );
				i = end + 1;
			} else {
				/* an initialised global: skip the braces, then declare it */
				int end = file->mates[j] + 1;

				while ( end < count && tokens[end].symbol != sSemi ) {
					end = tokens[end].symbol == sLBrace && file->mates[end] > 0 ? file->mates[end] + 1 : end + 1;
				}
				AddDeclaration( fileIndex, begin, end < count ? end : count );
				i = end + 1;
			}
		}
	}
}

/* Adds a node for each macro and runs the code checks on its replacement list. */
static void ParseMacros( int fileIndex ) {
	file_t *file = &files[fileIndex];
	int i, j;

	for ( i = 0; i < file->numMacros; i++ ) {
		macro_t *macro = &file->macros[i];

		macro->node = AddNode( N_MACRO, macro->name, fileIndex, macro->line, macro->begin, macro->end, NF_IN_MACRO );
		ScanCode( fileIndex, file->macroTokens, file->macroMates, macro->begin, macro->end, macro->node, 1 );
		for ( j = macro->begin; j + 1 < macro->end; j++ ) {
			int symbol = file->macroTokens[j].symbol;
			int open = j + 1;

			if ( symbol != sStruct && symbol != sClass && symbol != sUnion ) {
				continue;
			}
			while ( open < macro->end && ( file->macroTokens[open].kind == T_ID || file->macroTokens[open].symbol == sPaste ) ) {
				open++;
			}
			if ( open < macro->end && file->macroTokens[open].symbol == sLBrace && file->macroMates[open] > 0 ) {
				ScanMembers( fileIndex, file->macroTokens, file->macroMates, open + 1, file->macroMates[open], macro->node );
				j = file->macroMates[open];
			}
		}
		CheckName( fileIndex, macro->line, macro->node, "macro", symbolText[macro->name] );
	}
}

/* Computes which files each file sees through its includes. */
static void ComputeReach( int firstFile ) {
	int i, changed;

	for ( i = firstFile; i < numFiles; i++ ) {
		files[i].reach = Alloc( (size_t)numFiles );
		files[i].reach[i] = 1;
	}
	do {
		changed = 0;
		for ( i = firstFile; i < numFiles; i++ ) {
			int j, k;

			for ( j = 0; j < files[i].numIncludes; j++ ) {
				const unsigned char *other = files[files[i].includes[j]].reach;

				for ( k = firstFile; k < numFiles; k++ ) {
					if ( other[k] && !files[i].reach[k] ) {
						files[i].reach[k] = 1;
						changed = 1;
					}
				}
			}
		}
	} while ( changed );
}

/* Finds a macro by name among the files `fromFile` includes so far. */
static int FindMacro( int name, int fromFile, macro_t **macro, int *macroFile ) {
	int stack[64];
	unsigned char *seen = Alloc( (size_t)numFiles + 1 );
	int depth = 0, found = 0;

	stack[depth++] = fromFile;
	seen[fromFile] = 1;
	while ( depth && !found ) {
		int fileIndex = stack[--depth];
		file_t *file = &files[fileIndex];
		int i;

		for ( i = 0; i < file->numMacros; i++ ) {
			if ( file->macros[i].name == name && file->macros[i].numParams >= 0 ) {
				*macro = &file->macros[i];
				*macroFile = fileIndex;
				found = 1;
			}
		}
		for ( i = 0; i < file->numIncludes && depth < 64; i++ ) {
			if ( !seen[file->includes[i]] ) {
				seen[file->includes[i]] = 1;
				stack[depth++] = file->includes[i];
			}
		}
	}
	free( seen );
	return found;
}

/*
===============================================================================

CROSS-FILE CHECKS

===============================================================================
*/

/* R1: one type name, several files, different bodies; struct/class keyword mismatch.
   R2: one global declared with different types. */
static void CheckDuplicates( int firstNode ) {
	int symbol;

	for ( symbol = 1; symbol < numSymbols; symbol++ ) {
		int node, other;

		for ( node = symbolFirstNode[symbol]; node >= 0; node = nodes[node].nextSameName ) {
			int definitions = 0, distinct = 0, conflict = -1;

			if ( node < firstNode ) {
				continue;
			}
			for ( other = symbolFirstNode[symbol]; other >= 0; other = nodes[other].nextSameName ) {
				if ( other < firstNode || other == node || nodes[other].file == nodes[node].file ) {
					continue;
				}
				if ( nodes[node].kind == N_TYPE && nodes[other].kind == N_TYPE ) {
					definitions++;
					if ( nodes[other].bodyHash != nodes[node].bodyHash ) {
						distinct++;
						conflict = other;
					}
				} else if ( nodes[node].kind == N_FORWARD && nodes[other].kind == N_TYPE
					&& nodes[other].keyword != sTypedef && nodes[other].keyword != sEnum
					&& ( nodes[node].keyword == sClass ) != ( nodes[other].keyword == sClass ) ) {
					conflict = other;
					distinct = -1;
				} else if ( nodes[node].kind == N_GLOBAL && nodes[other].kind == N_GLOBAL
					&& nodes[other].bodyHash != nodes[node].bodyHash ) {
					distinct++;
					conflict = other;
				}
			}
			if ( conflict < 0 ) {
				continue;
			}
			if ( nodes[node].kind == N_TYPE ) {
				Report( nodes[node].file, nodes[node].line, RULE_R1, node,
					Format( "type `%s` has %d other definitions, %d with a different body (one in %s)",
						symbolText[symbol], definitions, distinct, files[nodes[conflict].file].path ) );
			} else if ( nodes[node].kind == N_FORWARD ) {
				Report( nodes[node].file, nodes[node].line, RULE_R1, node,
					Format( "`%s %s` is declared with the other keyword in %s", symbolText[nodes[node].keyword],
						symbolText[symbol], files[nodes[conflict].file].path ) );
			} else {
				Report( nodes[node].file, nodes[node].line, RULE_R2, node,
					Format( "global `%s` is declared with a different type in %s", symbolText[symbol],
						files[nodes[conflict].file].path ) );
			}
		}
	}
}

/* R25: a prototype written in a source file for a function defined elsewhere. */
static void CheckLocalPrototypes( int firstNode ) {
	int node;

	for ( node = firstNode; node < numNodes; node++ ) {
		int other, definedHere = 0;

		if ( nodes[node].kind != N_PROTOTYPE || files[nodes[node].file].isHeader || ( nodes[node].flags & NF_STATIC ) ) {
			continue;
		}
		for ( other = symbolFirstNode[nodes[node].name]; other >= 0; other = nodes[other].nextSameName ) {
			if ( nodes[other].kind == N_FUNCTION && nodes[other].file == nodes[node].file ) {
				definedHere = 1;
			}
		}
		if ( !definedHere ) {
			Report( nodes[node].file, nodes[node].line, RULE_R25, node,
				Format( "prototype of `%s` in a source file: it belongs in a header", symbolText[nodes[node].name] ) );
		}
	}
}

/*
===============================================================================

JSON

A small reader for the unit manifests.

===============================================================================
*/

typedef enum { J_NULL, J_BOOL, J_NUMBER, J_STRING, J_ARRAY, J_OBJECT } jsonKind_t;

typedef struct json_s {
	int kind;				/* jsonKind_t */
	char *string;			/* J_STRING, and the key of an object member */
	char *key;
	double number;
	struct json_s *child;	/* first element or member */
	struct json_s *next;
} json_t;

static const char *jsonAt;

static void JsonSkipSpace( void ) {
	while ( *jsonAt == ' ' || *jsonAt == '\t' || *jsonAt == '\n' || *jsonAt == '\r' ) {
		jsonAt++;
	}
}

/* Reads a string; escapes other than \" and \\ are kept as written. */
static char *JsonString( void ) {
	const char *start = ++jsonAt;
	char *out, *o;

	while ( *jsonAt && *jsonAt != '"' ) {
		jsonAt += *jsonAt == '\\' && jsonAt[1] ? 2 : 1;
	}
	out = o = Alloc( (size_t)( jsonAt - start ) + 1 );
	while ( start < jsonAt ) {
		if ( *start == '\\' && ( start[1] == '"' || start[1] == '\\' || start[1] == '/' ) ) {
			start++;
		}
		*o++ = *start++;
	}
	if ( *jsonAt == '"' ) {
		jsonAt++;
	}
	return out;
}

static json_t *JsonValue( void ) {
	json_t *value = Alloc( sizeof( *value ) );
	json_t **tail = &value->child;

	JsonSkipSpace();
	if ( *jsonAt == '{' || *jsonAt == '[' ) {
		char close = *jsonAt == '{' ? '}' : ']';

		value->kind = *jsonAt == '{' ? J_OBJECT : J_ARRAY;
		jsonAt++;
		JsonSkipSpace();
		while ( *jsonAt && *jsonAt != close ) {
			char *key = NULL;
			json_t *item;

			if ( value->kind == J_OBJECT ) {
				if ( *jsonAt != '"' ) {
					Fatal( "malformed JSON object" );
				}
				key = JsonString();
				JsonSkipSpace();
				if ( *jsonAt == ':' ) {
					jsonAt++;
				}
			}
			item = JsonValue();
			item->key = key;
			*tail = item;
			tail = &item->next;
			JsonSkipSpace();
			if ( *jsonAt == ',' ) {
				jsonAt++;
			}
			JsonSkipSpace();
		}
		if ( *jsonAt ) {
			jsonAt++;
		}
	} else if ( *jsonAt == '"' ) {
		value->kind = J_STRING;
		value->string = JsonString();
	} else if ( !strncmp( jsonAt, "true", 4 ) || !strncmp( jsonAt, "false", 5 ) ) {
		value->kind = J_BOOL;
		value->number = *jsonAt == 't';
		jsonAt += *jsonAt == 't' ? 4 : 5;
	} else if ( !strncmp( jsonAt, "null", 4 ) ) {
		jsonAt += 4;
	} else {
		char *end;

		value->kind = J_NUMBER;
		value->number = strtod( jsonAt, &end );
		if ( end == jsonAt ) {
			Fatal( "malformed JSON value" );
		}
		jsonAt = end;
	}
	return value;
}

static json_t *JsonParseFile( const char *path ) {
	int length;
	char *text = ReadFile( path, &length );

	if ( !text ) {
		Fatal( "cannot read %s", path );
	}
	jsonAt = text;
	return JsonValue();
}

static json_t *JsonMember( const json_t *object, const char *key ) {
	json_t *member;

	for ( member = object && object->kind == J_OBJECT ? object->child : NULL; member; member = member->next ) {
		if ( !strcmp( member->key, key ) ) {
			return member;
		}
	}
	return NULL;
}

/*
===============================================================================

UNITS

===============================================================================
*/

typedef struct {
	char id[96];
	int numFunctions, numBytes;				/* units with a byte receipt */
	int verifiedFunctions, verifiedBytes;	/* ... and reviewed compiler evidence */
	int ruleFunctions, ruleBytes;			/* verified, and every [match] rule passes */
	int candidateRuleFunctions, candidateRuleBytes;
	int pendingFunctions[NUM_MATCH_RULES], pendingBytes[NUM_MATCH_RULES];
	int byFunction, byClass, byFile;		/* how each unit's source was found */
} targetTotals_t;

static targetTotals_t *targets;
static int numTargets, targetCapacity;
static int closureStamp;
static FILE *unitsOut;
static const char *explainUnit;

/* Reduces a decorated x86 symbol to the name the source spells:
   _name, _name@8, @name@8, ?name@Class@@..., ??1Class@@... */
static int SourceName( const char *symbol, char *out, size_t size ) {
	const char *p = symbol;
	char parts[8][128];
	int numParts = 0;
	int special = 0;
	size_t length;
	int i;

	out[0] = 0;
	if ( !strncmp( p, "__ehhandler$", 12 ) ) {
		p += 12;
	}
	if ( *p == '?' ) {
		p++;
		if ( *p == '?' ) {
			p++;
			if ( *p == '0' || *p == '1' ) {
				special = *p++;
			} else if ( p[0] == '_' && ( p[1] == 'G' || p[1] == 'E' ) ) {
				special = '1';		/* a deleting destructor belongs with the destructor */
				p += 2;
			} else {
				return 0;
			}
		}
		while ( *p && *p != '@' && numParts < 8 ) {
			const char *end = strchr( p, '@' );

			if ( !end || *p == '?' || (size_t)( end - p ) >= sizeof( parts[0] ) ) {
				return 0;
			}
			memcpy( parts[numParts], p, (size_t)( end - p ) );
			parts[numParts++][end - p] = 0;
			p = end + 1;
		}
		if ( !numParts ) {
			return 0;
		}
		for ( i = numParts - 1; i >= ( special ? 0 : 1 ); i-- ) {
			if ( strlen( out ) + strlen( parts[i] ) + 3 >= size ) {
				return 0;
			}
			strcat( out, parts[i] );
			strcat( out, "::" );
		}
		if ( strlen( out ) + strlen( parts[0] ) + 2 >= size ) {
			return 0;
		}
		if ( special == '1' ) {
			strcat( out, "~" );
		}
		strcat( out, parts[0] );
		return 1;
	}
	if ( *p == '_' || *p == '@' ) {
		p++;
	}
	length = strlen( p );
	if ( length >= size ) {
		return 0;
	}
	strcpy( out, p );
	{
		char *at = strrchr( out, '@' );

		if ( at && at[1] && strspn( at + 1, "0123456789" ) == strlen( at + 1 ) ) {
			*at = 0;
		}
	}
	return out[0] != 0;
}

/* Collects the [match] rules a node breaks, with those of everything it names. */
static unsigned Closure( int start, const unsigned char *visible, int explain ) {
	int *stack = NULL;
	int capacity = 0, depth = 0;
	unsigned mask = 0;

	stack = Grow( stack, &capacity, 1, sizeof( int ) );
	stack[depth++] = start;
	nodes[start].stamp = closureStamp;
	while ( depth ) {
		const node_t *node = &nodes[--depth >= 0 ? stack[depth] : 0];
		const file_t *file = &files[node->file];
		const token_t *tokens = ( node->flags & NF_IN_MACRO ) ? file->macroTokens : file->tokens;
		int i;

		mask |= node->matchMask;
		if ( explain && node->matchMask ) {
			for ( i = 0; i < numFindings; i++ ) {
				if ( findings[i].node == (int)( node - nodes ) && findings[i].rule < NUM_MATCH_RULES ) {
					printf( "  %s:%d: %s [match] %s\n", files[findings[i].file].path, findings[i].line,
						ruleNames[findings[i].rule], findings[i].message );
				}
			}
		}
		for ( i = node->begin - node->numRefs; i < node->end; i++ ) {
			int other, symbol;

			/* the pasted names first, then the node's own tokens */
			if ( i < node->begin ) {
				symbol = node->refs[i - ( node->begin - node->numRefs )];
			} else if ( tokens[i].kind == T_ID ) {
				symbol = tokens[i].symbol;
			} else {
				continue;
			}
			for ( other = symbolFirstNode[symbol]; other >= 0; other = nodes[other].nextSameName ) {
				const node_t *candidate = &nodes[other];

				if ( candidate->stamp == closureStamp || !visible[candidate->file] ) {
					continue;
				}
				/* another unit's function is that unit's business; a helper compiled into
				   this one (static, inline, or defined in a header) is part of this source */
				if ( candidate->kind == N_FUNCTION && !( candidate->flags & ( NF_STATIC | NF_INLINE ) )
					&& !files[candidate->file].isHeader ) {
					continue;
				}
				nodes[other].stamp = closureStamp;
				stack = Grow( stack, &capacity, depth + 1, sizeof( int ) );
				stack[depth++] = other;
			}
		}
	}
	free( stack );
	return mask;
}

/* Judges one unit: finds its function in its inputs and totals its rule status. */
static void JudgeUnit( targetTotals_t *totals, const json_t *unit ) {
	const json_t *id = JsonMember( unit, "id" );
	const json_t *size = JsonMember( unit, "size" );
	const json_t *inputs = JsonMember( unit, "inputs" );
	const json_t *symbol = JsonMember( unit, "rebuilt_symbol" );
	const json_t *input;
	unsigned char *visible;
	unsigned mask = 0;
	char name[512];
	const char *how = "file";
	int bytes, verified, i, node, found = -1;
	int explain;

	if ( !id || !size || !inputs || !JsonMember( unit, "match" ) ) {
		return;
	}
	bytes = (int)size->number;
	verified = JsonMember( unit, "recipe_evidence" ) != NULL;
	explain = explainUnit && !strcmp( explainUnit, id->string );
	visible = Alloc( (size_t)numFiles + 1 );
	for ( input = inputs->child; input; input = input->next ) {
		int fileIndex = input->kind == J_STRING ? FindFile( input->string ) : -1;

		if ( fileIndex < 0 ) {
			continue;		/* an evidence note, not a source */
		}
		for ( i = currentEditionFirstFile; i < numFiles; i++ ) {
			visible[i] |= files[fileIndex].reach[i];
		}
	}
	closureStamp++;
	if ( symbol && symbol->kind == J_STRING && SourceName( symbol->string, name, sizeof( name ) ) ) {
		int nameSymbol = InternString( name );
		char *scope;

		for ( node = symbolFirstNode[nameSymbol]; node >= 0; node = nodes[node].nextSameName ) {
			if ( nodes[node].kind == N_FUNCTION && visible[nodes[node].file] ) {
				found = node;
				how = "function";
			}
		}
		/* a method defined inside its class is charged to the class */
		scope = strstr( name, "::" );
		if ( found < 0 && scope ) {
			*scope = 0;
			for ( node = symbolFirstNode[InternString( name )]; node >= 0; node = nodes[node].nextSameName ) {
				if ( nodes[node].kind == N_TYPE && nodes[node].keyword != sTypedef && visible[nodes[node].file] ) {
					found = node;
					how = "class";
				}
			}
		}
	}
	if ( explain ) {
		printf( "%s: %s, %d bytes, source found by %s\n", id->string, verified ? "verified" : "candidate", bytes, how );
	}
	if ( found >= 0 ) {
		mask = Closure( found, visible, explain );
	} else {
		/* the function was not found by name: charge everything its source files hold */
		for ( input = inputs->child; input; input = input->next ) {
			int fileIndex = input->kind == J_STRING ? FindFile( input->string ) : -1;

			if ( fileIndex < 0 || files[fileIndex].isHeader ) {
				continue;
			}
			for ( node = 0; node < numNodes; node++ ) {
				if ( nodes[node].file == fileIndex && nodes[node].stamp != closureStamp ) {
					mask |= Closure( node, visible, explain );
				}
			}
		}
	}
	free( visible );

	totals->numFunctions++;
	totals->numBytes += bytes;
	totals->byFunction += !strcmp( how, "function" );
	totals->byClass += !strcmp( how, "class" );
	totals->byFile += !strcmp( how, "file" );
	if ( verified ) {
		totals->verifiedFunctions++;
		totals->verifiedBytes += bytes;
	}
	if ( !mask ) {
		if ( verified ) {
			totals->ruleFunctions++;
			totals->ruleBytes += bytes;
		} else {
			totals->candidateRuleFunctions++;
			totals->candidateRuleBytes += bytes;
		}
	}
	for ( i = 0; i < NUM_MATCH_RULES; i++ ) {
		if ( mask & ( 1u << i ) ) {
			totals->pendingFunctions[i]++;
			totals->pendingBytes[i] += bytes;
		}
	}
	if ( explain ) {
		printf( "  status: %s\n", mask ? "MATCH-PENDING" : "matched under the rules" );
	}
	if ( unitsOut ) {
		fprintf( unitsOut, "%s\t%s\t%d\t%s\t%s\t%s\t", totals->id, id->string, bytes, verified ? "verified" : "candidate",
			mask ? "MATCH-PENDING" : "matched", how );
		for ( i = 0; i < NUM_MATCH_RULES; i++ ) {
			if ( mask & ( 1u << i ) ) {
				fprintf( unitsOut, "%s ", ruleNames[i] );
			}
		}
		fprintf( unitsOut, "\n" );
	}
}

/* Loads every source a list of units names. */
static void LoadUnitSources( const char *editionDir, const json_t *units ) {
	const json_t *unit, *input;

	for ( unit = units && units->kind == J_ARRAY ? units->child : NULL; unit; unit = unit->next ) {
		const json_t *inputs = JsonMember( unit, "inputs" );

		for ( input = inputs ? inputs->child : NULL; input; input = input->next ) {
			if ( input->kind == J_STRING && ( EndsWith( input->string, ".c" ) || EndsWith( input->string, ".cpp" )
				|| EndsWith( input->string, ".h" ) || EndsWith( input->string, ".hpp" ) ) ) {
				LoadFile( editionDir, input->string );
			}
		}
	}
}

/*
===============================================================================

EDITIONS AND REPORTS

===============================================================================
*/

static int CompareStrings( const void *a, const void *b ) {
	return strcmp( *(char *const *)a, *(char *const *)b );
}

/* Lists the *.json files of a directory, sorted. */
static int ListJson( const char *directory, char ***names ) {
	char **list = NULL;
	int count = 0, capacity = 0;
#if defined(_MSC_VER)
	struct _finddata_t entry;
	char *pattern = Format( "%s/*.json", directory );
	intptr_t handle = _findfirst( pattern, &entry );

	if ( handle != -1 ) {
		do {
			list = Grow( list, &capacity, count + 1, sizeof( char * ) );
			list[count++] = CopyString( entry.name, (int)strlen( entry.name ) );
		} while ( _findnext( handle, &entry ) == 0 );
		_findclose( handle );
	}
#else
	DIR *dir = opendir( directory );
	struct dirent *entry;

	while ( dir && ( entry = readdir( dir ) ) != NULL ) {
		if ( EndsWith( entry->d_name, ".json" ) ) {
			list = Grow( list, &capacity, count + 1, sizeof( char * ) );
			list[count++] = CopyString( entry->d_name, (int)strlen( entry->d_name ) );
		}
	}
	if ( dir ) {
		closedir( dir );
	}
#endif
	if ( count ) {
		qsort( list, (size_t)count, sizeof( char * ), CompareStrings );
	}
	*names = list;
	return count;
}

/* Checks one edition folder ("pc", "ps2"): its sources, then each target's units. */
static void CheckEdition( const char *root, const char *edition ) {
	char *editionDir = Format( "%s/%s", root, edition );
	char *configDir = Format( "%s/config", editionDir );
	char **names;
	int count = ListJson( configDir, &names );
	json_t **configs = Alloc( sizeof( json_t * ) * (size_t)( count + 1 ) );
	json_t ***shards = Alloc( sizeof( json_t ** ) * (size_t)( count + 1 ) );
	int firstFile = numFiles;
	int firstNode = numNodes;
	int i, j;

	currentEditionFirstFile = firstFile;
	for ( i = 0; i < count; i++ ) {
		const json_t *unitFiles, *name;
		int numShards = 0;

		configs[i] = JsonParseFile( Format( "%s/%s", configDir, names[i] ) );
		LoadUnitSources( editionDir, JsonMember( configs[i], "units" ) );
		unitFiles = JsonMember( configs[i], "unit_files" );
		for ( name = unitFiles ? unitFiles->child : NULL; name; name = name->next ) {
			numShards++;
		}
		shards[i] = Alloc( sizeof( json_t * ) * (size_t)( numShards + 1 ) );
		for ( j = 0, name = unitFiles ? unitFiles->child : NULL; name; name = name->next, j++ ) {
			shards[i][j] = JsonParseFile( Format( "%s/%s", editionDir, name->string ) );
			LoadUnitSources( editionDir, shards[i][j] );
		}
	}
	/* files may be added while lexing includes, so parse by index */
	for ( i = firstFile; i < numFiles; i++ ) {
		ParseMacros( i );
	}
	for ( i = firstFile; i < numFiles; i++ ) {
		ParseFile( i );
	}
	ComputeReach( firstFile );
	CheckDuplicates( firstNode );
	CheckLocalPrototypes( firstNode );

	for ( i = 0; i < count; i++ ) {
		targetTotals_t *totals;
		const json_t *id = JsonMember( configs[i], "id" );
		const json_t *unit, *units;

		targets = Grow( targets, &targetCapacity, numTargets + 1, sizeof( *targets ) );
		totals = &targets[numTargets++];
		snprintf( totals->id, sizeof( totals->id ), "%s", id && id->kind == J_STRING ? id->string : names[i] );
		units = JsonMember( configs[i], "units" );
		for ( unit = units ? units->child : NULL; unit; unit = unit->next ) {
			JudgeUnit( totals, unit );
		}
		for ( j = 0; shards[i][j]; j++ ) {
			for ( unit = shards[i][j]->child; unit; unit = unit->next ) {
				JudgeUnit( totals, unit );
			}
		}
	}
}

/* Writes the committed report: totals only, so it changes when a status changes. */
static void WriteJson( FILE *out ) {
	int counts[NUM_RULES];
	int i, rule;

	memset( counts, 0, sizeof( counts ) );
	for ( i = 0; i < numFindings; i++ ) {
		counts[findings[i].rule]++;
	}
	fprintf( out, "{\n  \"schema_version\": 1,\n  \"checker\": \"tools/rules/rules.c\",\n" );
	fprintf( out, "  \"rules\": \"docs/code-rules/rules.md\",\n  \"sources\": {\n    \"files\": %d,\n", numFiles );
	fprintf( out, "    \"match_findings\": {" );
	for ( rule = 0; rule < NUM_MATCH_RULES; rule++ ) {
		fprintf( out, "%s\"%s\": %d", rule ? ", " : "", ruleNames[rule], counts[rule] );
	}
	fprintf( out, "},\n    \"advisory_findings\": {" );
	for ( rule = NUM_MATCH_RULES; rule < NUM_RULES; rule++ ) {
		fprintf( out, "%s\"%s\": %d", rule > NUM_MATCH_RULES ? ", " : "", ruleNames[rule], counts[rule] );
	}
	fprintf( out, "}\n  },\n  \"targets\": [\n" );
	for ( i = 0; i < numTargets; i++ ) {
		const targetTotals_t *t = &targets[i];

		fprintf( out, "    {\n      \"id\": \"%s\",\n", t->id );
		fprintf( out, "      \"bytes_matched\": {\"functions\": %d, \"bytes\": %d},\n", t->numFunctions, t->numBytes );
		fprintf( out, "      \"verified\": {\"functions\": %d, \"bytes\": %d},\n", t->verifiedFunctions, t->verifiedBytes );
		fprintf( out, "      \"verified_under_rules\": {\"functions\": %d, \"bytes\": %d},\n", t->ruleFunctions, t->ruleBytes );
		fprintf( out, "      \"candidate_under_rules\": {\"functions\": %d, \"bytes\": %d},\n", t->candidateRuleFunctions,
			t->candidateRuleBytes );
		fprintf( out, "      \"match_pending\": {\"functions\": %d, \"bytes\": %d},\n",
			t->numFunctions - t->ruleFunctions - t->candidateRuleFunctions,
			t->numBytes - t->ruleBytes - t->candidateRuleBytes );
		fprintf( out, "      \"pending_by_rule\": {" );
		for ( rule = 0; rule < NUM_MATCH_RULES; rule++ ) {
			fprintf( out, "%s\"%s\": {\"functions\": %d, \"bytes\": %d}", rule ? ", " : "", ruleNames[rule],
				t->pendingFunctions[rule], t->pendingBytes[rule] );
		}
		fprintf( out, "},\n      \"source_found_by\": {\"function\": %d, \"class\": %d, \"file\": %d}\n    }%s\n",
			t->byFunction, t->byClass, t->byFile, i + 1 < numTargets ? "," : "" );
	}
	fprintf( out, "  ]\n}\n" );
}

/* Prints the status table for the README. */
static void WriteMarkdown( FILE *out ) {
	int i;

	fprintf( out, "| Target | Bytes matched | Verified | Verified under the rules | MATCH-PENDING |\n" );
	fprintf( out, "| --- | ---: | ---: | ---: | ---: |\n" );
	for ( i = 0; i < numTargets; i++ ) {
		const targetTotals_t *t = &targets[i];

		fprintf( out, "| `%s` | %d | %d | %d | %d |\n", t->id, t->numBytes, t->verifiedBytes, t->ruleBytes,
			t->numBytes - t->ruleBytes - t->candidateRuleBytes );
	}
}

static void WriteSummary( FILE *out ) {
	int counts[NUM_RULES];
	int i, rule;

	memset( counts, 0, sizeof( counts ) );
	for ( i = 0; i < numFindings; i++ ) {
		counts[findings[i].rule]++;
	}
	fprintf( out, "%d source files, %d findings\n", numFiles, numFindings );
	for ( rule = 0; rule < NUM_RULES; rule++ ) {
		fprintf( out, "  %-4s %-8s %6d\n", ruleNames[rule], rule < NUM_MATCH_RULES ? "[match]" : "advisory", counts[rule] );
	}
	for ( i = 0; i < numTargets; i++ ) {
		const targetTotals_t *t = &targets[i];

		if ( !t->numFunctions ) {
			continue;
		}
		fprintf( out, "%s\n", t->id );
		fprintf( out, "  bytes matched:            %6d functions %9d bytes\n", t->numFunctions, t->numBytes );
		fprintf( out, "  verified:                 %6d functions %9d bytes\n", t->verifiedFunctions, t->verifiedBytes );
		fprintf( out, "  verified under the rules: %6d functions %9d bytes\n", t->ruleFunctions, t->ruleBytes );
		fprintf( out, "  MATCH-PENDING:            %6d functions %9d bytes\n",
			t->numFunctions - t->ruleFunctions - t->candidateRuleFunctions,
			t->numBytes - t->ruleBytes - t->candidateRuleBytes );
		for ( rule = 0; rule < NUM_MATCH_RULES; rule++ ) {
			if ( t->pendingFunctions[rule] ) {
				fprintf( out, "    %-4s %6d functions %9d bytes\n", ruleNames[rule], t->pendingFunctions[rule],
					t->pendingBytes[rule] );
			}
		}
	}
}

int main( int argc, char **argv ) {
	const char *root = ".";
	const char *jsonPath = NULL;
	const char *unitsPath = NULL;
	int listFindings = 0, check = 0, markdown = 0;
	int i;

	for ( i = 1; i < argc; i++ ) {
		if ( !strcmp( argv[i], "--root" ) && i + 1 < argc ) {
			root = argv[++i];
		} else if ( !strcmp( argv[i], "--json" ) && i + 1 < argc ) {
			jsonPath = argv[++i];
		} else if ( !strcmp( argv[i], "--units" ) && i + 1 < argc ) {
			unitsPath = argv[++i];
		} else if ( !strcmp( argv[i], "--explain" ) && i + 1 < argc ) {
			explainUnit = argv[++i];
		} else if ( !strcmp( argv[i], "--findings" ) ) {
			listFindings = 1;
		} else if ( !strcmp( argv[i], "--check" ) ) {
			check = 1;
		} else if ( !strcmp( argv[i], "--markdown" ) ) {
			markdown = 1;
		} else {
			fprintf( stderr, "usage: rules [--root DIR] [--findings] [--units FILE] [--explain UNIT]\n"
				"             [--json FILE] [--check] [--markdown]\n" );
			return 2;
		}
	}
	InternKeywords();
	if ( unitsPath ) {
		unitsOut = fopen( unitsPath, "wb" );
		if ( !unitsOut ) {
			Fatal( "cannot write %s", unitsPath );
		}
		fprintf( unitsOut, "target\tunit\tbytes\tevidence\tstatus\tsource_found_by\trules\n" );
	}
	CheckEdition( root, "pc" );
	CheckEdition( root, "ps2" );
	if ( unitsOut ) {
		fclose( unitsOut );
	}
	if ( listFindings ) {
		for ( i = 0; i < numFindings; i++ ) {
			printf( "%s:%d: %s %s %s\n", files[findings[i].file].path, findings[i].line, ruleNames[findings[i].rule],
				findings[i].rule < NUM_MATCH_RULES ? "[match]" : "advisory", findings[i].message );
		}
	}
	if ( markdown ) {
		WriteMarkdown( stdout );
	}
	if ( check || jsonPath ) {
		char *path = jsonPath ? CopyString( jsonPath, (int)strlen( jsonPath ) ) : Format( "%s/reports/rules.json", root );

		if ( check ) {
			char *temporary = Format( "%s.new", path );
			char *expected, *actual;
			int expectedLength = 0, actualLength = 0;
			FILE *out = fopen( temporary, "wb" );

			if ( !out ) {
				Fatal( "cannot write %s", temporary );
			}
			WriteJson( out );
			fclose( out );
			actual = ReadFile( temporary, &actualLength );
			remove( temporary );
			expected = ReadFile( path, &expectedLength );
			if ( !expected || expectedLength != actualLength || memcmp( expected, actual, (size_t)actualLength ) ) {
				fprintf( stderr, "rules: %s is stale; run the rules command with --json %s\n", path, path );
				return 1;
			}
			printf( "Rule report is current.\n" );
		} else {
			FILE *out = fopen( path, "wb" );

			if ( !out ) {
				Fatal( "cannot write %s", path );
			}
			WriteJson( out );
			fclose( out );
		}
	}
	if ( !listFindings && !markdown && !explainUnit ) {
		WriteSummary( stdout );
	}
	return 0;
}
