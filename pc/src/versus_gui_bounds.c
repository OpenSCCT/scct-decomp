#include "versus_gui_component.h"

struct style_border {
    unsigned char prefix[0x98];
    int left, top, right, bottom;
};

void __fastcall gui_clone_dimensions(struct gui_component *self, void *unused, struct gui_component *from)
{
    if (from) {
        self->width = from->methods->width(from);
        self->height = from->methods->height(from);
        self->left = from->methods->left(from);
        self->top = from->methods->top(from);
    }
}

void __fastcall gui_update_bounds(struct gui_component *self)
{
    self->bounds.left = self->methods->left(self);
    self->bounds.top = self->methods->top(self);
    self->bounds.right = self->methods->left(self) + self->methods->width(self);
    self->bounds.bottom = self->methods->top(self) + self->methods->height(self);
    if (self->style) {
        self->client.left = self->bounds.left + self->style->left;
        self->client.top = self->bounds.top + self->style->top;
        self->client.right = self->bounds.right - self->style->right;
        self->client.bottom = self->bounds.bottom - self->style->bottom;
    } else {
        self->client.left = self->bounds.left;
        self->client.top = self->bounds.top;
        self->client.right = self->bounds.right;
        self->client.bottom = self->bounds.bottom;
    }
}
