// Express the parent scene in the child's local coordinate system.
FLevelSceneNode::FLevelSceneNode(FLevelSceneNode* InParent, INT InViewZone, FMatrix LocalToParent)
    : FSceneNode(InParent)
{
    Level = InParent->Level;
    Model = InParent->Model;
    ViewZone = InViewZone;
    InvisibleZone = -1;
    ViewActor = 0;
    StencilRef = Viewport->NextStencilBit;
    Viewport->NextStencilBit <<= 1;

    FMatrix ParentToLocal = LocalToParent.Inverse();
    WorldToCamera = Parent->WorldToCamera * LocalToParent;
    CameraToWorld = ParentToLocal * Parent->CameraToWorld;
    WorldToScreen = CameraToScreen * WorldToCamera;
    ScreenToWorld = CameraToWorld * ScreenToCamera;
    Determinant = WorldToScreen.Determinant();

    ViewOrigin = ParentToLocal.TransformFVector(Parent->ViewOrigin);
    CameraX = ScreenToWorld.TransformNormal(FVector(2.f / Viewport->SizeX, 0.f, 0.f));
    CameraY = ScreenToWorld.TransformNormal(FVector(0.f, 2.f / Viewport->SizeY, 0.f));
}
