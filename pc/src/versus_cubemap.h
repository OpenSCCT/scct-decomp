#ifndef VERSUS_CUBEMAP_H
#define VERSUS_CUBEMAP_H

#include "versus_canvas_materials.h"

class FStaticCubemap;

// Engine.Cubemap registers six UTexture faces starting at +0xc0.
class UCubemap : public UTexture {
public:
    UCubemap();
    virtual ~UCubemap();

    UTexture *Faces[6];
    FStaticCubemap *CubemapInterface;
};

#endif
