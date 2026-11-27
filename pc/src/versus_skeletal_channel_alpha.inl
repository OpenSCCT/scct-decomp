inline void USkeletalMeshInstance::UpdateBlendAlpha(INT Channel, FLOAT Target, FLOAT Rate)
{
    if (Channel >= 0 && Channel < Channels.ArrayNum) {
        MeshAnimChannel &C = static_cast<MeshAnimChannel *>(Channels.Data)[Channel];
        FLOAT Delta = C.CurrentAlpha - Target;
        if ((Delta >= 0.f ? Delta : -Delta) <= Rate)
            C.CurrentAlpha = Target;
        else if (Target > C.CurrentAlpha)
            C.CurrentAlpha += Rate;
        else
            C.CurrentAlpha -= Rate;
    }
}
