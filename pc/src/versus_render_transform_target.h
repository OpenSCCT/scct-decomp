#ifndef VERSUS_RENDER_TRANSFORM_TARGET_H
#define VERSUS_RENDER_TRANSFORM_TARGET_H

class UMaterial;
class FRenderInterface;
class FVertexStream;
struct FSphere;
struct FMatrix;

class FRenderTransformTarget
{
  public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void EnableLighting(FRenderInterface *RI, INT Dynamic, INT Static, INT Modulate, INT LightingOnly, FSphere LightSphere);
    virtual void SetTransform(FRenderInterface *RI, INT Type, const FMatrix &Matrix);
    virtual void Slot1c();
    virtual INT SetDynamicStream(FRenderInterface *RI, INT Index, FVertexStream *Stream);
    virtual void SetMaterial(FRenderInterface *RI, UMaterial *Material, INT Flags);
};

#endif
