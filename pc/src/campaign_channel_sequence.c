#include "campaign_name_index.h"
#include "campaign_channel_constants.h"

/* FAKEMATCH: the C fastcall signature wraps the channel's integer array index
   so that it stays on the stack after the mesh receiver. */
struct Index { int value; };
struct Clip;
/* FAKEMATCH: the C virtual call uses a one-pointer wrapper to pass the clip
   address on the stack to the frame-count and rate methods. */
struct ClipRef { struct Clip *ptr; };
struct Bank;
struct BankMethods {
    void *reserved[24];
    struct Clip *(__fastcall *lookup)(struct Bank *, struct Name);
};
struct Bank { const struct BankMethods *methods; };
struct ChannelSequenceEntry {
    struct Name sequence;
    unsigned char reserved_04[0x40];
    unsigned char bank;
    unsigned char reserved_45[0x3b];
};
struct ChannelSequenceMesh;
struct ChannelSequenceMethods {
    void *reserved_00[45];
    struct Clip *(__fastcall *lookup)(struct ChannelSequenceMesh *, struct Name);
    void *reserved_b8[4];
    float (__fastcall *frames)(struct ChannelSequenceMesh *, struct ClipRef);
    float (__fastcall *rate)(struct ChannelSequenceMesh *, struct ClipRef);
};
struct ChannelSequenceMesh {
    const struct ChannelSequenceMethods *methods;
    unsigned char reserved_04[0x74];
    struct Bank **banks;
    unsigned char reserved_7c[0x18];
    struct ChannelSequenceEntry *channels;
};

struct Clip *__fastcall channel_clip(struct ChannelSequenceMesh *mesh, struct Index index)
{
    const struct ChannelSequenceEntry *channel = &mesh->channels[index.value];
    struct Bank *bank = mesh->banks[channel->bank];
    return bank->methods->lookup(bank, channel->sequence);
}

float __fastcall channel_frames(struct ChannelSequenceMesh *mesh, struct Index index)
{
    struct ClipRef clip;
    clip.ptr = mesh->methods->lookup(mesh, mesh->channels[index.value].sequence);
    return clip.ptr ? mesh->methods->frames(mesh, clip) : zero_frames;
}

float __fastcall channel_rate(struct ChannelSequenceMesh *mesh, struct Index index)
{
    struct ClipRef clip;
    clip.ptr = mesh->methods->lookup(mesh, mesh->channels[index.value].sequence);
    return clip.ptr ? mesh->methods->rate(mesh, clip) : missing_rate;
}
