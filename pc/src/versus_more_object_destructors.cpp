// More Unreal Engine 2 class destructors from the Steam Versus payload. A class
// whose registered placement constructor does not identify its vtable is named
// UnnamedClass followed by that vtable's address relative to the image base.
// Each class destructor runs UObject::ConditionalDestroy() before its parent's
// destructor, as the engine's DECLARE_CLASS destructor does. Only the members these
// destructors touch are declared; VirtualSlot names stand for engine virtual methods
// whose names this translation unit does not need.
enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

class UObject {
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    int Index;
    unsigned Reserved[5];
    unsigned ObjectFlags;
    int ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed)) {
            ObjectFlags = (ObjectFlags & ~(RF_DebugDestroy | RF_Destroyed)) | RF_Destroyed;
            Destroy();
            return 1;
        }
        return 0;
    }
};

// Parent classes whose own destructors are matched elsewhere or remain open.
class AInternetInfo : public UObject { public: virtual ~AInternetInfo(); };
class UESBPatch : public UObject { public: virtual ~UESBPatch(); };
class UESBRope : public UObject { public: virtual ~UESBRope(); };
class UnnamedClass2F7AD8 : public UObject { public: virtual ~UnnamedClass2F7AD8(); };
class UnnamedClass303F10 : public UObject { public: virtual ~UnnamedClass303F10(); };
class UnnamedClass3066B8 : public UObject { public: virtual ~UnnamedClass3066B8(); };
class UnnamedClass30BBB8 : public UObject { public: virtual ~UnnamedClass30BBB8(); };
class UnnamedClass30C340 : public UObject { public: virtual ~UnnamedClass30C340(); };
class UnnamedClass30C9E8 : public UObject { public: virtual ~UnnamedClass30C9E8(); };
class UnnamedClass30CED0 : public UObject { public: virtual ~UnnamedClass30CED0(); };
class UnnamedClass30D0B8 : public UObject { public: virtual ~UnnamedClass30D0B8(); };

class UnnamedClass30D7D8 : public UObject { public: virtual ~UnnamedClass30D7D8(); };
UnnamedClass30D7D8::~UnnamedClass30D7D8() { ConditionalDestroy(); }

class UnnamedClass30D6A0 : public UObject { public: virtual ~UnnamedClass30D6A0(); };
UnnamedClass30D6A0::~UnnamedClass30D6A0() { ConditionalDestroy(); }

class UnnamedClass30D600 : public UnnamedClass30D6A0 { public: virtual ~UnnamedClass30D600(); };
UnnamedClass30D600::~UnnamedClass30D600() { ConditionalDestroy(); }

class UIntProperty : public UnnamedClass30D600 { public: virtual ~UIntProperty(); };
UIntProperty::~UIntProperty() { ConditionalDestroy(); }

class UBoolProperty : public UnnamedClass30D600 { public: virtual ~UBoolProperty(); };
UBoolProperty::~UBoolProperty() { ConditionalDestroy(); }

class UStrProperty : public UnnamedClass30D600 { public: virtual ~UStrProperty(); };
UStrProperty::~UStrProperty() { ConditionalDestroy(); }

class UArrayProperty : public UnnamedClass30D600 { public: virtual ~UArrayProperty(); };
UArrayProperty::~UArrayProperty() { ConditionalDestroy(); }

class UTextBufferFactory : public UnnamedClass30CED0 { public: virtual ~UTextBufferFactory(); };
UTextBufferFactory::~UTextBufferFactory() { ConditionalDestroy(); }

class UByteProperty : public UnnamedClass30D600 { public: virtual ~UByteProperty(); };
UByteProperty::~UByteProperty() { ConditionalDestroy(); }

class UFloatProperty : public UnnamedClass30D600 { public: virtual ~UFloatProperty(); };
UFloatProperty::~UFloatProperty() { ConditionalDestroy(); }

class UObjectProperty : public UnnamedClass30D600 { public: virtual ~UObjectProperty(); };
UObjectProperty::~UObjectProperty() { ConditionalDestroy(); }

class UNameProperty : public UnnamedClass30D600 { public: virtual ~UNameProperty(); };
UNameProperty::~UNameProperty() { ConditionalDestroy(); }

class UFixedArrayProperty : public UnnamedClass30D600 { public: virtual ~UFixedArrayProperty(); };
UFixedArrayProperty::~UFixedArrayProperty() { ConditionalDestroy(); }

class UMapProperty : public UnnamedClass30D600 { public: virtual ~UMapProperty(); };
UMapProperty::~UMapProperty() { ConditionalDestroy(); }

class UStructProperty : public UnnamedClass30D600 { public: virtual ~UStructProperty(); };
UStructProperty::~UStructProperty() { ConditionalDestroy(); }

class UDelegateProperty : public UnnamedClass30D600 { public: virtual ~UDelegateProperty(); };
UDelegateProperty::~UDelegateProperty() { ConditionalDestroy(); }

class UObjectExporterT3D : public UnnamedClass30C9E8 { public: virtual ~UObjectExporterT3D(); };
UObjectExporterT3D::~UObjectExporterT3D() { ConditionalDestroy(); }

class UPrimitive : public UObject { public: virtual ~UPrimitive(); };
UPrimitive::~UPrimitive() { ConditionalDestroy(); }

class UnnamedClass30B990 : public UObject { public: virtual ~UnnamedClass30B990(); };
UnnamedClass30B990::~UnnamedClass30B990() { ConditionalDestroy(); }

class UMeshInstance : public UPrimitive { public: virtual ~UMeshInstance(); };
UMeshInstance::~UMeshInstance() { ConditionalDestroy(); }

class UnnamedClass30A7B0 : public UPrimitive { public: virtual ~UnnamedClass30A7B0(); };
UnnamedClass30A7B0::~UnnamedClass30A7B0() { ConditionalDestroy(); }

class UnnamedClass309E98 : public UnnamedClass30B990 { public: virtual ~UnnamedClass309E98(); };
UnnamedClass309E98::~UnnamedClass309E98() { ConditionalDestroy(); }

class UnnamedClass309E00 : public UnnamedClass309E98 { public: virtual ~UnnamedClass309E00(); };
UnnamedClass309E00::~UnnamedClass309E00() { ConditionalDestroy(); }

class UShadowBitmapMaterial : public UnnamedClass309E00 { public: virtual ~UShadowBitmapMaterial(); };
UShadowBitmapMaterial::~UShadowBitmapMaterial() { ConditionalDestroy(); }

class UScriptedTexture : public UnnamedClass309E00 { public: virtual ~UScriptedTexture(); };
UScriptedTexture::~UScriptedTexture() { ConditionalDestroy(); }

class UnnamedClass3099B0 : public UObject { public: virtual ~UnnamedClass3099B0(); };
UnnamedClass3099B0::~UnnamedClass3099B0() { ConditionalDestroy(); }

class UnnamedClass3098A0 : public UnnamedClass3099B0 { public: virtual ~UnnamedClass3098A0(); };
UnnamedClass3098A0::~UnnamedClass3098A0() { ConditionalDestroy(); }

class UProjectorMaterial : public UnnamedClass309E98 { public: virtual ~UProjectorMaterial(); };
UProjectorMaterial::~UProjectorMaterial() { ConditionalDestroy(); }

class UProjectorPrimitive : public UPrimitive { public: virtual ~UProjectorPrimitive(); };
UProjectorPrimitive::~UProjectorPrimitive() { ConditionalDestroy(); }

class UParticleMaterial : public UnnamedClass309E98 { public: virtual ~UParticleMaterial(); };
UParticleMaterial::~UParticleMaterial() { ConditionalDestroy(); }

class UPackageMapLevel : public UnnamedClass30C340 { public: virtual ~UPackageMapLevel(); };
UPackageMapLevel::~UPackageMapLevel() { ConditionalDestroy(); }

class UModifier : public UnnamedClass30B990 { public: virtual ~UModifier(); };
UModifier::~UModifier() { ConditionalDestroy(); }

class UVertexColor : public UnnamedClass309E98 { public: virtual ~UVertexColor(); };
UVertexColor::~UVertexColor() { ConditionalDestroy(); }

class UConstantMaterial : public UnnamedClass309E98 { public: virtual ~UConstantMaterial(); };
UConstantMaterial::~UConstantMaterial() { ConditionalDestroy(); }

class UCombiner : public UnnamedClass30B990 { public: virtual ~UCombiner(); };
UCombiner::~UCombiner() { ConditionalDestroy(); }

class ULitSpecularMaterial : public UnnamedClass309E98 { public: virtual ~ULitSpecularMaterial(); };
ULitSpecularMaterial::~ULitSpecularMaterial() { ConditionalDestroy(); }

class UShader : public UnnamedClass309E98 { public: virtual ~UShader(); };
UShader::~UShader() { ConditionalDestroy(); }

class UEchelonLightingMaterial : public UnnamedClass30B990 { public: virtual ~UEchelonLightingMaterial(); };
UEchelonLightingMaterial::~UEchelonLightingMaterial() { ConditionalDestroy(); }

class UTexCoordMaterial : public UnnamedClass309E98 { public: virtual ~UTexCoordMaterial(); };
UTexCoordMaterial::~UTexCoordMaterial() { ConditionalDestroy(); }

class UProxyBitmapMaterial : public UnnamedClass309E00 { public: virtual ~UProxyBitmapMaterial(); };
UProxyBitmapMaterial::~UProxyBitmapMaterial() { ConditionalDestroy(); }

class UServerCommandlet : public UnnamedClass30D0B8 { public: virtual ~UServerCommandlet(); };
UServerCommandlet::~UServerCommandlet() { ConditionalDestroy(); }

class ACamera : public UnnamedClass3066B8 { public: virtual ~ACamera(); };
ACamera::~ACamera() { ConditionalDestroy(); }

class UnnamedClass304548 : public UObject { public: virtual ~UnnamedClass304548(); };
UnnamedClass304548::~UnnamedClass304548() { ConditionalDestroy(); }

class UnnamedClass304020 : public UnnamedClass303F10 { public: virtual ~UnnamedClass304020(); };
UnnamedClass304020::~UnnamedClass304020() { ConditionalDestroy(); }

class UnnamedClass303C40 : public UnnamedClass30BBB8 { public: virtual ~UnnamedClass303C40(); };
UnnamedClass303C40::~UnnamedClass303C40() { ConditionalDestroy(); }

class UnnamedClass2FF448 : public AInternetInfo { public: virtual ~UnnamedClass2FF448(); };
UnnamedClass2FF448::~UnnamedClass2FF448() { ConditionalDestroy(); }

class UnnamedClass2FF580 : public UnnamedClass2FF448 { public: virtual ~UnnamedClass2FF580(); };
UnnamedClass2FF580::~UnnamedClass2FF580() { ConditionalDestroy(); }

class ASLANClientLink : public UnnamedClass2FF580 { public: virtual ~ASLANClientLink(); };
ASLANClientLink::~ASLANClientLink() { ConditionalDestroy(); }

class ASGadMultiPresDetectorLauncher : public UnnamedClass2F7AD8 { public: virtual ~ASGadMultiPresDetectorLauncher(); };
ASGadMultiPresDetectorLauncher::~ASGadMultiPresDetectorLauncher() { ConditionalDestroy(); }

class UESBChain : public UESBRope { public: virtual ~UESBChain(); };
UESBChain::~UESBChain() { ConditionalDestroy(); }

class UESBStripDoor : public UESBPatch { public: virtual ~UESBStripDoor(); };
UESBStripDoor::~UESBStripDoor() { ConditionalDestroy(); }

class UnnamedClass2F2628 : public UnnamedClass30D7D8 { public: virtual ~UnnamedClass2F2628(); };
UnnamedClass2F2628::~UnnamedClass2F2628() { ConditionalDestroy(); }
