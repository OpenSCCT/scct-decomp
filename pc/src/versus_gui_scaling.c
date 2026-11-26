/* The stock layout uses the first active viewport. A normalized dimension
   scales with its parent when requested, or with the viewport otherwise. */
#include "versus_gui_component.h"

struct display_viewport {
    unsigned char prefix[0xa0];
    int width, height;
};
struct gui_display {
    unsigned char prefix[0x2c];
    const struct display_viewport **viewports;
    int viewport_count;
};
struct gui_session {
    unsigned char prefix[0x28];
    const struct gui_display *display;
};
struct gui_context {
    unsigned char prefix[0x30];
    const struct gui_session *session;
};

float __fastcall gui_actual_width(struct gui_component *self)
{
    const struct gui_context *context = self->context;
    const struct display_viewport *view;
    if (!context || !context->session || !context->session->display ||
        !context->session->display->viewport_count || !(view = context->session->display->viewports[0]))
        return 0.0f;
    if (self->width <= 1.0f) {
        struct gui_component *owner;
        if (self->scale_to_parent && (owner = self->parent))
            return self->width * owner->methods->width(owner);
        return self->width * view->width;
    }
    return self->width;
}

float __fastcall gui_actual_height(struct gui_component *self)
{
    const struct gui_context *context = self->context;
    const struct display_viewport *view;
    if (!context || !context->session || !context->session->display ||
        !context->session->display->viewport_count || !(view = context->session->display->viewports[0]))
        return 0.0f;
    if (self->height <= 1.0f) {
        struct gui_component *owner;
        if (self->scale_to_parent && (owner = self->parent))
            return self->height * owner->methods->height(owner);
        return self->height * view->height;
    }
    return self->height;
}
