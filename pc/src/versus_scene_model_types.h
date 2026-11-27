#ifndef VERSUS_SCENE_MODEL_TYPES_H
#define VERSUS_SCENE_MODEL_TYPES_H

struct FBspNode {
    BYTE unk_00[0x2c];
    INT iSurf;
    BYTE unk_30[0x50 - 0x30];
    short iSection;
    BYTE unk_52[0x5c - 0x52];
};

struct FBspSurf {
    BYTE unk_00[0x14];
    DWORD PolyFlags;
    BYTE unk_18[0x2c - 0x18];
};

// The collision query uses this prefix of the model.
struct FPointRegion { AZoneInfo *Zone; INT iLeaf; BYTE ZoneNumber; };

struct FZoneProperties {
    AZoneInfo *ZoneActor;
    DWORD unk_04[3];
};

class UModel : public UPrimitive {
public:
    BYTE unk_50[4];
    TTransArray<FBspNode> Nodes;
    BYTE unk_64[0x94 - 0x64];
    TTransArray<FBspSurf> Surfs;
    BYTE unk_a4[0xd4 - 0xa4];
    TArray<struct FBspSection> Sections;
    BYTE unk_e0[0x114 - 0xe0];
    TArray<FZoneProperties> Zones;

    FPointRegion PointRegion(AZoneInfo *Zone, const FVector &Location) const;
    void BuildRenderData();  // prepares the BSP render sections
};

#endif
