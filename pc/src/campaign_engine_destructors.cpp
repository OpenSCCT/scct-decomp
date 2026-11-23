// campaign_engine_destructors.cpp -- destructors of engine classes the script natives use
#include "unreal_object.h"
#include "unreal_containers.h"
#include "unreal_class.h"
#include "unreal_property.h"
#include "unreal_actor.h"
#include "unreal_pawn.h"
#include "campaign_level_info.h"
#include "campaign_native_classes.h"

// UState::~UState
UState::~UState()
{
    ConditionalDestroy();
}

// UBoolProperty::~UBoolProperty
UBoolProperty::~UBoolProperty()
{
    ConditionalDestroy();
}

// AController::~AController
AController::~AController()
{
    ConditionalDestroy();
}

// AInfo::~AInfo
AInfo::~AInfo()
{
    ConditionalDestroy();
}

// USound::~USound
USound::~USound()
{
    ConditionalDestroy();
}

// ABrush::~ABrush
ABrush::~ABrush()
{
    ConditionalDestroy();
}
