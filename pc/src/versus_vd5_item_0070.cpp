// Work item 0070: Versus RVA 0xa8380.
// InternalConstructor for an unidentified class (DECLARE_CLASS:
//     static void InternalConstructor(void* X) { new((EInternal*)X) TClass; }).
// The class's default constructor is inlined: it calls the base constructor
// at RVA 0x3eb10 (LTCG, this on the stack) and installs the vtable at
// 0x10c08e00. Class names are not recovered; neutral names are used.

typedef unsigned int size_t;

enum EInternal { EC_Internal };

inline void* operator new(size_t Size, EInternal* Mem) { return (void*)Mem; }
inline void operator delete(void* Object, EInternal* Mem) {}

// Base class whose constructor lives at RVA 0x3eb10 (unidentified).
class UnnamedBase_3eb10
{
public:
    __declspec(noinline) UnnamedBase_3eb10();
    virtual ~UnnamedBase_3eb10();
    int Fields[8];
};

// Derived class with vtable 0x10c08e00 (unidentified).
class UnnamedClass_a8380 : public UnnamedBase_3eb10
{
public:
    virtual ~UnnamedClass_a8380();
};

void InternalConstructor_a8380(void* X)
{
    new((EInternal*)X) UnnamedClass_a8380;
}

// Scaffolding for the link, not part of the unit: the base constructor lives
// in another LTCG unit; a minimal body gives it retail's this-on-the-stack
// convention.
int Touch(void*, int);
struct Member_Stand
{
    Member_Stand();
    ~Member_Stand();
    int Value;
};
UnnamedBase_3eb10::UnnamedBase_3eb10()
{
    Member_Stand A, B, C;
    for (int i = 0; i < 8; i++) Fields[i] = Touch(this, i);
}
void Driver_a8380(void* X) { InternalConstructor_a8380(X); }
