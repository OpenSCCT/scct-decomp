// unreal_commandlet.h -- UCommandlet
#ifndef UNREAL_COMMANDLET_H
#define UNREAL_COMMANDLET_H

#include "unreal_object.h"

#ifdef SCCT_VERSUS

// Core.Commandlet: 0x1dc bytes, 23 virtual functions
class UCommandlet : public UObject {
public:
    virtual ~UCommandlet();
    virtual void VirtualSlot22();

    BYTE unk_28[0x1b4];
};

#else // Campaign

// Core.Commandlet: 0x1dc bytes, 25 virtual functions
class UCommandlet : public UObject {
public:
    virtual ~UCommandlet();
    virtual INT Main(const TCHAR *Parms);

    BYTE unk_28[0x1b4];

    DECLARE_NATIVE(execMain)
};

#endif // SCCT_VERSUS

#endif // UNREAL_COMMANDLET_H
