#include "versus_build.h"
#include "versus_registration_arrays.h"
#include "versus_canvas_materials.h"
#include "versus_mipmap.h"
#include "versus_app_memzero.h"
#include "unreal_math.h"

enum ETextureClearFlags { TCLEAR_Bitmap = 2 };

void UTexture::Clear(DWORD ClearFlags)
{
    if (ClearFlags & TCLEAR_Bitmap) {
        for (INT i = 0; i < Mips.Num(); ++i)
            appMemzero(Mips(i).DataArray.Data, Mips(i).DataArray.Num());
    }
}

void UTexture::ClearColor(FColor Color)
{
    if (Format == TEXF_RGBA8) {
        for (INT i = 0; i < USize * VSize; ++i)
            static_cast<FColor *>(Mips(0).DataArray.Data)[i] = Color;
    }
}
