#include "campaign_name_index.h"

struct SequenceGroupList {
    int *names;
    int count;
    int capacity;
    __declspec(noinline) int FindIndex(const Name& name, int& index);
};

int SequenceGroupList::FindIndex(const Name& name, int& index)
{
    for (index = 0; index < count; ++index) {
        if (names[index] == name.value)
            return 1;
    }
    return 0;
}

struct SequenceGroupClip { int name; SequenceGroupList groups; };
struct SequenceGroupClipRef { SequenceGroupClip *ptr; };
struct SequenceGroupOwner {
    int HasSequenceGroup(SequenceGroupClipRef clip, Name name);
};

int SequenceGroupOwner::HasSequenceGroup(SequenceGroupClipRef clip, Name name)
{
    int found = 0;
    return clip.ptr ? clip.ptr->groups.FindIndex(name, found) : 0;
}
