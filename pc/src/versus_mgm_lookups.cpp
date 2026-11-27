#include "versus_mgm.h"

MgmArea *FindMgmArea(MgmPackage *Package, const ANSICHAR *Name)
{
    return FindMgmArea(Package, MgmNameId(Name));
}

MgmChild *FindMgmChild(MgmArea *Area, const ANSICHAR *Name)
{
    return FindMgmChild(Area, MgmNameId(Name));
}

MgmArea *FindMgmArea(MgmPackage *Package, MgmId Id)
{
    return Package->FindArea(Id);
}

MgmChild *FindMgmChild(MgmArea *Area, MgmId Id)
{
    return Area->FindChild(Id);
}

MgmArea *MgmPackage::FindArea(MgmId Id)
{
    MgmArea **End = AreasEnd;
    for (MgmArea **It = Areas; It != End; ++It) {
        if ((*It)->GetId() == Id)
            return *It;
    }
    return 0;
}

MgmChild *MgmArea::FindChild(MgmId Id)
{
    MgmChild **End = ChildrenEnd;
    for (MgmChild **It = Children; It != End; ++It) {
        if ((*It)->GetId() == Id)
            return *It;
    }
    return 0;
}
