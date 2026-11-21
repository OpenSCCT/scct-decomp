// Ordered red-black tree behind the engine's map and set containers.
//
// The head node doubles as the nil sentinel: its Parent is the root, its Left
// the smallest element and its Right the largest. Every empty link points at
// the head. Container errors are ignored, as in the shipped game.
namespace stl {

template<class T> struct Less {
    bool operator()(const T &A, const T &B) const { return A < B; }
};

template<class A, class B> struct Pair {
    Pair() : First(A()), Second(B()) {}
    Pair(const A &InFirst, const B &InSecond) : First(InFirst), Second(InSecond) {}
    template<class C, class D> Pair(const Pair<C, D> &Other) : First(Other.First), Second(Other.Second) {}
    A First;
    B Second;
};

// Map elements are (key, value) pairs ordered by key.
template<class K, class V, class Cmp, bool Multi> class MapTraits {
public:
    typedef K KeyType;
    typedef Pair<const K, V> ValueType;
    typedef Cmp KeyCompare;
    enum { IsMulti = Multi };
    MapTraits() : Comp() {}
    static const K &KeyOf(const ValueType &Value) { return Value.First; }
    Cmp Comp;
};

// Set elements are their own keys.
template<class K, class Cmp, bool Multi> class SetTraits {
public:
    typedef K KeyType;
    typedef K ValueType;
    typedef Cmp KeyCompare;
    enum { IsMulti = Multi };
    SetTraits() : Comp() {}
    static const K &KeyOf(const ValueType &Value) { return Value; }
    Cmp Comp;
};

template<class Traits, template<class> class Alloc> class Tree : public Traits {
public:
    typedef typename Traits::KeyType KeyType;
    typedef typename Traits::ValueType ValueType;
    typedef size_t SizeType;
    enum Colour { Red, Black };

    struct Node {
        Node(Node *InLeft, Node *InParent, Node *InRight, const ValueType &InValue, char InColour)
            : Left(InLeft), Parent(InParent), Right(InRight), Value(InValue), Colour(InColour), IsNil(false) {}
        Node *Left;
        Node *Parent;
        Node *Right;
        ValueType Value;
        char Colour;
        char IsNil;
    };
    typedef Node *NodePtr;

protected:
    static char &ColourOf(NodePtr N) { return N->Colour; }
    static char &IsNil(NodePtr N) { return N->IsNil; }
    static const KeyType &Key(NodePtr N) { return Traits::KeyOf(N->Value); }
    static NodePtr &Left(NodePtr N) { return N->Left; }
    static NodePtr &Parent(NodePtr N) { return N->Parent; }
    static NodePtr &Right(NodePtr N) { return N->Right; }
    static ValueType &Value(NodePtr N) { return N->Value; }

public:
    class ConstIterator {
    public:
        ConstIterator() : Ptr(0) {}
        ConstIterator(NodePtr N) : Ptr(N) {}
        const ValueType &operator*() const { return Value(Ptr); }
        const ValueType *operator->() const { return &**this; }
        ConstIterator &operator++() { Inc(); return *this; }
        ConstIterator operator++(int) { ConstIterator Old = *this; ++*this; return Old; }
        ConstIterator &operator--() { Dec(); return *this; }
        ConstIterator operator--(int) { ConstIterator Old = *this; --*this; return Old; }
        bool operator==(const ConstIterator &Other) const { return Ptr == Other.Ptr; }
        bool operator!=(const ConstIterator &Other) const { return !(*this == Other); }
        // Step to the previous element; from the head, to the largest.
        void Dec() {
            if (IsNil(Ptr))
                Ptr = Right(Ptr);
            else if (!IsNil(Left(Ptr)))
                Ptr = Max(Left(Ptr));
            else {
                NodePtr Up;
                while (!IsNil(Up = Parent(Ptr)) && Ptr == Left(Up))
                    Ptr = Up;
                if (!IsNil(Up))
                    Ptr = Up;
            }
        }
        // Step to the next element; past the largest, to the head.
        void Inc() {
            if (IsNil(Ptr))
                ;
            else if (!IsNil(Right(Ptr)))
                Ptr = Min(Right(Ptr));
            else {
                NodePtr Up;
                while (!IsNil(Up = Parent(Ptr)) && Ptr == Right(Up))
                    Ptr = Up;
                Ptr = Up;
            }
        }
        NodePtr GetNode() const { return Ptr; }
    protected:
        NodePtr Ptr;
    };

    class Iterator : public ConstIterator {
    public:
        Iterator() {}
        Iterator(NodePtr N) : ConstIterator(N) {}
        ValueType &operator*() const { return (ValueType &)**(ConstIterator *)this; }
        ValueType *operator->() const { return &**this; }
        Iterator &operator++() { ++(*(ConstIterator *)this); return *this; }
        Iterator operator++(int) { Iterator Old = *this; ++*this; return Old; }
        Iterator &operator--() { --(*(ConstIterator *)this); return *this; }
        Iterator operator--(int) { Iterator Old = *this; --*this; return Old; }
    };

    typedef Pair<Iterator, bool> PairIb;
    typedef Pair<Iterator, Iterator> PairIi;

    Tree() { Init(); }
    Tree(const Tree &Other) { Init(); CopyFrom(Other); }
    ~Tree() { Tidy(); }
    Tree &operator=(const Tree &Other) {
        if (this != &Other) {
            Erase(Begin(), End());
            this->Comp = Other.Comp;
            CopyFrom(Other);
        }
        return *this;
    }

    Iterator Begin() { return Iterator(Lmost()); }
    ConstIterator Begin() const { return ConstIterator(Lmost()); }
    Iterator End() { return Iterator(Head); }
    ConstIterator End() const { return ConstIterator(Head); }
    SizeType Size() const { return Count; }
    bool Empty() const { return Size() == 0; }

    // Insert unless an equal key exists (or always, for multi containers).
    PairIb Insert(const ValueType &Val) {
        NodePtr Try = Root();
        NodePtr Where = Head;
        bool AddLeft = true;
        while (!IsNil(Try)) {
            Where = Try;
            AddLeft = this->Comp(Traits::KeyOf(Val), Key(Try));
            Try = AddLeft ? Left(Try) : Right(Try);
        }
        if (this->IsMulti)
            return PairIb(InsertAt(AddLeft, Where, Val), true);
        else {
            Iterator It = Iterator(Where);
            if (!AddLeft)
                ;
            else if (It == Begin())
                return PairIb(InsertAt(true, Where, Val), true);
            else
                --It;
            if (this->Comp(Key(It.GetNode()), Traits::KeyOf(Val)))
                return PairIb(InsertAt(AddLeft, Where, Val), true);
            else
                return PairIb(It, false);
        }
    }

    // Insert using Hint when it is next to the right place.
    Iterator Insert(Iterator Hint, const ValueType &Val) {
        Iterator Next;
        if (Size() == 0)
            return InsertAt(true, Head, Val);
        else if (this->IsMulti) {
            if (Hint == Begin()) {
                if (!this->Comp(Key(Hint.GetNode()), Traits::KeyOf(Val)))
                    return InsertAt(true, Hint.GetNode(), Val);
            } else if (Hint == End()) {
                if (!this->Comp(Traits::KeyOf(Val), Key(Rmost())))
                    return InsertAt(false, Rmost(), Val);
            } else if (!this->Comp(Key(Hint.GetNode()), Traits::KeyOf(Val))
                       && !this->Comp(Traits::KeyOf(Val), Key((--(Next = Hint)).GetNode()))) {
                if (IsNil(Right(Next.GetNode())))
                    return InsertAt(false, Next.GetNode(), Val);
                else
                    return InsertAt(true, Hint.GetNode(), Val);
            } else if (!this->Comp(Traits::KeyOf(Val), Key(Hint.GetNode()))
                       && (++(Next = Hint) == End()
                           || !this->Comp(Key(Next.GetNode()), Traits::KeyOf(Val)))) {
                if (IsNil(Right(Hint.GetNode())))
                    return InsertAt(false, Hint.GetNode(), Val);
                else
                    return InsertAt(true, Next.GetNode(), Val);
            }
        } else {
            if (Hint == Begin()) {
                if (this->Comp(Traits::KeyOf(Val), Key(Hint.GetNode())))
                    return InsertAt(true, Hint.GetNode(), Val);
            } else if (Hint == End()) {
                if (this->Comp(Key(Rmost()), Traits::KeyOf(Val)))
                    return InsertAt(false, Rmost(), Val);
            } else if (this->Comp(Traits::KeyOf(Val), Key(Hint.GetNode()))
                       && this->Comp(Key((--(Next = Hint)).GetNode()), Traits::KeyOf(Val))) {
                if (IsNil(Right(Next.GetNode())))
                    return InsertAt(false, Next.GetNode(), Val);
                else
                    return InsertAt(true, Hint.GetNode(), Val);
            } else if (this->Comp(Key(Hint.GetNode()), Traits::KeyOf(Val))
                       && (++(Next = Hint) == End()
                           || this->Comp(Traits::KeyOf(Val), Key(Next.GetNode())))) {
                if (IsNil(Right(Hint.GetNode())))
                    return InsertAt(false, Hint.GetNode(), Val);
                else
                    return InsertAt(true, Next.GetNode(), Val);
            }
        }
        return Insert(Val).First;
    }

    // Unlink one node, rebalance, free it, and return its successor.
    Iterator Erase(Iterator Where) {
        NodePtr Erased = Where.GetNode();
        ++Where;
        NodePtr Fix;
        NodePtr FixParent;
        NodePtr N = Erased;
        if (IsNil(Left(N)))
            Fix = Right(N);
        else if (IsNil(Right(N)))
            Fix = Left(N);
        else {
            N = Where.GetNode();
            Fix = Right(N);
        }
        if (N == Erased) {
            FixParent = Parent(Erased);
            if (!IsNil(Fix))
                Parent(Fix) = FixParent;
            if (Root() == Erased)
                Root() = Fix;
            else if (Left(FixParent) == Erased)
                Left(FixParent) = Fix;
            else
                Right(FixParent) = Fix;
            if (Lmost() == Erased)
                Lmost() = IsNil(Fix) ? FixParent : Min(Fix);
            if (Rmost() == Erased)
                Rmost() = IsNil(Fix) ? FixParent : Max(Fix);
        } else {
            // The successor N takes the erased node's place.
            Parent(Left(Erased)) = N;
            Left(N) = Left(Erased);
            if (N == Right(Erased))
                FixParent = N;
            else {
                FixParent = Parent(N);
                if (!IsNil(Fix))
                    Parent(Fix) = FixParent;
                Left(FixParent) = Fix;
                Right(N) = Right(Erased);
                Parent(Right(Erased)) = N;
            }
            if (Root() == Erased)
                Root() = N;
            else if (Left(Parent(Erased)) == Erased)
                Left(Parent(Erased)) = N;
            else
                Right(Parent(Erased)) = N;
            Parent(N) = Parent(Erased);
            char Swap = ColourOf(N);
            ColourOf(N) = ColourOf(Erased);
            ColourOf(Erased) = Swap;
        }
        if (ColourOf(Erased) == Black) {
            for (; Fix != Root() && ColourOf(Fix) == Black; FixParent = Parent(Fix))
                if (Fix == Left(FixParent)) {
                    N = Right(FixParent);
                    if (ColourOf(N) == Red) {
                        ColourOf(N) = Black;
                        ColourOf(FixParent) = Red;
                        Lrotate(FixParent);
                        N = Right(FixParent);
                    }
                    if (IsNil(N))
                        Fix = FixParent;
                    else if (ColourOf(Left(N)) == Black && ColourOf(Right(N)) == Black) {
                        ColourOf(N) = Red;
                        Fix = FixParent;
                    } else {
                        if (ColourOf(Right(N)) == Black) {
                            ColourOf(Left(N)) = Black;
                            ColourOf(N) = Red;
                            Rrotate(N);
                            N = Right(FixParent);
                        }
                        ColourOf(N) = ColourOf(FixParent);
                        ColourOf(FixParent) = Black;
                        ColourOf(Right(N)) = Black;
                        Lrotate(FixParent);
                        break;
                    }
                } else {
                    N = Left(FixParent);
                    if (ColourOf(N) == Red) {
                        ColourOf(N) = Black;
                        ColourOf(FixParent) = Red;
                        Rrotate(FixParent);
                        N = Left(FixParent);
                    }
                    if (IsNil(N))
                        Fix = FixParent;
                    else if (ColourOf(Right(N)) == Black && ColourOf(Left(N)) == Black) {
                        ColourOf(N) = Red;
                        Fix = FixParent;
                    } else {
                        if (ColourOf(Left(N)) == Black) {
                            ColourOf(Right(N)) = Black;
                            ColourOf(N) = Red;
                            Lrotate(N);
                            N = Left(FixParent);
                        }
                        ColourOf(N) = ColourOf(FixParent);
                        ColourOf(FixParent) = Black;
                        ColourOf(Left(N)) = Black;
                        Rrotate(FixParent);
                        break;
                    }
                }
            ColourOf(Fix) = Black;
        }
        NodeAlloc.destroy(Erased);
        NodeAlloc.Deallocate(Erased, 1);
        if (0 < Count)
            --Count;
        return Where;
    }

    Iterator Erase(Iterator First, Iterator Last) {
        if (First == Begin() && Last == End()) {
            Clear();
            return Begin();
        } else {
            while (First != Last)
                Erase(First++);
            return First;
        }
    }

    SizeType Erase(const KeyType &K) {
        PairIi Range = EqualRange(K);
        SizeType Num = 0;
        for (Iterator It = Range.First; It != Range.Second; ++It)
            ++Num;
        Erase(Range.First, Range.Second);
        return Num;
    }

    void Clear() {
        EraseSubtree(Root());
        Root() = Head, Count = 0;
        Lmost() = Head, Rmost() = Head;
    }

    Iterator Find(const KeyType &K) {
        Iterator Where = LowerBound(K);
        return Where == End() || this->Comp(K, Key(Where.GetNode())) ? End() : Where;
    }
    ConstIterator Find(const KeyType &K) const {
        ConstIterator Where = LowerBound(K);
        return Where == End() || this->Comp(K, Key(Where.GetNode())) ? End() : Where;
    }
    Iterator LowerBound(const KeyType &K) { return Iterator(Lbound(K)); }
    ConstIterator LowerBound(const KeyType &K) const { return ConstIterator(Lbound(K)); }
    Iterator UpperBound(const KeyType &K) { return Iterator(Ubound(K)); }
    ConstIterator UpperBound(const KeyType &K) const { return ConstIterator(Ubound(K)); }
    PairIi EqualRange(const KeyType &K) { return PairIi(LowerBound(K), UpperBound(K)); }

protected:
    void CopyFrom(const Tree &Other) {
        Root() = CopySubtree(Other.Root(), Head);
        Count = Other.Size();
        if (!IsNil(Root())) {
            Lmost() = Min(Root());
            Rmost() = Max(Root());
        } else
            Lmost() = Head, Rmost() = Head;
    }

    NodePtr CopySubtree(NodePtr From, NodePtr Where) {
        NodePtr NewRoot = Head;
        if (!IsNil(From)) {
            NodePtr N = BuyNode(Head, Where, Head, Value(From), ColourOf(From));
            if (IsNil(NewRoot))
                NewRoot = N;
            Left(N) = CopySubtree(Left(From), N);
            Right(N) = CopySubtree(Right(From), N);
        }
        return NewRoot;
    }

    // Free a subtree: recurse right, loop left.
    void EraseSubtree(NodePtr Top) {
        for (NodePtr N = Top; !IsNil(N); Top = N) {
            EraseSubtree(Right(N));
            N = Left(N);
            NodeAlloc.destroy(Top);
            NodeAlloc.Deallocate(Top, 1);
        }
    }

    void Init() {
        Head = BuyNode();
        IsNil(Head) = true;
        Root() = Head;
        Lmost() = Head, Rmost() = Head;
        Count = 0;
    }

    // Link a new red node under Where, then restore the colour rules.
    Iterator InsertAt(bool AddLeft, NodePtr Where, const ValueType &Val) {
        NodePtr NewNode = BuyNode(Head, Where, Head, Val, Red);
        ++Count;
        if (Where == Head) {
            Root() = NewNode;
            Lmost() = NewNode, Rmost() = NewNode;
        } else if (AddLeft) {
            Left(Where) = NewNode;
            if (Where == Lmost())
                Lmost() = NewNode;
        } else {
            Right(Where) = NewNode;
            if (Where == Rmost())
                Rmost() = NewNode;
        }
        for (NodePtr N = NewNode; ColourOf(Parent(N)) == Red; )
            if (Parent(N) == Left(Parent(Parent(N)))) {
                Where = Right(Parent(Parent(N)));
                if (ColourOf(Where) == Red) {
                    ColourOf(Parent(N)) = Black;
                    ColourOf(Where) = Black;
                    ColourOf(Parent(Parent(N))) = Red;
                    N = Parent(Parent(N));
                } else {
                    if (N == Right(Parent(N))) {
                        N = Parent(N);
                        Lrotate(N);
                    }
                    ColourOf(Parent(N)) = Black;
                    ColourOf(Parent(Parent(N))) = Red;
                    Rrotate(Parent(Parent(N)));
                }
            } else {
                Where = Left(Parent(Parent(N)));
                if (ColourOf(Where) == Red) {
                    ColourOf(Parent(N)) = Black;
                    ColourOf(Where) = Black;
                    ColourOf(Parent(Parent(N))) = Red;
                    N = Parent(Parent(N));
                } else {
                    if (N == Left(Parent(N))) {
                        N = Parent(N);
                        Rrotate(N);
                    }
                    ColourOf(Parent(N)) = Black;
                    ColourOf(Parent(Parent(N))) = Red;
                    Lrotate(Parent(Parent(N)));
                }
            }
        ColourOf(Root()) = Black;
        return Iterator(NewNode);
    }

    // First node whose key is not less than K, or the head.
    NodePtr Lbound(const KeyType &K) const {
        NodePtr N = Root();
        NodePtr Where = Head;
        while (!IsNil(N))
            if (this->Comp(Key(N), K))
                N = Right(N);
            else {
                Where = N;
                N = Left(N);
            }
        return Where;
    }

    // First node whose key is greater than K, or the head.
    NodePtr Ubound(const KeyType &K) const {
        NodePtr N = Root();
        NodePtr Where = Head;
        while (!IsNil(N))
            if (this->Comp(K, Key(N))) {
                Where = N;
                N = Left(N);
            } else
                N = Right(N);
        return Where;
    }

    NodePtr &Lmost() const { return Left(Head); }
    NodePtr &Rmost() const { return Right(Head); }
    NodePtr &Root() const { return Parent(Head); }

    void Lrotate(NodePtr Where) {
        NodePtr N = Right(Where);
        Right(Where) = Left(N);
        if (!IsNil(Left(N)))
            Parent(Left(N)) = Where;
        Parent(N) = Parent(Where);
        if (Where == Root())
            Root() = N;
        else if (Where == Left(Parent(Where)))
            Left(Parent(Where)) = N;
        else
            Right(Parent(Where)) = N;
        Left(N) = Where;
        Parent(Where) = N;
    }

    void Rrotate(NodePtr Where) {
        NodePtr N = Left(Where);
        Left(Where) = Right(N);
        if (!IsNil(Right(N)))
            Parent(Right(N)) = Where;
        Parent(N) = Parent(Where);
        if (Where == Root())
            Root() = N;
        else if (Where == Right(Parent(Where)))
            Right(Parent(Where)) = N;
        else
            Left(Parent(Where)) = N;
        Right(N) = Where;
        Parent(Where) = N;
    }

    static NodePtr Max(NodePtr N) {
        while (!IsNil(Right(N)))
            N = Right(N);
        return N;
    }
    static NodePtr Min(NodePtr N) {
        while (!IsNil(Left(N)))
            N = Left(N);
        return N;
    }

    // The head node: null links, black, not yet marked nil.
    NodePtr BuyNode() {
        NodePtr N = NodeAlloc.Allocate(1);
        PtrAlloc.construct(&Left(N), 0);
        PtrAlloc.construct(&Parent(N), 0);
        PtrAlloc.construct(&Right(N), 0);
        ColourOf(N) = Black;
        IsNil(N) = false;
        return N;
    }
    NodePtr BuyNode(NodePtr L, NodePtr P, NodePtr R, const ValueType &Val, char C) {
        NodePtr N = NodeAlloc.Allocate(1);
        new ((void *)N) Node(L, P, R, Val, C);
        return N;
    }

    void Tidy() {
        Erase(Begin(), End());
        PtrAlloc.destroy(&Left(Head));
        PtrAlloc.destroy(&Parent(Head));
        PtrAlloc.destroy(&Right(Head));
        NodeAlloc.Deallocate(Head, 1);
        Head = 0, Count = 0;
    }

    Alloc<Node> NodeAlloc;
    Alloc<NodePtr> PtrAlloc;
    Alloc<ValueType> ValAlloc;
    NodePtr Head;
    SizeType Count;
};

template<class K, class V, template<class> class A, class Cmp = Less<K> >
class Map : public Tree<MapTraits<K, V, Cmp, false>, A> {
public:
    typedef Tree<MapTraits<K, V, Cmp, false>, A> Super;
    typedef typename Super::Iterator Iterator;
    typedef typename Super::ValueType ValueType;
    // Find K, inserting a default value when absent.
    V &operator[](const K &Key) {
        Iterator Where = this->LowerBound(Key);
        if (Where == this->End() || this->Comp(Key, this->Key(Where.GetNode())))
            Where = this->Insert(Where, ValueType(Key, V()));
        return (*Where).Second;
    }
};

template<class K, class V, template<class> class A, class Cmp = Less<K> >
class MultiMap : public Tree<MapTraits<K, V, Cmp, true>, A> {};

template<class K, template<class> class A, class Cmp = Less<K> >
class Set : public Tree<SetTraits<K, Cmp, false>, A> {};

template<class K, template<class> class A, class Cmp = Less<K> >
class MultiSet : public Tree<SetTraits<K, Cmp, true>, A> {};

} // namespace stl
inline void *operator new(size_t, void *Where) { return Where; }
typedef unsigned short TCHAR;
void *operator new(size_t Size, const TCHAR *Tag);
void operator delete(void *Ptr);
extern const TCHAR *GContainerTag;

// Allocates container storage from the engine heap.
template<class T> class TContainerAllocator {
public:
    T *Allocate(size_t Count) { return (T *)operator new(Count * sizeof(T), GContainerTag); }
    void Deallocate(T *Ptr, size_t) { operator delete(Ptr); }
    void construct(T *Ptr, const T &Value) { new ((void *)Ptr) T(Value); }
    void destroy(T *Ptr) { Ptr->~T(); }
    size_t MaxSize() const { size_t Count = (size_t)-1 / sizeof(T); return 0 < Count ? Count : 1; }
};

struct FItem_4219a0 { int Words[7]; };
template class stl::Tree<stl::MapTraits<int, FItem_4219a0, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4219a0, TContainerAllocator>;
struct FItem_4501d0 { int Words[9]; };
template class stl::Tree<stl::MapTraits<int, FItem_4501d0, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4501d0, TContainerAllocator>;
struct FItem_48a6c0 { int Words[1]; };
template class stl::Tree<stl::MapTraits<int, FItem_48a6c0, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_48a6c0, TContainerAllocator>;
struct FItem_48d990 { int Words[2]; };
template class stl::Tree<stl::MapTraits<int, FItem_48d990, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_48d990, TContainerAllocator>;
struct FItem_497030 { int Words[1]; };
template class stl::Tree<stl::MapTraits<int, FItem_497030, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_497030, TContainerAllocator>;
struct FItem_499e10 { int Words[1]; };
template class stl::Tree<stl::MapTraits<int, FItem_499e10, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_499e10, TContainerAllocator>;
struct FItem_4a0150 { int Words[1]; };
template class stl::Tree<stl::MapTraits<int, FItem_4a0150, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4a0150, TContainerAllocator>;
struct FItem_4a3e90 { int Words[1]; };
template class stl::Tree<stl::MapTraits<int, FItem_4a3e90, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4a3e90, TContainerAllocator>;
struct FItem_4a6890 { int Words[1]; };
template class stl::Tree<stl::MapTraits<int, FItem_4a6890, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4a6890, TContainerAllocator>;
struct FItem_4ac700 { int Words[4]; };
template class stl::Tree<stl::MapTraits<int, FItem_4ac700, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4ac700, TContainerAllocator>;
struct FItem_4afff0 { int Words[1]; };
template class stl::Tree<stl::MapTraits<int, FItem_4afff0, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4afff0, TContainerAllocator>;
struct FItem_4b0bd0 { int Words[4]; };
template class stl::Tree<stl::MapTraits<int, FItem_4b0bd0, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4b0bd0, TContainerAllocator>;
struct FItem_4c07f0 { int Words[1]; };
template class stl::Tree<stl::MapTraits<int, FItem_4c07f0, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4c07f0, TContainerAllocator>;
struct FItem_4c6390 { int Words[1]; };
template class stl::Tree<stl::MapTraits<int, FItem_4c6390, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4c6390, TContainerAllocator>;
struct FItem_4cb790 { int Words[1]; };
template class stl::Tree<stl::MapTraits<int, FItem_4cb790, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4cb790, TContainerAllocator>;
struct FItem_4cb890 { int Words[1]; };
template class stl::Tree<stl::MapTraits<int, FItem_4cb890, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4cb890, TContainerAllocator>;
struct FItem_4d06e0 { int Words[32]; };
template class stl::Tree<stl::MapTraits<int, FItem_4d06e0, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4d06e0, TContainerAllocator>;
struct FItem_4d4a50 { int Words[8]; };
template class stl::Tree<stl::MapTraits<int, FItem_4d4a50, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4d4a50, TContainerAllocator>;
struct FItem_4d83f0 { int Words[1]; };
template class stl::Tree<stl::MapTraits<int, FItem_4d83f0, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4d83f0, TContainerAllocator>;
struct FItem_4dee30 { int Words[4]; };
template class stl::Tree<stl::MapTraits<int, FItem_4dee30, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4dee30, TContainerAllocator>;
struct FItem_4eceb0 { int Words[1]; };
template class stl::Tree<stl::MapTraits<int, FItem_4eceb0, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4eceb0, TContainerAllocator>;
struct FItem_4ee800 { int Words[1]; };
template class stl::Tree<stl::MapTraits<int, FItem_4ee800, stl::Less<int>, false>, TContainerAllocator>;
template class stl::Map<int, FItem_4ee800, TContainerAllocator>;
