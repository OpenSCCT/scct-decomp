#include "campaign_channel_constants.h"
/* FAKEMATCH: the C fastcall signature wraps the channel's integer array index
   so that it stays on the stack after the mesh receiver. */
struct Index { int value; };
struct ChannelActivityMesh;
struct ChannelActivityMethods {
    void *reserved[56];
    int (__fastcall *active)(struct ChannelActivityMesh *, struct Index);
};
struct AnimationPlaybackChannel {
    unsigned sequence;
    unsigned reserved_04;
    float rate;
    float position;
    float end_position;
    float blend_rate;
    unsigned char reserved_18[0x18];
    unsigned field_30;
    unsigned char reserved_34[0x4c];
};
struct ChannelActivityMesh {
    const struct ChannelActivityMethods *methods;
    unsigned char reserved[0x90];
    struct AnimationPlaybackChannel *channels;
    int count;
};

int __fastcall channel_active(struct ChannelActivityMesh *mesh, struct Index index)
{
    if (mesh->count > index.value && index.value >= 0) {
        struct AnimationPlaybackChannel *channel = &mesh->channels[index.value];
        if (channel->sequence) {
            if (channel->position >= zero_rate ? channel->rate != zero_rate : channel->blend_rate != zero_rate)
                return 1;
        }
    }
    return 0;
}

int __fastcall stop_channels(struct ChannelActivityMesh *mesh)
{
    int i;
    for (i = 0; i < mesh->count; ++i) {
        mesh->channels[i].rate = 0;
        mesh->channels[i].blend_rate = 0;
        mesh->channels[i].field_30 = 0;
    }
    return 1;
}

int __fastcall channel_blending(struct ChannelActivityMesh *mesh, struct Index index)
{
    if (mesh->count > index.value && index.value >= 0 &&
        mesh->channels[index.value].position < zero_position &&
        mesh->methods->active(mesh, index))
        return 1;
    return 0;
}
