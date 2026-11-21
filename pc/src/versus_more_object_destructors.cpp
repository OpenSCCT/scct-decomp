// versus_more_object_destructors.cpp -- more Versus class destructors that destroy no member
//
// Each destructor runs UObject::ConditionalDestroy before the members and the parent class
// are destroyed.
#include "versus_build.h"
#include "unreal_field.h"
#include "unreal_property.h"
#include "versus_core_classes.h"
#include "versus_engine_classes.h"
#include "versus_ipdrv_classes.h"
#include "versus_sbase_classes.h"
#include "versus_softbody_classes.h"
#include "versus_window_classes.h"

// USubsystem::~USubsystem
USubsystem::~USubsystem()
{
    ConditionalDestroy();
}

// UField::~UField
UField::~UField()
{
    ConditionalDestroy();
}

// UProperty::~UProperty
UProperty::~UProperty()
{
    ConditionalDestroy();
}

// UIntProperty::~UIntProperty
UIntProperty::~UIntProperty()
{
    ConditionalDestroy();
}

// UBoolProperty::~UBoolProperty
UBoolProperty::~UBoolProperty()
{
    ConditionalDestroy();
}

// UStrProperty::~UStrProperty
UStrProperty::~UStrProperty()
{
    ConditionalDestroy();
}

// UArrayProperty::~UArrayProperty
UArrayProperty::~UArrayProperty()
{
    ConditionalDestroy();
}

// UTextBufferFactory::~UTextBufferFactory
UTextBufferFactory::~UTextBufferFactory()
{
    ConditionalDestroy();
}

// UByteProperty::~UByteProperty
UByteProperty::~UByteProperty()
{
    ConditionalDestroy();
}

// UFloatProperty::~UFloatProperty
UFloatProperty::~UFloatProperty()
{
    ConditionalDestroy();
}

// UObjectProperty::~UObjectProperty
UObjectProperty::~UObjectProperty()
{
    ConditionalDestroy();
}

// UNameProperty::~UNameProperty
UNameProperty::~UNameProperty()
{
    ConditionalDestroy();
}

// UFixedArrayProperty::~UFixedArrayProperty
UFixedArrayProperty::~UFixedArrayProperty()
{
    ConditionalDestroy();
}

// UMapProperty::~UMapProperty
UMapProperty::~UMapProperty()
{
    ConditionalDestroy();
}

// UStructProperty::~UStructProperty
UStructProperty::~UStructProperty()
{
    ConditionalDestroy();
}

// UDelegateProperty::~UDelegateProperty
UDelegateProperty::~UDelegateProperty()
{
    ConditionalDestroy();
}

// UObjectExporterT3D::~UObjectExporterT3D
UObjectExporterT3D::~UObjectExporterT3D()
{
    ConditionalDestroy();
}

// UPrimitive::~UPrimitive
UPrimitive::~UPrimitive()
{
    ConditionalDestroy();
}

// UMaterial::~UMaterial
UMaterial::~UMaterial()
{
    ConditionalDestroy();
}

// UMeshInstance::~UMeshInstance
UMeshInstance::~UMeshInstance()
{
    ConditionalDestroy();
}

// UMesh::~UMesh
UMesh::~UMesh()
{
    ConditionalDestroy();
}

// URenderedMaterial::~URenderedMaterial
URenderedMaterial::~URenderedMaterial()
{
    ConditionalDestroy();
}

// UBitmapMaterial::~UBitmapMaterial
UBitmapMaterial::~UBitmapMaterial()
{
    ConditionalDestroy();
}

// UShadowBitmapMaterial::~UShadowBitmapMaterial
UShadowBitmapMaterial::~UShadowBitmapMaterial()
{
    ConditionalDestroy();
}

// UScriptedTexture::~UScriptedTexture
UScriptedTexture::~UScriptedTexture()
{
    ConditionalDestroy();
}

// URenderResource::~URenderResource
URenderResource::~URenderResource()
{
    ConditionalDestroy();
}

// UVertexStreamBase::~UVertexStreamBase
UVertexStreamBase::~UVertexStreamBase()
{
    ConditionalDestroy();
}

// UProjectorMaterial::~UProjectorMaterial
UProjectorMaterial::~UProjectorMaterial()
{
    ConditionalDestroy();
}

// UProjectorPrimitive::~UProjectorPrimitive
UProjectorPrimitive::~UProjectorPrimitive()
{
    ConditionalDestroy();
}

// UParticleMaterial::~UParticleMaterial
UParticleMaterial::~UParticleMaterial()
{
    ConditionalDestroy();
}

// UPackageMapLevel::~UPackageMapLevel
UPackageMapLevel::~UPackageMapLevel()
{
    ConditionalDestroy();
}

// UModifier::~UModifier
UModifier::~UModifier()
{
    ConditionalDestroy();
}

// UVertexColor::~UVertexColor
UVertexColor::~UVertexColor()
{
    ConditionalDestroy();
}

// UConstantMaterial::~UConstantMaterial
UConstantMaterial::~UConstantMaterial()
{
    ConditionalDestroy();
}

// UCombiner::~UCombiner
UCombiner::~UCombiner()
{
    ConditionalDestroy();
}

// ULitSpecularMaterial::~ULitSpecularMaterial
ULitSpecularMaterial::~ULitSpecularMaterial()
{
    ConditionalDestroy();
}

// UShader::~UShader
UShader::~UShader()
{
    ConditionalDestroy();
}

// UEchelonLightingMaterial::~UEchelonLightingMaterial
UEchelonLightingMaterial::~UEchelonLightingMaterial()
{
    ConditionalDestroy();
}

// UTexCoordMaterial::~UTexCoordMaterial
UTexCoordMaterial::~UTexCoordMaterial()
{
    ConditionalDestroy();
}

// UProxyBitmapMaterial::~UProxyBitmapMaterial
UProxyBitmapMaterial::~UProxyBitmapMaterial()
{
    ConditionalDestroy();
}

// UServerCommandlet::~UServerCommandlet
UServerCommandlet::~UServerCommandlet()
{
    ConditionalDestroy();
}

// ACamera::~ACamera
ACamera::~ACamera()
{
    ConditionalDestroy();
}

// UChannel::~UChannel
UChannel::~UChannel()
{
    ConditionalDestroy();
}

// UCubemap::~UCubemap
UCubemap::~UCubemap()
{
    ConditionalDestroy();
}

// AERainVolume::~AERainVolume
AERainVolume::~AERainVolume()
{
    ConditionalDestroy();
}

// AInternetLink::~AInternetLink
AInternetLink::~AInternetLink()
{
    ConditionalDestroy();
}

// AUdpLink::~AUdpLink
AUdpLink::~AUdpLink()
{
    ConditionalDestroy();
}

// ASLANClientLink::~ASLANClientLink
ASLANClientLink::~ASLANClientLink()
{
    ConditionalDestroy();
}

// ASGadMultiPresDetectorLauncher::~ASGadMultiPresDetectorLauncher
ASGadMultiPresDetectorLauncher::~ASGadMultiPresDetectorLauncher()
{
    ConditionalDestroy();
}

// UESBChain::~UESBChain
UESBChain::~UESBChain()
{
    ConditionalDestroy();
}

// UESBStripDoor::~UESBStripDoor
UESBStripDoor::~UESBStripDoor()
{
    ConditionalDestroy();
}

// UWindowManager::~UWindowManager
UWindowManager::~UWindowManager()
{
    ConditionalDestroy();
}
