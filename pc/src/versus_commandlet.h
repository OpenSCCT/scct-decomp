// versus_commandlet.h -- Core and Engine commandlets
#ifndef VERSUS_COMMANDLET_H
#define VERSUS_COMMANDLET_H

#ifndef VERSUS_NATIVE_CLASS_TYPES_H
#include "unreal_object.h"
#endif

#ifdef SCCT_VERSUS

// Core.Commandlet: 0x1dc bytes, 23 virtual functions
class UCommandlet : public UObject {
public:
    virtual ~UCommandlet();
    virtual INT Main(const TCHAR *Parms);

    BYTE unk_28[0x1b4];
};

// Engine.ServerCommandlet: 0x1dc bytes, 23 virtual functions
class UServerCommandlet : public UCommandlet {
public:
    virtual ~UServerCommandlet();
    virtual INT Main(const TCHAR *Parms);
};

#endif

#endif // VERSUS_COMMANDLET_H
