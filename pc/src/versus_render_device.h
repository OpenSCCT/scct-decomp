// versus_render_device.h -- Versus render-device virtual calls made by the viewport.
#ifndef VERSUS_RENDER_DEVICE_H
#define VERSUS_RENDER_DEVICE_H

class UViewport;
class FRenderInterface;

// Render device: slot 3 is the virtual destructor.
class URenderDevice
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual ~URenderDevice();
    virtual void Slot04();
    virtual void Slot05();
    virtual void Slot06();
    virtual void Slot07();
    virtual void Slot08();
    virtual void Slot09();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void UnSetRes(UViewport *Viewport);
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();
    virtual void Slot33();
    virtual void Slot34();
    virtual FRenderInterface *Lock(UViewport *Viewport, unsigned char *HitData, int *HitSize);
    virtual void Unlock(FRenderInterface *RenderInterface);
    virtual void Present(UViewport *Viewport);
};

#endif
