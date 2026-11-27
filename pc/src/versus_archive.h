// Archive interface shared by Versus property and asset serialization.
#ifndef VERSUS_ARCHIVE_H
#define VERSUS_ARCHIVE_H

#include "unreal_types.h"

struct FCompactIndex { INT Value; };
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FLazyLoader;
class UObject;
class FName;

class FArchive
{
public:
    FArchive()
        : ArVer(175), ArNetVer(2000), ArLicenseeVer(0), ArIsLoading(0), ArIsSaving(0),
          ArIsTrans(0), ArIsPersistent(0), ArForEdit(1), ArForClient(1), ArForServer(1),
          ArIsError(0), ArIsCriticalError(0), ArFlags34(3), ArFlags38(0), ArMaxSerializeSize(-1) {}
    virtual ~FArchive() {}
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(UObject *Object);                  // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    virtual FArchive &operator<<(FName &Name);              // +0x1c
    virtual FArchive &operator<<(UObject *&Object);         // +0x18
    virtual INT MapName(FName *Name);                       // +0x20
    virtual INT MapObject(UObject *Object);                 // +0x24
    virtual INT Tell();                                     // +0x28
    virtual INT TotalSize();                                // +0x2c
    virtual UBOOL AtEnd();                                  // +0x30
    virtual void Flush();                                   // +0x34
    virtual void Precache(INT HintCount);                   // +0x38
    virtual void Seek(INT InPos);                           // +0x3c
    virtual void AttachLazyLoader(FLazyLoader *LazyLoader); // +0x40
    virtual void DetachLazyLoader(FLazyLoader *LazyLoader); // +0x44

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }
    UBOOL IsPersistent() { return ArIsPersistent; }

    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.Serialize(&I, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F) { Ar.Serialize(&F, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;          // +0x04
    INT ArNetVer;       // +0x08
    INT ArLicenseeVer;  // +0x0c
    UBOOL ArIsLoading;  // +0x10
    UBOOL ArIsSaving;   // +0x14
    UBOOL ArIsTrans;    // +0x18
    UBOOL ArIsPersistent; // +0x1c
    UBOOL ArForEdit, ArForClient, ArForServer;
    UBOOL ArIsError, ArIsCriticalError;
    INT ArFlags34, ArFlags38, ArMaxSerializeSize;
};

#endif
