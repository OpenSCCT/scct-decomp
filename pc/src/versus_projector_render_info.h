#ifndef VERSUS_PROJECTOR_RENDER_INFO_H
#define VERSUS_PROJECTOR_RENDER_INFO_H

class AProjector;
class UMaterial;
class UTexture;

enum EProjectorFlags {
    PRF_Perspective = 0x01,
    PRF_Gradient = 0x04,
    PRF_ProjectOnBackfaces = 0x10,
    PRF_BorderClampMode = 0x20
};

// The render-info constructor copies the projector's matrices, bounds and frustum planes.
class FProjectorRenderInfo {
public:
    AProjector *Projector;
    INT ReferenceCount;
    DOUBLE LastRenderTime;
    DOUBLE Expires;
    UMaterial *Material;
    UTexture *GradientTexture;
    BYTE MaterialBlendingOp;
    BYTE FrameBufferBlendingOp;
    FMatrix Matrix;
    FMatrix InvMatrix;
    FVector BoxCenter;
    FVector BoxExtent;
    FPlane FrustumPlanes[6];
    FMatrix WorldToTexture;
    DWORD ProjectorFlags;

    FProjectorRenderInfo *AddReference()
    {
        ++ReferenceCount;
        return this;
    }
    void RemoveReference();
    UBOOL Render(DOUBLE CurrentTime);
};

#endif
