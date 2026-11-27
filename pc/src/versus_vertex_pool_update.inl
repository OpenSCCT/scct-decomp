void UpdateVertexPools(UViewport *Viewport)
{
    FVertexPool *PrevPool = 0;
    FVertexPool *Pool = GFirstVertexPool;
    while (Pool)
    {
        Pool->Stream = 0;
        if (--Pool->UnusedFrames <= 0)
        {
            if (PrevPool)
                PrevPool->NextPool = Pool->NextPool;
            else
                GFirstVertexPool = Pool->NextPool;
            Pool->NextPool = 0;
            Viewport->RenDev->FlushResource(Pool->GetCacheId());
            delete Pool;
            Pool = PrevPool;
        }
        PrevPool = Pool;
        if (Pool)
            Pool = Pool->NextPool;
        else
            Pool = GFirstVertexPool;
    }
}
