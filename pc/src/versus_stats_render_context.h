#ifndef VERSUS_STATS_RENDER_CONTEXT_H
#define VERSUS_STATS_RENDER_CONTEXT_H

#include "versus_build.h"
#include "versus_stats_arrays.h"
#include "versus_name.h"
#include "versus_pawn_action_events.h"
#include "versus_engine_stats.h"
#include "versus_canvas.h"
#include "versus_viewport_types.h"
#include "versus_scene_level_types.h"
#include "versus_native_subsystem.h"

class UNetConnection : public UPlayer
{
  public:
    BYTE unk_68[0x1a0 - 0x68];
    FLOAT InBytes, OutBytes, InPackets, OutPackets, InBunches, OutBunches, InLoss, OutLoss, InUnordered,
        OutUnordered, InVoiceBytes, OutVoiceBytes, Lag;
    BYTE unk_1d4[0x26fc - 0x1d4];
    TArray<class UChannel *> OpenChannels;
};

class UNetDriver : public USubsystem
{
  public:
    BYTE unk_28[4];
    TArray<UNetConnection *> ClientConnections;
    UNetConnection *ServerConnection;
};

class UEngine : public USubsystem
{
  public:
    BYTE Unknown[0x48 - sizeof(USubsystem)];
    INT FPS, RenderPage, Hardware, Game, Net;
    BYTE BeforeAudio[0x74 - 0x5c];
    INT Audio;
    BYTE BeforePerformance[0x8c - 0x78];
    INT Performance;
};

#endif
