// Work item 0007: Versus RVA 0x4bc0-0x4c49.

// UnnamedClass_4bc0: neutral name. Holds a singly linked list whose head is at
// +0x24; each node links to the next at +0x28 (same layout as the node type).
class UnnamedClass_4bc0
{
public:
    char Pad00[0x24];
    UnnamedClass_4bc0* Children; // +0x24
    UnnamedClass_4bc0* Next;     // +0x28

    int Contains(UnnamedClass_4bc0* Other);
};

// RVA 0x4bc0: true when Other is null or appears in the list.
int UnnamedClass_4bc0::Contains(UnnamedClass_4bc0* Other)
{
    if (Other)
    {
        for (UnnamedClass_4bc0* Node = Children; ; Node = Node->Next)
        {
            if (!Node)
                return 0;
            if (Node == Other)
                break;
        }
    }
    return 1;
}

// RVA 0x4bf0: the compiler's `vector constructor iterator' shape: run a
// thiscall callback over Count elements of Size bytes each.
class UnnamedElement_4bf0
{
public:
    void Construct();
};
typedef void (UnnamedElement_4bf0::*ElementCallback)();

void __stdcall VectorIterator_4bf0(void* Ptr, unsigned Size, int Count, ElementCallback Callback)
{
    while (--Count >= 0)
    {
        (((UnnamedElement_4bf0*)Ptr)->*Callback)();
        Ptr = (char*)Ptr + Size;
    }
}

// RVA 0x4c20 (not written): FDist-style |A - B| for two 3-float vectors, with
// A in EAX and B in ECX. That register pair is a link-time-generated custom
// calling convention, which plain cl /c cannot reproduce.
