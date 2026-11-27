#ifndef VERSUS_MGM_H
#define VERSUS_MGM_H

#include "versus_build.h"
#include "unreal_types.h"

// Hud.mgm uses the CRC32 of a lowercase name as each serialized resource ID.
class MgmId {
    DWORD Value;
public:
    bool operator==(const MgmId &Other) const { return Value == Other.Value; }
};

MgmId MgmNameId(const ANSICHAR *Name);

struct MgmImageRegion;
struct MgmImage;

struct MgmContent;

class MgmChild {
public:
    BYTE UnknownBeforeVisible[4];
    BYTE Visible;
    BYTE UnknownBeforeId[0x24 - 5];
    MgmId Id;
    BYTE UnknownBeforeContent[4];
    MgmContent *Content;
    MgmId GetId() const;
};

class MgmArea {
public:
    BYTE UnknownBeforeId[0x20];
    MgmId Id;
    BYTE UnknownBeforeChildren[4];
    MgmChild **Children;
    MgmChild **ChildrenEnd;
    MgmId GetId() const;
    MgmChild *FindChild(MgmId Id);
    void SetVisible(BYTE Value, BYTE IncludeChildren);
};

class MgmPackage {
public:
    BYTE UnknownBeforeAreas[8];
    MgmArea **Areas;
    MgmArea **AreasEnd;
    MgmArea *FindArea(MgmId Id);
};

MgmArea *FindMgmArea(MgmPackage *Package, const ANSICHAR *Name);
MgmArea *FindMgmArea(MgmPackage *Package, MgmId Id);
MgmChild *FindMgmChild(MgmArea *Area, const ANSICHAR *Name);
MgmChild *FindMgmChild(MgmArea *Area, MgmId Id);

#endif
