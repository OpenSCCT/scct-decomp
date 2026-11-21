// USkeletalMeshInstance vtable slot 44 (vtable 0x30a048): does the animation
// sequence belong to the given group? Same layout as the neighbouring
// accessors in pc/src/versus_animation_sequences.c; this is unused.
struct mesh_instance;
struct animation_sequence {
    int name;
    const int *groups;
    int group_count, group_capacity;
    int start_frame, frame_count;
    float rate;
    const void *notifies;
    int notify_count;
};

extern "C" int __fastcall sequence_has_group(const mesh_instance *self, void *unused, const animation_sequence *clip, int group)
{
    if (!clip)
        return 0;
    for (int i = 0; i < clip->group_count; i++) {
        if (clip->groups[i] == group)
            return 1;
    }
    return 0;
}
