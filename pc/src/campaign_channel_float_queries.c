#include "campaign_channel_constants.h"

struct Channel {
    unsigned char unk_00[8];
    float rate;
    float position;
    float end_position;
    unsigned char unk_14[4];
    float unk_18;
    unsigned char unk_1c[20];
    float unk_30;
    unsigned char unk_34[12];
    float unk_40;
    unsigned char unk_44[60];
};
/* Descriptive local layout view; the retail class name is not recovered. */
struct ChannelMeshView { unsigned char unk_00[0x94]; struct Channel *channels; int count; };
/* FAKEMATCH: the C fastcall signature wraps the channel's integer array index
   so that it stays on the stack after the mesh receiver. */
struct Index { int value; };

#define CHANNEL_QUERY(Entry, Field) \
    float __fastcall Entry(const struct ChannelMeshView *mesh, struct Index index) \
    { \
        if (index.value >= 0 && index.value < mesh->count) \
            return mesh->channels[index.value].Field; \
        return zero_value; \
    }

CHANNEL_QUERY(query_0d5280, end_position)
CHANNEL_QUERY(query_0d52e0, rate)
CHANNEL_QUERY(query_0d5380, unk_30)
CHANNEL_QUERY(query_0d53b0, unk_40)
CHANNEL_QUERY(query_0d5540, position)
CHANNEL_QUERY(query_0d5570, end_position)
CHANNEL_QUERY(query_0d55a0, unk_18)
