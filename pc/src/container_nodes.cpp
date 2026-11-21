// Node allocation for the engine's std::list and std::map/std::set instances
// (Dinkumware VC7.1 list::_Buynode and _Tree::_Buynode) over the engine heap.
// Each routine allocates a node, builds its links inside a catch-all region,
// and returns the block to the allocator before rethrowing.
typedef unsigned int size_t;
inline void *operator new(size_t, void *where) { return where; }

struct HeapTag;
extern const HeapTag ListNodeTag;
extern "C" void *CurrentHeap();
extern "C" void *HeapAllocate(void *heap, size_t size, const HeapTag *tag, int line, int kind);

template<class T1, class T2> inline void ConstructValue(T1 *where, const T2 &value)
{
    new ((void *)where) T1(value);
}

template<class T> struct EngineAllocator
{
    T *allocate(size_t count) { return (T *)HeapAllocate(CurrentHeap(), count * sizeof(T), &ListNodeTag, 0, 7); }
    void deallocate(T *block, size_t count);  // out of line in the engine
    void construct(T *where, const T &value) { ConstructValue(where, value); }
    void destroy(T *) {}
};

// Element storage of a given size whose copy constructor is out of line.
template<size_t Size> struct Element
{
    Element(const Element &other);
    char bytes[Size];
};

// Element storage that needs eight-byte alignment (it starts with a double).
template<size_t Size> struct WideElement
{
    WideElement(const WideElement &other);
    double first;
    char rest[Size - 8];
};

// ----- std::list -----

template<size_t ValueSize> struct ListNode
{
    ListNode(ListNode *next, ListNode *prev, const Element<ValueSize> &value);  // out of line
    ListNode *next;
    ListNode *prev;
    Element<ValueSize> value;
};

// A list of pointers or handles: the node constructor is inlined.
struct WordListNode
{
    WordListNode(WordListNode *next_, WordListNode *prev_, const int &value_) : next(next_), prev(prev_), value(value_) {}
    WordListNode *next;
    WordListNode *prev;
    int value;
};

template<class Node, class Value> struct ListStorage
{
    EngineAllocator<Node> nodes;
    EngineAllocator<Node *> links;
    Node *head;
    size_t count;

    Node *BuyHeadNode();
    Node *BuyNode(Node *next, Node *prev, const Value &value);
};

template<class Node, class Value> Node *ListStorage<Node, Value>::BuyHeadNode()
{
    Node *node = nodes.allocate(1);
    int linked = 0;
    try
    {
        links.construct(&node->next, node);
        ++linked;
        links.construct(&node->prev, node);
    }
    catch (...)
    {
        if (0 < linked)
            links.destroy(&node->next);
        nodes.deallocate(node, 1);
        throw;
    }
    return node;
}

template<class Node, class Value> Node *ListStorage<Node, Value>::BuyNode(Node *next, Node *prev, const Value &value)
{
    Node *node = nodes.allocate(1);
    try
    {
        new ((void *)node) Node(next, prev, value);
    }
    catch (...)
    {
        nodes.deallocate(node, 1);
        throw;
    }
    return node;
}

// ----- std::map / std::set -----

enum { Red, Black };

template<class Value> struct TreeNode
{
    TreeNode(TreeNode *left, TreeNode *parent, TreeNode *right, const Value &value, char color);  // out of line
    TreeNode *left;
    TreeNode *parent;
    TreeNode *right;
    Value value;
    char color;
    char isnil;
};

struct EmptyCompare {};

template<class Value> struct TreeStorage
{
    typedef TreeNode<Value> Node;
    EmptyCompare compare;
    EngineAllocator<Node> nodes;
    EngineAllocator<Node *> links;
    Node *head;
    size_t count;

    Node *BuyHeadNode();
    Node *BuyNode(Node *left, Node *parent, Node *right, const Value &value, char color);
};

template<class Value> typename TreeStorage<Value>::Node *TreeStorage<Value>::BuyHeadNode()
{
    Node *node = nodes.allocate(1);
    int linked = 0;
    try
    {
        links.construct(&node->left, 0);
        ++linked;
        links.construct(&node->parent, 0);
        ++linked;
        links.construct(&node->right, 0);
    }
    catch (...)
    {
        if (1 < linked)
            links.destroy(&node->parent);
        if (0 < linked)
            links.destroy(&node->left);
        nodes.deallocate(node, 1);
        throw;
    }
    node->color = Black;
    node->isnil = false;
    return node;
}

template<class Value> typename TreeStorage<Value>::Node *TreeStorage<Value>::BuyNode(
    Node *left, Node *parent, Node *right, const Value &value, char color)
{
    Node *node = nodes.allocate(1);
    try
    {
        new ((void *)node) Node(left, parent, right, value, color);
    }
    catch (...)
    {
        nodes.deallocate(node, 1);
        throw;
    }
    return node;
}

template struct ListStorage<WordListNode, int>;
template struct ListStorage<ListNode<0x04>, Element<0x04> >;
template struct ListStorage<ListNode<0x08>, Element<0x08> >;
template struct ListStorage<ListNode<0x0c>, Element<0x0c> >;
template struct ListStorage<ListNode<0x10>, Element<0x10> >;
template struct ListStorage<ListNode<0x38>, Element<0x38> >;
template struct TreeStorage<Element<0x08> >;
template struct TreeStorage<Element<0x0c> >;
template struct TreeStorage<Element<0x14> >;
template struct TreeStorage<Element<0x24> >;
template struct TreeStorage<Element<0x88> >;
template struct TreeStorage<WideElement<0x10> >;
