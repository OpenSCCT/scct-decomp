#include "versus_native_properties.h"

UEnum::UEnum(UField *InSuper) : UField(InSuper) {}

UByteProperty::UByteProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags, UEnum *InEnum)
    : UProperty(EC_CppProperty, InOffset, InCategory, InFlags), Enum(InEnum) {}

static const DWORD RF_Public = 4;
static const DWORD CPF_Config = 0x4000;
#define STRUCT_OFFSET(type, member) ((INT)&((type *)0)->member)

template<class T> inline void *operator new(unsigned int, TArray<T> &Array)
{
    INT Index = Array.Add(1, sizeof(T));
    return &Array(Index);
}

static const EName NAME_Brightness = (EName)411;
static const EName NAME_CaptureMouse = (EName)414;
static const EName NAME_Client = (EName)611;
static const EName NAME_Contrast = (EName)412;
static const EName NAME_Coronas = (EName)427;
static const EName NAME_Decals = (EName)425;
static const EName NAME_DecoLayers = (EName)428;
static const EName NAME_Display = (EName)961;
static const EName NAME_ETextureDetail = (EName)431;
static const EName NAME_FullscreenViewportX = (EName)409;
static const EName NAME_FullscreenViewportY = (EName)410;
static const EName NAME_Gamma = (EName)413;
static const EName NAME_High = (EName)434;
static const EName NAME_Higher = (EName)435;
static const EName NAME_Low = (EName)438;
static const EName NAME_Lower = (EName)437;
static const EName NAME_MinDesiredFrameRate = (EName)424;
static const EName NAME_NoFractalAnim = (EName)426;
static const EName NAME_NoLighting = (EName)423;
static const EName NAME_Normal = (EName)436;
static const EName NAME_Projectors = (EName)429;
static const EName NAME_ReportDynamicUploads = (EName)430;
static const EName NAME_ScreenFlashes = (EName)422;
static const EName NAME_TextureDetailInterface = (EName)419;
static const EName NAME_TextureDetailLightmap = (EName)421;
static const EName NAME_TextureDetailPlayerSkin = (EName)416;
static const EName NAME_TextureDetailRenderMap = (EName)420;
static const EName NAME_TextureDetailTerrain = (EName)418;
static const EName NAME_TextureDetailWeaponSkin = (EName)417;
static const EName NAME_TextureDetailWorld = (EName)415;
static const EName NAME_UltraHigh = (EName)432;
static const EName NAME_UltraLow = (EName)440;
static const EName NAME_VeryHigh = (EName)433;
static const EName NAME_VeryLow = (EName)439;
static const EName NAME_WindowedViewportX = (EName)407;
static const EName NAME_WindowedViewportY = (EName)408;

class UEngine;
class UViewport;

class UClient : public UObject {
public:
    void StaticConstructor();

    UEngine *Engine;
    TArray<UViewport *> Viewports;
    UBOOL CaptureMouse;
    UBOOL NoLighting;
    UBOOL NoFractalAnim;
    UBOOL DecoLayers;
    UBOOL ScreenFlashes;
    UBOOL Decals;
    UBOOL Coronas;
    UBOOL Projectors;
    UBOOL ReportDynamicUploads;
    INT WindowedViewportX;
    INT WindowedViewportY;
    FLOAT MinDesiredFrameRate;
    INT FullscreenViewportX;
    INT FullscreenViewportY;
    FLOAT Brightness;
    FLOAT Contrast;
    FLOAT Gamma;
    BYTE unk_7c[0x4];
    BYTE TextureDetailWorld;
    BYTE unk_81[0x3];
    BYTE TextureDetailPlayerSkin;
    BYTE unk_85[0x3];
    BYTE TextureDetailWeaponSkin;
    BYTE unk_89[0x3];
    BYTE TextureDetailTerrain;
    BYTE unk_8d[0x3];
    BYTE TextureDetailInterface;
    BYTE unk_91[0x3];
    BYTE TextureDetailRenderMap;
    BYTE unk_95[0x3];
    BYTE TextureDetailLightmap;
    BYTE unk_99[0x7];
    UEnum *TextureDetailEnum;
};

void UClient::StaticConstructor()
{
    TextureDetailEnum = new (GetClass(), NAME_ETextureDetail) UEnum(0);
    new (TextureDetailEnum->Names) FName(NAME_UltraHigh);
    new (TextureDetailEnum->Names) FName(NAME_VeryHigh);
    new (TextureDetailEnum->Names) FName(NAME_High);
    new (TextureDetailEnum->Names) FName(NAME_Higher);
    new (TextureDetailEnum->Names) FName(NAME_Normal);
    new (TextureDetailEnum->Names) FName(NAME_Lower);
    new (TextureDetailEnum->Names) FName(NAME_Low);
    new (TextureDetailEnum->Names) FName(NAME_VeryLow);
    new (TextureDetailEnum->Names) FName(NAME_UltraLow);

    new (GetClass(), NAME_WindowedViewportX, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, WindowedViewportX), NAME_Client, CPF_Config);
    new (GetClass(), NAME_WindowedViewportY, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, WindowedViewportY), NAME_Client, CPF_Config);
    new (GetClass(), NAME_FullscreenViewportX, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, FullscreenViewportX), NAME_Client, CPF_Config);
    new (GetClass(), NAME_FullscreenViewportY, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, FullscreenViewportY), NAME_Client, CPF_Config);
    new (GetClass(), NAME_Brightness, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, Brightness), NAME_Display, CPF_Config);
    new (GetClass(), NAME_Contrast, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, Contrast), NAME_Display, CPF_Config);
    new (GetClass(), NAME_Gamma, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, Gamma), NAME_Display, CPF_Config);
    new (GetClass(), NAME_CaptureMouse, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, CaptureMouse), NAME_Display, CPF_Config);
    new (GetClass(), NAME_TextureDetailWorld, RF_Public) UByteProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, TextureDetailWorld), NAME_Display, CPF_Config, TextureDetailEnum);
    new (GetClass(), NAME_TextureDetailPlayerSkin, RF_Public) UByteProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, TextureDetailPlayerSkin), NAME_Display, CPF_Config, TextureDetailEnum);
    new (GetClass(), NAME_TextureDetailWeaponSkin, RF_Public) UByteProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, TextureDetailWeaponSkin), NAME_Display, CPF_Config, TextureDetailEnum);
    new (GetClass(), NAME_TextureDetailTerrain, RF_Public) UByteProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, TextureDetailTerrain), NAME_Display, CPF_Config, TextureDetailEnum);
    new (GetClass(), NAME_TextureDetailInterface, RF_Public) UByteProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, TextureDetailInterface), NAME_Display, CPF_Config, TextureDetailEnum);
    new (GetClass(), NAME_TextureDetailRenderMap, RF_Public) UByteProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, TextureDetailRenderMap), NAME_Display, CPF_Config, TextureDetailEnum);
    new (GetClass(), NAME_TextureDetailLightmap, RF_Public) UByteProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, TextureDetailLightmap), NAME_Display, CPF_Config, TextureDetailEnum);
    new (GetClass(), NAME_ScreenFlashes, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, ScreenFlashes), NAME_Display, CPF_Config);
    new (GetClass(), NAME_NoLighting, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, NoLighting), NAME_Display, CPF_Config);
    new (GetClass(), NAME_MinDesiredFrameRate, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, MinDesiredFrameRate), NAME_Display, CPF_Config);
    new (GetClass(), NAME_Decals, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, Decals), NAME_Display, CPF_Config);
    new (GetClass(), NAME_NoFractalAnim, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, NoFractalAnim), NAME_Display, CPF_Config);
    new (GetClass(), NAME_Coronas, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, Coronas), NAME_Display, CPF_Config);
    new (GetClass(), NAME_DecoLayers, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, DecoLayers), NAME_Display, CPF_Config);
    new (GetClass(), NAME_Projectors, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, Projectors), NAME_Display, CPF_Config);
    new (GetClass(), NAME_ReportDynamicUploads, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UClient, ReportDynamicUploads), NAME_Display, CPF_Config);
}
