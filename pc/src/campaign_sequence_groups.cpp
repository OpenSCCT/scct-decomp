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
struct SequenceGroupOwner {
    int HasSequenceGroup(SequenceGroupClip *clip, Name name);
};

int SequenceGroupOwner::HasSequenceGroup(SequenceGroupClip *clip, Name name)
{
    int found = 0;
    return clip ? clip->groups.FindIndex(name, found) : 0;
}
