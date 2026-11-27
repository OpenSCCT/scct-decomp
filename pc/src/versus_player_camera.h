#ifndef VERSUS_PLAYER_CAMERA_H
#define VERSUS_PLAYER_CAMERA_H

class FString;

enum ECamMode {
    ECM_Walking,
    ECM_WalkingCr,
    ECM_Running,
    ECM_RunningCr,
    ECM_SecondPerson,
    ECM_SecondPersonCr,
    ECM_Grab,
    ECM_GrabFP,
    ECM_Carry,
    ECM_CarryCr,
    ECM_Throw,
    ECM_ThrowCr,
    ECM_Sniping,
    ECM_HSphere,
    ECM_FSphere,
    ECM_HOH,
    ECM_HOHFU,
    ECM_HOHFP,
    ECM_BTW,
    ECM_BTWPeakLeft,
    ECM_BTWPeakRight,
    ECM_BTWLeftFP,
    ECM_BTWRightFP,
    ECM_Rapel,
    ECM_RapelFP,
    ECM_DoorPeekRight,
    ECM_DoorPeekLeft,
    ECM_SplitJump,
    ECM_SplitJumpFP,
    ECM_FirstPerson,
    ECM_OnLedge,
    ECM_HOHFPHanged,
    ECM_OnLadder,
    ECM_NoTargetCol,
    ECM_SmoothTransitionCentered,
    ECM_MAX
};

enum EVolumeSize { EVS_Normal, EVS_Small, EVS_Tiny, EVS_Minute };

struct ECamParam {
    FVector offset[EVS_Minute + 1];
    FLOAT Distance[EVS_Minute + 1];
    INT minYaw;
    INT maxYaw;
    INT minPitch;
    INT maxPitch;
    FLOAT Damping;
    FLOAT interSpeed;
    FLOAT collInterSpeed;
    FLOAT collCBInterSpeed;
    FLOAT targetXYSpeed;
    FLOAT targetZSpeed;
    FLOAT twigX;
    FLOAT twigZ;
    FLOAT biasCut;
    FLOAT biasSlope;
    FLOAT offsetSpeed;
    INT useAngles;
    INT alignPawn;
    INT usePitchCurve;
    INT useCollTarget;
    INT useCylColl;
    INT useColl;
    INT useTwig;
};

// SBase.SPlayerCam has 35 presets and 78 virtual functions.
class ASPlayerCam : public AActor {
public:
    virtual ~ASPlayerCam();
    UBOOL LoadCameraParameters(INT Mode);
    FString GetCamModeStringFromEnum(INT Mode);

    ECamParam m_camParam[ECM_MAX];
    BYTE unk_17c0[0x18f0 - 0x17c0];
};

#endif
