#include "versus_mgm_page_stack.h"

MgmPageStackEntry::MgmPageStackEntry(MgmArea *InPage, bool InTopLevel, signed char InPriority)
    : Page(InPage), TopLevel(InTopLevel), Priority(InPriority)
{
}
