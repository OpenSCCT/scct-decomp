#ifndef VERSUS_MGM_BINDINGS_H
#define VERSUS_MGM_BINDINGS_H

#include "versus_mgm.h"

inline void BindMgmArea(MgmArea *&Area, MgmPackage *Package, const ANSICHAR *Name)
{
    Area = FindMgmArea(Package, Name);
}

inline void HideMgmChild(MgmArea *Area, const ANSICHAR *Name)
{
    FindMgmChild(Area, Name)->Visible = 0;
}

#endif
