// unreal_name.h -- FName, an index into the engine's global name table
#ifndef UNREAL_NAME_H
#define UNREAL_NAME_H

#include "unreal_types.h"

// Indices of names the Campaign executable registers before any package loads.
enum EName {
    NAME_None      = 0,
    NAME_Log       = 760,
    NAME_Critical  = 761,
    NAME_ScriptLog = 770
};

// FNameEntry::Flags bit. The name is open: no symbol evidence names it.
enum {
    NameFlag_00001000 = 0x00001000      // output for this name is suppressed
};

// One entry of the global name table.
struct FNameEntry {
    INT   Index;
    DWORD Flags;                // NameFlag_ bits
};

struct FName {
    INT Index;

    FName() {}
    FName(EName N) : Index(N) {}
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
    UBOOL operator!=(const FName &Other) const { return Index != Other.Index; }

    static UBOOL        Initialized;    // the name table exists
    static FNameEntry **Names;          // the name table, indexed by FName::Index

    // Whether log output tagged with this name is switched off.
    static UBOOL SafeSuppressed(EName Index)
    {
        return Initialized && (Names[Index]->Flags & NameFlag_00001000);
    }
};

#endif // UNREAL_NAME_H
