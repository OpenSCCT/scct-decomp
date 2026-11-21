// unreal_subsystem.h -- USubsystem
#ifndef UNREAL_SUBSYSTEM_H
#define UNREAL_SUBSYSTEM_H

#include "unreal_object.h"

#ifdef SCCT_VERSUS

// Core.Subsystem: 0x28 bytes, 23 virtual functions
class USubsystem : public UObject {
public:
    virtual ~USubsystem();
    virtual void VirtualSlot22();
};

#else // Campaign

// An object that executes console commands.
class FExec {
public:
    virtual UBOOL Exec(const TCHAR *Cmd, class FOutputDevice &Ar) = 0;
};

// Core.Subsystem: 0x2c bytes, 25 virtual functions, and the FExec vtable at 0x28
class USubsystem : public UObject, public FExec {
public:
    virtual ~USubsystem();
    virtual void VirtualSlot24();
};

#endif // SCCT_VERSUS

#endif // UNREAL_SUBSYSTEM_H
