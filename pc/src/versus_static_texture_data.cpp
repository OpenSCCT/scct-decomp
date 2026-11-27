#include "versus_build.h"
#include "versus_registration_arrays.h"
#include "versus_canvas_materials.h"
#include "versus_static_textures.h"
#include "versus_mipmap.h"

void *FStaticTexture::GetRawTextureData(INT MipIndex)
{
    if (!Owner->bParametric)
        Owner->Mips(MipIndex).DataArray.Load();
    return Owner->Mips(MipIndex).DataArray.Data;
}

void FStaticTexture::UnloadRawTextureData(INT MipIndex)
{
    if (!Owner->bParametric)
        Owner->Mips(MipIndex).DataArray.TLazyArray<BYTE>::Unload();
}
