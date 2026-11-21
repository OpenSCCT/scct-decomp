// w4_item_0081.cpp -- Versus RVA 0x146620-0x1466bc

typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned __int64 QWORD;

#pragma pack(push, 4)

class FArray {
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;

    INT Add(INT Count, INT ElementSize);
};

template<class T> class TArray : public FArray {
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Add(INT Count = 1) { return FArray::Add(Count, sizeof(T)); }
    INT AddItem(const T &Item);
};

// TArray<T>::AddItem -- appends a single element to the array and returns its index.
template<class T> INT TArray<T>::AddItem(const T &Item)
{
    INT Index = Add(1);
    (*this)(Index) = Item;
    return Index;
}

// Neutral name; 8-byte element of four 16-bit words copied field-by-field in 0x146620.
struct UnnamedItem_146620 {
    _WORD unk_0;
    _WORD unk_2;
    _WORD unk_4;
    _WORD unk_6;

    UnnamedItem_146620 &operator=(const UnnamedItem_146620 &Other)
    {
        unk_0 = Other.unk_0;
        unk_2 = Other.unk_2;
        unk_4 = Other.unk_4;
        unk_6 = Other.unk_6;
        return *this;
    }
};

extern QWORD GNextCacheID;

// MakeCacheID -- allocates the next unique render resource cache identifier.
inline QWORD MakeCacheID(DWORD Base)
{
    return (GNextCacheID++ * 0x100) + Base;
}

// Neutral name; chain node whose deleting destructor is at 0x146700 (versus_node_chain_deletion.c).
class UnnamedNode_146650 {
public:
    QWORD               CacheId;
    DWORD               unk_0c;
    DWORD               unk_10;
    DWORD               unk_14;
    DWORD               unk_18;
    UnnamedNode_146650 *Next;
    DWORD               unk_20;

    UnnamedNode_146650(DWORD InUnk0c, UnnamedNode_146650 *InNext);
    virtual ~UnnamedNode_146650();
};

// UnnamedNode_146650::UnnamedNode_146650 -- initializes cache ID, next chain link, and zero fields.
UnnamedNode_146650::UnnamedNode_146650(DWORD InUnk0c, UnnamedNode_146650 *InNext)
{
    CacheId = MakeCacheID(0xe1);
    unk_0c  = InUnk0c;
    unk_14  = 0;
    unk_18  = 0;
    Next    = InNext;
    unk_20  = 0;
}

#pragma pack(pop)

// Scaffolding for the link, not part of the units.
void Sink(INT);
void SinkNode(UnnamedNode_146650 *);

void Driver_146620(TArray<UnnamedItem_146620> *Arr, const UnnamedItem_146620 *Item, INT Mode)
{
    Sink(Mode);
    switch (Mode) {
    case 0: Sink(Arr->AddItem(*Item)); break;
    case 1: Sink(Arr->AddItem(*Item)); Sink(1); break;
    case 2: Sink(Arr->AddItem(*Item)); Sink(2); break;
    case 3: Sink(Arr->AddItem(*Item)); Sink(3); break;
    case 4: Sink(Arr->AddItem(*Item)); Sink(4); break;
    case 5: Sink(Arr->AddItem(*Item)); Sink(5); break;
    case 6: Sink(Arr->AddItem(*Item)); Sink(6); break;
    default: Sink(Arr->AddItem(*Item)); break;
    }
}

void Driver_146650(DWORD InUnk0c, UnnamedNode_146650 *InNext, INT Mode)
{
    Sink(Mode);
    switch (Mode) {
    case 0: SinkNode(new UnnamedNode_146650(InUnk0c, InNext)); break;
    case 1: SinkNode(new UnnamedNode_146650(InUnk0c + 1, InNext)); break;
    case 2: SinkNode(new UnnamedNode_146650(InUnk0c + 2, InNext)); break;
    case 3: SinkNode(new UnnamedNode_146650(InUnk0c + 3, InNext)); break;
    case 4: SinkNode(new UnnamedNode_146650(InUnk0c + 4, InNext)); break;
    case 5: SinkNode(new UnnamedNode_146650(InUnk0c + 5, InNext)); break;
    default: SinkNode(new UnnamedNode_146650(InUnk0c + 6, InNext)); break;
    }
}
