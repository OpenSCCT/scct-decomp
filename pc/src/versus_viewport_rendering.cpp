// versus_viewport_rendering.cpp -- finish and present a Versus viewport frame.
#include <string.h>
#include "versus_viewport.h"
#include "versus_render_device.h"

extern "C" void __fastcall versus_viewport_begin(Viewport *self)
{
    self->device->Unlock(self->render_interface);
    self->pending_present = 1;
}

extern "C" void __fastcall versus_viewport_end(Viewport *self)
{
    if (self->pending_present) {
        self->pending_present = 0;
        // Viewport is the shared layout view of the retail UWindowsViewport receiver.
        self->device->Present(reinterpret_cast<UViewport *>(self));
        memcpy(&self->presented_lock_time, &self->last_lock_time, sizeof self->last_lock_time);
        self->unk_9c = 0;
    }
}
