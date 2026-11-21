// versus_member_destructors.cpp -- Versus class destructors that destroy one member
//
// Each destructor runs UObject::ConditionalDestroy before the members and the parent class
// are destroyed.
#include "versus_build.h"
#include "versus_engine_classes.h"
#include "versus_gui_classes.h"
#include "versus_sbase_classes.h"

// UGlobalTempObjects::~UGlobalTempObjects
UGlobalTempObjects::~UGlobalTempObjects()
{
    ConditionalDestroy();
}

// ADecorationList::~ADecorationList
ADecorationList::~ADecorationList()
{
    ConditionalDestroy();
}

// USparkEmitter::~USparkEmitter
USparkEmitter::~USparkEmitter()
{
    ConditionalDestroy();
}

// AEmitter::~AEmitter
AEmitter::~AEmitter()
{
    ConditionalDestroy();
}

// UMaterialSequence::~UMaterialSequence
UMaterialSequence::~UMaterialSequence()
{
    ConditionalDestroy();
}

// UMaterialSwitch::~UMaterialSwitch
UMaterialSwitch::~UMaterialSwitch()
{
    ConditionalDestroy();
}

// UInteractionMaster::~UInteractionMaster
UInteractionMaster::~UInteractionMaster()
{
    ConditionalDestroy();
}

// UPolys::~UPolys
UPolys::~UPolys()
{
    ConditionalDestroy();
}

// ATeamInfo::~ATeamInfo
ATeamInfo::~ATeamInfo()
{
    ConditionalDestroy();
}

// AVolume::~AVolume
AVolume::~AVolume()
{
    ConditionalDestroy();
}

// AController::~AController
AController::~AController()
{
    ConditionalDestroy();
}

// ATrigger::~ATrigger
ATrigger::~ATrigger()
{
    ConditionalDestroy();
}

// ANote::~ANote
ANote::~ANote()
{
    ConditionalDestroy();
}

// AFileLog::~AFileLog
AFileLog::~AFileLog()
{
    ConditionalDestroy();
}

// UPalette::~UPalette
UPalette::~UPalette()
{
    ConditionalDestroy();
}

// UGUIMultiComponent::~UGUIMultiComponent
UGUIMultiComponent::~UGUIMultiComponent()
{
    ConditionalDestroy();
}

// UGUIPageWaitLaunch::~UGUIPageWaitLaunch
UGUIPageWaitLaunch::~UGUIPageWaitLaunch()
{
    ConditionalDestroy();
}

// UGUIList::~UGUIList
UGUIList::~UGUIList()
{
    ConditionalDestroy();
}

// UGUISlider::~UGUISlider
UGUISlider::~UGUISlider()
{
    ConditionalDestroy();
}

// UGUITitleBar::~UGUITitleBar
UGUITitleBar::~UGUITitleBar()
{
    ConditionalDestroy();
}

// UGUIComboBox::~UGUIComboBox
UGUIComboBox::~UGUIComboBox()
{
    ConditionalDestroy();
}

// UGUIButton::~UGUIButton
UGUIButton::~UGUIButton()
{
    ConditionalDestroy();
}

// UGUINumericEdit::~UGUINumericEdit
UGUINumericEdit::~UGUINumericEdit()
{
    ConditionalDestroy();
}

// UGUICheckBox::~UGUICheckBox
UGUICheckBox::~UGUICheckBox()
{
    ConditionalDestroy();
}

// ASInteractObject::~ASInteractObject
ASInteractObject::~ASInteractObject()
{
    ConditionalDestroy();
}

// ASBasicGamePlayObject::~ASBasicGamePlayObject
ASBasicGamePlayObject::~ASBasicGamePlayObject()
{
    ConditionalDestroy();
}

// ASObjectiveTrigger::~ASObjectiveTrigger
ASObjectiveTrigger::~ASObjectiveTrigger()
{
    ConditionalDestroy();
}

// ASBombTargetInteraction::~ASBombTargetInteraction
ASBombTargetInteraction::~ASBombTargetInteraction()
{
    ConditionalDestroy();
}

// ASVolumetricSensor::~ASVolumetricSensor
ASVolumetricSensor::~ASVolumetricSensor()
{
    ConditionalDestroy();
}

// ASTriggerLight::~ASTriggerLight
ASTriggerLight::~ASTriggerLight()
{
    ConditionalDestroy();
}

// ASSpyBulletLauncher::~ASSpyBulletLauncher
ASSpyBulletLauncher::~ASSpyBulletLauncher()
{
    ConditionalDestroy();
}

// ASProjMarqueurSpy::~ASProjMarqueurSpy
ASProjMarqueurSpy::~ASProjMarqueurSpy()
{
    ConditionalDestroy();
}

// ASBasePawn::~ASBasePawn
ASBasePawn::~ASBasePawn()
{
    ConditionalDestroy();
}

// ASMission::~ASMission
ASMission::~ASMission()
{
    ConditionalDestroy();
}

// ASInterrupteur::~ASInterrupteur
ASInterrupteur::~ASInterrupteur()
{
    ConditionalDestroy();
}

// ASGPOControl::~ASGPOControl
ASGPOControl::~ASGPOControl()
{
    ConditionalDestroy();
}

// ASComputerInteraction::~ASComputerInteraction
ASComputerInteraction::~ASComputerInteraction()
{
    ConditionalDestroy();
}

// ASGadGasMask::~ASGadGasMask
ASGadGasMask::~ASGadGasMask()
{
    ConditionalDestroy();
}

// ASGadBackPack::~ASGadBackPack
ASGadBackPack::~ASGadBackPack()
{
    ConditionalDestroy();
}
