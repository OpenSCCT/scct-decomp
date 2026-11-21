// Item 0255: RVA 0x5ffe0. Releases the Direct3D resources held by a large
// render-device object (fields at 0x30e1c..0x30ea8). The object is most likely
// UD3DRenderDevice (its deleting destructor sits at 0x604e0), but the class
// and member names here are neutral since the layout is not recovered.

struct IUnknownLike
{
    virtual long __stdcall QueryInterface(const void *Iid, void **Out) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
};

#define SAFE_RELEASE(p) { if (p) { (p)->Release(); (p) = 0; } }

class UnnamedRenderDevice_5ffe0
{
public:
    char Pad0[0x30e1c];
    IUnknownLike *Res1c;          // 0x30e1c
    IUnknownLike *Res20;          // 0x30e20
    IUnknownLike *Res24;          // 0x30e24
    IUnknownLike *Res28;          // 0x30e28
    IUnknownLike *Res2c;          // 0x30e2c
    IUnknownLike *Res30[4];       // 0x30e30
    IUnknownLike *Res40;          // 0x30e40
    char Pad44[0x30e5c - 0x30e44];
    IUnknownLike *Res5c;          // 0x30e5c
    IUnknownLike *Res60;          // 0x30e60
    IUnknownLike *Res64;          // 0x30e64
    IUnknownLike *Res68;          // 0x30e68
    IUnknownLike *Res6c;          // 0x30e6c
    IUnknownLike *Res70;          // 0x30e70
    IUnknownLike *Res74;          // 0x30e74
    IUnknownLike *Res78;          // 0x30e78
    IUnknownLike *Res7c;          // 0x30e7c
    IUnknownLike *Res80;          // 0x30e80
    IUnknownLike *Res84;          // 0x30e84
    IUnknownLike *Res88;          // 0x30e88
    IUnknownLike *Res8c;          // 0x30e8c
    IUnknownLike *Res90;          // 0x30e90
    IUnknownLike *Res94[2];       // 0x30e94
    char Pad9c[0x30ea4 - 0x30e9c];
    IUnknownLike *Resa4;          // 0x30ea4

    void ReleaseResources();
};

void UnnamedRenderDevice_5ffe0::ReleaseResources()
{
    SAFE_RELEASE(Res1c);
    SAFE_RELEASE(Res20);
    for (int i = 0; i < 4; i++)
        SAFE_RELEASE(Res30[i]);
    SAFE_RELEASE(Res2c);
    SAFE_RELEASE(Resa4);
    SAFE_RELEASE(Res68);
    SAFE_RELEASE(Res6c);
    SAFE_RELEASE(Res70);
    SAFE_RELEASE(Res74);
    SAFE_RELEASE(Res78);
    SAFE_RELEASE(Res7c);
    SAFE_RELEASE(Res80);
    SAFE_RELEASE(Res84);
    SAFE_RELEASE(Res88);
    SAFE_RELEASE(Res28);
    SAFE_RELEASE(Res24);
    SAFE_RELEASE(Res40);
    SAFE_RELEASE(Res5c);
    SAFE_RELEASE(Res60);
    SAFE_RELEASE(Res64);
    SAFE_RELEASE(Res90);
    SAFE_RELEASE(Res8c);
    for (int j = 0; j < 2; j++)
        SAFE_RELEASE(Res94[j]);
}

// Scaffolding for the link, not part of the unit.
void Driver_5ffe0(UnnamedRenderDevice_5ffe0 *D) { D->ReleaseResources(); }
void Driver2_5ffe0(UnnamedRenderDevice_5ffe0 *D) { D->ReleaseResources(); }
