#ifndef VERSUS_MGM_BINDINGS_H
#define VERSUS_MGM_BINDINGS_H

#include "versus_mgm.h"

inline void BindMgmArea(MgmArea *&Area, MgmPackage *Package, const ANSICHAR *Name)
{
    Area = FindMgmArea(Package, Name);
}

#endif
