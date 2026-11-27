#include "versus_mgm_allocator.h"
#include "versus_mgm.h"
#include "versus_mgm_page_stack.h"

void MgmPageStack::PushPage(MgmArea *Page, bool TopLevel, signed char Priority)
{
    INT Index = Entries.size();
    while (Index > 0 && Priority < Entries[Index - 1].Priority)
        --Index;

    TopLevel = TopLevel || Entries.empty();
    if (Active) {
        if (TopLevel) {
            for (INT i = Index - 1; i >= TopLevelIndex; --i)
                Entries[i].Page->Deactivate();
        } else {
            for (INT i = Index - 1; i >= TopLevelIndex; --i)
                Entries[i].Page->PagePushed(Page);
        }
    }

    Entries.insert(Entries.begin() + Index, MgmPageStackEntry(Page, TopLevel, Priority));
    if (TopLevel && Index > TopLevelIndex)
        TopLevelIndex = Index;
    if (Active)
        Page->Activate();
    if (PlayOnShow) {
        Page->SetTime(0.f, 1);
        Page->SetPlaying(1);
    }
    Page->UpdateMouse(MgmMouseEvent(0, MousePosition));
}

void MgmPageStack::PopPage(bool All, signed char MaxPriority)
{
    bool RemovedTopLevel = false;
    INT Index;
    do {
        Index = Entries.size() - 1;
        for (; Index >= 0; --Index)
            if (Entries[Index].Priority <= MaxPriority)
                break;
        if (Index < 0)
            return;

        MgmPageStackEntry Removed = Entries[Index];
        Entries.erase(Entries.begin() + Index);
        if (Active)
            Removed.Page->Deactivate();
        if (Removed.TopLevel) {
            RemovedTopLevel = true;
            break;
        }
        if (Active) {
            for (INT i = Index - 1; i >= 0; --i) {
                Entries[i].Page->PagePopped(Removed.Page);
                if (Entries[i].TopLevel)
                    break;
            }
        }
    } while (All);

    UpdateTopLevelIndex();
    if (RemovedTopLevel) {
        for (INT i = TopLevelIndex; i < Index; ++i) {
            if (PlayOnShow)
                Entries[i].Page->SetTime(0.f, 1);
            if (Active)
                Entries[i].Page->Activate();
        }
    }
    if (!Entries.empty())
        Entries.back().Page->UpdateMouse(MgmMouseEvent(0, MousePosition));
}
