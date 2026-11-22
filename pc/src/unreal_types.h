// unreal_types.h -- the engine's basic types
#ifndef UNREAL_TYPES_H
#define UNREAL_TYPES_H

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef double DOUBLE;
#ifdef SCCT_VERSUS
typedef DWORD UBOOL;                  // a boolean that fills a machine word
#else
typedef int UBOOL;                  // a boolean that fills a machine word
#endif
typedef DWORD BITFIELD;             // the word a run of one-bit members shares
typedef char ANSICHAR;
typedef unsigned short TCHAR;       // both executables are Unicode builds

#endif // UNREAL_TYPES_H
