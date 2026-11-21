// w4_item_0096.cpp -- Versus RVA 0x14f4a0 (FIndexBuffer subclass constructor)

typedef int INT;
typedef unsigned short _WORD;
typedef unsigned __int64 QWORD;

enum ECacheIDBase {
    CID_RenderIndices = 0xe2,
};

extern QWORD GNextCacheId;

static inline QWORD MakeCacheID(ECacheIDBase Base) {
    return (GNextCacheId++) * 0x100 + Base;
}

class FRenderResource {
public:
    virtual QWORD GetCacheId() = 0;
    virtual INT GetRevision() = 0;
};

class FIndexBuffer : public FRenderResource {
public:
    virtual INT GetSize() = 0;
    virtual void GetContents(void *Data) = 0;
};

// Neutral name: FIndexBuffer subclass constructed at 0x14f4a0 (vtable 0x10c03398).
// GetContents (0x14f510) tracks MinVertexIndex (+0x10) and MaxVertexIndex (+0x12).
class FIndexBuffer_14f4a0 : public FIndexBuffer {
public:
    void *Owner;
    QWORD CacheId;
    _WORD MinVertexIndex;
    _WORD MaxVertexIndex;

    FIndexBuffer_14f4a0(void *InOwner);

    virtual QWORD GetCacheId();
    virtual INT GetRevision();
    virtual INT GetSize();
    virtual void GetContents(void *Data);
};

// FIndexBuffer_14f4a0::FIndexBuffer_14f4a0 (RVA 0x14f4a0)
// Initializes the index buffer owner, unique render-index cache ID, and vertex range.
FIndexBuffer_14f4a0::FIndexBuffer_14f4a0(void *InOwner) {
    Owner = InOwner;
    CacheId = MakeCacheID(CID_RenderIndices);
    MinVertexIndex = 0x7fff;
    MaxVertexIndex = 0;
}

// Scaffolding for the link, not part of the unit.
extern void UseIndexBuffer(FIndexBuffer *Buf);
extern void *GetOwner(INT Index);

void Driver_14f4a0(INT Mode) {
    switch (Mode) {
    case 0: {
        FIndexBuffer_14f4a0 Buf(GetOwner(0));
        UseIndexBuffer(&Buf);
        break;
    }
    case 1: {
        FIndexBuffer_14f4a0 Buf(GetOwner(1));
        UseIndexBuffer(&Buf);
        break;
    }
    case 2: {
        FIndexBuffer_14f4a0 Buf(GetOwner(2));
        UseIndexBuffer(&Buf);
        break;
    }
    case 3: {
        FIndexBuffer_14f4a0 Buf(GetOwner(3));
        UseIndexBuffer(&Buf);
        break;
    }
    case 4: {
        FIndexBuffer_14f4a0 Buf(GetOwner(4));
        UseIndexBuffer(&Buf);
        break;
    }
    case 5: {
        FIndexBuffer_14f4a0 Buf(GetOwner(5));
        UseIndexBuffer(&Buf);
        break;
    }
    case 6: {
        FIndexBuffer_14f4a0 Buf(GetOwner(6));
        UseIndexBuffer(&Buf);
        break;
    }
    case 7: {
        FIndexBuffer_14f4a0 Buf(GetOwner(7));
        UseIndexBuffer(&Buf);
        break;
    }
    }
}
