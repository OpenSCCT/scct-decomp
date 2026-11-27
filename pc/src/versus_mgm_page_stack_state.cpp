#include "versus_mgm_page_stack.h"

MgmPageStack::MgmPageStack(bool InPlayOnShow, bool InActive)
    : TopLevelIndex(0), Active(InActive), PlayOnShow(InPlayOnShow)
{
}

void MgmPageStack::UpdateTopLevelIndex()
{
    TopLevelIndex = 0;
    for (INT i = Entries.size() - 1; i >= 0; --i) {
        if (Entries[i].TopLevel) {
            TopLevelIndex = i;
            break;
        }
    }
}
