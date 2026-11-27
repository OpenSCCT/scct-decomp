#ifndef VERSUS_MGM_PAGE_STACK_H
#define VERSUS_MGM_PAGE_STACK_H

#include "versus_build.h"
#include "unreal_types.h"
#include <vector>

#include "versus_mgm_keyframes.h"

class MgmArea;

struct MgmMouseEvent {
    DWORD Unknown00;
    MgmPoint Position;

    MgmMouseEvent(DWORD InValue, const MgmPoint &InPosition)
        : Unknown00(InValue), Position(InPosition) {}
};

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
    MgmPoint MousePosition;

    MgmPageStack(bool InPlayOnShow, bool InActive);
    void UpdateTopLevelIndex();
    void PushPage(MgmArea *Page, bool TopLevel, signed char Priority);
    void PopPage(bool All, signed char MaxPriority);
};

#endif
