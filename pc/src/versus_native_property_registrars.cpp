// Register reflected native configuration fields and defaults for the three device classes.
#include "versus_build.h"
#include "versus_native_properties.h"


#include "versus_d3d_render_device.h"
static const DWORD RF_Public = 4;
static const DWORD CPF_Config = 0x4000;
#define STRUCT_OFFSET(type, member) ((INT)&((type *)0)->member)

static const EName NAME_AdapterNumber = (EName)67;
static const EName NAME_AllowDownloads = (EName)254;
static const EName NAME_CONFClientInternetMaxNetSpeed = (EName)6002;
static const EName NAME_CONFClientInternetMinNetSpeed = (EName)6003;
static const EName NAME_CONFClientLagToTakeAction = (EName)6004;
static const EName NAME_CONFClientLanMaxNetSpeed = (EName)6005;
static const EName NAME_CONFClientLanMinNetSpeed = (EName)6006;
static const EName NAME_CONFClientMaxAllowedLag = (EName)6007;
static const EName NAME_CONFClientNetSpeedStepUp = (EName)6008;
static const EName NAME_CONFDedicatedServerInternetMaxNetSpeed = (EName)6009;
static const EName NAME_CONFDedicatedServerInternetMinNetSpeed = (EName)6010;
static const EName NAME_CONFDedicatedServerLagToTakeAction = (EName)6011;
static const EName NAME_CONFDedicatedServerLanMaxNetSpeed = (EName)6012;
static const EName NAME_CONFDedicatedServerLanMinNetSpeed = (EName)6013;
static const EName NAME_CONFDedicatedServerMaxAllowedLag = (EName)6014;
static const EName NAME_CONFDedicatedServerNetSpeedStepUp = (EName)6015;
static const EName NAME_CONFListenServerInternetMaxNetSpeed = (EName)6016;
static const EName NAME_CONFListenServerInternetMinNetSpeed = (EName)6017;
static const EName NAME_CONFListenServerLagToTakeAction = (EName)6018;
static const EName NAME_CONFListenServerLanMaxNetSpeed = (EName)6019;
static const EName NAME_CONFListenServerLanMinNetSpeed = (EName)6020;
static const EName NAME_CONFListenServerMaxAllowedLag = (EName)6021;
static const EName NAME_CONFListenServerNetSpeedStepUp = (EName)6022;
static const EName NAME_CheckForOverflow = (EName)65;
static const EName NAME_Client = (EName)611;
static const EName NAME_ConnectionTimeout = (EName)96;
static const EName NAME_DecompressTextures = (EName)66;
static const EName NAME_DefaultTexMipBias = (EName)72;
static const EName NAME_DescFlags = (EName)77;
static const EName NAME_Description = (EName)46;
static const EName NAME_DesiredRefreshRate = (EName)69;
static const EName NAME_DetailTexMipBias = (EName)71;
static const EName NAME_DetailTextures = (EName)78;
static const EName NAME_HighDetailActors = (EName)75;
static const EName NAME_InitialConnectTimeout = (EName)97;
static const EName NAME_KeepAliveTime = (EName)98;
static const EName NAME_LanServerMaxTickRate = (EName)253;
static const EName NAME_LevelOfAnisotropy = (EName)70;
static const EName NAME_MaxClientRate = (EName)149;
static const EName NAME_MaxDownloadSize = (EName)255;
static const EName NAME_MaxPixelShaderVersion = (EName)68;
static const EName NAME_NetServerMaxTickRate = (EName)252;
static const EName NAME_Options = (EName)960;
static const EName NAME_ReduceMouseLag = (EName)63;
static const EName NAME_RelevantTimeout = (EName)99;
static const EName NAME_ServerTravelPause = (EName)148;
static const EName NAME_SpawnPrioritySeconds = (EName)147;
static const EName NAME_SuperHighDetailActors = (EName)76;
static const EName NAME_TesselationFactor = (EName)73;
static const EName NAME_Use16bit = (EName)89;
static const EName NAME_Use16bitTextures = (EName)94;
static const EName NAME_UseCubemaps = (EName)62;
static const EName NAME_UseHardwareTL = (EName)56;
static const EName NAME_UseHardwareVS = (EName)57;
static const EName NAME_UseNPatches = (EName)64;
static const EName NAME_UsePrecaching = (EName)58;
static const EName NAME_UseStencil = (EName)79;
static const EName NAME_UseTrilinear = (EName)59;
static const EName NAME_UseTripleBuffering = (EName)61;
static const EName NAME_UseVSync = (EName)60;
static const EName NAME_maxAcceptableUnAckBunch = (EName)6023;

class UNetDriver : public USubsystem {
public:
    void StaticConstructor();

    BYTE unk_28[0x24];
    FLOAT ConnectionTimeout;
    FLOAT InitialConnectTimeout;
    FLOAT KeepAliveTime;
    FLOAT RelevantTimeout;
    FLOAT SpawnPrioritySeconds;
    FLOAT ServerTravelPause;
    INT MaxClientRate;
    INT NetServerMaxTickRate;
    INT LanServerMaxTickRate;
    UBOOL AllowDownloads;
    BYTE unk_74[0x14];
    INT MaxDownloadSize;
    BYTE unk_8c[0xc];
    INT CONFClientNetSpeedStepUp;
    INT CONFClientInternetMinNetSpeed;
    INT CONFClientInternetMaxNetSpeed;
    INT CONFClientLanMinNetSpeed;
    INT CONFClientLanMaxNetSpeed;
    FLOAT CONFClientLagToTakeAction;
    FLOAT CONFClientMaxAllowedLag;
    INT CONFListenServerNetSpeedStepUp;
    INT CONFListenServerInternetMinNetSpeed;
    INT CONFListenServerInternetMaxNetSpeed;
    INT CONFListenServerLanMinNetSpeed;
    INT CONFListenServerLanMaxNetSpeed;
    FLOAT CONFListenServerLagToTakeAction;
    FLOAT CONFListenServerMaxAllowedLag;
    INT CONFDedicatedServerNetSpeedStepUp;
    INT CONFDedicatedServerInternetMinNetSpeed;
    INT CONFDedicatedServerInternetMaxNetSpeed;
    INT CONFDedicatedServerLanMinNetSpeed;
    INT CONFDedicatedServerLanMaxNetSpeed;
    FLOAT CONFDedicatedServerLagToTakeAction;
    FLOAT CONFDedicatedServerMaxAllowedLag;
    BYTE unk_ec[0xc];
    INT maxAcceptableUnAckBunch;
    BYTE unk_fc[0x8];
    INT unk_104;
    INT unk_108;
};

void UNetDriver::StaticConstructor()
{
    new (GetClass(), NAME_ConnectionTimeout, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, ConnectionTimeout), NAME_Client, CPF_Config);
    new (GetClass(), NAME_InitialConnectTimeout, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, InitialConnectTimeout), NAME_Client, CPF_Config);
    new (GetClass(), NAME_KeepAliveTime, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, KeepAliveTime), NAME_Client, CPF_Config);
    new (GetClass(), NAME_RelevantTimeout, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, RelevantTimeout), NAME_Client, CPF_Config);
    new (GetClass(), NAME_SpawnPrioritySeconds, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, SpawnPrioritySeconds), NAME_Client, CPF_Config);
    new (GetClass(), NAME_ServerTravelPause, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, ServerTravelPause), NAME_Client, CPF_Config);
    new (GetClass(), NAME_MaxClientRate, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, MaxClientRate), NAME_Client, CPF_Config);
    new (GetClass(), NAME_NetServerMaxTickRate, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, NetServerMaxTickRate), NAME_Client, CPF_Config);
    new (GetClass(), NAME_LanServerMaxTickRate, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, LanServerMaxTickRate), NAME_Client, CPF_Config);
    new (GetClass(), NAME_AllowDownloads, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, AllowDownloads), NAME_Client, CPF_Config);
    new (GetClass(), NAME_MaxDownloadSize, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, MaxDownloadSize), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFClientNetSpeedStepUp, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFClientNetSpeedStepUp), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFClientInternetMinNetSpeed, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFClientInternetMinNetSpeed), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFClientInternetMaxNetSpeed, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFClientInternetMaxNetSpeed), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFClientLanMinNetSpeed, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFClientLanMinNetSpeed), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFClientLanMaxNetSpeed, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFClientLanMaxNetSpeed), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFClientLagToTakeAction, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFClientLagToTakeAction), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFClientMaxAllowedLag, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFClientMaxAllowedLag), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFListenServerNetSpeedStepUp, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFListenServerNetSpeedStepUp), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFListenServerInternetMinNetSpeed, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFListenServerInternetMinNetSpeed), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFListenServerInternetMaxNetSpeed, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFListenServerInternetMaxNetSpeed), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFListenServerLanMinNetSpeed, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFListenServerLanMinNetSpeed), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFListenServerLanMaxNetSpeed, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFListenServerLanMaxNetSpeed), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFListenServerLagToTakeAction, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFListenServerLagToTakeAction), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFListenServerMaxAllowedLag, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFListenServerMaxAllowedLag), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFDedicatedServerNetSpeedStepUp, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFDedicatedServerNetSpeedStepUp), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFDedicatedServerInternetMinNetSpeed, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFDedicatedServerInternetMinNetSpeed), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFDedicatedServerInternetMaxNetSpeed, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFDedicatedServerInternetMaxNetSpeed), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFDedicatedServerLanMinNetSpeed, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFDedicatedServerLanMinNetSpeed), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFDedicatedServerLanMaxNetSpeed, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFDedicatedServerLanMaxNetSpeed), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFDedicatedServerLagToTakeAction, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFDedicatedServerLagToTakeAction), NAME_Client, CPF_Config);
    new (GetClass(), NAME_CONFDedicatedServerMaxAllowedLag, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, CONFDedicatedServerMaxAllowedLag), NAME_Client, CPF_Config);
    new (GetClass(), NAME_maxAcceptableUnAckBunch, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UNetDriver, maxAcceptableUnAckBunch), NAME_Client, CPF_Config);

    MaxClientRate = 25000;
    unk_104 = 0;
    unk_108 = 0;
}

void URenderDevice::StaticConstructor()
{
    new (GetClass(), NAME_HighDetailActors, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(URenderDevice, HighDetailActors), NAME_Client, CPF_Config);
    new (GetClass(), NAME_SuperHighDetailActors, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(URenderDevice, SuperHighDetailActors), NAME_Client, CPF_Config);
    new (GetClass(), NAME_Description, RF_Public) UStrProperty(EC_CppProperty,
        STRUCT_OFFSET(URenderDevice, Description), NAME_Client, CPF_Config);
    new (GetClass(), NAME_DescFlags, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(URenderDevice, DescFlags), NAME_Client, CPF_Config);
    new (GetClass(), NAME_DetailTextures, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(URenderDevice, DetailTextures), NAME_Client, CPF_Config);
    new (GetClass(), NAME_UseStencil, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(URenderDevice, UseStencil), NAME_Client, CPF_Config);
    new (GetClass(), NAME_Use16bit, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(URenderDevice, Use16bit), NAME_Client, CPF_Config);
    new (GetClass(), NAME_Use16bitTextures, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(URenderDevice, Use16bitTextures), NAME_Client, CPF_Config);

    unk_2c = 0;
}

void UD3DRenderDevice::StaticConstructor()
{
    new (GetClass(), NAME_UseHardwareTL, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, UseHardwareTL), NAME_Options, CPF_Config);
    new (GetClass(), NAME_UseHardwareVS, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, UseHardwareVS), NAME_Options, CPF_Config);
    new (GetClass(), NAME_UsePrecaching, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, UsePrecaching), NAME_Options, CPF_Config);
    new (GetClass(), NAME_UseTrilinear, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, UseTrilinear), NAME_Options, CPF_Config);
    new (GetClass(), NAME_UseVSync, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, UseVSync), NAME_Options, CPF_Config);
    new (GetClass(), NAME_UseTripleBuffering, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, UseTripleBuffering), NAME_Options, CPF_Config);
    new (GetClass(), NAME_UseCubemaps, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, UseCubemaps), NAME_Options, CPF_Config);
    new (GetClass(), NAME_ReduceMouseLag, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, ReduceMouseLag), NAME_Options, CPF_Config);
    new (GetClass(), NAME_UseNPatches, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, UseNPatches), NAME_Options, CPF_Config);
    new (GetClass(), NAME_CheckForOverflow, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, CheckForOverflow), NAME_Options, CPF_Config);
    new (GetClass(), NAME_DecompressTextures, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, DecompressTextures), NAME_Options, CPF_Config);
    new (GetClass(), NAME_AdapterNumber, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, AdapterNumber), NAME_Options, CPF_Config);
    new (GetClass(), NAME_MaxPixelShaderVersion, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, MaxPixelShaderVersion), NAME_Options, CPF_Config);
    new (GetClass(), NAME_DesiredRefreshRate, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, DesiredRefreshRate), NAME_Options, CPF_Config);
    new (GetClass(), NAME_LevelOfAnisotropy, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, LevelOfAnisotropy), NAME_Options, CPF_Config);
    new (GetClass(), NAME_DetailTexMipBias, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, DetailTexMipBias), NAME_Options, CPF_Config);
    new (GetClass(), NAME_DefaultTexMipBias, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, DefaultTexMipBias), NAME_Options, CPF_Config);
    new (GetClass(), NAME_TesselationFactor, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UD3DRenderDevice, TesselationFactor), NAME_Options, CPF_Config);

    unk_58 = 1;
}
