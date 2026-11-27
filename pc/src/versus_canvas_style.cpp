#include "versus_build.h"
#include "versus_native_class_types.h"
#include "versus_canvas.h"
#include "versus_canvas_util.h"
#include "versus_canvas_materials.h"
#include "versus_global_temp_objects.h"

static UBOOL IsChildOf(const UClass *Type, const UClass *Base) {
    for (; Type; Type = static_cast<const UClass *>(Type->SuperField)) {
        if (Type == Base)
            return 1;
    }
    return 0;
}

#include "versus_construct_object.h"
extern UObject *GObjTransientPkg;
extern UGlobalTempObjects *GGlobalTempObjects;

enum EFrameBufferBlending {
    FB_Overwrite = 0, FB_Modulate = 1, FB_AlphaBlend = 2,
    FB_Translucent = 4, FB_Darken = 5, FB_Brighten = 6
};
enum ERenderStyle {
    STY_Masked = 2, STY_Translucent, STY_Modulated, STY_Alpha, STY_Additive, STY_Subtractive
};

namespace CanvasStyle {
BYTE LastStyle;
UMaterial *LastMaterial;
UMaterial *LastResult;
UFinalBlend *FinalBlend;
}
using namespace CanvasStyle;

UMaterial *UCanvas::GetStyleMaterial(UMaterial *Material) {
    UMaterial *Result = Material;
    if (Style == LastStyle && Material == LastMaterial) {
        Result = LastResult;
    } else {
        pCanvasUtil->Flush();
        LastStyle = Style;
        LastMaterial = Material;
        if (Material && IsChildOf(Material->Class, &UTexture::PrivateStaticClass)
            && Style != 0xff
            && !Material->IsA(&UCombiner::PrivateStaticClass)
            && !Material->IsA(&UShader::PrivateStaticClass)
            && !Material->IsA(&ULitSpecularMaterial::PrivateStaticClass)
            && !Material->IsA(&UFinalBlend::PrivateStaticClass)) {
            if (!FinalBlend) {
                UFinalBlend *Blend = static_cast<UFinalBlend *>(ConstructObject(
                    &UFinalBlend::PrivateStaticClass, GObjTransientPkg));
                FinalBlend = Blend;
                GGlobalTempObjects->AddReference(reinterpret_cast<UObject **>(&FinalBlend));
                GGlobalTempObjects->AddReference(reinterpret_cast<UObject **>(&LastMaterial));
                GGlobalTempObjects->AddReference(reinterpret_cast<UObject **>(&LastResult));
            }
            FinalBlend->Material = Material;
            FinalBlend->TwoSided = 0;
            FinalBlend->ZWrite = 0;
            FinalBlend->ZTest = 0;
            switch (Style) {
            case STY_Masked:
                FinalBlend->FrameBufferBlending = FB_Overwrite;
                FinalBlend->AlphaTest = 1;
                FinalBlend->AlphaRef = 127;
                Result = FinalBlend;
                break;
            case STY_Translucent:
                FinalBlend->FrameBufferBlending = FB_Translucent;
                FinalBlend->AlphaTest = 0;
                Result = FinalBlend;
                break;
            case STY_Modulated:
                FinalBlend->FrameBufferBlending = FB_Modulate;
                FinalBlend->AlphaTest = 0;
                Result = FinalBlend;
                break;
            case STY_Alpha:
                FinalBlend->FrameBufferBlending = FB_AlphaBlend;
                FinalBlend->AlphaTest = 1;
                FinalBlend->AlphaRef = 0;
                Result = FinalBlend;
                break;
            case STY_Additive:
                FinalBlend->FrameBufferBlending = FB_Brighten;
                FinalBlend->AlphaTest = 1;
                FinalBlend->AlphaRef = 0;
                Result = FinalBlend;
                break;
            case STY_Subtractive:
                FinalBlend->FrameBufferBlending = FB_Darken;
                FinalBlend->AlphaTest = 0;
                Result = FinalBlend;
                break;
            }
        }
    }
    LastResult = Result;
    return Result;
}
void UGlobalTempObjects::AddReference(UObject **Ref) {
    GlobalObjectPtrs.AddItem(Ref);
}
