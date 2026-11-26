#include "campaign_channel_constants.h"
#define POSITION_ZERO_AS_FLOAT (*(const float *)&zero_position)
struct PlaybackThresholdChannel {
    unsigned char reserved_00[12];
    float position;
    float end_position;
    unsigned char reserved_14[108];
};
struct PlaybackThresholdMesh {
    unsigned char reserved[0x94];
    struct PlaybackThresholdChannel *channels;
    int count;
};
/* FAKEMATCH: the C fastcall signature wraps the channel's integer array index
   so that it stays on the stack after the mesh receiver. */
struct Index { int value; };

__declspec(noinline) int __fastcall reached_position(struct PlaybackThresholdMesh *mesh, struct Index index, float position)
{
    if (position < POSITION_ZERO_AS_FLOAT || position > mesh->channels[index.value].end_position)
        position = mesh->channels[index.value].end_position;
    if (mesh->count > index.value && index.value >= 0 && mesh->channels[index.value].position >= position)
        return 1;
    return 0;
}

int __fastcall reached_end(struct PlaybackThresholdMesh *mesh, struct Index index)
{
    return reached_position(mesh, index, -1.0f);
}
