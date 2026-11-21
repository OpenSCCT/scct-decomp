// versus_multi_member_destructors.cpp -- Versus class destructors that destroy several members
//
// Each destructor runs UObject::ConditionalDestroy before the members and the parent class
// are destroyed.
#include "versus_build.h"
#include "unreal_actor.h"
#include "unreal_class.h"
#include "versus_engine_classes.h"
#include "versus_gui_classes.h"
#include "versus_sbase_classes.h"

// UClass::~UClass
UClass::~UClass()
{
    ConditionalDestroy();
}

// AActor::~AActor
AActor::~AActor()
{
    ConditionalDestroy();
}

// UPersistentData::~UPersistentData
UPersistentData::~UPersistentData()
{
    ConditionalDestroy();
}

// UParticleEmitter::~UParticleEmitter
UParticleEmitter::~UParticleEmitter()
{
    ConditionalDestroy();
}

// AInventory::~AInventory
AInventory::~AInventory()
{
    ConditionalDestroy();
}

// ASLogManager::~ASLogManager
ASLogManager::~ASLogManager()
{
    ConditionalDestroy();
}

// AESoftBodyActor::~AESoftBodyActor
AESoftBodyActor::~AESoftBodyActor()
{
    ConditionalDestroy();
}

// UTrailEmitter::~UTrailEmitter
UTrailEmitter::~UTrailEmitter()
{
    ConditionalDestroy();
}

// UMatchInfo::~UMatchInfo
UMatchInfo::~UMatchInfo()
{
    ConditionalDestroy();
}

// APawn::~APawn
APawn::~APawn()
{
    ConditionalDestroy();
}

// AMover::~AMover
AMover::~AMover()
{
    ConditionalDestroy();
}

// UBeamEmitter::~UBeamEmitter
UBeamEmitter::~UBeamEmitter()
{
    ConditionalDestroy();
}

// USound::~USound
USound::~USound()
{
    ConditionalDestroy();
}

// ULevelSummary::~ULevelSummary
ULevelSummary::~ULevelSummary()
{
    ConditionalDestroy();
}

// AGameReplicationInfo::~AGameReplicationInfo
AGameReplicationInfo::~AGameReplicationInfo()
{
    ConditionalDestroy();
}

// APlayerReplicationInfo::~APlayerReplicationInfo
APlayerReplicationInfo::~APlayerReplicationInfo()
{
    ConditionalDestroy();
}

// AMotionTrackingVision::~AMotionTrackingVision
AMotionTrackingVision::~AMotionTrackingVision()
{
    ConditionalDestroy();
}

// AZoneInfo::~AZoneInfo
AZoneInfo::~AZoneInfo()
{
    ConditionalDestroy();
}

// ALevelInfo::~ALevelInfo
ALevelInfo::~ALevelInfo()
{
    ConditionalDestroy();
}

// UGUIComponent::~UGUIComponent
UGUIComponent::~UGUIComponent()
{
    ConditionalDestroy();
}

// UGUIMenuOption::~UGUIMenuOption
UGUIMenuOption::~UGUIMenuOption()
{
    ConditionalDestroy();
}

// UGUIPage::~UGUIPage
UGUIPage::~UGUIPage()
{
    ConditionalDestroy();
}

// UGUIChatBox::~UGUIChatBox
UGUIChatBox::~UGUIChatBox()
{
    ConditionalDestroy();
}

// UGUIMultiPageLabel::~UGUIMultiPageLabel
UGUIMultiPageLabel::~UGUIMultiPageLabel()
{
    ConditionalDestroy();
}

// UGUIProgressBar::~UGUIProgressBar
UGUIProgressBar::~UGUIProgressBar()
{
    ConditionalDestroy();
}

// UGUIScrollText::~UGUIScrollText
UGUIScrollText::~UGUIScrollText()
{
    ConditionalDestroy();
}

// UGUITabControl::~UGUITabControl
UGUITabControl::~UGUITabControl()
{
    ConditionalDestroy();
}

// UGUIEditBox::~UGUIEditBox
UGUIEditBox::~UGUIEditBox()
{
    ConditionalDestroy();
}

// UGUILabel::~UGUILabel
UGUILabel::~UGUILabel()
{
    ConditionalDestroy();
}

// UGUIFont::~UGUIFont
UGUIFont::~UGUIFont()
{
    ConditionalDestroy();
}

// ASGamePlayObject::~ASGamePlayObject
ASGamePlayObject::~ASGamePlayObject()
{
    ConditionalDestroy();
}

// USMapSettings::~USMapSettings
USMapSettings::~USMapSettings()
{
    ConditionalDestroy();
}

// ASAnimatedMesh::~ASAnimatedMesh
ASAnimatedMesh::~ASAnimatedMesh()
{
    ConditionalDestroy();
}

// ASMagicEvent::~ASMagicEvent
ASMagicEvent::~ASMagicEvent()
{
    ConditionalDestroy();
}

// ASLift::~ASLift
ASLift::~ASLift()
{
    ConditionalDestroy();
}

// ASTeamInfo::~ASTeamInfo
ASTeamInfo::~ASTeamInfo()
{
    ConditionalDestroy();
}

// USXBoxLiveRef::~USXBoxLiveRef
USXBoxLiveRef::~USXBoxLiveRef()
{
    ConditionalDestroy();
}

// USPlayerProfile::~USPlayerProfile
USPlayerProfile::~USPlayerProfile()
{
    ConditionalDestroy();
}

// ASWeaponDefense::~ASWeaponDefense
ASWeaponDefense::~ASWeaponDefense()
{
    ConditionalDestroy();
}

// ASObjective::~ASObjective
ASObjective::~ASObjective()
{
    ConditionalDestroy();
}

// ASGadTorcheLaser::~ASGadTorcheLaser
ASGadTorcheLaser::~ASGadTorcheLaser()
{
    ConditionalDestroy();
}

// ASGadTorche::~ASGadTorche
ASGadTorche::~ASGadTorche()
{
    ConditionalDestroy();
}

// ASAlarm::~ASAlarm
ASAlarm::~ASAlarm()
{
    ConditionalDestroy();
}

// ASGoggle::~ASGoggle
ASGoggle::~ASGoggle()
{
    ConditionalDestroy();
}

// ASShareObjectInteraction::~ASShareObjectInteraction
ASShareObjectInteraction::~ASShareObjectInteraction()
{
    ConditionalDestroy();
}

// ASCamNetwork::~ASCamNetwork
ASCamNetwork::~ASCamNetwork()
{
    ConditionalDestroy();
}
