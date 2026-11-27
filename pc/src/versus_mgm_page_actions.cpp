#include "versus_mgm_hud_context.h"

class MgmPageAction {
public:
    virtual ~MgmPageAction();
    virtual void Visit(class MgmActionVisitor &Visitor);
    virtual void Execute() = 0;
    virtual INT GetType() const = 0;
};

struct MgmPageLink {
    virtual ~MgmPageLink();
    virtual void Accept(class MgmActionVisitor &Visitor);
    BYTE Unknown04[4];
    MgmArea *Page;
    BYTE Unknown0c[8];
};

class MgmPushPageAction : public MgmPageAction {
public:
    virtual void Execute();
    virtual INT GetType() const;

    MgmPageLink PageLink;
    bool TopLevel;
    signed char Priority;
};

class MgmPopPageAction : public MgmPageAction {
public:
    virtual void Execute();
    virtual INT GetType() const;

    signed char MaxPriority;
};

void SelectDefaultMgmArea(MgmArea *Page);

void MgmPushPageAction::Execute()
{
    if (PageLink.Page) {
        GMgmMenuSystem->PageStack.PushPage(PageLink.Page, TopLevel, Priority);
        SelectDefaultMgmArea(PageLink.Page);
    }
}

void MgmPopPageAction::Execute()
{
    GMgmMenuSystem->PageStack.PopPage(false, MaxPriority);
}
