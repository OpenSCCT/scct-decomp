struct FlagQueryChannel {
    unsigned sequence;
    unsigned char reserved_04[0x24];
    unsigned flags;
    unsigned char reserved_2c[0x54];
};
struct FlagQueryMesh {
    unsigned char reserved[0x94];
    struct FlagQueryChannel *channels;
    int count;
};
/* FAKEMATCH: the C fastcall signature wraps the channel's integer array index
   so that it stays on the stack after the mesh receiver. */
struct Index { int value; };
/* FAKEMATCH: this C argument wrapper puts the result address on the stack. */
struct Output { unsigned *name; };
static __forceinline int valid(const struct FlagQueryMesh *mesh, int i)
{
    return mesh->count > i && i >= 0;
}
int __fastcall channel_flag_one(const struct FlagQueryMesh *mesh, struct Index index)
{
    return valid(mesh, index.value) ? (mesh->channels[index.value].flags >> 1) & 1u : 0;
}
int __fastcall channel_flag_four(const struct FlagQueryMesh *mesh, struct Index index)
{
    return valid(mesh, index.value) ? (mesh->channels[index.value].flags >> 4) & 1u : 0;
}
int __fastcall clear_channel_flags(struct FlagQueryMesh *mesh, struct Index index)
{
    if (valid(mesh, index.value)) {
        mesh->channels[index.value].flags &= ~2u;
        mesh->channels[index.value].flags &= ~1u;
        return 1;
    }
    return 0;
}
unsigned *__fastcall channel_sequence_name(const struct FlagQueryMesh *mesh, struct Output output, struct Index index)
{
    if (index.value >= 0 && index.value < mesh->count) {
        *output.name = mesh->channels[index.value].sequence;
        return output.name;
    }
    *output.name = 0;
    return output.name;
}
