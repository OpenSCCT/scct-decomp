#include "versus_build.h"
#include "versus_stats_arrays.h"
#include "versus_pawn_action_events.h"
#include "versus_player_camera.h"

TCHAR CameraRecursionWarning[] = L"WARNING!\nRecursive loading of camera parameters: %s";

UBOOL CameraLoaded[ECM_MAX];
UBOOL CameraLoading[ECM_MAX];
void appMemcpy(void *Dest, const void *Src, INT Count);
DWORD __cdecl appMsgf(INT Type, const TCHAR *Text, ...);

// A preset may inherit all its defaults from another mode before applying its own settings.
UBOOL ASPlayerCam::LoadCameraParameters(INT Mode)
{
    // The native initializer visits the 35 reflected modes. Both flags are shared across recursive loads.
    if (CameraLoaded[Mode])
        return 1;
    if (Mode < 0 || Mode >= ECM_MAX)
        return 0;
    if (CameraLoading[Mode]) {
        appMsgf(0, CameraRecursionWarning, *GetCamModeStringFromEnum(Mode));
        return 0;
    }
    CameraLoading[Mode] = 1;

    switch (Mode) {
    case ECM_Walking: {
        ECamParam &Param = m_camParam[ECM_Walking];
        Param.interSpeed = 400.0f;
        Param.collInterSpeed = 400.0f;
        Param.collCBInterSpeed = 400.0f;
        Param.targetXYSpeed = 75.0f;
        Param.offsetSpeed = 75.0f;
        Param.alignPawn = 0;
        Param.usePitchCurve = 1;
        Param.useCollTarget = 0;
        Param.useCylColl = 1;
        Param.useColl = 1;
        Param.useAngles = 1;
        Param.useTwig = 1;
        Param.Distance[EVS_Normal] = 250.0f;
        Param.Distance[EVS_Small] = 175.0f;
        Param.Distance[EVS_Tiny] = 100.0f;
        Param.Distance[EVS_Minute] = 150.0f;
        Param.targetZSpeed = 300.0f;
        Param.minYaw = -65536;
        Param.maxYaw = 65536;
        Param.minPitch = -13000;
        Param.maxPitch = 12000;
        Param.twigX = 20.0f;
        Param.twigZ = 10.0f;
        Param.Damping = 8.0f;
        Param.biasCut = 0.7f;
        Param.biasSlope = 0.7f;
        break;
    }
    case ECM_WalkingCr: {
        if (LoadCameraParameters(ECM_Walking))
            appMemcpy(&m_camParam[ECM_WalkingCr], &m_camParam[ECM_Walking], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_WalkingCr];
        Param.offset[EVS_Minute].X = 0.0f;
        Param.offset[EVS_Minute].Y = 10.0f;
        Param.offset[EVS_Minute].Z = -60.0f;
        break;
    }
    case ECM_Running: {
        if (LoadCameraParameters(ECM_Walking))
            appMemcpy(&m_camParam[ECM_Running], &m_camParam[ECM_Walking], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_Running];
        Param.interSpeed = 500.0f;
        Param.collInterSpeed = 500.0f;
        Param.collCBInterSpeed = 0.0f;
        break;
    }
    case ECM_RunningCr: {
        if (LoadCameraParameters(ECM_WalkingCr))
            appMemcpy(&m_camParam[ECM_RunningCr], &m_camParam[ECM_WalkingCr], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_RunningCr];
        Param.interSpeed = 500.0f;
        Param.collInterSpeed = 500.0f;
        Param.collCBInterSpeed = 0.0f;
        break;
    }
    case ECM_FirstPerson: {
        if (LoadCameraParameters(ECM_Walking))
            appMemcpy(&m_camParam[ECM_FirstPerson], &m_camParam[ECM_Walking], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_FirstPerson];
        Param.alignPawn = 1;
        Param.offset[EVS_Normal].Y = 0.0f;
        Param.offset[EVS_Normal].Z = 0.0f;
        Param.offset[EVS_Small].Y = 0.0f;
        Param.offset[EVS_Small].Z = 0.0f;
        Param.offset[EVS_Tiny].Y = 0.0f;
        Param.offset[EVS_Tiny].Z = 0.0f;
        Param.Distance[EVS_Normal] = 0.0f;
        Param.Distance[EVS_Small] = 0.0f;
        Param.Distance[EVS_Tiny] = 0.0f;
        Param.usePitchCurve = 0;
        Param.useCollTarget = 0;
        Param.useCylColl = 0;
        Param.useColl = 1;
        Param.collCBInterSpeed = 0.0f;
        Param.interSpeed = 800.0f;
        Param.collInterSpeed = 400.0f;
        Param.twigX = 30.0f;
        Param.twigZ = 30.0f;
        Param.targetZSpeed = 200.0f;
        Param.minYaw = -65536;
        Param.maxYaw = 65536;
        Param.minPitch = -15000;
        Param.maxPitch = 15000;
        Param.Damping = 6.0f;
        Param.biasCut = 0.75f;
        Param.biasSlope = 0.3f;
        break;
    }
    case ECM_SecondPerson: {
        if (LoadCameraParameters(ECM_Walking))
            appMemcpy(&m_camParam[ECM_SecondPerson], &m_camParam[ECM_Walking], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_SecondPerson];
        Param.offset[EVS_Normal].Y = 27.0f;
        Param.offset[EVS_Small].Y = 30.0f;
        Param.offset[EVS_Tiny].Y = 28.0f;
        Param.Distance[EVS_Normal] = 30.0f;
        Param.Distance[EVS_Small] = 32.0f;
        Param.alignPawn = 1;
        Param.Distance[EVS_Tiny] = 30.0f;
        Param.offset[EVS_Normal].Z = 0.0f;
        Param.offset[EVS_Small].Z = 0.0f;
        Param.offset[EVS_Tiny].Z = 0.0f;
        Param.twigX = 30.0f;
        Param.interSpeed = 400.0f;
        Param.twigZ = 30.0f;
        Param.targetZSpeed = 100.0f;
        Param.collInterSpeed = 400.0f;
        Param.minYaw = -65536;
        Param.maxYaw = 65536;
        Param.minPitch = -15000;
        Param.maxPitch = 15000;
        Param.Damping = 6.0f;
        Param.usePitchCurve = 0;
        Param.biasCut = 0.75f;
        Param.offsetSpeed = 400.0f;
        Param.biasSlope = 0.3f;
        Param.useCollTarget = 1;
        Param.useCylColl = 0;
        Param.useColl = 1;
        Param.collCBInterSpeed = 0.0f;
        break;
    }
    case ECM_SecondPersonCr: {
        if (LoadCameraParameters(ECM_SecondPerson))
            appMemcpy(&m_camParam[ECM_SecondPersonCr], &m_camParam[ECM_SecondPerson], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_SecondPersonCr];
        Param.offset[EVS_Small].Z = 0.0f;
        Param.offset[EVS_Tiny].Z = 0.0f;
        Param.Distance[EVS_Normal] = 10.0f;
        Param.Distance[EVS_Small] = 42.0f;
        Param.Distance[EVS_Tiny] = 40.0f;
        Param.offset[EVS_Normal].Y = 27.0f;
        Param.offset[EVS_Normal].Z = 20.0f;
        Param.offset[EVS_Small].Y = 30.0f;
        Param.offset[EVS_Tiny].Y = 28.0f;
        break;
    }
    case ECM_Grab: {
        if (LoadCameraParameters(ECM_Walking))
            appMemcpy(&m_camParam[ECM_Grab], &m_camParam[ECM_Walking], sizeof(ECamParam));
        break;
    }
    case ECM_GrabFP: {
        if (LoadCameraParameters(ECM_SecondPerson))
            appMemcpy(&m_camParam[ECM_GrabFP], &m_camParam[ECM_SecondPerson], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_GrabFP];
        Param.offset[EVS_Normal].Z = -5.0f;
        Param.offset[EVS_Small].Z = -5.0f;
        Param.offset[EVS_Tiny].Z = -5.0f;
        Param.offset[EVS_Normal].Y = 15.0f;
        Param.Distance[EVS_Normal] = 90.0f;
        Param.Distance[EVS_Small] = 90.0f;
        Param.Distance[EVS_Tiny] = 90.0f;
        Param.offset[EVS_Small].Y = 15.0f;
        Param.offset[EVS_Tiny].Y = 15.0f;
        Param.minPitch = -5000;
        Param.maxPitch = 7500;
        break;
    }
    case ECM_Carry: {
        if (LoadCameraParameters(ECM_Walking))
            appMemcpy(&m_camParam[ECM_Carry], &m_camParam[ECM_Walking], sizeof(ECamParam));
        break;
    }
    case ECM_CarryCr: {
        if (LoadCameraParameters(ECM_WalkingCr))
            appMemcpy(&m_camParam[ECM_CarryCr], &m_camParam[ECM_WalkingCr], sizeof(ECamParam));
        break;
    }
    case ECM_Throw: {
        ECamParam &Param = m_camParam[ECM_Throw];
        Param.Distance[EVS_Normal] = 70.0f;
        Param.Distance[EVS_Small] = 70.0f;
        Param.Distance[EVS_Tiny] = 70.0f;
        Param.offset[EVS_Normal].Z = -10.0f;
        Param.offset[EVS_Small].Z = -10.0f;
        Param.offset[EVS_Tiny].Z = -10.0f;
        Param.offset[EVS_Normal].Y = 30.0f;
        Param.offset[EVS_Small].Y = 30.0f;
        Param.offset[EVS_Tiny].Y = 30.0f;
        Param.alignPawn = 1;
        Param.usePitchCurve = 0;
        Param.useCollTarget = 1;
        Param.useCylColl = 1;
        Param.useColl = 1;
        Param.useAngles = 1;
        Param.targetZSpeed = 300.0f;
        Param.useTwig = 1;
        Param.minYaw = -65536;
        Param.interSpeed = 400.0f;
        Param.collInterSpeed = 400.0f;
        Param.collCBInterSpeed = 400.0f;
        Param.maxYaw = 65536;
        Param.targetXYSpeed = 400.0f;
        Param.minPitch = -14000;
        Param.maxPitch = 14000;
        Param.twigX = 20.0f;
        Param.offsetSpeed = 400.0f;
        Param.twigZ = 20.0f;
        Param.Damping = 6.0f;
        Param.biasCut = 0.75f;
        Param.biasSlope = 0.3f;
        break;
    }
    case ECM_ThrowCr: {
        if (LoadCameraParameters(ECM_Throw))
            appMemcpy(&m_camParam[ECM_ThrowCr], &m_camParam[ECM_Throw], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_ThrowCr];
        Param.Distance[EVS_Normal] = 70.0f;
        Param.Distance[EVS_Small] = 70.0f;
        Param.Distance[EVS_Tiny] = 70.0f;
        Param.Distance[EVS_Minute] = 50.0f;
        break;
    }
    case ECM_Sniping: {
        if (LoadCameraParameters(ECM_SecondPerson))
            appMemcpy(&m_camParam[ECM_Sniping], &m_camParam[ECM_SecondPerson], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_Sniping];
        Param.offset[EVS_Normal].Y = 25.0f;
        Param.offset[EVS_Small].Y = 25.0f;
        Param.offset[EVS_Tiny].Y = 25.0f;
        Param.offset[EVS_Minute].Y = 25.0f;
        Param.offset[EVS_Normal].X = 0.0f;
        Param.offset[EVS_Normal].Z = 0.0f;
        Param.offset[EVS_Small].X = 0.0f;
        Param.offset[EVS_Small].Z = 0.0f;
        Param.offset[EVS_Tiny].X = 0.0f;
        Param.offset[EVS_Tiny].Z = 0.0f;
        Param.offset[EVS_Minute].X = 0.0f;
        Param.offset[EVS_Minute].Z = 0.0f;
        Param.Distance[EVS_Normal] = 0.0f;
        Param.Distance[EVS_Small] = 0.0f;
        Param.Distance[EVS_Tiny] = 0.0f;
        Param.Distance[EVS_Minute] = 0.0f;
        Param.useTwig = 0;
        Param.targetZSpeed = 200.0f;
        Param.targetXYSpeed = 200.0f;
        Param.interSpeed = 800.0f;
        Param.Damping = 8.0f;
        Param.biasCut = 0.7f;
        Param.biasSlope = 0.7f;
        break;
    }
    case ECM_HSphere: {
        if (LoadCameraParameters(ECM_FSphere))
            appMemcpy(&m_camParam[ECM_HSphere], &m_camParam[ECM_FSphere], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_HSphere];
        Param.usePitchCurve = 1;
        Param.useAngles = 1;
        Param.useTwig = 1;
        Param.minYaw = -20000;
        Param.maxYaw = 20000;
        Param.minPitch = -13000;
        Param.maxPitch = 12000;
        Param.twigX = 10.0f;
        Param.twigZ = 30.0f;
        break;
    }
    case ECM_FSphere: {
        ECamParam &Param = m_camParam[ECM_FSphere];
        Param.interSpeed = 400.0f;
        Param.collInterSpeed = 400.0f;
        Param.collCBInterSpeed = 400.0f;
        Param.targetXYSpeed = 400.0f;
        Param.offsetSpeed = 400.0f;
        Param.useCollTarget = 1;
        Param.useCylColl = 1;
        Param.useColl = 1;
        Param.useAngles = 1;
        Param.Distance[EVS_Normal] = 250.0f;
        Param.Distance[EVS_Small] = 175.0f;
        Param.Distance[EVS_Tiny] = 100.0f;
        Param.targetZSpeed = 300.0f;
        Param.minYaw = -65536;
        Param.maxYaw = 65536;
        Param.minPitch = -13000;
        Param.maxPitch = 10000;
        Param.Damping = 8.0f;
        Param.biasCut = 0.7f;
        Param.biasSlope = 0.7f;
        break;
    }
    case ECM_OnLedge: {
        if (LoadCameraParameters(ECM_HSphere))
            appMemcpy(&m_camParam[ECM_OnLedge], &m_camParam[ECM_HSphere], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_OnLedge];
        Param.offset[EVS_Normal].Z = 10.0f;
        Param.offset[EVS_Small].Z = 10.0f;
        Param.offset[EVS_Tiny].Z = 10.0f;
        Param.offset[EVS_Normal].Y = 0.0f;
        Param.offset[EVS_Small].X = 0.0f;
        Param.offset[EVS_Tiny].Y = 0.0f;
        Param.useCollTarget = 0;
        Param.offset[EVS_Normal].X = -40.0f;
        Param.offsetSpeed = 20.0f;
        Param.minYaw = -65535;
        Param.maxYaw = 65535;
        Param.minPitch = -15000;
        Param.maxPitch = 15000;
        break;
    }
    case ECM_HOH: {
        if (LoadCameraParameters(ECM_FSphere))
            appMemcpy(&m_camParam[ECM_HOH], &m_camParam[ECM_FSphere], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_HOH];
        Param.useCollTarget = 0;
        Param.offsetSpeed = 20.0f;
        Param.twigX = 40.0f;
        Param.twigZ = 30.0f;
        Param.minPitch = -13000;
        Param.maxPitch = 10000;
        break;
    }
    case ECM_HOHFU: {
        if (LoadCameraParameters(ECM_FSphere))
            appMemcpy(&m_camParam[ECM_HOHFU], &m_camParam[ECM_FSphere], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_HOHFU];
        Param.offset[EVS_Normal].X = -40.0f;
        Param.offset[EVS_Small].X = -40.0f;
        Param.offset[EVS_Tiny].X = -40.0f;
        Param.useCollTarget = 0;
        Param.usePitchCurve = 1;
        Param.offsetSpeed = 20.0f;
        Param.maxPitch = 12000;
        Param.minPitch = -13000;
        break;
    }
    case ECM_HOHFP: {
        ECamParam &Param = m_camParam[ECM_HOHFP];
        Param.offset[EVS_Normal].Z = 40.0f;
        Param.targetXYSpeed = 40.0f;
        Param.offsetSpeed = 40.0f;
        Param.offset[EVS_Normal].Y = 0.0f;
        Param.useAngles = 1;
        Param.collCBInterSpeed = 0.0f;
        Param.useTwig = 1;
        Param.offset[EVS_Normal].X = 5.0f;
        Param.useCollTarget = 0;
        Param.Distance[EVS_Normal] = 27.0f;
        Param.minYaw = -10000;
        Param.maxYaw = 10000;
        Param.minPitch = -12000;
        Param.maxPitch = 5000;
        Param.interSpeed = 200.0f;
        Param.targetZSpeed = 30.0f;
        Param.twigX = 30.0f;
        Param.twigZ = 30.0f;
        Param.Damping = 6.0f;
        Param.biasCut = 0.75f;
        Param.biasSlope = 0.3f;
        break;
    }
    case ECM_BTW: {
        ECamParam &Param = m_camParam[ECM_BTW];
        Param.Distance[EVS_Minute] = 50.0f;
        Param.offset[EVS_Minute].Z = 50.0f;
        Param.collInterSpeed = 400.0f;
        Param.useAngles = 1;
        Param.usePitchCurve = 1;
        Param.useCollTarget = 0;
        Param.useCylColl = 1;
        Param.useColl = 1;
        Param.Distance[EVS_Normal] = 150.0f;
        Param.Distance[EVS_Small] = 125.0f;
        Param.Distance[EVS_Tiny] = 100.0f;
        Param.offset[EVS_Minute].X = 20.0f;
        Param.offset[EVS_Normal].X = 15.0f;
        Param.minYaw = -20000;
        Param.maxYaw = 20000;
        Param.minPitch = -13000;
        Param.maxPitch = 13000;
        Param.interSpeed = 200.0f;
        Param.collCBInterSpeed = 400.0f;
        Param.targetXYSpeed = 125.0f;
        Param.targetZSpeed = 250.0f;
        Param.Damping = 8.0f;
        Param.biasCut = 0.7f;
        Param.biasSlope = 0.7f;
        Param.offsetSpeed = 125.0f;
        break;
    }
    case ECM_BTWPeakLeft: {
        if (LoadCameraParameters(ECM_BTW))
            appMemcpy(&m_camParam[ECM_BTWPeakLeft], &m_camParam[ECM_BTW], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_BTWPeakLeft];
        Param.offset[EVS_Normal].Z = -10.0f;
        Param.offset[EVS_Small].Z = -10.0f;
        Param.offset[EVS_Tiny].Z = -10.0f;
        Param.offset[EVS_Minute].Z = -10.0f;
        Param.Distance[EVS_Normal] = 100.0f;
        Param.Distance[EVS_Small] = 100.0f;
        Param.Distance[EVS_Tiny] = 100.0f;
        Param.offset[EVS_Normal].Y = -60.0f;
        Param.offset[EVS_Small].Y = -60.0f;
        Param.offset[EVS_Tiny].Y = -60.0f;
        Param.offset[EVS_Minute].Y = -50.0f;
        Param.Distance[EVS_Minute] = 50.0f;
        break;
    }
    case ECM_BTWPeakRight: {
        if (LoadCameraParameters(ECM_BTWPeakLeft))
            appMemcpy(&m_camParam[ECM_BTWPeakRight], &m_camParam[ECM_BTWPeakLeft], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_BTWPeakRight];
        Param.offset[EVS_Normal].Z = -10.0f;
        Param.offset[EVS_Small].Z = -10.0f;
        Param.offset[EVS_Tiny].Z = -10.0f;
        Param.offset[EVS_Normal].Y = 60.0f;
        Param.offset[EVS_Minute].Z = -10.0f;
        Param.offset[EVS_Small].Y = 60.0f;
        Param.offset[EVS_Tiny].Y = 60.0f;
        Param.offset[EVS_Minute].Y = 50.0f;
        break;
    }
    case ECM_BTWLeftFP: {
        if (LoadCameraParameters(ECM_BTWPeakLeft))
            appMemcpy(&m_camParam[ECM_BTWLeftFP], &m_camParam[ECM_BTWPeakLeft], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_BTWLeftFP];
        Param.Distance[EVS_Normal] = 50.0f;
        Param.Distance[EVS_Small] = 50.0f;
        Param.Distance[EVS_Tiny] = 50.0f;
        Param.Distance[EVS_Minute] = 50.0f;
        Param.minYaw = -12000;
        Param.minPitch = -12000;
        Param.maxYaw = 2000;
        Param.maxPitch = 12000;
        Param.Damping = 6.0f;
        Param.biasCut = 0.75f;
        Param.biasSlope = 0.3f;
        break;
    }
    case ECM_BTWRightFP: {
        if (LoadCameraParameters(ECM_BTWPeakRight))
            appMemcpy(&m_camParam[ECM_BTWRightFP], &m_camParam[ECM_BTWPeakRight], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_BTWRightFP];
        Param.Distance[EVS_Normal] = 50.0f;
        Param.Distance[EVS_Small] = 50.0f;
        Param.Distance[EVS_Tiny] = 50.0f;
        Param.Distance[EVS_Minute] = 50.0f;
        Param.maxYaw = 12000;
        Param.maxPitch = 12000;
        Param.minYaw = -2000;
        Param.minPitch = -12000;
        Param.Damping = 6.0f;
        Param.biasCut = 0.75f;
        Param.biasSlope = 0.3f;
        break;
    }
    case ECM_Rapel: {
        if (LoadCameraParameters(ECM_HSphere))
            appMemcpy(&m_camParam[ECM_Rapel], &m_camParam[ECM_HSphere], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_Rapel];
        Param.offset[EVS_Normal].X = -30.0f;
        Param.offset[EVS_Normal].Z = -20.0f;
        Param.offset[EVS_Small].Z = -20.0f;
        Param.offset[EVS_Tiny].Z = -20.0f;
        Param.offset[EVS_Small].X = -30.0f;
        Param.offset[EVS_Tiny].X = -30.0f;
        break;
    }
    case ECM_RapelFP: {
        ECamParam &Param = m_camParam[ECM_RapelFP];
        Param.offset[EVS_Normal].Z = -35.0f;
        Param.offset[EVS_Small].Z = -35.0f;
        Param.offset[EVS_Tiny].Z = -35.0f;
        Param.Distance[EVS_Normal] = 45.0f;
        Param.offset[EVS_Normal].X = -60.0f;
        Param.offset[EVS_Normal].Y = 25.0f;
        Param.offset[EVS_Small].X = -60.0f;
        Param.Distance[EVS_Small] = 45.0f;
        Param.offset[EVS_Small].Y = 25.0f;
        Param.Distance[EVS_Tiny] = 45.0f;
        Param.offset[EVS_Tiny].Y = 25.0f;
        Param.targetXYSpeed = 400.0f;
        Param.useAngles = 1;
        Param.offset[EVS_Tiny].X = -60.0f;
        Param.offsetSpeed = 400.0f;
        Param.collCBInterSpeed = 0.0f;
        Param.minYaw = -12000;
        Param.useTwig = 1;
        Param.maxYaw = 12000;
        Param.minPitch = -8000;
        Param.maxPitch = 13000;
        Param.interSpeed = 800.0f;
        Param.targetZSpeed = 300.0f;
        Param.twigX = 30.0f;
        Param.twigZ = 30.0f;
        Param.Damping = 6.0f;
        Param.biasCut = 0.75f;
        Param.biasSlope = 0.3f;
        break;
    }
    case ECM_DoorPeekRight: {
        ECamParam &Param = m_camParam[ECM_DoorPeekRight];
        Param.offset[EVS_Normal].X = 45.0f;
        Param.offset[EVS_Small].X = 45.0f;
        Param.offset[EVS_Normal].Z = 5.0f;
        Param.offset[EVS_Tiny].X = 45.0f;
        Param.Distance[EVS_Normal] = 50.0f;
        Param.Distance[EVS_Small] = 50.0f;
        Param.Distance[EVS_Tiny] = 50.0f;
        Param.offset[EVS_Normal].Y = 25.0f;
        Param.offset[EVS_Small].Y = 25.0f;
        Param.offset[EVS_Tiny].Y = 25.0f;
        Param.interSpeed = 400.0f;
        Param.collInterSpeed = 400.0f;
        Param.offset[EVS_Small].Z = 5.0f;
        Param.collCBInterSpeed = 400.0f;
        Param.minYaw = 0;
        Param.offset[EVS_Tiny].Z = 5.0f;
        Param.targetZSpeed = 300.0f;
        Param.maxYaw = 16000;
        Param.minPitch = -12000;
        Param.useAngles = 1;
        Param.maxPitch = 12000;
        Param.Damping = 8.0f;
        Param.biasCut = 0.7f;
        Param.useTwig = 1;
        Param.targetXYSpeed = 400.0f;
        Param.offsetSpeed = 400.0f;
        Param.biasSlope = 0.7f;
        Param.twigX = 20.0f;
        Param.twigZ = 40.0f;
        break;
    }
    case ECM_DoorPeekLeft: {
        ECamParam &Param = m_camParam[ECM_DoorPeekLeft];
        Param.offset[EVS_Normal].X = 45.0f;
        Param.offset[EVS_Normal].Y = -25.0f;
        Param.offset[EVS_Small].Y = -25.0f;
        Param.offset[EVS_Tiny].Y = -25.0f;
        Param.offset[EVS_Small].X = 45.0f;
        Param.offset[EVS_Tiny].X = 45.0f;
        Param.Distance[EVS_Normal] = 50.0f;
        Param.Distance[EVS_Small] = 50.0f;
        Param.Distance[EVS_Tiny] = 50.0f;
        Param.interSpeed = 400.0f;
        Param.collInterSpeed = 400.0f;
        Param.collCBInterSpeed = 400.0f;
        Param.targetXYSpeed = 400.0f;
        Param.offsetSpeed = 400.0f;
        Param.maxYaw = 0;
        Param.offset[EVS_Normal].Z = 5.0f;
        Param.offset[EVS_Small].Z = 5.0f;
        Param.offset[EVS_Tiny].Z = 5.0f;
        Param.useAngles = 1;
        Param.targetZSpeed = 300.0f;
        Param.minYaw = -16000;
        Param.minPitch = -12000;
        Param.maxPitch = 12000;
        Param.Damping = 8.0f;
        Param.biasCut = 0.7f;
        Param.biasSlope = 0.7f;
        Param.useTwig = 1;
        Param.twigX = 20.0f;
        Param.twigZ = 40.0f;
        break;
    }
    case ECM_SplitJump: {
        if (LoadCameraParameters(ECM_FSphere))
            appMemcpy(&m_camParam[ECM_SplitJump], &m_camParam[ECM_FSphere], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_SplitJump];
        Param.offset[EVS_Normal].Z = -40.0f;
        Param.offset[EVS_Small].Z = 30.0f;
        Param.offset[EVS_Tiny].Z = 30.0f;
        Param.interSpeed = 50.0f;
        Param.offsetSpeed = 40.0f;
        Param.useCollTarget = 0;
        break;
    }
    case ECM_SplitJumpFP: {
        if (LoadCameraParameters(ECM_SplitJump))
            appMemcpy(&m_camParam[ECM_SplitJumpFP], &m_camParam[ECM_SplitJump], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_SplitJumpFP];
        Param.alignPawn = 1;
        Param.offset[EVS_Normal].Z = 0.0f;
        Param.usePitchCurve = 0;
        Param.useCylColl = 0;
        Param.useColl = 1;
        Param.collCBInterSpeed = 0.0f;
        Param.offset[EVS_Normal].X = 5.0f;
        Param.offset[EVS_Normal].Y = 12.0f;
        Param.Distance[EVS_Normal] = 27.0f;
        Param.collInterSpeed = 400.0f;
        Param.twigX = 30.0f;
        Param.twigZ = 30.0f;
        Param.targetZSpeed = 100.0f;
        Param.minYaw = -65536;
        Param.maxYaw = 65536;
        Param.minPitch = -15000;
        Param.maxPitch = 15000;
        Param.Damping = 6.0f;
        Param.biasCut = 0.75f;
        Param.biasSlope = 0.3f;
        break;
    }
    case ECM_OnLadder: {
        if (LoadCameraParameters(ECM_Walking))
            appMemcpy(&m_camParam[ECM_OnLadder], &m_camParam[ECM_Walking], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_OnLadder];
        Param.offset[EVS_Normal].X = -20.0f;
        Param.minYaw = -32767;
        Param.maxYaw = 32768;
        Param.minPitch = -15000;
        Param.maxPitch = 14000;
        break;
    }
    case ECM_HOHFPHanged: {
        if (LoadCameraParameters(ECM_BTWLeftFP))
            appMemcpy(&m_camParam[ECM_HOHFPHanged], &m_camParam[ECM_BTWLeftFP], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_HOHFPHanged];
        Param.offset[EVS_Normal].X = -30.0f;
        Param.offset[EVS_Normal].Y = -15.0f;
        Param.offset[EVS_Normal].Z = -120.0f;
        Param.Distance[EVS_Normal] = 125.0f;
        Param.offsetSpeed = 40.0f;
        break;
    }
    case ECM_NoTargetCol: {
        if (LoadCameraParameters(ECM_Walking))
            appMemcpy(&m_camParam[ECM_NoTargetCol], &m_camParam[ECM_Walking], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_NoTargetCol];
        Param.useCollTarget = 0;
        Param.interSpeed = 200.0f;
        Param.minYaw = -32767;
        Param.maxYaw = 32768;
        Param.minPitch = -15000;
        Param.maxPitch = 14000;
        break;
    }
    case ECM_SmoothTransitionCentered: {
        if (LoadCameraParameters(ECM_Walking))
            appMemcpy(&m_camParam[ECM_SmoothTransitionCentered], &m_camParam[ECM_Walking], sizeof(ECamParam));
        ECamParam &Param = m_camParam[ECM_SmoothTransitionCentered];
        Param.targetZSpeed = 50.0f;
        Param.offset[EVS_Normal].X = 0.0f;
        Param.offset[EVS_Normal].Y = 0.0f;
        Param.offset[EVS_Normal].Z = 0.0f;
        Param.offset[EVS_Small].X = 0.0f;
        Param.offset[EVS_Small].Y = 0.0f;
        Param.offset[EVS_Small].Z = 0.0f;
        Param.offset[EVS_Tiny].X = 0.0f;
        Param.offset[EVS_Tiny].Y = 0.0f;
        Param.offset[EVS_Tiny].Z = 0.0f;
        Param.offset[EVS_Minute].X = 0.0f;
        Param.offset[EVS_Minute].Y = 0.0f;
        Param.offset[EVS_Minute].Z = 0.0f;
        Param.interSpeed = 50.0f;
        break;
    }
    }
    CameraLoaded[Mode] = 1;
    CameraLoading[Mode] = 0;
    return 1;
}

static TCHAR EmptyCameraModeName[] = L"";
FString ASPlayerCam::GetCamModeStringFromEnum(INT Mode)
{
    if (Mode == ECM_Walking)
        return FString(L"ECM_Walking");
    if (Mode == ECM_WalkingCr)
        return FString(L"ECM_WalkingCr");
    if (Mode == ECM_Running)
        return FString(L"ECM_Running");
    if (Mode == ECM_RunningCr)
        return FString(L"ECM_RunningCr");
    if (Mode == ECM_SecondPerson)
        return FString(L"ECM_SecondPerson");
    if (Mode == ECM_SecondPersonCr)
        return FString(L"ECM_SecondPersonCr");
    if (Mode == ECM_Grab)
        return FString(L"ECM_Grab");
    if (Mode == ECM_GrabFP)
        return FString(L"ECM_GrabFP");
    if (Mode == ECM_Carry)
        return FString(L"ECM_Carry");
    if (Mode == ECM_CarryCr)
        return FString(L"ECM_CarryCr");
    if (Mode == ECM_Throw)
        return FString(L"ECM_Throw");
    if (Mode == ECM_ThrowCr)
        return FString(L"ECM_ThrowCr");
    if (Mode == ECM_Sniping)
        return FString(L"ECM_Sniping");
    if (Mode == ECM_HSphere)
        return FString(L"ECM_HSphere");
    if (Mode == ECM_FSphere)
        return FString(L"ECM_FSphere");
    if (Mode == ECM_HOH)
        return FString(L"ECM_HOH");
    if (Mode == ECM_HOHFU)
        return FString(L"ECM_HOHFU");
    if (Mode == ECM_HOHFP)
        return FString(L"ECM_HOHFP");
    if (Mode == ECM_BTW)
        return FString(L"ECM_BTW");
    if (Mode == ECM_BTWPeakLeft)
        return FString(L"ECM_BTWPeakLeft");
    if (Mode == ECM_BTWPeakRight)
        return FString(L"ECM_BTWPeakRight");
    if (Mode == ECM_BTWLeftFP)
        return FString(L"ECM_BTWLeftFP");
    if (Mode == ECM_BTWRightFP)
        return FString(L"ECM_BTWRightFP");
    if (Mode == ECM_Rapel)
        return FString(L"ECM_Rapel");
    if (Mode == ECM_RapelFP)
        return FString(L"ECM_RapelFP");
    if (Mode == ECM_DoorPeekRight)
        return FString(L"ECM_DoorPeekRight");
    if (Mode == ECM_DoorPeekLeft)
        return FString(L"ECM_DoorPeekLeft");
    if (Mode == ECM_SplitJump)
        return FString(L"ECM_SplitJump");
    if (Mode == ECM_SplitJumpFP)
        return FString(L"ECM_SplitJumpFP");
    if (Mode == ECM_FirstPerson)
        return FString(L"ECM_FirstPerson");
    if (Mode == ECM_OnLedge)
        return FString(L"ECM_OnLedge");
    if (Mode == ECM_HOHFPHanged)
        return FString(L"ECM_HOHFPHanged");
    if (Mode == ECM_OnLadder)
        return FString(L"ECM_OnLadder");
    if (Mode == ECM_NoTargetCol)
        return FString(L"ECM_NoTargetCol");
    if (Mode == ECM_SmoothTransitionCentered)
        return FString(L"ECM_SmoothTransitionCentered");
    return FString(EmptyCameraModeName);
}
