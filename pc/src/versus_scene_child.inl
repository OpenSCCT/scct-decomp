// A child scene starts with its parent's camera and render target.
FSceneNode::FSceneNode(FSceneNode* InParent)
{
    Parent = InParent;
    Viewport = InParent->Viewport;
    RenderTarget = InParent->RenderTarget;
    Recursion = InParent->Recursion + 1;
    WorldToCamera = InParent->WorldToCamera;
    CameraToScreen = InParent->CameraToScreen;
    ScreenToCamera = InParent->ScreenToCamera;
    CameraToWorld = InParent->CameraToWorld;
    WorldToScreen = InParent->WorldToScreen;
    ScreenToWorld = InParent->ScreenToWorld;
    ViewOrigin = InParent->ViewOrigin;
    CameraX = InParent->CameraX;
    CameraY = InParent->CameraY;
    Determinant = WorldToScreen.Determinant();
}
