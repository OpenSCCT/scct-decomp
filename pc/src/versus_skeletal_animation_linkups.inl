// Add an animation and optional reference mesh unless the animation was already linked.
UBOOL USkeletalMeshInstance::SetAnimLinkup(UMeshAnimation *Anim, UMesh *RefMesh)
{
    if (Anim) {
        TArray<MeshAnimLinkup> &Links = AnimLinkups;
        INT Found = -1;
        for (INT i = 0; i < Links.Num(); i++) {
            if (Links(i).Anim == Anim) {
                Found = i;
                break;
            }
        }
        if (Found == -1) {
            INT Index = AnimLinkups.Num();
            AnimLinkups.AddZeroed(sizeof(MeshAnimLinkup), 1);
            AnimLinkups(Index).Anim = Anim;
            AnimLinkups(Index).RefMesh = RefMesh;
        }
        LinkupsChanged();
    }
    return 1;
}

// Install the skeletal mesh defaults on the first animation lookup.
void USkeletalMeshInstance::ActualizeAnimLinkups()
{
    if (this && AnimLinkups.Num() == 0 && GetMesh()
        && static_cast<USkeletalMesh *>(GetMesh())->DefaultAnim) {
        SetAnimLinkup(static_cast<USkeletalMesh *>(GetMesh())->DefaultAnim,
                      static_cast<USkeletalMesh *>(GetMesh())->DefaultRefMesh);
    }
}

// GetFrame selects the channel's animation object through virtual slot 75.
UMeshAnimation *USkeletalMeshInstance::CurrentSkelAnim(INT Channel)
{
    ActualizeAnimLinkups();
    if (Channel >= 0 && Channel < Channels.Num()) {
        INT Index = Channels(Channel).MeshAnimIndex;
        if (Index > -1 && AnimLinkups.Num() > Index && AnimLinkups(Index).Anim)
            return AnimLinkups(Index).Anim;
        return static_cast<USkeletalMesh *>(GetMesh())->DefaultAnim;
    }
    return static_cast<USkeletalMesh *>(GetMesh())->DefaultAnim;
}
