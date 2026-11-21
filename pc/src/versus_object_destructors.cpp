// versus_object_destructors.cpp -- Versus class destructors that destroy no member
//
// Each destructor runs UObject::ConditionalDestroy before the members and the parent class
// are destroyed.
#include "versus_build.h"
#include "unreal_field.h"
#include "unreal_function.h"
#include "unreal_interaction.h"
#include "unreal_property.h"
#include "versus_core_classes.h"
#include "versus_engine_classes.h"
#include "versus_gui_classes.h"
#include "versus_sbase_classes.h"
#include "versus_softbody_classes.h"

// UState::~UState
UState::~UState()
{
    ConditionalDestroy();
}

// UPackage::~UPackage
UPackage::~UPackage()
{
    ConditionalDestroy();
}

// UFunction::~UFunction
UFunction::~UFunction()
{
    ConditionalDestroy();
}

// UClassProperty::~UClassProperty
UClassProperty::~UClassProperty()
{
    ConditionalDestroy();
}

// USpriteEmitter::~USpriteEmitter
USpriteEmitter::~USpriteEmitter()
{
    ConditionalDestroy();
}

// UFlicFlocEmitter::~UFlicFlocEmitter
UFlicFlocEmitter::~UFlicFlocEmitter()
{
    ConditionalDestroy();
}

// UInteractions::~UInteractions
UInteractions::~UInteractions()
{
    ConditionalDestroy();
}

// UInteraction::~UInteraction
UInteraction::~UInteraction()
{
    ConditionalDestroy();
}

// UMagmaInteraction::~UMagmaInteraction
UMagmaInteraction::~UMagmaInteraction()
{
    ConditionalDestroy();
}

// ULANErrorHandler::~ULANErrorHandler
ULANErrorHandler::~ULANErrorHandler()
{
    ConditionalDestroy();
}

// ADecoVolumeObject::~ADecoVolumeObject
ADecoVolumeObject::~ADecoVolumeObject()
{
    ConditionalDestroy();
}

// AKeypoint::~AKeypoint
AKeypoint::~AKeypoint()
{
    ConditionalDestroy();
}

// ULodMeshInstance::~ULodMeshInstance
ULodMeshInstance::~ULodMeshInstance()
{
    ConditionalDestroy();
}

// AStaticMeshActor::~AStaticMeshActor
AStaticMeshActor::~AStaticMeshActor()
{
    ConditionalDestroy();
}

// UAnimNotify::~UAnimNotify
UAnimNotify::~UAnimNotify()
{
    ConditionalDestroy();
}

// UAnimNotify_Scripted::~UAnimNotify_Scripted
UAnimNotify_Scripted::~UAnimNotify_Scripted()
{
    ConditionalDestroy();
}

// UAnimNotify_Script::~UAnimNotify_Script
UAnimNotify_Script::~UAnimNotify_Script()
{
    ConditionalDestroy();
}

// UAnimNotify_StopSound::~UAnimNotify_StopSound
UAnimNotify_StopSound::~UAnimNotify_StopSound()
{
    ConditionalDestroy();
}

// UAnimNotify_Sound::~UAnimNotify_Sound
UAnimNotify_Sound::~UAnimNotify_Sound()
{
    ConditionalDestroy();
}

// UAnimNotify_DestroyEffect::~UAnimNotify_DestroyEffect
UAnimNotify_DestroyEffect::~UAnimNotify_DestroyEffect()
{
    ConditionalDestroy();
}

// UAnimNotify_Effect::~UAnimNotify_Effect
UAnimNotify_Effect::~UAnimNotify_Effect()
{
    ConditionalDestroy();
}

// UAnimation::~UAnimation
UAnimation::~UAnimation()
{
    ConditionalDestroy();
}

// AInfo::~AInfo
AInfo::~AInfo()
{
    ConditionalDestroy();
}

// UMeshObject::~UMeshObject
UMeshObject::~UMeshObject()
{
    ConditionalDestroy();
}

// AProjector::~AProjector
AProjector::~AProjector()
{
    ConditionalDestroy();
}

// AShadowProjector::~AShadowProjector
AShadowProjector::~AShadowProjector()
{
    ConditionalDestroy();
}

// AMoverRotating::~AMoverRotating
AMoverRotating::~AMoverRotating()
{
    ConditionalDestroy();
}

// UMeshEmitter::~UMeshEmitter
UMeshEmitter::~UMeshEmitter()
{
    ConditionalDestroy();
}

// UOpacityModifier::~UOpacityModifier
UOpacityModifier::~UOpacityModifier()
{
    ConditionalDestroy();
}

// USpecialVisionTextureModifier::~USpecialVisionTextureModifier
USpecialVisionTextureModifier::~USpecialVisionTextureModifier()
{
    ConditionalDestroy();
}

// UEMFTextureModifier::~UEMFTextureModifier
UEMFTextureModifier::~UEMFTextureModifier()
{
    ConditionalDestroy();
}

// UHeatTextureModifier::~UHeatTextureModifier
UHeatTextureModifier::~UHeatTextureModifier()
{
    ConditionalDestroy();
}

// UFinalBlend::~UFinalBlend
UFinalBlend::~UFinalBlend()
{
    ConditionalDestroy();
}

// UTexModifier::~UTexModifier
UTexModifier::~UTexModifier()
{
    ConditionalDestroy();
}

// UTexCoordSource::~UTexCoordSource
UTexCoordSource::~UTexCoordSource()
{
    ConditionalDestroy();
}

// UTexMatrix::~UTexMatrix
UTexMatrix::~UTexMatrix()
{
    ConditionalDestroy();
}

// UTexEnvMap::~UTexEnvMap
UTexEnvMap::~UTexEnvMap()
{
    ConditionalDestroy();
}

// UTexOscillator::~UTexOscillator
UTexOscillator::~UTexOscillator()
{
    ConditionalDestroy();
}

// UTexOscillatorTriggered::~UTexOscillatorTriggered
UTexOscillatorTriggered::~UTexOscillatorTriggered()
{
    ConditionalDestroy();
}

// UTexRotator::~UTexRotator
UTexRotator::~UTexRotator()
{
    ConditionalDestroy();
}

// UTexScaler::~UTexScaler
UTexScaler::~UTexScaler()
{
    ConditionalDestroy();
}

// UTexFriendlyPanner::~UTexFriendlyPanner
UTexFriendlyPanner::~UTexFriendlyPanner()
{
    ConditionalDestroy();
}

// UTexPanner::~UTexPanner
UTexPanner::~UTexPanner()
{
    ConditionalDestroy();
}

// UTexPannerTriggered::~UTexPannerTriggered
UTexPannerTriggered::~UTexPannerTriggered()
{
    ConditionalDestroy();
}

// UFadeColor::~UFadeColor
UFadeColor::~UFadeColor()
{
    ConditionalDestroy();
}

// UConstantColor::~UConstantColor
UConstantColor::~UConstantColor()
{
    ConditionalDestroy();
}

// UColorModifier::~UColorModifier
UColorModifier::~UColorModifier()
{
    ConditionalDestroy();
}

// UPlayerInput::~UPlayerInput
UPlayerInput::~UPlayerInput()
{
    ConditionalDestroy();
}

// UCheatManager::~UCheatManager
UCheatManager::~UCheatManager()
{
    ConditionalDestroy();
}

// UCanvas::~UCanvas
UCanvas::~UCanvas()
{
    ConditionalDestroy();
}

// UI3DL2Listener::~UI3DL2Listener
UI3DL2Listener::~UI3DL2Listener()
{
    ConditionalDestroy();
}

// ACarriedObject::~ACarriedObject
ACarriedObject::~ACarriedObject()
{
    ConditionalDestroy();
}

// AAntiPortalActor::~AAntiPortalActor
AAntiPortalActor::~AAntiPortalActor()
{
    ConditionalDestroy();
}

// AReplicationInfo::~AReplicationInfo
AReplicationInfo::~AReplicationInfo()
{
    ConditionalDestroy();
}

// ABrush::~ABrush
ABrush::~ABrush()
{
    ConditionalDestroy();
}

// ABlockingVolume::~ABlockingVolume
ABlockingVolume::~ABlockingVolume()
{
    ConditionalDestroy();
}

// ATriggers::~ATriggers
ATriggers::~ATriggers()
{
    ConditionalDestroy();
}

// ALineOfSightTrigger::~ALineOfSightTrigger
ALineOfSightTrigger::~ALineOfSightTrigger()
{
    ConditionalDestroy();
}

// AInternetInfo::~AInternetInfo
AInternetInfo::~AInternetInfo()
{
    ConditionalDestroy();
}

// ALocalMessage::~ALocalMessage
ALocalMessage::~ALocalMessage()
{
    ConditionalDestroy();
}

// APlayerStart::~APlayerStart
APlayerStart::~APlayerStart()
{
    ConditionalDestroy();
}

// ASBulletImpact::~ASBulletImpact
ASBulletImpact::~ASBulletImpact()
{
    ConditionalDestroy();
}

// ASImpactEffectBase::~ASImpactEffectBase
ASImpactEffectBase::~ASImpactEffectBase()
{
    ConditionalDestroy();
}

// AEffects::~AEffects
AEffects::~AEffects()
{
    ConditionalDestroy();
}

// AProjectile::~AProjectile
AProjectile::~AProjectile()
{
    ConditionalDestroy();
}

// ADecoration::~ADecoration
ADecoration::~ADecoration()
{
    ConditionalDestroy();
}

// ASkyZoneInfo::~ASkyZoneInfo
ASkyZoneInfo::~ASkyZoneInfo()
{
    ConditionalDestroy();
}

// ALight::~ALight
ALight::~ALight()
{
    ConditionalDestroy();
}

// AGameStats::~AGameStats
AGameStats::~AGameStats()
{
    ConditionalDestroy();
}

// ASImpactManager::~ASImpactManager
ASImpactManager::~ASImpactManager()
{
    ConditionalDestroy();
}

// UGUI::~UGUI
UGUI::~UGUI()
{
    ConditionalDestroy();
}

// UmoEditBox::~UmoEditBox
UmoEditBox::~UmoEditBox()
{
    ConditionalDestroy();
}

// UmoListEditBox::~UmoListEditBox
UmoListEditBox::~UmoListEditBox()
{
    ConditionalDestroy();
}

// UmoListEditBox_GameMode::~UmoListEditBox_GameMode
UmoListEditBox_GameMode::~UmoListEditBox_GameMode()
{
    ConditionalDestroy();
}

// UStrategicMap::~UStrategicMap
UStrategicMap::~UStrategicMap()
{
    ConditionalDestroy();
}

// UGUIListBase::~UGUIListBase
UGUIListBase::~UGUIListBase()
{
    ConditionalDestroy();
}

// UGUIVertList::~UGUIVertList
UGUIVertList::~UGUIVertList()
{
    ConditionalDestroy();
}

// UGUIScrollBarBase::~UGUIScrollBarBase
UGUIScrollBarBase::~UGUIScrollBarBase()
{
    ConditionalDestroy();
}

// UGUIVertScrollBarLabel::~UGUIVertScrollBarLabel
UGUIVertScrollBarLabel::~UGUIVertScrollBarLabel()
{
    ConditionalDestroy();
}

// UGUIMultiPageLabelBox::~UGUIMultiPageLabelBox
UGUIMultiPageLabelBox::~UGUIMultiPageLabelBox()
{
    ConditionalDestroy();
}

// UGUIMOTDInfoBox::~UGUIMOTDInfoBox
UGUIMOTDInfoBox::~UGUIMOTDInfoBox()
{
    ConditionalDestroy();
}

// UGUISessionInfoBox::~UGUISessionInfoBox
UGUISessionInfoBox::~UGUISessionInfoBox()
{
    ConditionalDestroy();
}

// UGUISearchFilterBox::~UGUISearchFilterBox
UGUISearchFilterBox::~UGUISearchFilterBox()
{
    ConditionalDestroy();
}

// UGUICadre::~UGUICadre
UGUICadre::~UGUICadre()
{
    ConditionalDestroy();
}

// UmoImageListMap::~UmoImageListMap
UmoImageListMap::~UmoImageListMap()
{
    ConditionalDestroy();
}

// UGUIListBoxBase::~UGUIListBoxBase
UGUIListBoxBase::~UGUIListBoxBase()
{
    ConditionalDestroy();
}

// UGUIScrollTextBox::~UGUIScrollTextBox
UGUIScrollTextBox::~UGUIScrollTextBox()
{
    ConditionalDestroy();
}

// UGUICircularList::~UGUICircularList
UGUICircularList::~UGUICircularList()
{
    ConditionalDestroy();
}

// UGUIHorzList::~UGUIHorzList
UGUIHorzList::~UGUIHorzList()
{
    ConditionalDestroy();
}

// UGUIPanel::~UGUIPanel
UGUIPanel::~UGUIPanel()
{
    ConditionalDestroy();
}

// UGUISplitter::~UGUISplitter
UGUISplitter::~UGUISplitter()
{
    ConditionalDestroy();
}

// UGUITabPanel::~UGUITabPanel
UGUITabPanel::~UGUITabPanel()
{
    ConditionalDestroy();
}

// UGUITabButton::~UGUITabButton
UGUITabButton::~UGUITabButton()
{
    ConditionalDestroy();
}

// UGUIMultiColumnListHeader::~UGUIMultiColumnListHeader
UGUIMultiColumnListHeader::~UGUIMultiColumnListHeader()
{
    ConditionalDestroy();
}

// UGUIListFriends::~UGUIListFriends
UGUIListFriends::~UGUIListFriends()
{
    ConditionalDestroy();
}

// UGUIMultiColumnListBox::~UGUIMultiColumnListBox
UGUIMultiColumnListBox::~UGUIMultiColumnListBox()
{
    ConditionalDestroy();
}

// UGUIListBox::~UGUIListBox
UGUIListBox::~UGUIListBox()
{
    ConditionalDestroy();
}

// UGUIHorzScrollBar::~UGUIHorzScrollBar
UGUIHorzScrollBar::~UGUIHorzScrollBar()
{
    ConditionalDestroy();
}

// UGUIGFXButton::~UGUIGFXButton
UGUIGFXButton::~UGUIGFXButton()
{
    ConditionalDestroy();
}

// UGUIHorzGripButton::~UGUIHorzGripButton
UGUIHorzGripButton::~UGUIHorzGripButton()
{
    ConditionalDestroy();
}

// UGUIHorzScrollButton::~UGUIHorzScrollButton
UGUIHorzScrollButton::~UGUIHorzScrollButton()
{
    ConditionalDestroy();
}

// UGUIHorzScrollZone::~UGUIHorzScrollZone
UGUIHorzScrollZone::~UGUIHorzScrollZone()
{
    ConditionalDestroy();
}

// UGUIVertScrollBar::~UGUIVertScrollBar
UGUIVertScrollBar::~UGUIVertScrollBar()
{
    ConditionalDestroy();
}

// UGUIVertGripButton::~UGUIVertGripButton
UGUIVertGripButton::~UGUIVertGripButton()
{
    ConditionalDestroy();
}

// UGUIVertScrollButton::~UGUIVertScrollButton
UGUIVertScrollButton::~UGUIVertScrollButton()
{
    ConditionalDestroy();
}

// UGUIVertScrollZone::~UGUIVertScrollZone
UGUIVertScrollZone::~UGUIVertScrollZone()
{
    ConditionalDestroy();
}

// UGUICheckBoxButton::~UGUICheckBoxButton
UGUICheckBoxButton::~UGUICheckBoxButton()
{
    ConditionalDestroy();
}

// UGUISpinnerButton::~UGUISpinnerButton
UGUISpinnerButton::~UGUISpinnerButton()
{
    ConditionalDestroy();
}

// UGUILabelPad::~UGUILabelPad
UGUILabelPad::~UGUILabelPad()
{
    ConditionalDestroy();
}

// UGUIImage::~UGUIImage
UGUIImage::~UGUIImage()
{
    ConditionalDestroy();
}

// ASFlagDropZoneInteraction::~ASFlagDropZoneInteraction
ASFlagDropZoneInteraction::~ASFlagDropZoneInteraction()
{
    ConditionalDestroy();
}

// ASMines::~ASMines
ASMines::~ASMines()
{
    ConditionalDestroy();
}

// ASPresDetector::~ASPresDetector
ASPresDetector::~ASPresDetector()
{
    ConditionalDestroy();
}

// ASNotifyNoise::~ASNotifyNoise
ASNotifyNoise::~ASNotifyNoise()
{
    ConditionalDestroy();
}

// ASDamageVolume::~ASDamageVolume
ASDamageVolume::~ASDamageVolume()
{
    ConditionalDestroy();
}

// ASDisk::~ASDisk
ASDisk::~ASDisk()
{
    ConditionalDestroy();
}

// ASFlaque::~ASFlaque
ASFlaque::~ASFlaque()
{
    ConditionalDestroy();
}

// ASSprinkler::~ASSprinkler
ASSprinkler::~ASSprinkler()
{
    ConditionalDestroy();
}

// ASOrientableObject::~ASOrientableObject
ASOrientableObject::~ASOrientableObject()
{
    ConditionalDestroy();
}

// ASProjoFixe::~ASProjoFixe
ASProjoFixe::~ASProjoFixe()
{
    ConditionalDestroy();
}

// ASLiftDoor::~ASLiftDoor
ASLiftDoor::~ASLiftDoor()
{
    ConditionalDestroy();
}

// ASInfirmary::~ASInfirmary
ASInfirmary::~ASInfirmary()
{
    ConditionalDestroy();
}

// ASFlashGen::~ASFlashGen
ASFlashGen::~ASFlashGen()
{
    ConditionalDestroy();
}

// ASWeapon::~ASWeapon
ASWeapon::~ASWeapon()
{
    ConditionalDestroy();
}

// ASWeaponAttaque::~ASWeaponAttaque
ASWeaponAttaque::~ASWeaponAttaque()
{
    ConditionalDestroy();
}

// ASWeaponDefenseDummy::~ASWeaponDefenseDummy
ASWeaponDefenseDummy::~ASWeaponDefenseDummy()
{
    ConditionalDestroy();
}

// ASTriggerInteraction::~ASTriggerInteraction
ASTriggerInteraction::~ASTriggerInteraction()
{
    ConditionalDestroy();
}

// ASStickyCamEmitter::~ASStickyCamEmitter
ASStickyCamEmitter::~ASStickyCamEmitter()
{
    ConditionalDestroy();
}

// ASGadget::~ASGadget
ASGadget::~ASGadget()
{
    ConditionalDestroy();
}

// ASSmokeLaunchEmitter::~ASSmokeLaunchEmitter
ASSmokeLaunchEmitter::~ASSmokeLaunchEmitter()
{
    ConditionalDestroy();
}

// ASSmokeEmitter::~ASSmokeEmitter
ASSmokeEmitter::~ASSmokeEmitter()
{
    ConditionalDestroy();
}

// ASSavedMove::~ASSavedMove
ASSavedMove::~ASSavedMove()
{
    ConditionalDestroy();
}

// ASRJ45Checker::~ASRJ45Checker
ASRJ45Checker::~ASRJ45Checker()
{
    ConditionalDestroy();
}

// ASProjGrenade::~ASProjGrenade
ASProjGrenade::~ASProjGrenade()
{
    ConditionalDestroy();
}

// ASProjSmoke::~ASProjSmoke
ASProjSmoke::~ASProjSmoke()
{
    ConditionalDestroy();
}

// ASProjPhospho::~ASProjPhospho
ASProjPhospho::~ASProjPhospho()
{
    ConditionalDestroy();
}

// ASProjFrag::~ASProjFrag
ASProjFrag::~ASProjFrag()
{
    ConditionalDestroy();
}

// ASProjFlashBang::~ASProjFlashBang
ASProjFlashBang::~ASProjFlashBang()
{
    ConditionalDestroy();
}

// ASProjFlare::~ASProjFlare
ASProjFlare::~ASProjFlare()
{
    ConditionalDestroy();
}

// ASProjChaffe::~ASProjChaffe
ASProjChaffe::~ASProjChaffe()
{
    ConditionalDestroy();
}

// ASPlayerCam::~ASPlayerCam
ASPlayerCam::~ASPlayerCam()
{
    ConditionalDestroy();
}

// ASPickupInteraction::~ASPickupInteraction
ASPickupInteraction::~ASPickupInteraction()
{
    ConditionalDestroy();
}

// ASPhosphoEmitter::~ASPhosphoEmitter
ASPhosphoEmitter::~ASPhosphoEmitter()
{
    ConditionalDestroy();
}

// ASPAWNDEFENSE::~ASPAWNDEFENSE
ASPAWNDEFENSE::~ASPAWNDEFENSE()
{
    ConditionalDestroy();
}

// ASPawnAttaque::~ASPawnAttaque
ASPawnAttaque::~ASPawnAttaque()
{
    ConditionalDestroy();
}

// ASNoiseEmitter::~ASNoiseEmitter
ASNoiseEmitter::~ASNoiseEmitter()
{
    ConditionalDestroy();
}

// ASMuzzleFlash::~ASMuzzleFlash
ASMuzzleFlash::~ASMuzzleFlash()
{
    ConditionalDestroy();
}

// ASMuzzleSticky::~ASMuzzleSticky
ASMuzzleSticky::~ASMuzzleSticky()
{
    ConditionalDestroy();
}

// ASMotionTrackingVision::~ASMotionTrackingVision
ASMotionTrackingVision::~ASMotionTrackingVision()
{
    ConditionalDestroy();
}

// ASMineProx::~ASMineProx
ASMineProx::~ASMineProx()
{
    ConditionalDestroy();
}

// ASMineLaser::~ASMineLaser
ASMineLaser::~ASMineLaser()
{
    ConditionalDestroy();
}

// USMatchInfo::~USMatchInfo
USMatchInfo::~USMatchInfo()
{
    ConditionalDestroy();
}

// ASLeaveInteraction::~ASLeaveInteraction
ASLeaveInteraction::~ASLeaveInteraction()
{
    ConditionalDestroy();
}

// ASLaserTrigger::~ASLaserTrigger
ASLaserTrigger::~ASLaserTrigger()
{
    ConditionalDestroy();
}

// ASLaserProjector::~ASLaserProjector
ASLaserProjector::~ASLaserProjector()
{
    ConditionalDestroy();
}

// ASLaserBeam::~ASLaserBeam
ASLaserBeam::~ASLaserBeam()
{
    ConditionalDestroy();
}

// ASLaserBeam_MineLaser::~ASLaserBeam_MineLaser
ASLaserBeam_MineLaser::~ASLaserBeam_MineLaser()
{
    ConditionalDestroy();
}

// ASInteractionManager::~ASInteractionManager
ASInteractionManager::~ASInteractionManager()
{
    ConditionalDestroy();
}

// ASGrenadeExplosion::~ASGrenadeExplosion
ASGrenadeExplosion::~ASGrenadeExplosion()
{
    ConditionalDestroy();
}

// ASGoggleBeam::~ASGoggleBeam
ASGoggleBeam::~ASGoggleBeam()
{
    ConditionalDestroy();
}

// ASGadTazerLauncher::~ASGadTazerLauncher
ASGadTazerLauncher::~ASGadTazerLauncher()
{
    ConditionalDestroy();
}

// ASGadNoiseEmitter::~ASGadNoiseEmitter
ASGadNoiseEmitter::~ASGadNoiseEmitter()
{
    ConditionalDestroy();
}

// ASGadGrenLauncher::~ASGadGrenLauncher
ASGadGrenLauncher::~ASGadGrenLauncher()
{
    ConditionalDestroy();
}

// ASGadBomb::~ASGadBomb
ASGadBomb::~ASGadBomb()
{
    ConditionalDestroy();
}

// ASFragLaunchEmitter::~ASFragLaunchEmitter
ASFragLaunchEmitter::~ASFragLaunchEmitter()
{
    ConditionalDestroy();
}

// ASFlashBang::~ASFlashBang
ASFlashBang::~ASFlashBang()
{
    ConditionalDestroy();
}

// ASFlagDropZone::~ASFlagDropZone
ASFlagDropZone::~ASFlagDropZone()
{
    ConditionalDestroy();
}

// ASFlag::~ASFlag
ASFlag::~ASFlag()
{
    ConditionalDestroy();
}

// ASFireTrace::~ASFireTrace
ASFireTrace::~ASFireTrace()
{
    ConditionalDestroy();
}

// ASComputerObjectiveTrigger::~ASComputerObjectiveTrigger
ASComputerObjectiveTrigger::~ASComputerObjectiveTrigger()
{
    ConditionalDestroy();
}

// ASChaffeEmitter::~ASChaffeEmitter
ASChaffeEmitter::~ASChaffeEmitter()
{
    ConditionalDestroy();
}

// ASCamera::~ASCamera
ASCamera::~ASCamera()
{
    ConditionalDestroy();
}

// ASBombTargetObjectiveTrigger::~ASBombTargetObjectiveTrigger
ASBombTargetObjectiveTrigger::~ASBombTargetObjectiveTrigger()
{
    ConditionalDestroy();
}

// ASBloodSplat::~ASBloodSplat
ASBloodSplat::~ASBloodSplat()
{
    ConditionalDestroy();
}

// ASAmmoStock::~ASAmmoStock
ASAmmoStock::~ASAmmoStock()
{
    ConditionalDestroy();
}

// ASAmbientSoundTrigger::~ASAmbientSoundTrigger
ASAmbientSoundTrigger::~ASAmbientSoundTrigger()
{
    ConditionalDestroy();
}

// ASFlareEmitter::~ASFlareEmitter
ASFlareEmitter::~ASFlareEmitter()
{
    ConditionalDestroy();
}

// ASFlareCourseEmitter::~ASFlareCourseEmitter
ASFlareCourseEmitter::~ASFlareCourseEmitter()
{
    ConditionalDestroy();
}

// ASExtincteurEmitter::~ASExtincteurEmitter
ASExtincteurEmitter::~ASExtincteurEmitter()
{
    ConditionalDestroy();
}

// ASFlashLight::~ASFlashLight
ASFlashLight::~ASFlashLight()
{
    ConditionalDestroy();
}

// ASFlashLight_FragGrenade::~ASFlashLight_FragGrenade
ASFlashLight_FragGrenade::~ASFlashLight_FragGrenade()
{
    ConditionalDestroy();
}

// ASDouilleEmitter::~ASDouilleEmitter
ASDouilleEmitter::~ASDouilleEmitter()
{
    ConditionalDestroy();
}

// ASTazerEmitter::~ASTazerEmitter
ASTazerEmitter::~ASTazerEmitter()
{
    ConditionalDestroy();
}

// ASMinePiegeSpy::~ASMinePiegeSpy
ASMinePiegeSpy::~ASMinePiegeSpy()
{
    ConditionalDestroy();
}

// ASAmmoStockInteraction::~ASAmmoStockInteraction
ASAmmoStockInteraction::~ASAmmoStockInteraction()
{
    ConditionalDestroy();
}

// ASMineProxInteraction::~ASMineProxInteraction
ASMineProxInteraction::~ASMineProxInteraction()
{
    ConditionalDestroy();
}

// ASExtincteur::~ASExtincteur
ASExtincteur::~ASExtincteur()
{
    ConditionalDestroy();
}

// ASGadSmokeGrenade::~ASGadSmokeGrenade
ASGadSmokeGrenade::~ASGadSmokeGrenade()
{
    ConditionalDestroy();
}

// ASGadPhosphoLauncher::~ASGadPhosphoLauncher
ASGadPhosphoLauncher::~ASGadPhosphoLauncher()
{
    ConditionalDestroy();
}

// ASGadFragGrenade::~ASGadFragGrenade
ASGadFragGrenade::~ASGadFragGrenade()
{
    ConditionalDestroy();
}

// ASGadFlareLauncher::~ASGadFlareLauncher
ASGadFlareLauncher::~ASGadFlareLauncher()
{
    ConditionalDestroy();
}

// ASGadChaffeGrenade::~ASGadChaffeGrenade
ASGadChaffeGrenade::~ASGadChaffeGrenade()
{
    ConditionalDestroy();
}

// ASGadFlashBang::~ASGadFlashBang
ASGadFlashBang::~ASGadFlashBang()
{
    ConditionalDestroy();
}

// ASGadCamNetwork::~ASGadCamNetwork
ASGadCamNetwork::~ASGadCamNetwork()
{
    ConditionalDestroy();
}

// ASStickyCam::~ASStickyCam
ASStickyCam::~ASStickyCam()
{
    ConditionalDestroy();
}

// ASWeaponDefense_Shotgun::~ASWeaponDefense_Shotgun
ASWeaponDefense_Shotgun::~ASWeaponDefense_Shotgun()
{
    ConditionalDestroy();
}

// ASImpactEffectShockerMetal::~ASImpactEffectShockerMetal
ASImpactEffectShockerMetal::~ASImpactEffectShockerMetal()
{
    ConditionalDestroy();
}

// ASImpactEffectShocker::~ASImpactEffectShocker
ASImpactEffectShocker::~ASImpactEffectShocker()
{
    ConditionalDestroy();
}

// ASMinePoison::~ASMinePoison
ASMinePoison::~ASMinePoison()
{
    ConditionalDestroy();
}

// ASMateInteraction::~ASMateInteraction
ASMateInteraction::~ASMateInteraction()
{
    ConditionalDestroy();
}

// ASHealMateInteraction::~ASHealMateInteraction
ASHealMateInteraction::~ASHealMateInteraction()
{
    ConditionalDestroy();
}

// ASBackPackInteraction::~ASBackPackInteraction
ASBackPackInteraction::~ASBackPackInteraction()
{
    ConditionalDestroy();
}

// ASRemoveSpyBulletInteraction::~ASRemoveSpyBulletInteraction
ASRemoveSpyBulletInteraction::~ASRemoveSpyBulletInteraction()
{
    ConditionalDestroy();
}

// ASWeaponDefense_Uzi::~ASWeaponDefense_Uzi
ASWeaponDefense_Uzi::~ASWeaponDefense_Uzi()
{
    ConditionalDestroy();
}

// ASWeaponDefenseDummy_Shotgun::~ASWeaponDefenseDummy_Shotgun
ASWeaponDefenseDummy_Shotgun::~ASWeaponDefenseDummy_Shotgun()
{
    ConditionalDestroy();
}

// ASWeaponDefenseDummy_Uzi::~ASWeaponDefenseDummy_Uzi
ASWeaponDefenseDummy_Uzi::~ASWeaponDefenseDummy_Uzi()
{
    ConditionalDestroy();
}

// ASPoisonEmitter::~ASPoisonEmitter
ASPoisonEmitter::~ASPoisonEmitter()
{
    ConditionalDestroy();
}

// ASGadHeartBeatSensor::~ASGadHeartBeatSensor
ASGadHeartBeatSensor::~ASGadHeartBeatSensor()
{
    ConditionalDestroy();
}

// ASCoronaLight::~ASCoronaLight
ASCoronaLight::~ASCoronaLight()
{
    ConditionalDestroy();
}

// ASStickyCamInteraction::~ASStickyCamInteraction
ASStickyCamInteraction::~ASStickyCamInteraction()
{
    ConditionalDestroy();
}

// ASVitre::~ASVitre
ASVitre::~ASVitre()
{
    ConditionalDestroy();
}

// AESBPatchActor::~AESBPatchActor
AESBPatchActor::~AESBPatchActor()
{
    ConditionalDestroy();
}

// AESBStripDoorActor::~AESBStripDoorActor
AESBStripDoorActor::~AESBStripDoorActor()
{
    ConditionalDestroy();
}

// AESBRopeActor::~AESBRopeActor
AESBRopeActor::~AESBRopeActor()
{
    ConditionalDestroy();
}

// AESBChainActor::~AESBChainActor
AESBChainActor::~AESBChainActor()
{
    ConditionalDestroy();
}
