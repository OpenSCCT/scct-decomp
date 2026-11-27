#ifndef VERSUS_MGM_PAGE_STACK_H
#define VERSUS_MGM_PAGE_STACK_H

#include "versus_build.h"
#include "unreal_types.h"
#include <vector>

class MgmArea;

struct MgmPageStackEntry {
    MgmArea *Page;
    bool TopLevel;
    signed char Priority;
    MgmPageStackEntry(MgmArea *Page, bool TopLevel, signed char Priority);
};

class MgmPageStack {
public:
    std::vector<MgmPageStackEntry> Entries;
    INT TopLevelIndex;
    bool Active, PlayOnShow;
    BYTE Unknown16[4];
    void PushPage(MgmArea *Page, bool TopLevel, signed char Priority);
    void PopPage(bool All, signed char MaxPriority);
};

#endif
