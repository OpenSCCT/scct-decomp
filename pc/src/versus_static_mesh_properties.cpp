#include "versus_build.h"
#include "versus_archive.h"
#include "versus_native_properties.h"

class UMaterial : public UObject { public: static UClass PrivateStaticClass; };

struct FStaticMeshMaterial {
    UMaterial *Material;
    UBOOL EnableCollision;
    INT unk_8;
};

class UPrimitive : public UObject {
public:
    BYTE unk_28[0x28];
};

class UStaticMesh : public UPrimitive {
public:
    BYTE unk_50[0xdc - 0x50];
    TArray<FStaticMeshMaterial> Materials;
    BYTE unk_e8[0x140 - 0xe8];
    UBOOL UseSimpleLineCollision, UseSimpleBoxCollision, UseVertexColor;
    BYTE unk_14c[0x194 - 0x14c];
    INT unk_194, unk_198, unk_19c;
    void StaticConstructor();
};

template<class T> inline void *operator new (unsigned int, TArray<T> &Array) {
    INT Index = Array.Add(1, sizeof(T));
    return &Array(Index);
}

static const EName NAME_Object = (EName)151;
static const EName NAME_UseSimpleLineCollision = (EName)37;
static const EName NAME_UseSimpleBoxCollision = (EName)38;
static const EName NAME_UseVertexColor = (EName)39;
static const EName NAME_StaticMeshMaterial = (EName)40;
static const EName NAME_EnableCollision = (EName)41;
static const EName NAME_Materials = (EName)42;
static const EName NAME_StructProperty0 = (EName)43;
static const EName NAME_Material = (EName)157817;

enum { RF_Public = 4, CPF_Edit = 1, CPF_EditConstArray = 0x40 };

#define STRUCT_OFFSET(type, member) ((INT)&((type *)0)->member)

void UStaticMesh::StaticConstructor()
{
    new (GetClass()->HideCategories) FName(NAME_Object);
    new (GetClass(), NAME_UseSimpleLineCollision, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UStaticMesh, UseSimpleLineCollision), NAME_None, CPF_Edit);
    new (GetClass(), NAME_UseSimpleBoxCollision, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UStaticMesh, UseSimpleBoxCollision), NAME_None, CPF_Edit);
    new (GetClass(), NAME_UseVertexColor, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(UStaticMesh, UseVertexColor), NAME_None, CPF_Edit);

    FArchive Ar;
    UStruct *MaterialStruct = new (GetClass(), NAME_StaticMeshMaterial) UStruct(0);
    new (MaterialStruct, NAME_Material, RF_Public) UObjectProperty(EC_CppProperty,
        STRUCT_OFFSET(FStaticMeshMaterial, Material), NAME_None, CPF_Edit, &UMaterial::PrivateStaticClass);
    new (MaterialStruct, NAME_EnableCollision, RF_Public) UBoolProperty(EC_CppProperty,
        STRUCT_OFFSET(FStaticMeshMaterial, EnableCollision), NAME_None, CPF_Edit);
    MaterialStruct->PropertiesSize = sizeof(FStaticMeshMaterial);
    MaterialStruct->Link(Ar, 0);
    UArrayProperty *Array = new (GetClass(), NAME_Materials, RF_Public) UArrayProperty(EC_CppProperty,
        STRUCT_OFFSET(UStaticMesh, Materials), NAME_None, CPF_Edit | CPF_EditConstArray);
    Array->Inner = new (Array, NAME_StructProperty0, RF_Public) UStructProperty(EC_CppProperty,
        0, NAME_None, CPF_Edit, MaterialStruct);
    UseSimpleLineCollision = 0;
    UseSimpleBoxCollision = 1;
    UseVertexColor = 0;
    unk_194 = -1;
    unk_198 = 0;
    unk_19c = 0;
}
