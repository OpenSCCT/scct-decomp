#ifndef VERSUS_CANVAS_FONT_H
#define VERSUS_CANVAS_FONT_H

#include "versus_build.h"
#include "unreal_object.h"
#include "unreal_containers.h"

class UMaterial;

struct FFontCharacter {
    INT StartU, StartV;
    INT USize, VSize;
    BYTE TextureIndex;
};

struct FCharRemapPair {
    INT HashNext;
    TCHAR Key, Value;
};

class UFont : public UObject {
public:
    TArray<FFontCharacter> Characters;
    TArray<UMaterial *> Textures;
    TArray<FCharRemapPair> CharRemapPairs;
    INT *CharRemapHash;
    INT CharRemapHashCount;
    UBOOL IsRemapped;
    INT Kerning;

    const FCharRemapPair &RemapPair(INT Index) const
    {
        return static_cast<const FCharRemapPair *>(CharRemapPairs.Data)[Index];
    }

    const TCHAR *FindRemappedCharacter(TCHAR Ch) const
    {
        for (INT Index = CharRemapHash[Ch & (CharRemapHashCount - 1)]; Index != -1; Index = RemapPair(Index).HashNext)
            if (RemapPair(Index).Key == Ch)
                return &RemapPair(Index).Value;
        return 0;
    }

    TCHAR RemapChar(TCHAR Ch) const
    {
        if (!IsRemapped)
            return Ch;
        const TCHAR *Remapped = FindRemappedCharacter(Ch);
        return Remapped ? *Remapped : ' ';
    }

    void GetCharSize(TCHAR Char, INT &Width, INT &Height) const
    {
        Width = Height = 0;
        TCHAR Ch = RemapChar(Char);
        if (Ch < Characters.ArrayNum) {
            const FFontCharacter &Glyph = static_cast<const FFontCharacter *>(Characters.Data)[Ch];
            Width = Glyph.USize;
            Height = Glyph.VSize;
        }
    }
};

#endif
