// The name type used by the Versus name registry and its native class registrations.
#ifndef VERSUS_NAME_H
#define VERSUS_NAME_H

#include "unreal_types.h"

enum EName { NAME_None = 0 };
enum EFindName { FNAME_Find, FNAME_Add, FNAME_Intrinsic };

struct FNameEntry {
    INT Index;
    DWORD Flags;
    FNameEntry *HashNext;
    TCHAR Name[64];
};

class FName {
public:
    INT Index;

    FName() {}
    FName(EName Name) : Index(Name) {}
    FName(const TCHAR *Name, EFindName FindType = FNAME_Add);
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
    UBOOL operator!=(const FName &Other) const { return Index != Other.Index; }

    static DWORD Initialized;
    static void StaticInit();
    static void Hardcode(FNameEntry *AutoName);
};

#endif
