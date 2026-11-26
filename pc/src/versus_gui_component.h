// versus_gui_component.h -- shared component layout from GUI access sites
#ifndef VERSUS_GUI_COMPONENT_H
#define VERSUS_GUI_COMPONENT_H

struct gui_component;
struct gui_context;
struct style_border;
struct font;

struct rectangle {
    float left, top, right, bottom;
};

struct color {
    unsigned char blue, green, red, alpha;
};

typedef float (__fastcall *gui_dimension_query)(struct gui_component *);

struct gui_component_methods {
    void *unk_00[26];
    gui_dimension_query width, height, left, top;
};

struct gui_component {
    const struct gui_component_methods *methods;
    unsigned char unk_04[0x24];
    const struct gui_context *context;
    struct gui_component *parent;
    unsigned char unk_30[0x2c];
    unsigned int bound_to_parent : 1;
    unsigned int scale_to_parent : 1;
    unsigned char unk_60[0x10];
    float top, left, width, height;
    unsigned char unk_80[0x1c];
    const struct style_border *style;
    struct rectangle bounds, client;
    unsigned char unk_c0[0x14];
    float saved_x, saved_y;
    struct color saved_color;
    struct font *saved_font;
    unsigned char saved_style;
};

#endif
