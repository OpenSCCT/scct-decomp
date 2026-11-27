// Register the native UNIAudio settings and apply the two floating-point defaults.
#include "versus_build.h"
#include "versus_native_properties.h"

class USubsystem : public UObject {};

class UAudioSubsystem : public USubsystem {
public:
    BYTE unk_28[4];
};

class UUNIAudioSubsystem : public UAudioSubsystem {
public:
    void StaticConstructor();

    BYTE unk_2c[0x138];
    FLOAT unk_164;
    FLOAT unk_168;
    FLOAT DopplerFactor;
    FLOAT MusicVolume;
    FLOAT AmbientVolume;
    FLOAT SoundVolume;
    FLOAT VoiceVolume;
    FLOAT TimeBetweenHWUpdates;
    FLOAT RollOff;
    INT Channels;
    UBOOL ReverseStereo;
    UBOOL UsePrecache;
    UBOOL UseEAX;
    UBOOL UseHardwareMixing;
    UBOOL DisablePitch;
    UBOOL LowQualitySound;
    BYTE unk_1a4[0x3c];
};

typedef char UUNIAudioSubsystemSizeCheck[sizeof(UUNIAudioSubsystem) == 0x1e0 ? 1 : -1];
static const DWORD RF_Public = 4;
static const DWORD CPF_Config = 0x4000;
#define STRUCT_OFFSET(type, member) ((INT)&((type *)0)->member)

static const EName NAME_UseEAX = (EName)165;
static const EName NAME_UsePrecache = (EName)166;
static const EName NAME_UseHardwareMixing = (EName)167;
static const EName NAME_ReverseStereo = (EName)168;
static const EName NAME_Channels = (EName)169;
static const EName NAME_MusicVolume = (EName)170;
static const EName NAME_SoundVolume = (EName)171;
static const EName NAME_AmbientVolume = (EName)172;
static const EName NAME_VoiceVolume = (EName)173;
static const EName NAME_DopplerFactor = (EName)174;
static const EName NAME_RollOff = (EName)175;
static const EName NAME_TimeBetweenHWUpdates = (EName)176;
static const EName NAME_DisablePitch = (EName)177;
static const EName NAME_LowQualitySound = (EName)178;

void UUNIAudioSubsystem::StaticConstructor()
{
    new (GetClass(), NAME_UseEAX, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UUNIAudioSubsystem, UseEAX), L"UNIAudio", CPF_Config);
    new (GetClass(), NAME_UsePrecache, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UUNIAudioSubsystem, UsePrecache), L"UNIAudio", CPF_Config);
    new (GetClass(), NAME_UseHardwareMixing, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UUNIAudioSubsystem, UseHardwareMixing), L"UNIAudio", CPF_Config);
    new (GetClass(), NAME_ReverseStereo, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UUNIAudioSubsystem, ReverseStereo), L"UNIAudio", CPF_Config);
    new (GetClass(), NAME_Channels, RF_Public) UIntProperty(EC_CppProperty,
        STRUCT_OFFSET(UUNIAudioSubsystem, Channels), L"UNIAudio", CPF_Config);
    new (GetClass(), NAME_MusicVolume, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UUNIAudioSubsystem, MusicVolume), L"UNIAudio", CPF_Config);
    new (GetClass(), NAME_SoundVolume, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UUNIAudioSubsystem, SoundVolume), L"UNIAudio", CPF_Config);
    new (GetClass(), NAME_AmbientVolume, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UUNIAudioSubsystem, AmbientVolume), L"UNIAudio", CPF_Config);
    new (GetClass(), NAME_VoiceVolume, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UUNIAudioSubsystem, VoiceVolume), L"UNIAudio", CPF_Config);
    new (GetClass(), NAME_DopplerFactor, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UUNIAudioSubsystem, DopplerFactor), L"UNIAudio", CPF_Config);
    new (GetClass(), NAME_RollOff, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UUNIAudioSubsystem, RollOff), L"UNIAudio", CPF_Config);
    new (GetClass(), NAME_TimeBetweenHWUpdates, RF_Public) UFloatProperty(EC_CppProperty,
        STRUCT_OFFSET(UUNIAudioSubsystem, TimeBetweenHWUpdates), L"UNIAudio", CPF_Config);
    new (GetClass(), NAME_DisablePitch, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UUNIAudioSubsystem, DisablePitch), L"UNIAudio", CPF_Config);
    new (GetClass(), NAME_LowQualitySound, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UUNIAudioSubsystem, LowQualitySound), L"UNIAudio", CPF_Config);

    unk_168 = 1.0f;
    unk_164 = 1.0f;
}
