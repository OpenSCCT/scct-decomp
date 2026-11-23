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
#ifndef SCCT_VERSUS
    BYTE     unk_8[0x4];
    ANSICHAR Name[1];           // the name's text; each entry is allocated to fit it
#endif
};

#ifndef SCCT_VERSUS
// The ring of 1024 buffers FName::operator* widens names into, and the index of the next one.
// Names and types invented from their uses.
extern TCHAR GUnk_112d7fb8[1024][100];
extern INT   GUnk_1130dfbc;

// Widens Src into Dest and returns Dest, or returns 0 for a null Src.
TCHAR *Unk_10cccde0(TCHAR *Dest, const ANSICHAR *Src);
#endif

struct FName {
    INT Index;

    FName() {}
    FName(EName N) : Index(N) {}
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
    UBOOL operator!=(const FName &Other) const { return Index != Other.Index; }
#ifndef SCCT_VERSUS
    // The name's text, widened into the next buffer of a ring of 1024.
    const TCHAR *operator*() const
    {
        TCHAR *Buffer = GUnk_112d7fb8[GUnk_1130dfbc];
        GUnk_1130dfbc = (GUnk_1130dfbc + 1) % 1024;
        return Unk_10cccde0(Buffer, Names[Index]->Name);
    }
#endif

    static UBOOL        Initialized;    // the name table exists
    static FNameEntry **Names;          // the name table, indexed by FName::Index

    // Whether log output tagged with this name is switched off.
    static UBOOL SafeSuppressed(EName Index)
    {
        return Initialized && (Names[Index]->Flags & NameFlag_00001000);
    }
};

#endif // UNREAL_NAME_H
