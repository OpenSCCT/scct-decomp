inline void FProjectorRenderInfo::RemoveReference()
{
    if (--ReferenceCount == 0)
        GMalloc->Free(this);
}

UBOOL FProjectorRenderInfo::Render(DOUBLE CurrentTime)
{
    if (Expires != 0.0 && !(GClient->Decals && GClient->Projectors && GClient->Engine->GRenDev->unk_58))
        goto Expired;
    if (Expires != 0.0) {
        if (Expires <= CurrentTime)
            goto Expired;
        if (LastRenderTime != 0.0 && CurrentTime - LastRenderTime > 1.0)
            goto Expired;
    }
    LastRenderTime = CurrentTime;
    return 1;

Expired:
    RemoveReference();
    return 0;
}
