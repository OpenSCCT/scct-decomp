#ifndef VERSUS_MGM_HUD_CONTEXT_H
#define VERSUS_MGM_HUD_CONTEXT_H
class UViewport;
class APlayerController;
class AGameReplicationInfo;
UViewport *GetMgmViewport();
APlayerController *GetMgmPlayerController();
AGameReplicationInfo *GetMgmGameReplicationInfo();
#endif
