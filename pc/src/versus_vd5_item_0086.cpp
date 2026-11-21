// Versus RVA 0xab7c0: UPolys::UPolys() (vtable 0x10c07700).
// UPolys is a UObject (0x28 bytes) holding TTransArray<FPoly> Element at 0x28:
// the TArray (Data, ArrayNum, ArrayMax) and the transaction Owner at 0x34,
// which UPolys sets to itself. Its deleting destructor (0xab800) and member
// destructor (0xab830) follow it in retail. LTCG gives it the this-on-the-stack
// convention, as its InternalConstructor calls it.
typedef int INT;
typedef unsigned int size_t;

enum EInternal { EC_Internal };
inline void *operator new(size_t Size, EInternal *Mem) { return (void *)Mem; }
inline void operator delete(void *Object, EInternal *Mem) {}

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray(INT InNum, INT ElementSize) : ArrayNum(InNum), ArrayMax(InNum)
    {
        Data = 0;
        if (ArrayMax)
            Realloc(ElementSize);
    }
    ~FArray();
    void Realloc(INT ElementSize);
};

template <class T> class TArray : public FArray
{
public:
    TArray(INT InNum = 0) : FArray(InNum, sizeof(T)) {}
};

class UObject
{
public:
    UObject() {}
    virtual ~UObject();
    INT Reserved[9];
};

template <class T> class TTransArray : public TArray<T>
{
public:
    TTransArray(UObject *InOwner, INT InNum = 0) : TArray<T>(InNum), Owner(InOwner) {}
    UObject *Owner;
};

class FPoly { public: INT Pad[0x5c]; };

class UPolys : public UObject
{
public:
    TTransArray<FPoly> Element;
    __declspec(noinline) UPolys();
    virtual ~UPolys();
    static void InternalConstructor(void *X) { new((EInternal *)X) UPolys; }
};

UPolys::UPolys()
:   Element(this)
{
}

// Scaffolding for the link, not part of the unit.
void Driver_ab7c0(void *X) { UPolys::InternalConstructor(X); }
