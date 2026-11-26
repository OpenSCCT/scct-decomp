#include "campaign_channel_constants.h"
struct Index { int value; };
struct Bit { unsigned value; };
union PlaybackControlFlags {
    unsigned value;
    struct { unsigned lower : 4, fourth : 1, upper : 27; } bits;
};
struct PlaybackControlChannel {
    unsigned char reserved_00[8];
    float rate, position, end_position, blend_rate, field_18;
    unsigned char reserved_1c[8];
    float rate_scale;
    union PlaybackControlFlags flags;
    unsigned reserved_2c;
    float weight;
    unsigned char reserved_34[8];
    float field_3c;
    unsigned char reserved_40[0x40];
};
struct PlaybackControlMesh {
    unsigned char reserved_00[0x94];
    struct PlaybackControlChannel *channels;
    int count;
    unsigned char reserved_9c[0x248];
    float step;
};
static __forceinline int valid(const struct PlaybackControlMesh *mesh, int index)
{
    return index >= 0 && index < mesh->count;
}
void __fastcall set_rate(struct PlaybackControlMesh *mesh, struct Index index, float value)
{
    if (valid(mesh, index.value)) {
        struct PlaybackControlChannel *channel = &mesh->channels[index.value];
        channel->rate = value * channel->rate_scale;
    }
}
void __fastcall set_weight(struct PlaybackControlMesh *mesh, struct Index index, float value)
{
    if (valid(mesh, index.value)) {
        struct PlaybackControlChannel *channel = &mesh->channels[index.value];
        channel->weight = value < zero_value ? zero_value : value < unit_value ? value : unit_value;
    }
}
void __fastcall set_flag_four(struct PlaybackControlMesh *mesh, struct Index index, struct Bit bit)
{
    if (valid(mesh, index.value)) {
        struct PlaybackControlChannel *channel = &mesh->channels[index.value];
        channel->flags.bits.fourth = bit.value;
    }
}
float __fastcall optional_field_3c(const struct PlaybackControlMesh *mesh, struct Index index)
{
    if (valid(mesh, index.value)) {
        const struct PlaybackControlChannel *channel = &mesh->channels[index.value];
        if (channel->flags.value & 0x400)
            return channel->field_3c;
    }
    return zero_value;
}
float __fastcall advance_position(const struct PlaybackControlMesh *mesh, struct Index index, float position)
{
    if (valid(mesh, index.value)) {
        const struct PlaybackControlChannel *channel = &mesh->channels[index.value];
        if (!(channel->flags.value & 0xc0))
            return position + mesh->step * channel->rate;
    }
    return position;
}
