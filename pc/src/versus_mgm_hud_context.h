#ifndef VERSUS_MGM_HUD_CONTEXT_H
#define VERSUS_MGM_HUD_CONTEXT_H
#include "versus_build.h"
#include "unreal_types.h"
#include "versus_mgm_page_stack.h"

class UViewport;
class MgmPackage;
struct MgmPackageNode;

// Package lookup walks the node list in the menu system.
struct MgmPackageList {
    BYTE Unknown00[4];
    MgmPackageNode *Head;
};
struct MgmMenuSystem {
    BYTE Unknown00[4];
    MgmPackageList Packages;
    BYTE Unknown0c[4];
    MgmPageStack PageStack;
    BYTE UnknownAfterStack[0x38 - 0x10 - sizeof(MgmPageStack)];
    UViewport *Viewport;
};
extern MgmMenuSystem *GMgmMenuSystem;
MgmPackage *FindMgmPackage(MgmPackageList *Packages, const ANSICHAR *Name);
class APlayerController;
class AGameReplicationInfo;
UViewport *GetMgmViewport();
APlayerController *GetMgmPlayerController();
AGameReplicationInfo *GetMgmGameReplicationInfo();
#endif
